

#include "main.h"
#include "stm32f4xx_hal.h"
#include "ssd1353.h"
#include "cmsis_os.h"





extern SPI_HandleTypeDef hspi4;

//HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)


#define ssd1353_spi_write(pData, Size)  HAL_SPI_Transmit(&hspi4, pData, Size, 100)
              

#define SSD1353_DC_CMD()                        HAL_GPIO_WritePin(SSD1353_DC_GPIO_Port, SSD1353_DC_Pin, GPIO_PIN_RESET)              
#define SSD1353_DC_DATA()                       HAL_GPIO_WritePin(SSD1353_DC_GPIO_Port, SSD1353_DC_Pin, GPIO_PIN_SET)

#define SSD1353_CS_EN()                         HAL_GPIO_WritePin(SSD1353_CS_GPIO_Port, SSD1353_CS_Pin, GPIO_PIN_RESET)              
#define SSD1353_CS_DIS()                        HAL_GPIO_WritePin(SSD1353_CS_GPIO_Port, SSD1353_CS_Pin, GPIO_PIN_SET)

#define SSD1353_RES_L()                         HAL_GPIO_WritePin(SSD1353_RES_GPIO_Port, SSD1353_RES_Pin, GPIO_PIN_RESET)              
#define SSD1353_RES_H()                         HAL_GPIO_WritePin(SSD1353_RES_GPIO_Port, SSD1353_RES_Pin, GPIO_PIN_SET)


#define SSD1353_DELAY_MS(N)                      osDelay(N)


uint8_t ssd1353_write_cmd(uint8_t cmd)
{
  uint8_t buff[8];
  
  SSD1353_DC_CMD();
  buff[0] = cmd;
  ssd1353_spi_write(buff, 1);
    
    
  return 0;
}

uint8_t ssd1353_write_data(uint8_t data)
{
  uint8_t buff[8];
  
  SSD1353_DC_DATA();
  buff[0] = data;
  ssd1353_spi_write(buff, 1);
  
  
  return 0;
}






//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Partial or Full Screen)
//
//    a: Column Address of Start
//    b: Column Address of End (Total Columns Devided by 4)
//    c: Row Address of Start
//    d: Row Address of End
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_Block(uint16_t Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
  unsigned char i,j;
	
  
  SSD1353_CS_EN();
  ssd1353_write_cmd(SSD1353_CMD_SET_ROW_ADDR);
  ssd1353_write_data(c);
  ssd1353_write_data(d);
  
  ssd1353_write_cmd(SSD1353_CMD_SET_COLUMU_ADDR);
  ssd1353_write_data(a);
  ssd1353_write_data(b);
  
  
  ssd1353_write_cmd(SSD1353_CMD_WRITE_RAM);


  for(i=0;i<(d-c+1);i++)
  {
    for(j=0;j<(b-a+1);j++)
    {
      ssd1353_write_data(Data);
      ssd1353_write_data(Data>>8);
    }
  }
  SSD1353_CS_DIS();
}



void ssd1353_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color_c, uint8_t color_b, uint8_t color_a)
{
  SSD1353_CS_EN();
  ssd1353_write_cmd(0x21);
  ssd1353_write_data(x1);
  ssd1353_write_data(y1);
  ssd1353_write_data(x2);
  ssd1353_write_data(y2);
  ssd1353_write_data(color_c);
  ssd1353_write_data(color_b);
  ssd1353_write_data(color_b);
  SSD1353_CS_DIS();
}

void ssd1353_drawing_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  SSD1353_CS_EN();
  ssd1353_write_cmd(0x22);
  ssd1353_write_data(x1);
  ssd1353_write_data(y1);
  ssd1353_write_data(x2);
  ssd1353_write_data(y2);
  ssd1353_write_data(0);
  ssd1353_write_data(0x3f);
  ssd1353_write_data(0);
  ssd1353_write_data(0);
  ssd1353_write_data(0x3f);
  ssd1353_write_data(0);
  SSD1353_CS_DIS();
}


void ssd1353_clear_window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  SSD1353_CS_EN();
  ssd1353_write_cmd(0x25);
  ssd1353_write_data(x1);
  ssd1353_write_data(y1);
  ssd1353_write_data(x2);
  ssd1353_write_data(y2);
  SSD1353_CS_DIS();
}




void ssd1353_test(void)
{
  SSD1353_DELAY_MS(500);
  
  
  Fill_Block(0xffff, 50,100,50,100);
  SSD1353_DELAY_MS(500);
  Fill_Block(0x07ff, 50,100,50,100);
  SSD1353_DELAY_MS(500);
  
  SSD1353_DELAY_MS(500);
  Fill_Block(0xff, 0,159,0,127);
  SSD1353_DELAY_MS(500);
  
  SSD1353_DELAY_MS(500);
  Fill_Block(0x00, 0,159,0,127);
  SSD1353_DELAY_MS(500);
  
  ssd1353_drawing_rectangle(0,0,159,127);
  
  
  
  
  
//  ssd1353_draw_line(0,0,159,127,0x3f,0x00,0x00);
//  SSD1353_DELAY_MS(500);
//  
//    SSD1353_DELAY_MS(500);
//  Fill_Block(0xFF, 0,160,0,128);
  SSD1353_DELAY_MS(500);
  ssd1353_draw_line(0,0,60,120,0x3f,0x00,0x00);
  SSD1353_DELAY_MS(500);
  
  
  Fill_Block(0xFF, 0,159,0,127);
  SSD1353_DELAY_MS(200);
  
  Fill_Block(0xff, 50,100,50,100);
  SSD1353_DELAY_MS(200);
  ssd1353_draw_line(0,0,159,127,0x3f,0x00,0x00);
  SSD1353_DELAY_MS(200);
  ssd1353_clear_window(0,0,159,127);
  SSD1353_DELAY_MS(200);
  
}


void ssd1353_init(void)
{
  SSD1353_DELAY_MS(200);
  SSD1353_RES_L();
  SSD1353_DELAY_MS(200);
  SSD1353_RES_H();

  SSD1353_CS_EN();
  
  ssd1353_write_cmd(SSD1353_CMD_LOCK);
  ssd1353_write_data(SSD1352_DATA_LOCK_DIS);
  
  ssd1353_write_cmd(SSD1353_CMD_DISPLAY_OFF);

  ssd1353_write_cmd(SSD1353_CMD_SET_ROW_ADDR);
  ssd1353_write_data(0);
  ssd1353_write_data(127);
  
  ssd1353_write_cmd(SSD1353_CMD_SET_COLUMU_ADDR);
  ssd1353_write_data(0);
  ssd1353_write_data(159);
  
  ssd1353_write_cmd(SSD1353_CMD_SET_DISPLAY_CLOCK);
  ssd1353_write_data(0xC0);
  ssd1353_write_cmd(0xA0);
  ssd1353_write_data(0X60);
  
  ssd1353_write_cmd(SSD1353_CMD_NORMAL_DISPLAY_ON);
  SSD1353_CS_DIS();
  
  
  
  
  
  
  
  
  
  
//  ssd1353_write_cmd(SSD1353_CMD_SET_SECOND_PRE_CHARGE_PERIOD);
//  ssd1353_write_data(0x03);
  
  
  
  
//  ssd1353_write_cmd(SSD1353_CMD_MASTER_CURRENT);
//  ssd1353_write_data(0x0F);
  

  
//  ssd1353_write_cmd(SSD1353_CMD_PHASE_PERIOD);
//  ssd1353_write_data(0xE2);
//  
//  ssd1353_write_cmd(SSD1353_CMD_SET_PRE_CHARGE_VOLTAGE);
//  ssd1353_write_data(0x1F);
  

  
  
//  ssd1353_write_cmd(SSD1353_CMD_SET_VCOMH);
//  ssd1353_write_data(0x07);
  
  
  //ssd1353_write_cmd(SSD1353_CMD_SET_DISPLAY_MODE_NORMAL);
  

  
//  ssd1353_write_cmd(SSD1353_CMD_SET_MULTIPLES_RATIO);
//  ssd1353_write_data(0x3F);

//  ssd1353_write_cmd(SSD1353_CMD_SET_DISPLAY_OFFSET);
//  ssd1353_write_data(0);
//  
//  ssd1353_write_cmd(SSD1353_CMD_SET_START_LINE);
//  ssd1353_write_data(0);


//      ssd1353_write_cmd(0x87);
//  ssd1353_write_data(0X00);
  
  
//  
//  SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(SSD1353_CMD_NORMAL_DISPLAY_ON);
//  SSD1353_DELAY_MS(200);
  
  //Fill_Block(0xf0, 0,0,128,128);


  //ssd1353_write_cmd(SSD1353_CMD_ENABLE_LINEAR_GRAY_SCALE_TABLE);
//  
//  ssd1353_write_cmd(0x25);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  ssd1353_write_data(159);
//  ssd1353_write_data(130);
//  
//  SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(0x21);
//  ssd1353_write_data(0);
//  ssd1353_write_data(10);
//  ssd1353_write_data(0);
//  ssd1353_write_data(100);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  
//SSD1353_DELAY_MS(200);
//  
//    ssd1353_write_cmd(0x25);
//  ssd1353_write_data(0);
//  ssd1353_write_data(2);
//  ssd1353_write_data(159);
//  ssd1353_write_data(130);
//  
//  SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(0x21);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  ssd1353_write_data(1);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  
//    SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(0x21);
//  ssd1353_write_data(20);
//  ssd1353_write_data(20);
//  ssd1353_write_data(120);
//  ssd1353_write_data(120);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  
//    SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(0x21);
//  ssd1353_write_data(40);
//  ssd1353_write_data(40);
//  ssd1353_write_data(120);
//  ssd1353_write_data(120);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  
//    SSD1353_DELAY_MS(200);
//  ssd1353_write_cmd(0x21);
//  ssd1353_write_data(50);
//  ssd1353_write_data(50);
//  ssd1353_write_data(100);
//  ssd1353_write_data(100);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  
//  
//  
//  SSD1353_DELAY_MS(500);
//  ssd1353_write_cmd(0x22);
//  ssd1353_write_data(50);
//  ssd1353_write_data(50);
//  ssd1353_write_data(100);
//  ssd1353_write_data(100);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  
//  SSD1353_DELAY_MS(500);
//  ssd1353_write_cmd(0x22);
//  ssd1353_write_data(40);
//  ssd1353_write_data(40);
//  ssd1353_write_data(110);
//  ssd1353_write_data(110);
//  ssd1353_write_data(0);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  
//  SSD1353_DELAY_MS(500);
//  ssd1353_write_cmd(0x22);
//  ssd1353_write_data(30);
//  ssd1353_write_data(30);
//  ssd1353_write_data(120);
//  ssd1353_write_data(120);
//  ssd1353_write_data(63);
//  ssd1353_write_data(0);
//  ssd1353_write_data(0);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
//  ssd1353_write_data(63);
////  
////  
////  
//  SSD1353_DELAY_MS(500);
//  
//  
//  Fill_Block(0xff, 50,100,50,100);
//  SSD1353_DELAY_MS(500);
//  
//  SSD1353_DELAY_MS(500);
//  Fill_Block(0xff, 0,159,0,127);
//  SSD1353_DELAY_MS(500);
//  
//  SSD1353_DELAY_MS(500);
//  Fill_Block(0x00, 0,159,0,127);
//  SSD1353_DELAY_MS(500);
//  
//  ssd1353_drawing_rectangle(0,0,159,127);
//  
//  
//  
//  
//  
////  ssd1353_draw_line(0,0,159,127,0x3f,0x00,0x00);
////  SSD1353_DELAY_MS(500);
////  
////    SSD1353_DELAY_MS(500);
////  Fill_Block(0xFF, 0,160,0,128);
//  SSD1353_DELAY_MS(500);
//  ssd1353_draw_line(0,0,2,1,0x3f,0x00,0x00);
//  SSD1353_DELAY_MS(500);
//  
//  ssd1353_write_cmd(SSD1353_CMD_SET_START_LINE);
//  ssd1353_write_data(20);
//  
//  ssd1353_write_cmd(SSD1353_CMD_WRITE_RAM);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////  ssd1353_write_data(0x00);
////    ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
//  ssd1353_write_data(0xff);
  
  
}


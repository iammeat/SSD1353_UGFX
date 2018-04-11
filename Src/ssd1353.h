
#ifndef _SSD1353_H
#define _SSD1353_H



#define         COMMAND_LOCK_INIT1      0x15         /* Set Column Address */
#define         COMMAND_LOCK_INIT2      0xB1         // "Command A2,B1,B3,BB,BE accessible if in unlock state"
#define         CMD_DISPLAY_SLEEP       0xAE                  // Set display to sleep mode
#define         CMD_DISPLAY_WAKE        0xAF // Wake up display from sleep mode
#define         CMD_CLOCK_DIVIDER       0xB3 // Set clock divider and display frequency
#define         CMD_REMAP                       0xA0 // Remap various display settings, like hardware mapping and most importantly color mode
#define         CMD_START_LINE          0xA1 // Set display start line, needs to be set to 96 for 128x96 displays
#define         CMD_DISPLAY_OFFSET              0xA2 // Set display offset (hardware dependent, needs to be set to 0)
#define         CMD_FUNCTION_SELECTION  0xAB // Used to activate/deactivate internal voltage regulator
#define         CMD_NORMAL_MODE         0xA6 // Normal display mode (display contents of video RAM)
#define         INTERNAL_VREG           0x01 // internal voltage regulator, other value is never used
#define         CMD_COLUMN_ADDRESS      0x15 // Set start and end column of active video RAM area
#define         CMD_ROW_ADDRESS         0x75 // Set start and end row of active video RAM area



			

#define			SSD1353_CMD_SET_COLUMU_ADDR		0x15
#define			SSD1353_CMD_SET_ROW_ADDR		0x75

#define                 SSD1353_CMD_WRITE_RAM                   0x5C           // Start writing to the video ram. After this, color data can be sent.
#define                 SSD1353_CMD_READ_RAM                    0x5D           // Start writing to the video ram. After this, color data can be sent.

#define                 SSD1353_CMD_MASTER_CURRENT              0x87            

#define			SSD1353_CMD_SET_RE_MAP			0xA0
#define			SSD1353_CMD_SET_START_LINE		0xA1
#define			SSD1353_CMD_SET_DISPLAY_OFFSET	        0xA2

#define                 SSD1353_CMD_SET_DISPLAY_MODE_NORMAL             0xA4
#define                 SSD1353_CMD_SET_DISPLAY_MODE_ENTIRE_ON          0xA5
#define                 SSD1353_CMD_SET_DISPLAY_MODE_ENTIRE_OFF         0xA6
#define                 SSD1353_CMD_SET_DISPLAY_MODE_INVERSE            0xA7

#define			SSD1353_CMD_SET_MULTIPLES_RATIO	                0xA8

#define			SSD1353_CMD_DIM_SETING			        0xAB
		


#define         SSD1353_CMD_DIM_DISPLAY_ON                              0xAC
#define         SSD1353_CMD_NORMAL_DISPLAY_ON                           0xAF
#define         SSD1353_CMD_DISPLAY_OFF                                 0xAE    


#define         SSD1353_CMD_PHASE_PERIOD                                0xB1

#define         SSD1353_CMD_SET_DISPLAY_CLOCK                           0xB3	
#define         SSD1353_CMD_SET_SECOND_PRE_CHARGE_PERIOD                0xB4

#define         SSD1353_CMD_ENABLE_LINEAR_GRAY_SCALE_TABLE              0xB9

#define         SSD1353_CMD_SET_PRE_CHARGE_VOLTAGE                      0xBB

#define         SSD1353_CMD_SET_VCOMH                                   0xBE            

#define         SSD1353_CMD_LOCK                0xFD            /* Set Command Lock */
#define         SSD1352_DATA_LOCK_EN            0x16
#define         SSD1352_DATA_LOCK_DIS           0x12            

#define         CMD_NOOP 0xAD                   // Sometimes used as a last command - doesn't do anything.


void ssd1353_test(void);


#endif  /* _SSD1353_H */


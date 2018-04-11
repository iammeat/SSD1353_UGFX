# SSD1353_UGFX
stm32驱动ssd1353 oled 









移植 ugfx

1 在工程下单独建立一个ugfx文件
2 拷贝配置头文件gfxconf.h和gfx.h
3 拷贝源码文件/src
4 将源码添加到工程下，删除不需要的
5 添加驱动芯片的驱动文件到ugfx下。驱动代码在驱动芯片文件下/drivers/gdisp/SSD1306,如下：
    board_SSD1306_template.h （这个需要修改为board_SSD1306.h）
    gdisp_lld_config.h
    gdisp_lld_SSD1306.c
    SSD1306.h
6 增加自己的板级文件
    board_SSD1306.c
7 实现相关缺少函数，见《移植ugfx》文件
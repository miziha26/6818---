#include "lcd.h"

char futing[2][32/8*33] = {
/*--  文字:  分  --*/
/*--  华文仿宋22;  此字体下对应的点阵为：宽x高=29x33   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=32x33  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,
0x00,0x03,0x80,0x00,0x00,0x31,0x80,0x00,0x00,0x30,0xC0,0x00,0x00,0x38,0xE0,0x00,
0x00,0x70,0x70,0x00,0x00,0x70,0x30,0x00,0x00,0xE0,0x38,0x00,0x01,0xC0,0x1C,0x00,
0x01,0xC0,0x1C,0x00,0x03,0x80,0x1E,0x00,0x07,0x00,0x7F,0x00,0x0E,0x7F,0xFF,0xF0,
0x1D,0xFE,0x33,0xF0,0x38,0x9C,0x30,0x00,0x70,0x18,0x30,0x00,0x40,0x38,0x70,0x00,
0x00,0x38,0x70,0x00,0x00,0x70,0x70,0x00,0x00,0x60,0x60,0x00,0x00,0xE0,0xE0,0x00,
0x01,0xDC,0xE0,0x00,0x03,0x8E,0xE0,0x00,0x07,0x07,0xC0,0x00,0x0E,0x03,0xC0,0x00,
0x38,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,

/*--  文字:  数  --*/
/*--  华文仿宋22;  此字体下对应的点阵为：宽x高=29x33   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=32x33  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x00,
0x00,0x70,0x38,0x00,0x00,0x3A,0x38,0x00,0x07,0x37,0x38,0x00,0x03,0xB7,0x30,0x00,
0x01,0xF6,0x30,0x00,0x01,0xF6,0x70,0x00,0x00,0x3F,0x60,0x00,0x03,0xFF,0xFF,0xC0,
0x1F,0xFE,0xFF,0x80,0x00,0xFC,0xC7,0x00,0x01,0xFE,0xCE,0x00,0x03,0xB7,0xEE,0x00,
0x07,0x73,0xEE,0x00,0x0E,0x77,0xEC,0x00,0x1C,0xEE,0x7C,0x00,0x3F,0xFE,0x3C,0x00,
0x1F,0xFC,0x38,0x00,0x01,0xDC,0x38,0x00,0x01,0x98,0x3C,0x00,0x03,0xF8,0x6C,0x00,
0x00,0x7E,0xEE,0x00,0x00,0xEF,0xC7,0x00,0x01,0xC3,0x87,0x80,0x07,0x07,0x07,0xF0,
0x1E,0x0E,0x03,0x80,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
};

char time1[2][32/8*33] =
{
    /*--  文字:  时  --*/
/*--  华文仿宋22;  此字体下对应的点阵为：宽x高=29x33   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=32x33  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,
0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x06,0x1C,0x0E,0x00,
0x07,0xFC,0x0E,0x00,0x07,0xD8,0x0E,0x00,0x07,0x18,0x0E,0x00,0x07,0x18,0x0E,0x00,
0x07,0x18,0x0F,0xE0,0x07,0x19,0xFF,0xE0,0x07,0xFF,0xFE,0x00,0x07,0xFB,0x0E,0x00,
0x07,0x19,0x8E,0x00,0x07,0x19,0xCE,0x00,0x07,0x19,0xEE,0x00,0x07,0x18,0xCE,0x00,
0x07,0x18,0x0E,0x00,0x07,0xF8,0x0E,0x00,0x07,0xF8,0x0E,0x00,0x07,0x18,0x0E,0x00,
0x07,0x18,0x0E,0x00,0x03,0x01,0xCC,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x3C,0x00,
0x00,0x00,0x1C,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,

/*--  文字:  间  --*/
/*--  华文仿宋22;  此字体下对应的点阵为：宽x高=29x33   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=32x33  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,
0x03,0x80,0x00,0x00,0x01,0xC0,0x07,0x00,0x01,0xEF,0xFF,0x80,0x0E,0xDF,0xFB,0x00,
0x07,0x00,0x03,0x00,0x07,0x00,0x03,0x00,0x06,0x60,0x63,0x00,0x06,0x3F,0xF3,0x00,
0x06,0x3F,0xE3,0x00,0x06,0x30,0xE3,0x00,0x06,0x30,0xE3,0x00,0x06,0x3F,0xE3,0x00,
0x06,0x3F,0xE3,0x00,0x06,0x30,0xE3,0x00,0x06,0x30,0xE3,0x00,0x06,0x3F,0xE3,0x00,
0x06,0x3F,0xE3,0x00,0x06,0x30,0x03,0x00,0x06,0x30,0x03,0x00,0x06,0x00,0x03,0x00,
0x06,0x00,0x33,0x00,0x06,0x00,0x1F,0x00,0x0E,0x00,0x0F,0x00,0x06,0x00,0x0F,0x00,
0x06,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,
};


char maohao[1][32/8*33] = 
{
    /*--  文字:  ：  --*/
/*--  华文仿宋22;  此字体下对应的点阵为：宽x高=29x33   --*/
/*--  宽度不是8的倍数，现调整为：宽度x高度=32x33  --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,
0x07,0xC0,0x00,0x00,0x07,0xC0,0x00,0x00,0x07,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,
0x07,0xC0,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,


};

char fen[1][96/8*99]=
{
	/*--  文字:  分  --*/
/*--  华文琥珀72;  此字体下对应的点阵为：宽x高=96x99   --*/
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x0E,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xC0,0x00,0x7F,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0xFF,0xF0,0x00,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0xFF,0xF8,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFE,0x07,0xFF,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x0F,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFF,0xFF,0x0F,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x3F,
0xFF,0xFF,0x9F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xDF,0xFF,
0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,
0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x03,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xBF,0xFF,0xFF,0xFF,0xC0,0x00,
0x00,0x00,0x1F,0xFF,0xFF,0xFF,0x9F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x3F,0xFF,
0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x0F,0xFF,
0xFF,0xFF,0xF8,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0xFF,0xFF,0xFE,0x00,
0x00,0x01,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x07,0xFF,0xFF,
0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x0F,0xFF,0xFF,0xFF,0xF8,0x00,0xFF,
0xFF,0xFF,0xFF,0xE0,0x00,0x1F,0xFF,0xFF,0xFF,0xF0,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,
0x00,0x3F,0xFF,0xFF,0xFF,0xE0,0x00,0x7F,0xFF,0xFF,0xFF,0xF8,0x00,0x7F,0xFF,0xFF,
0xFF,0xC0,0x00,0x3F,0xFF,0xFF,0xFF,0xFC,0x01,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x1F,
0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x0F,0xFF,0xFF,0xFF,0xFE,
0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFF,
0xFE,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0x07,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x01,
0xFF,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
0x0F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0x0F,0xFF,0xF8,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x0F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xFF,0x0F,0xFF,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x3F,0xFF,
0x0F,0xFF,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x1F,0xFE,0x07,0xFF,0x1F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0xFC,0x07,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x8F,0xFC,0x03,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xF8,
0x03,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xF0,0x01,0xFE,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xE0,0x00,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xE3,0x80,0x00,0x7E,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
0x00,0x1C,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x0F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xE0,0x03,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xF0,0x00,
0x00,0x00,0x00,0x0F,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x0F,
0xFF,0xFF,0xE0,0x01,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xC0,0x01,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0xF0,0x00,
0x00,0x00,0x00,0x1F,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x3F,
0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xC0,0x03,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xF0,0x00,
0x00,0x00,0x00,0x7F,0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0xFF,
0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0x00,0x03,
0xFF,0xFF,0xF0,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xE0,0x00,
0x00,0x00,0x07,0xFF,0xFF,0xFF,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x0F,0xFF,
0xFF,0xFE,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFE,0x00,0x03,
0xFF,0xFF,0xE0,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xE0,0x00,
0x00,0x00,0xFF,0xFF,0xFF,0xFC,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x03,0xFF,0xFF,
0xFF,0xF8,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xF8,0x07,0xFF,
0xFF,0xFF,0xE0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xF0,0x3F,0xFF,0xFF,0xFF,0xE0,0x00,
0x00,0x3F,0xFF,0xFF,0xFF,0xF0,0x7F,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x7F,0xFF,0xFF,
0xFF,0xE0,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xC1,0xFF,0xFF,
0xFF,0xFF,0xE0,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x81,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,
0x00,0xFF,0xFF,0xFF,0xFF,0x81,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0xFF,
0xFF,0x01,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xFF,
0xFF,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,
0x00,0xFF,0xFF,0xFF,0xF8,0x03,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0xFF,0xFF,0xFF,
0xF0,0x03,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x7F,0xFF,0xFF,0xE0,0x01,0xFF,0xFF,
0xFF,0xFF,0x80,0x00,0x00,0x7F,0xFF,0xFF,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x3F,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x3F,0xFF,0xFC,
0x00,0x01,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x1F,0xFF,0xF0,0x00,0x00,0xFF,0xFF,
0xFF,0xFC,0x00,0x00,0x00,0x0F,0xFF,0xE0,0x00,0x00,0x7F,0xFF,0xFF,0xF0,0x00,0x00,
0x00,0x03,0xFF,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0xF8,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,


};

/*
    lcd_display_word:在LCD屏幕上显示一个字符
    @x:字符开始显示的起始x坐标
    @y:字符开始显示的起始y坐标
    @w:显示字符的宽
    @h:显示字符的高
    @word_array:保存取模信息数组名
    @color:字符显示的颜色
    @plcd:帧缓冲区域的首地址
    返回值：
        成功 0
        失败 -1
        int
*/
int lcd_display_word(int x, int y, int w, int h, char *word_array, int color, unsigned int *plcd)
{
    //在LCD屏幕上起始位置为（x,y）显示一个宽为w，高为h，颜色为color的字符
    //遍历当前word_array，判断当前到底哪个像素点应该要显示颜色，哪些不进行显示
    //计算该像素点显示到LCD屏幕的哪个具体位置
    for(int i=0; i<w/8*h; i++) //遍历当前word_array,这层遍历遍历到数组的每一个元素（字节为单位）
    {
        //判断哪些像素点要显示颜色（判断一个字节中的一位是0还是1）
        //遍历当前元素里面的每一位（一个字节从高位往低位依次遍历每一位，判断该位是0还是1）
        for(int j=7; j>=0; j--) //从高位来遍历到低位进行判断
        {
            if(word_array[i] >> j & 1) //非0为真，表示当前这位为1，要对其进行显示颜色
            {
                //计算该像素点在屏幕上显示的位置
                int x0 = x + i%(w/8)*8 + (7-j);
                int y0 = y + i/(w/8);
                display_point(plcd, x0, y0, color);
            }
        }
    }
}
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include "lcd.h"
#include "bmp.h"
#include "touch.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "font.h"
#include <pthread.h>



#define lcd_path "/dev/fb0"
#define bpath13 "./bmp/13.bmp"
#define bpath14 "./bmp/14.bmp"



/*
    lcd_display_rectangle:在LCD屏幕上显示矩形
    @x0:开始显示矩形的起始x坐标
    @y0:开始显示矩形的起始y坐标
    @w:矩形的宽
    @h:矩形的高
    @plcd:帧缓冲区域的首地址
    @color:矩形需要显示的颜色
    返回值：
        int 
        成功 0
        失败 -1
*/
int lcd_display_rectangle(int x0, int y0, int w, int h, unsigned int *plcd, unsigned int color)
{
    if(plcd == NULL || x0<0 || x0>=800 || y0<0 || y0>=480 || (x0+w)>800 || (y0+h)>480)
    {
        printf("%s:%d", __FUNCTION__, __LINE__);
        return -1;
    }

    for(int i=y0; i<y0+h; i++)
    {
        for(int j=x0; j<x0+w; j++)
        {
            display_point(plcd, j, i, color);
        }
    }

    return 0;
}

/*
    display_point:给屏幕上坐标为(x0,y0)像素点显示一个color颜色
    @plcd:帧缓冲区域的首地址
    @x0:x坐标
    @y0:y坐标
    @color:显示的颜色
    返回值：
        void
*/
void display_point(unsigned int *plcd, int x0, int y0, int color)
{
    if(plcd == NULL)
    {
        return ;
    }

    *(plcd + 800*y0 + x0) = color;
}

void lcd_draw_num(int num)//显示分数
{
    int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return  ;
	}
    unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
    //分离出num的每一个数字位
    int a,b,c,d;
    a = num/1000;
    b = (num%1000)/100;
    c = (num%100)/10;
    d = num%10;

    if(num>=1000)
    {
        lcd_display_word(245, 0, 16, 33, word2[a], 0x00FF7F24, plcd);
        lcd_display_word(261, 0, 16, 33, word2[b], 0x00FF7F24, plcd);
        lcd_display_word(277, 0, 16, 33, word2[c], 0x00FF7F24, plcd);
        lcd_display_word(293, 0, 16, 33, word2[d], 0x00FF7F24, plcd);
    }
    else if(num >=100)
    {   
        lcd_display_word(245, 0, 16, 33, word2[b], 0x00FF7F24, plcd);
        lcd_display_word(261, 0, 16, 33, word2[c], 0x00FF7F24, plcd);
        lcd_display_word(277, 0, 16, 33, word2[d], 0x00FF7F24, plcd);
    }
    else if(num >= 10)
    {   
        lcd_display_word(245, 0, 16, 33, word2[c], 0x00FF7F24, plcd);
        lcd_display_word(261, 0, 16, 33, word2[d], 0x00FF7F24, plcd);
    }
    else 
    {
        lcd_display_word(245, 0, 16, 33, word2[d], 0x00FF7F24, plcd);
    }

}

void lcd_draw_num1(int num)//显示倒计时数字
{
    int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return  ;
	}
    unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
    //分离出num的每一个数字位
    int a,b;

    a = (num%100)/10;
    b = num%10;

    if(num >= 10)
    {   
        lcd_display_word(635, 0, 16, 33, word2[a], 0x00FF7F24, plcd);
        lcd_display_word(651, 0, 16, 33, word2[b], 0x00FF7F24, plcd);
    }
    else 
    {
        lcd_display_word(635, 0, 16, 33, word2[b], 0x00FF7F24, plcd);
    }

}

void lcd_draw_num3(int num)//结尾显示分数
{
    int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return  ;
	}
    unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
    //分离出num的每一个数字位
    int a,b,c;

    a = (num%1000)/100;
    b = (num%100)/10;
    c = num%10;

    if(num >=100)
    {   
        lcd_display_word(300, 200, 56, 99, word3[a], 0x00FF7F24, plcd);
        lcd_display_word(356, 200, 56, 99, word3[b], 0x00FF7F24, plcd);
        lcd_display_word(412, 200, 56, 99, word3[c], 0x00FF7F24, plcd);
    }
    else if(num >= 10)
    {   
        lcd_display_word(300, 200, 56, 99, word3[b], 0x00FF7F24, plcd);
        lcd_display_word(356, 200, 56, 99, word3[c], 0x00FF7F24, plcd);
    }
    else 
    {
        lcd_display_word(356, 200, 56, 99, word3[c], 0x00FF7F24, plcd);
    }

}


void *daojishi(void *arg)//倒计时
{   
    printf(" ");//pthread_cancle取消线程需要有系统调用（write printf read）
	int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return NULL ;
	}
	//2.操作屏幕文件,写入你想要显示到屏幕上的颜色值
	unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	for(int i=30;i>=0;i--)
	{
		lcd_draw_num1(i);
        sleep(1);
		display_bmp(bpath13,635,0,plcd);
	}
}
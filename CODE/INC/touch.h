#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "lcd.h"
#include "bmp.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "font.h"
#include <pthread.h>


typedef struct touch
{
    int touch_fd; //保存文件描述符
    int x; //保存x坐标
    int y;//保存获取到的y坐标
}Touch;

typedef enum
{
	TouchError,//错误码
	TouchClick,//点击的
	TouchLeft,//左滑
	TouchRight,//右滑
	TouchUp,//上滑
	TouchDown,//下滑
}TouchDirection;

void draw_game(int x,int y);
void* show(void*arg);
void TouchInit(void);//初始化屏幕
void closeTouch(void);//关闭屏幕
TouchDirection GetDir(int *x, int *y);//判断滑动
int get_touch_coordinate(int touch_fd, int *x, int *y);//获取坐标
void* get_xy(void *arg);








#endif
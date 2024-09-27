#include"mp3.h"
#include"touch.h"
#include<stdio.h>
#include"mp4.h"
#include <sys/mman.h>
#include <sys/types.h>
#include"bmp.h"

int touch_fd;
unsigned int *plcd;
int music_i=1;//音乐编号

int main()  
{   
    printf("hello world\n");
    //打开屏幕文件
    int lcd_fd = open("/dev/fb0", O_RDWR);
    if(lcd_fd == -1)
    {
        perror("open lcd fail");
        return -1;
    }            
    //映射屏幕文件
    plcd = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);

    display_bmp("./bmpbinfa/17.bmp",0,0,plcd);//主页面
    display_bmp("./bmpbinfa/12.bmp",50,30,plcd);//mp3播放器
    display_bmp("./bmpbinfa/13.bmp",325,30,plcd);//MP4播放器
    display_bmp("./bmpbinfa/14.bmp",600,30,plcd);//电子相册
    display_bmp("./bmpbinfa/15.bmp",240,270,plcd);//打地鼠
    //display_bmp("./bmpbinfa/16.bmp",410,270,plcd);//2048

    //打开触摸屏文件
    touch_fd = open("/dev/input/event0", O_RDONLY);
    if(-1 == touch_fd)
    {
        perror("open touch fail");
        return -1;
    }   
	int x = -1, y = -1; //屏幕坐标点从（0,0）
    
    while(1)
    {
        get_touch_coordinate(touch_fd, &x, &y);
        printf("x=%d y=%d\n", x, y);
        display_bmp("./bmpbinfa/17.bmp",0,0,plcd);//主页面
        display_bmp("./bmpbinfa/12.bmp",50,30,plcd);//mp3播放器
        display_bmp("./bmpbinfa/13.bmp",325,30,plcd);//MP4播放器
        display_bmp("./bmpbinfa/14.bmp",600,30,plcd);//电子相册
        display_bmp("./bmpbinfa/15.bmp",240,270,plcd);//打地鼠
        //display_bmp("./bmpbinfa/16.bmp",410,270,plcd);//2048
        if(x>=50 && x<=200 && y>=30 && y<=180)//mp3播放
        {       
            run(&music_i);
        }
        else if(x>=325 && x<=475 && y>=30 && y<=180)//mp4播放
        {
            playmp4();
        }
        else if(x>=600 && x<=750 && y>=30 && y<=180)//电子相册
        {
            pic();
        }
        else if(x>=240 && x<=390 && y>=270 && y<=420)//打地鼠
        {
            dishu();
        }
        
    }
    closeTouch();

    return 0;
}



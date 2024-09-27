#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include "lcd.h"
#include "linklist.h"
#include "getpath.h"
#include "bmp.h"
#include "touch.h"
#include "font.h"

#define LCD_PATH "/dev/fb0"
#define TOUCH_PATH "/dev/input/event0"
int pic();
int pic()
{

    //打开屏幕文件
    int lcd_fd = open(LCD_PATH, O_RDWR);
    if(lcd_fd == -1)
    {
        perror("open lcd fail");
        return -1;  
    }
    //映射屏幕文件
    unsigned int *plcd = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd_fd, 0);
    //打开触摸屏文件
    Touch get_th; //创建了一个结构体变量，变量保存触摸屏文件描述符及获得的x，y坐标
    get_th.touch_fd = open(TOUCH_PATH, O_RDONLY);
    if(-1 == get_th.touch_fd)
    {
        perror("open touch fail");
        return -1;
    }
    get_th.x = -1;
    get_th.y = -1;

    //创建一条线程执行分支
    pthread_t tid;
    pthread_create(&tid, NULL, get_xy, &get_th);

    //1.创建双向循环链表
    DulLinklist *head = create_double_circle_linklist_head();

    //2.获取path路径下所有后缀名.bmp的路径
    get_bmp_path("./bmppic/", head);

    Dulnode *p = head->first;
    display_bmp(p->data, 0, 0, plcd); //先让屏幕先显示一张图片
    while(p) //循环显示链表中保存的路径所有的BMP图片
    {
        if(get_th.x>=0 && get_th.x<=100 && get_th.y>=0 && get_th.y<=100)//点击屏幕某个位置，显示上一张
        {
            get_th.x = -1, get_th.y = -1;
            p = p->prev; //指向上一个数据节点
            printf("正在播放上一张\n");
            display_bmp(p->data, 0, 0, plcd);
        }
        else if(get_th.x>=700 && get_th.x<=800 && get_th.y>=0 && get_th.y<=100)//点击屏幕另一个位置，显示下一张
        {
            get_th.x = -1, get_th.y = -1;
            p = p->next;
            printf("正在播放下一张\n");
            display_bmp(p->data, 0, 0, plcd);
        }
        else if(get_th.x>=0 && get_th.x<=100 && get_th.y>=380 && get_th.y<=480) //循环播放
        {
            get_th.x = -1, get_th.y = -1;
            printf("进入循环播放\n");
            while(1)
            {
                p = p->next;
                display_bmp(p->data, 0, 0, plcd);
                sleep(2);
                if(get_th.x>=0 && get_th.x<=100 && get_th.y>=0 && get_th.y<=100)
                {
                    printf("退出循环播放\n");
                    get_th.x = -1, get_th.y = -1;
                    break;
                }
            }
        } 
        else if(get_th.x>=700 && get_th.x<=800 && get_th.y>=380 && get_th.y<=480)   
        {
            printf("退出整个电子相册\n");
            break;
        } 
    }
    
    //4.销毁链表    
    head = delete_linklist(head);

    //关闭屏幕文件
    close(lcd_fd);
    close(get_th.touch_fd);
}
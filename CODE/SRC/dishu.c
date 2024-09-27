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

#define TOUCH_PATH "/dev/input/event0"
#define lcd_path "/dev/fb0"
#define bpath4 "./bmp/4.bmp"
#define bpath8 "./bmp/8.bmp"
#define bpath9 "./bmp/9.bmp"
#define bpath10 "./bmp/10.bmp"
#define bpath11 "./bmp/11.bmp"
#define bpath12 "./bmp/12.bmp"
#define bpath13 "./bmp/13.bmp"
#define bpath14 "./bmp/14.bmp"
#define bpath15 "./bmp/15.bmp"
#define bpathk1 "./bmp/k1.bmp"
#define bpathk2 "./bmp/k2.bmp"
#define bpathk3 "./bmp/k3.bmp"
#define bpathk4 "./bmp/k4.bmp"
#define bpathk5 "./bmp/k5.bmp"
#define bpathk6 "./bmp/k6.bmp"
#define bpathk7 "./bmp/k7.bmp"
#define bpathk8 "./bmp/k8.bmp"
#define bpathk9 "./bmp/k9.bmp"
int dishu(void);

int dishu(void)
{	
	struct tm *localtime(const time_t *timer);
	int sum = 0;//分数
	int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return -1 ;
	}
		
	//2.操作屏幕文件,写入你想要显示到屏幕上的颜色值
	unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	again://点击返回按钮后从这里开始重新执行
	display_bmp1(bpath11,0,0,plcd);//开始界面
	
	int touch_fd = open(TOUCH_PATH, O_RDONLY);
    if(-1 == touch_fd)
    {
        perror("open touch fail");
        return -1;
    }
	int x = -1, y = -1; //屏幕坐标点从（0,0）
    get_touch_coordinate(touch_fd, &x, &y);
    printf("x=%d y=%d\n", x, y);
	
	

	while(1)
	{	
		if(x>=285 && x<=520 && y>=230 && y<=290)//点击开始游戏
		{
			display_bmp(bpath4,0,0,plcd);//游戏主界面
			display_bmp(bpath10,750,0,plcd);//返回键
			lcd_display_word(160, 0, 32, 33, futing[0], 0x00FF7F24, plcd); 
			lcd_display_word(192, 0, 32, 33, futing[1], 0x00FF7F24, plcd); 
			lcd_display_word(224, 0, 32, 33, maohao[0], 0x00FF7F24, plcd); 
			lcd_display_word(550, 0, 32, 33, time1[0], 0x00FF7F24, plcd);
			lcd_display_word(582, 0, 32, 33, time1[1], 0x00FF7F24, plcd);
			lcd_display_word(614, 0, 32, 33, maohao[0], 0x00FF7F24, plcd); 

			lcd_draw_num(sum);//显示分数

			pthread_t tid1;
			pthread_create(&tid1, NULL,daojishi,(void*)sum);//倒计时

			int a;
			pthread_t tid;
			pthread_create(&tid, NULL,show,(void*)a);//显示地鼠图
			
			time_t currentTime = time(NULL);
    		struct tm* localTime = localtime(&currentTime);
			int minute1=localTime->tm_min;
    		int second1=localTime->tm_sec;//获取开始时的时间
			printf("%da\n",second1);

			while(1)
			{	
				time_t currentTime1 = time(NULL);
      			struct tm* localTime1= localtime(&currentTime1);
				int minute2=localTime1->tm_min;
      			int second2=localTime1->tm_sec;//获取游戏运行时间
				printf("%db\n",second2);
				if(minute2-minute1>=1)
				{
					second1=60-second1;
					// minute1++;
					printf("%dab\n",second1);
					if(second1+second2>=30)//超过30秒就结束游戏
					{
						printf("%d,%d",second1,second2);
						display_bmp(bpath14,0,0,plcd);//结束界面
						lcd_draw_num3(sum);//打印分数
						lcd_display_word(480,200,96,99,fen[0],0x00FF7F24,plcd);//单独打印分字
						pthread_cancel(tid);
						pthread_cancel(tid1);
						
							get_touch_coordinate(touch_fd, &x, &y);
							if(x>=270 && x<= 530 && y>=310 && y<= 350)//返回主界面
							{
								sum=0;
								goto again;
							}
							else if(x>=280 && x<= 520 && y>=380 && y<=420)//退出游戏
							{
								display_bmp(bpath15,0,0,plcd);
								return 0;
							}

						

					}
				}
				else if((second2-second1)>=30)//超过30秒就结束游戏
				{		
						printf("%d %dxv",second1,second2);
						pthread_cancel(tid);
						pthread_cancel(tid1);
						display_bmp(bpath14,0,0,plcd);
						lcd_draw_num3(sum);
						printf("zh");
						lcd_display_word(480,200,96,99,fen[0],0x00FF7F24,plcd);
						
							get_touch_coordinate(touch_fd, &x, &y);
							if(x>=270 && x<= 530 && y>=310 && y<= 350)
							{
								pthread_cancel(tid);
								pthread_cancel(tid1);
								sum=0;
								goto again;
							}
							else if(x>=280 && x<= 520 && y>=380 && y<=420)
							{
								display_bmp(bpath15,0,0,plcd);
								return 0;
							}
							
						
				}


				get_touch_coordinate(touch_fd, &x, &y);
            	printf("x=%d y=%d\n", x, y);
				if(x >= 150 && x <= 230 && y >= 145 && y <= 225)//k1
				{
					display_bmp2(bpath9,150,145,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk1,150,145,plcd);
				}
				else if(x >= 360 && x <= 440 && y >= 145 && y <= 225)//k2
				{
					display_bmp2(bpath9,360,145,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk2,360,145,plcd);
				}
				else if(x >= 570 && x <= 650 && y >= 145 && y <= 225)//k3
				{
					display_bmp2(bpath9,570,145,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk3,570,145,plcd);
				}
				else if(x >= 150 && x <= 230 && y >= 245 && y <= 325)//k4
				{
					display_bmp2(bpath9,150,245,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk4,150,245,plcd);
				}
				else if(x >= 360 && x <= 440 && y >= 245 && y <= 325)//k5
				{
					display_bmp2(bpath9,360,245,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk5,360,245,plcd);
				}
				else if(x >= 570 && x <= 650 && y >= 245 && y <= 325)//k6
				{
					display_bmp2(bpath9,570,245,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk6,570,245,plcd);
				}
				else if(x >= 150 && x <= 230 && y >= 345 && y <= 425)//k7
				{
					display_bmp2(bpath9,150,345,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk7,150,345,plcd);
				}
				else if(x >= 360 && x <= 440 && y >= 345 && y <= 425)//k8
				{
					display_bmp2(bpath9,360,345,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk8,360,345,plcd);
				}
				else if(x >= 570 && x <= 650 && y >= 345 && y <= 425)//k9
				{
					display_bmp2(bpath9,570,345,plcd);
					sum+=10;
					display_bmp(bpath12,245,0,plcd);
					lcd_draw_num(sum);
					sleep(1);
					display_bmp(bpathk9,570,345,plcd);
				}
				else if(x >= 750 && x <= 800 && y >= 0 && y<= 30)//返回键
				{
					pthread_cancel(tid);
					pthread_cancel(tid1);
					sum=0;
					goto again;
				}

			}
			display_bmp(bpath14,0,0,plcd);
			lcd_draw_num3(sum);
		}
			
		else if(x>=335 && x<=445 && y>=410 && y<=450)//退出
		{
			display_bmp(bpath15,0,0,plcd);
			return 0;
		}

		get_touch_coordinate(touch_fd, &x, &y);
	}
 }




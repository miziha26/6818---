#include"mp3.h"
#include"touch.h"
#include "bmp.h" 
#include "lcd.h"

int volumeLevel = 50;  // 初始音量为50%
bool ifMuted = false;  // 初始状态不是静音
int isPaused = 0;  // 初始状态不是暂停
int jkl=1;
void run(int *music_i)
{
    display_bmp("./bmpbinfa/20.bmp",0,0,plcd);//主页面
    int x=-1,y=-1;
    TouchInit();
    if(cshmusic(music_i)!=0)
    {
        return ;
    }   

    while(1)
    {
        TouchDirection dir=GetDir(&x,&y);
        if(dir==TouchLeft)//播放上一首
        {
            (*music_i)--;
            if((*music_i)<=0)
            {
                (*music_i)=3;
            }

            system("killall -9 madplay");
        }
        else if(dir==TouchRight)//播放下一首
        {
            (*music_i)++;
            if((*music_i)>=4)
            {
                (*music_i)=1;
            }
            system("killall -9 madplay");
        }
        //dir==TouchClick && x>=0 && x<=700 && y>=0 && y<=480
        //dir==TouchClick && x>=700 && x<=800 && y>=200 && y<=480
        else if(dir==TouchClick && x>=0 && x<=400 && y>=0 && y<=240)//退出
        {
            jkl=0;
            system("killall -9 madplay");
            printf("ko\n");
            break;
        }
        else if(dir==TouchClick && x>=0 && x<=400 && y>=240 && y<=480)//暂停
        {
            printf("123789\n");
            if(isPaused==0)
            {
                // 暂停前先设置 isPaused 状态
                isPaused = 1;
                // 停止播放
                system("killall -STOP madplay");
            }
            else
            {
                // 设置 isPaused 状态
                isPaused = 0;
                // 恢复播放
                system("killall -CONT madplay");
            }
        }
        
    }

}

int cshmusic(int*music_i)
{
    pthread_t pthread;
    if(pthread_create(&pthread,NULL,play,music_i)!=0)
    {
        perror("create error");
        return -1;
    }
    return 0;
}

void *play(void*arg)
{
    pthread_detach(pthread_self());
    int * music_i=(int *)arg;
    char buf[200]={0};
    while(jkl==1)
    {
        sprintf(buf,"madplay -Q ./mp3/%d.mp3",*music_i);
        system("killall -9 madplay");
        system(buf);
        sleep(1);

    }
}
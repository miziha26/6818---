#include "touch.h"
#include "mp4.h"
#include "bmp.h" 
#include "lcd.h"

#define SPEED_INCREMENT 0.5  // 倍速增量
pthread_mutex_t mutex;
bool isMuted = false;  // 初始状态不是静音
float playback_speed = 1.0;  // 初始倍速为1.0
int mp4_i=1;//视频编号
int pp=1;//1播放0暂停

void *progress(void *arg)
{
    pthread_detach(pthread_self());
    int fifo_w=open("./1.fifo",O_RDWR);
    int fifo_r=open("./2.fifo",O_RDWR);
    char buf[1024]={0};
    float percent=0.0;
    while(1)
    {   
        // if(pp==0)
        // {
        //     return 0;
        // }
        PipeClear(fifo_r);
        if(pp==1)
        {   
            write(fifo_w,"get_percent_pos\n",16);
            read(fifo_r,buf,1024);
            sscanf(buf,"ANS_PERCENT_POSITION=%f",&percent);
            printf("反馈的消息是:%f\n",percent);
            int nb=percent/100*800;
            lcd_display_rectangle(0,370,nb,10,(unsigned int *)arg,0x00DB00);
        }
        if(percent==100)
        {
            break;
        }
    }

}


int playmp4(void)   
{   
    display_bmp("./bmpbinfa/5.bmp",0,380,plcd);//白底
    display_bmp("./bmpbinfa/1.bmp",250,400,plcd);//上一曲
    display_bmp("./bmpbinfa/2.bmp",450,400,plcd);//下一曲
    display_bmp("./bmpbinfa/3.bmp",350,400,plcd);//暂停
    display_bmp("./bmpbinfa/4.bmp",725,400,plcd);//返回键
    display_bmp("./bmpbinfa/6.bmp",150,400,plcd);//快退   
    display_bmp("./bmpbinfa/7.bmp",550,400,plcd);//快进
    display_bmp("./bmpbinfa/8.bmp",0,400,plcd);//减速
    display_bmp("./bmpbinfa/9.bmp",75,400,plcd);//加速
    display_bmp("./bmpbinfa/10.bmp",650,400,plcd);//静音
    //创建管道   
    int o = mkfifo("./1.fifo",0664);
    if(-1 == o)//有问题了
    {
        //管道不存在而失败就是真的失败
        if(errno != EEXIST)
        {
            perror("mkfifo error");
            return -1;
        }
        printf("管道以存在，继续操作即可\n");
    }
    int w = mkfifo("./2.fifo",0664);
    if(-1 == w)//有问题了
    {
        //管道不存在而失败就是真的失败
        if(errno != EEXIST)
        {
            perror("mkfifo error");
            return -1;
        }
        printf("管道以存在，继续操作即可\n");
    }
    //开一个子进程去跑mplayer
    pid_t pid = fork();

    int fifo_r = open("./2.fifo",O_RDWR);//这个管道读mplayer反馈的信息
    if(pid == 0)
    {
        //这个 1.fifo是maplayer去读的管道
        //将标准输出重定向到2.fifo
        dup2(fifo_r,1);
        int r = execlp("mplayer","mplayer","-quiet","-slave","-input","file=./1.fifo","-zoom","-x","800","-y","380","./mp4/1.mp4",NULL);
        if(-1 == r)
        {
            perror("exec error");
        }
        return -1;
    }

    if(pid > 0)
    {
        //父进程才会走到这里
        int fifo_w = open("./1.fifo",O_RDWR);
        pthread_mutex_init(&mutex,NULL);//用之前先初始化
        
        pthread_t tid;
        if(pthread_create(&tid, NULL, progress, plcd)!=0)//创建线程去显示进度条 
        {
            perror("thread create error");
        }
        while(1)
        {   
            int x = -1, y = -1; //屏幕坐标点从（0,0）
            get_touch_coordinate(touch_fd, &x, &y);
            printf("x=%d y=%d\n", x, y);
            if(x>=0 && x<=800 && y>=0 && y<=160)//加音量
            {
                printf("加音量\n");
                char com[20] = {0};
                sprintf(com, "volume 100 1\n");
                write(fifo_w, com, strlen(com));
            }
            else if(x>=0 && x<=800 && y>=160 && y<=380)//减音量
            {
                printf("减音量\n");
                char com[20] = {0};
                sprintf(com, "volume 50 1\n");
                write(fifo_w, com, strlen(com));
            }
            else if(x>=350 && x<=450 && y>=400 && y<=480)//暂停
            {   
                if(pp==1)
                pp=0;
                else
                pp=1;
                pthread_mutex_lock(&mutex); //上锁
                write(fifo_w,"pause\n",6);//暂停
                pthread_mutex_unlock(&mutex);//解锁
            }
            else  if(x>=0 && x<=100 && y>=380 && y<=480)//点另外一个地方干这个事情  有反馈的信息
            {
                char buf[1024] = {0};
                PipeClear(fifo_r);//每次有反馈的时候先将读管道里面的垃圾清除以下
                write(fifo_w,"get_time_pos\n",13);//等待maplayer回我信息
                read(fifo_r,buf,1024);   
                printf("反馈的消息是:%s\n",buf);
            }
            else if(x>=700 && x<=800 && y>=400 && y<=480)//退出播放
            {
                system("killall -kill mplayer");
                pthread_cancel(tid);
                kill(pid,9);
                break;
            }
            else if(x>= 450 && x<=550 && y>=400 && y<=480)//播放下一个视频
            {
                mp4_i++;
                if(mp4_i==4)   
                {
                    mp4_i=1;
                }
                char com[20]={0};
                sprintf(com,"loadfile ./mp4/%d.mp4\n",mp4_i);
                write(fifo_w, com, strlen(com));
            }
            else if(x>=250 && x<=350 && y>=400 && y<=480)//播放上一个视频
            {
                mp4_i--;
                if(mp4_i==0)
                {
                    mp4_i=3;
                }
                char com[20]={0};
                sprintf(com,"loadfile ./mp4/%d.mp4\n",mp4_i);
                write(fifo_w, com, strlen(com));
            }
            else if(x>=150 && x<=250 && y>=400 && y<=480)//快退5秒
            {
                char com[20]={0};
                sprintf(com,"seek -5\n");
                write(fifo_w, com, strlen(com));
            }
            else if(x>=550 && x<=650 && y>=400 && y<=480)//快进5秒
            {
                char com[20]={0};
                sprintf(com,"seek +5\n");
                write(fifo_w, com, strlen(com));
            }
            else if(x>=75 && x<=150 && y>=400 && y<=480)//加速
            {
                playback_speed += SPEED_INCREMENT;
                char com[20]={0};
                sprintf(com,"speed_set %f\n", playback_speed);
                write(fifo_w, com, strlen(com));
            }
            else if(x>=0 && x<=75 && y>=400 && y<=480)//减速
            {
                playback_speed -= SPEED_INCREMENT;
                char com[20]={0};    
                sprintf(com,"speed_set %f\n", playback_speed);
                write(fifo_w, com, strlen(com));
            }
            else if(x>=650 && x<=725 && y>=400 && y<=480)//静音
            {
                if (isMuted) {
                    // 取消静音
                    char com[20] = {0};
                    sprintf(com, "volume 100 1\n");  // 将音量设置为最大值
                    write(fifo_w, com, strlen(com));
                    isMuted = false;
                } else {
                    // 静音
                    char com[20] = {0};
                    sprintf(com, "mute 1\n");  // 静音
                    write(fifo_w, com, strlen(com));
                    isMuted = true;
                }
            }
        }
    }
    pthread_mutex_destroy(&mutex);//销毁锁
    printf("父进程死了！！！！！！！！！！！！！\n");
    return 0;
}

//清除一个管道里面的消息
void PipeClear(int pipefd)
{
	char buf[1025] = {0};
	//pipefd默认阻塞  当没有数据的时候会卡死
	//你卡不死就可以了啊 我设置你为非阻塞
	unsigned int s;
	//获取属性
	s = fcntl(pipefd,F_GETFL);
	//设置非阻塞属性
	s |= O_NONBLOCK;
	fcntl(pipefd,F_SETFL,s);
	while(1)
	{
		int r = read(pipefd,buf,1024);
		if(-1 == r)
		{
			//perror("read pipefd error");
			break;
		}
		else if(0 == r)
		{
			printf("pipe clear success!!\n");
			break;
		}
		printf("PipeClear = %s\n",buf);
	}
	//清楚完毕之后需要设置回阻塞
	s &= ~O_NONBLOCK;
	fcntl(pipefd,F_SETFL,s);
}



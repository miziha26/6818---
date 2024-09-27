#include"touch.h"

#define bpath8 "./bmp/8.bmp"
#define lcd_path "/dev/fb0"
#define bpathk1 "./bmp/k1.bmp"
#define bpathk2 "./bmp/k2.bmp"
#define bpathk3 "./bmp/k3.bmp"
#define bpathk4 "./bmp/k4.bmp"
#define bpathk5 "./bmp/k5.bmp"
#define bpathk6 "./bmp/k6.bmp"
#define bpathk7 "./bmp/k7.bmp"
#define bpathk8 "./bmp/k8.bmp"
#define bpathk9 "./bmp/k9.bmp"

static int touch_fd = -1;

//初始化屏幕
void TouchInit(void)
{
    touch_fd = open("/dev/input/event0",O_RDWR);
    if(-1 == touch_fd)
    {
        perror("open ev error");
        exit(1);
    }
}

//关闭屏幕
void closeTouch(void)
{
    close(touch_fd);
}
//获取方向
TouchDirection GetDir(int *x, int *y)
{
	struct input_event ev;

	int ev_x,ev_y,ev_x0,ev_y0;
	while(1)
	{
		int r = read(touch_fd,&ev,sizeof(ev));
		if(0 >= r)//这里错误了可以进行超时处理
		{
			perror("read ev error");
			return TouchError;
		}

		if(ev.type == EV_ABS)//获取坐标值
		{
			if(ev.code == ABS_X)
			{
				ev_x = ev.value;
			}
			else if(ev.code == ABS_Y)
			{
				ev_y = ev.value;
			}
		}
	
		if(ev.type == 0x01 && ev.code == BTN_TOUCH && ev.value == 1)//点击下去
		{
			ev_x0 = ev_x;
			ev_y0 = ev_y;
		}
		else if(ev.type == 0x01 && ev.code == BTN_TOUCH && ev.value == 0)//手抬起来
		{
			if(ev_x0 == ev_x && ev_y0 == ev_y)
			{
				*x = ev_x;
                *y = ev_y;
				return TouchClick;//点击
			}
				
			else
			{
				if(ev_x0 > ev_x)
				{
					*x = ev_x;
					*y = ev_y;
					return TouchLeft;
				}	
				else if(ev_x0 < ev_x)
				{
					*x = ev_x;
					*y = ev_y;
					return TouchRight;
				}
				else if(ev_y0 < ev_y)
				{
					*x = ev_x;
					*y = ev_y;
					return TouchUp;
				}
				else if(ev_y0 > ev_y)
				{
					*x = ev_x;
					*y = ev_y;
					return TouchDown;
				}
			}
			
		}
	}
}

int get_touch_coordinate(int touch_fd, int *x, int *y)
{
    //读取触摸屏文件的输入数据并进行解析
    struct input_event ev;
    int flag_x=0, flag_y=0;

    while(1)
    {
        int res = read(touch_fd, &ev, sizeof(ev)); //只要没有点击屏幕，阻塞在read这代码
        if(res != sizeof(ev)) //读取数据不完整
        {
            continue; //继续下一次读取
        }

        //解析读取出来的数据，解析结构体成员type code value
        if(ev.type == EV_ABS && ev.code == ABS_X) //代表的绝对x坐标轴
        {
            *x = ev.value *800*1.0/1040; //等比缩放 
            flag_x=1;
        }
        else if(ev.type == EV_ABS && ev.code == ABS_Y)//代表的绝对y坐标轴
        {
            *y = ev.value *480*1.0/600; //等比缩放
            flag_y=1;
        }

        if(flag_x && flag_y)
        {
            break;
        }
    }
}


void draw_game(int x,int y) //显示地鼠
{
    
    int lcd_fd = open(lcd_path, O_RDWR);
	if(lcd_fd == -1)
	{
		return  ;
	}
	unsigned int * plcd = mmap(NULL,800*480*4,PROT_READ | PROT_WRITE, MAP_SHARED,lcd_fd,0);
	

		//找到空白位置随机生成
		int t=x*10+y;
		switch (t)
		{
		case 0:display_bmp1(bpath8,150,145,plcd);
			   sleep(1);
			   display_bmp(bpathk1,150,145,plcd);
			break;
		case 1:display_bmp1(bpath8,360,145,plcd);//360 440 145 225
			   sleep(1);
			   display_bmp(bpathk2,360,145,plcd);
			break;
		case 2:display_bmp1(bpath8,570,145,plcd);//570 650 145 225
			   sleep(1);
			   display_bmp(bpathk3,570,145,plcd);
			break;
		case 10:display_bmp1(bpath8,150,245,plcd);//150 230 245 325
				sleep(1);
			   	display_bmp(bpathk4,150,245,plcd);
			break;
		case 11:display_bmp1(bpath8,360,245,plcd);
				sleep(1);
			   	display_bmp(bpathk5,360,245,plcd);
			break;
		case 12:display_bmp1(bpath8,570,245,plcd);
				sleep(1);
			   	display_bmp(bpathk6,570,245,plcd);
			break;
		case 20:display_bmp1(bpath8,150,345,plcd);
				sleep(1);
			    display_bmp(bpathk7,150,345,plcd);
			break;
		case 21:display_bmp1(bpath8,360,345,plcd);
				sleep(1);
			    display_bmp(bpathk8,360,345,plcd);
			break;
		case 22:display_bmp1(bpath8,570,345,plcd);
				sleep(1);
				display_bmp(bpathk9,570,345,plcd);
			break;
		default:
			break;
		}



}

void* show(void*arg)
{
	printf(" ");//pthread_cancle取消线程需要有系统调用（write printf read）
    int num[3][3]={0};
			srand(time(NULL));
			int k = 0;//表示空白的数量
			int nx[16] = {0};   //所有空白的横坐标
			int ny[16] = {0};  //所有空白的纵坐标
			while(k<=9)
			{
				k=0;
				int i,j;
				for(i=0;i<3;i++)  //3行
				{
					for(j=0;j<3;j++) //3列
					{
						if(num[i][j] == 0) //找到一个空白
						{
							//把第k个空白记录下来
							nx[k] = i;
							ny[k] = j;
							k++;
						}
					}
				}
				//找到了k个空白,在所有的空白中随机一个位置
				if(k == 0)
				{
					return NULL;
				}
				int r = rand()%k; //r就是0~k之间的一个数
				draw_game(nx[r],ny[r]);
                sleep(0.5);
            }
}

//电子相册
void* get_xy(void *arg) //线程服务函数只能传递一个参数，指令需要使用到其他的参数
{
    while(1)
    {
        get_touch_coordinate(((Touch*)arg)->touch_fd, &(((Touch*)arg)->x), &(((Touch*)arg)->y));
        printf("x=%d y=%d\n", (((Touch*)arg)->x), (((Touch*)arg)->y));
    }
}


#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "lcd.h"
#include "bmp.h"

/*
    display_bmp:在LCD屏幕上显示BMP图片
    @path:显示的图片的路径     
    @x0:显示图片的起始x坐标
    @y0:显示图片的起始y坐标
    @plcd:帧缓冲区域的首地址
    返回值：
        成功 0
        失败 -1
        int
*/

int display_bmp1(char *path, int x0, int y0, unsigned int *plcd)
{
    if(plcd == NULL || x0<0 || x0>=800 || y0<0 || y0>=480)
    {
        printf("%s:%d", __FUNCTION__, __LINE__);
        return -1;
    }

    //1.open打开图片文件
    int bmp_fd = open(path, O_RDONLY);
    if(-1 == bmp_fd)
    {
        printf("open %s fail", path);
        return -1;
    }

    //2.解析图片宽、高、色深
    //解析宽
    int width; 
    lseek(bmp_fd, 0x12, SEEK_SET);	
    read(bmp_fd, &width, 4);
    //解析高
    int height;
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd, &height, 4);
    //解析色深
    short depth;
    lseek(bmp_fd, 0x1C, SEEK_SET);
    read(bmp_fd, &depth, 2);

    //3.获取像素数组的数据
    //计算像素数组的大小
    int line_effective_bytes = abs(width) * (depth/8); //一行的有效字节数
    int laizi = 0; //一行的赖子数
    int line_total_bytes = 0; //一行的总字节数
    int piexl_array_bytes = 0; //整个像素数组的字节数
    if(line_effective_bytes % 4 != 0) //证明会有填充字节
    {
        laizi = 4 - line_effective_bytes % 4;
    }
    line_total_bytes = laizi + line_effective_bytes;
    piexl_array_bytes = line_total_bytes * abs(height); //abs(),求绝对值

    //把像素数据全部从图片文件中读取出来
    unsigned char piexl_arr[piexl_array_bytes]; 
    lseek(bmp_fd, 0x36, SEEK_SET);
    read(bmp_fd, piexl_arr, piexl_array_bytes);  

    //4.解析像素数组中的数据，得到一个一个的像素点显示到LCD屏幕对应的位置
    int a,r,g,b;
    int k=0; //遍历piexl_arr数组
    int color;

    for(int j=0; j<abs(height); j++) 
    {
        for(int i=0; i<abs(width); i++) //循环1次把该行的所有像素点显示了  //2
        {
            b = piexl_arr[k++];
            g = piexl_arr[k++];
            r = piexl_arr[k++];
            if(depth == 32)
            {
                a = piexl_arr[k++];
            }
            else
            {
                a = 0;
            }
            color = a<<24 | r<<16 | g<<8 | b; //得到了一个颜色值（像素点）
            //把获取到的像素点显示开发板上对应位置上
            int x = width>0 ? x0+i : x0+abs(width)-1-i;
            int y = height>0 ? y0+abs(height)-1-j : y0+j;
            if(color!=0x00FFFFEC)
            {
                display_point(plcd, x, y, color);
            }
        }
        
        k += laizi; //跳过每一行后面的癞子数目
    }

    //5.关闭图片文件
    close(bmp_fd);
    return 0;
}

int display_bmp2(char *path, int x0, int y0, unsigned int *plcd)
{
    if(plcd == NULL || x0<0 || x0>=800 || y0<0 || y0>=480)
    {
        printf("%s:%d", __FUNCTION__, __LINE__);
        return -1;
    }

    //1.open打开图片文件
    int bmp_fd = open(path, O_RDONLY);
    if(-1 == bmp_fd)
    {
        printf("open %s fail", path);
        return -1;
    }

    //2.解析图片宽、高、色深
    //解析宽
    int width; 
    lseek(bmp_fd, 0x12, SEEK_SET);	
    read(bmp_fd, &width, 4);
    //解析高
    int height;
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd, &height, 4);
    //解析色深
    short depth;
    lseek(bmp_fd, 0x1C, SEEK_SET);
    read(bmp_fd, &depth, 2);

    //3.获取像素数组的数据
    //计算像素数组的大小
    int line_effective_bytes = abs(width) * (depth/8); //一行的有效字节数
    int laizi = 0; //一行的赖子数
    int line_total_bytes = 0; //一行的总字节数
    int piexl_array_bytes = 0; //整个像素数组的字节数
    if(line_effective_bytes % 4 != 0) //证明会有填充字节
    {
        laizi = 4 - line_effective_bytes % 4;
    }
    line_total_bytes = laizi + line_effective_bytes;
    piexl_array_bytes = line_total_bytes * abs(height); //abs(),求绝对值

    //把像素数据全部从图片文件中读取出来
    unsigned char piexl_arr[piexl_array_bytes]; 
    lseek(bmp_fd, 0x36, SEEK_SET);
    read(bmp_fd, piexl_arr, piexl_array_bytes);  
    
    //4.解析像素数组中的数据，得到一个一个的像素点显示到LCD屏幕对应的位置
    int a,r,g,b;
    int k=0; //遍历piexl_arr数组
    int color;

    for(int j=0; j<abs(height); j++) 
    {
        for(int i=0; i<abs(width); i++) //循环1次把该行的所有像素点显示了  //2
        {   
            b = piexl_arr[k++];
            g = piexl_arr[k++];
            r = piexl_arr[k++];
            if(depth == 32)
            {
                a = piexl_arr[k++];
            }
            else
            {
                a = 0;
            }
            color = a<<24 | r<<16 | g<<8 | b; //得到了一个颜色值（像素点）
            //把获取到的像素点显示开发板上对应位置上
            int x = width>0 ? x0+i : x0+abs(width)-1-i;
            int y = height>0 ? y0+abs(height)-1-j : y0+j;
            if(color!=0x00FFFFDE)
            {
                display_point(plcd, x, y, color);
            }

            
        }
        
        k += laizi; //跳过每一行后面的癞子数目
    }

    //5.关闭图片文件
    close(bmp_fd);
    return 0;
}

int display_bmp(char *path, int x0, int y0, unsigned int *plcd)
{
    if(plcd == NULL || x0<0 || x0>=800 || y0<0 || y0>=480)
    {
        printf("%s:%d", __FUNCTION__, __LINE__);
        return -1;
    }
                    
    //1.open打开图片文件
    int bmp_fd = open(path, O_RDONLY);
    if(-1 == bmp_fd)
    {
        printf("open %s fail", path);
        return -1;
    }

    //2.解析图片宽、高、色深
    //解析宽
    int width; 
    lseek(bmp_fd, 0x12, SEEK_SET);	
    read(bmp_fd, &width, 4);
    //解析高
    int height;
    lseek(bmp_fd, 0x16, SEEK_SET);
    read(bmp_fd, &height, 4);
    //解析色深
    short depth;
    lseek(bmp_fd, 0x1C, SEEK_SET);
    read(bmp_fd, &depth, 2);

    //3.获取像素数组的数据
    //计算像素数组的大小
    int line_effective_bytes = abs(width) * (depth/8); //一行的有效字节数
    int laizi = 0; //一行的赖子数
    int line_total_bytes = 0; //一行的总字节数
    int piexl_array_bytes = 0; //整个像素数组的字节数
    if(line_effective_bytes % 4 != 0) //证明会有填充字节
    {
        laizi = 4 - line_effective_bytes % 4;
    }
    line_total_bytes = laizi + line_effective_bytes;
    piexl_array_bytes = line_total_bytes * abs(height); //abs(),求绝对值

    //把像素数据全部从图片文件中读取出来
    unsigned char piexl_arr[piexl_array_bytes]; 
    lseek(bmp_fd, 0x36, SEEK_SET);
    read(bmp_fd, piexl_arr, piexl_array_bytes);  

    //4.解析像素数组中的数据，得到一个一个的像素点显示到LCD屏幕对应的位置
    int a,r,g,b;
    int k=0; //遍历piexl_arr数组
    int color;

    for(int j=0; j<abs(height); j++) 
    {
        for(int i=0; i<abs(width); i++) //循环1次把该行的所有像素点显示了  //2
        {
            b = piexl_arr[k++];
            g = piexl_arr[k++];
            r = piexl_arr[k++];
            if(depth == 32)
            {
                a = piexl_arr[k++];
            }
            else
            {
                a = 0;
            }
            color = a<<24 | r<<16 | g<<8 | b; //得到了一个颜色值（像素点）
            //把获取到的像素点显示开发板上对应位置上
            int x = width>0 ? x0+i : x0+abs(width)-1-i;
            int y = height>0 ? y0+abs(height)-1-j : y0+j;
            display_point(plcd, x, y, color);
        }
        
        k += laizi; //跳过每一行后面的癞子数目
    }

    //5.关闭图片文件
    close(bmp_fd);
    return 0;
}

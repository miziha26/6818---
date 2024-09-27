#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "getpath.h"

/*
	get_bmp_path:打印指定路径下所有后缀为.bmp的路径
	@path:指定需要获取的目录路径名
    @head:链表的头结点的地址
	返回值：
		void
*/
void get_bmp_path(const char *path, DulLinklist *head) // ./test
{
	//1.打开一个目录
    DIR *drip = opendir(path);
    if(drip == NULL)//打开失败
    {
        perror("opendir fail");
        return ;
    }

    //2.读取目录项
    struct dirent *dt;
    while(dt = readdir(drip)) // test1
    {
        char temp_path[1024] = {0};
        sprintf(temp_path, "%s/%s", path, dt->d_name);   //把目录和获取出来的文件名合成一条路径

        //获取目录项的属性
        struct stat st;
        stat(temp_path, &st);

        //如果获取出来的目录项又是一个子目录，应该按照同样的目录的读取规则读取目录项
        if(S_ISDIR(st.st_mode)) //是子目录
        {
            //排除. 和 ..
            if(strcmp(dt->d_name, ".")==0 || strcmp(dt->d_name, "..")==0)
            {
                continue;
            }
            get_bmp_path(temp_path, head); 
        }
        else if(S_ISREG(st.st_mode))//满足是普通文件
        {
            if(strcmp(dt->d_name+strlen(dt->d_name)-4, ".bmp") == 0)//满足后缀为.bmp
            {
            	tail_insert(head, temp_path);
            }
        }
    }

    //3.关闭目录文件
    closedir(drip);
}

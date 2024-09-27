#ifndef __MP3_H__
#define __MP3_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <stdbool.h>

extern int volumeLevel;  // 全局变量保存音量信息
extern bool ifMuted;     // 是否静音的标志
extern unsigned int *plcd;



extern int music_i;

//初始化music 成功返回0，失败返回非0
int cshmusic(int*music_i);
void *play(void*arg);
void run(int *music_i);






#endif
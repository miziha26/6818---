#ifndef __MP4_H__
#define __MP4_H__

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

extern int touch_fd;
extern unsigned int *plcd;
void PipeClear(int pipefd);
int playmp4(void);
void *progress(void *arg);






#endif
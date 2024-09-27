#ifndef __BMP_H__
#define __BMP_H__

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "lcd.h"

int display_bmp(char *path, int x0, int y0, unsigned int *plcd);
int display_bmp1(char *path, int x0, int y0, unsigned int *plcd);
int display_bmp2(char *path, int x0, int y0, unsigned int *plcd);

#endif
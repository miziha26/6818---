#ifndef __LCD_H__
#define __LCD_H__

void display_point(unsigned int *plcd, int x0, int y0, int color);
int lcd_display_rectangle(int x0, int y0, int w, int h, unsigned int *plcd, unsigned int color);
int lcd_display_circle(int x0, int y0, int r, unsigned int *plcd, unsigned int color);
void lcd_draw_num(int num);
void lcd_draw_num1(int num);
void *daojishi(void *arg);
extern int  sum;
void lcd_draw_num3(int num);




#endif
#ifndef __PORT_H__
#define __PORT_H__

#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#ifndef __PORT_C__
#define main hocus_main
#define rand rand16
#define clk_times getclock()
#define _fmalloc malloc
#endif

#define interrupt
#define pascal
#define far
#define huge

struct WORDREGS
{
    unsigned int ax;
    unsigned int bx;
    unsigned int cx;
    unsigned int dx;
    unsigned int si;
    unsigned int di;
    unsigned int cflag;
    unsigned int flags;
};

struct BYTEREGS
{
    unsigned char al;
    unsigned char ah;
    unsigned char bl;
    unsigned char bh;
    unsigned char cl;
    unsigned char ch;
    unsigned char dl;
    unsigned char dh;
};

union REGS
{
    struct WORDREGS x;
    struct BYTEREGS h;
};

typedef void (*intfunc)(void);

void gotoxy(int x, int y);
void setmem(void *target, unsigned long len, char val);
unsigned char inportb(unsigned int port);
unsigned char outportb(unsigned int port, unsigned char value);
void setvect(int interrupt, void (*handler)(void));
intfunc getvect(int interrupt arg0);
void sound(int arg0);
void nosound(void);
int int86(int inter_no, union REGS *input_regs, union REGS *output_regs);
int getclock(void);
int rand16(void);
void swap_buffer();
void update_palette(unsigned char *rgb, unsigned char pel_start, int pel_count);
unsigned char *get_surface_pixel(int i);
int getch(void);
int kbhit(void);

#ifndef _MSC_VER
char *itoa(int value, char *result, int base);
#define ltoa itoa
void strupr(char *p);
#define unlink remove
#endif

#endif
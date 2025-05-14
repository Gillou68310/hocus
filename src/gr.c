#include "common.h"

typedef unsigned char (*line_t)[80];

// module: GR
// size: 0x4b
// addr: 0520:000B
void settext()
{
    // stack: [BP-16]
    // size: 16
    union REGS regs;
    // register: SI
    // size: 2
    int i;
}

// module: GR
// size: 0x48
// addr: 0520:0056
void setvpage(int page)
{
    // register: SI
    // size: 2
    // int page;
    // stack: [BP-2]
    // size: 2
    unsigned int addr;
    // stack: [BP-3]
    // size: 1
    unsigned char raddr;
}

// module: GR
// size: 0x23
// addr: 0520:009E
void setapage(int page)
{
    // register: SI
    // size: 2
    // int page;
    vga = vgap[page];
    apg = page;
}

// module: GR
// size: 0x1f
// addr: 0520:00C1
void wait_for_retrace(void)
{
}

// module: GR
// size: 0x12
// addr: 0520:00E0
void setreadplane(unsigned char plane)
{
}

// module: GR
// size: 0x23
// addr: 0520:00F2
void screen(unsigned char on)
{
}

// module: GR
// size: 0x12
// addr: 0520:0115
void enable_pixels(unsigned char mask)
{
}

// module: GR
// size: 0x1c
// addr: 0520:0127
void latches(int on)
{
}

// module: GR
// size: 0x73
// addr: 0520:0143
void setvga(void)
{
    // register: DI
    // size: 2
    int i;
}

// module: GR
// size: 0x40
// addr: 0520:01B6
void scopy(int dest, int src)
{
}

// module: GR
// size: 0x81
// addr: 0520:01F6
void copyblock(int sp, int lx, int ty, int rx, int by, int dp, int dx, int dy)
{
    // register: DI
    // size: 2
    // int lx;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-2]
    // size: 2
    int l;
}

// module: GR
// size: 0x2c
// addr: 0520:0277
void clearscreen(void)
{
}

// module: GR
// size: 0x4d
// addr: 0520:02A3
void clearbox(int lx, int ty, int rx, int by)
{
    // register: SI
    // size: 2
    // int ty;
    // register: DI
    // size: 2
    // int lx;
}

// module: GR
// size: 0x37
// addr: 0520:02F0
int pixel_clr(int x, int y)
{
    // register: SI
    // size: 2
    // int x;
}

// module: GR
// size: 0x3a
// addr: 0520:0327
void pixel(int x, int y, int c)
{
    // register: SI
    // size: 2
    // int x;
}

// module: GR
// size: 0x2b
// addr: 0520:0361
void blankpixelbox(int lx, int ty, int rx, int by)
{
    // register: SI
    // size: 2
    // int ty;
    // register: DI
    // size: 2
    int i;
}

// module: GR
// size: 0x3e
// addr: 0520:038C
void write_pels(unsigned char *rgb, unsigned char pel_start, int pel_count)
{
    // register: CX
    // size: 2
    // int pel_count;
}

// module: GR
// size: 0x3f
// addr: 0520:03CA
void read_pels(unsigned char *rgb, unsigned char pel_start, int pel_count)
{
    // register: CX
    // size: 2
    // int pel_count;
}

// module: GR
// size: 0x58
// addr: 0520:0409
void fade_out(int scans)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;
}

// module: GR
// size: 0x45
// addr: 0520:0461
void fade_in(int scans)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;
}

// module: GR
// size: 0x46
// addr: 0520:04A6
void fade_in_white(void)
{
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int j;
}

// module: GR
// size: 0x2a
// addr: 0520:04EC
void clear_palette(void)
{
    // register: SI
    // size: 2
    int i;
}

// module: GR
// size: 0x18
// addr: 0520:0516
void turn_on_palette(void)
{
}

// module: GR
// size: 0x15e
// addr: 0520:052E
void unpackpcxfile(void)
{
    // register: SI
    // size: 2
    int nn;
    // register: DI
    // size: 2
    int n;
    // stack: [BP-2]
    // size: 2
    int c;
    // stack: [BP-4]
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 2
    int j;
    // stack: [BP-326]
    // size: 320
    unsigned char line[4][80];
}

// module: GR
// size: 0xc4
// addr: 0520:068C
void load_pcx(int db_rec, int setpal)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 4
    long offset;
    // stack: [BP-8]
    // size: 4
    long length;
}

// module: GR
// size: 0x8a
// addr: 0520:0750
void capture_screen(void)
{
    // stack: [BP-2]
    // size: 2
    int p;
    // register: SI
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 4
    FILE *fp;
}

// module: GR
// size: 0x8c
// addr: 0520:07DA
void show_bin(int db_rec)
{
    // stack: [BP-2]
    // size: 2
    int p;
    // register: SI
    // size: 2
    int i;
    // stack: [BP-6]
    // size: 4
    long offset;
}

// module: GR
// size: 0x92
// addr: 0520:0866
void restore_graphics_fragment(int db_rec, int sx, int sy)
{
    // register: SI
    // size: 2
    int x;
    // register: DI
    // size: 2
    int y;
    // stack: [BP-2]
    // size: 2
    int p;
    // stack: [BP-6]
    // size: 4
    long offset;
}

// module: GR
// size: 0x3e
// addr: 0520:08F8
void restore_palette_fragment(int db_rec, int s, int setpal)
{
    // register: SI
    // size: 2
    // int s;
}
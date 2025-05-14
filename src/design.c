#include "common.h"

// module: DESIGN
// size: 0x1a
// addr: 09F0:0004
void set_all_layers(int on)
{
    // register: DX
    // size: 2
    int i;
}

// module: DESIGN
// size: 0x466
// addr: 09F0:001E
void make_status_line(void)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-22]
    // size: 21
    unsigned char dummy[21];
}

// module: DESIGN
// size: 0x79
// addr: 09F0:0484
void show_marker_cursor(int x, int y, int c)
{
    // register: DI
    // size: 2
    // int x;
    // register: SI
    // size: 2
    int i;
}

// module: DESIGN
// size: 0xc9
// addr: 09F0:04FD
void trim_coords(void)
{
}

// module: DESIGN
// size: 0x4e8
// addr: 09F0:05C6
void show_design_screen(void)
{
    // register: DI
    // size: 2
    int x;
    // stack: [BP-2]
    // size: 2
    int y;
    // stack: [BP-4]
    // size: 2
    int py;
    // stack: [BP-6]
    // size: 2
    int slx;
    // stack: [BP-8]
    // size: 2
    int sty;
    // stack: [BP-10]
    // size: 2
    int srx;
    // stack: [BP-12]
    // size: 2
    int sby;
    // stack: [BP-14]
    // size: 2
    int showswitchrange;
    // stack: [BP-16]
    // size: 2
    int ofs;
    // register: SI
    // size: 2
    int v;
    // stack: [BP-18]
    // size: 2
    int vv;
    // stack: [BP-20]
    // size: 2
    int blank;
}

// module: DESIGN
// size: 0xd5
// addr: 09F0:0AAE
void pick_from_palette(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
    // stack: [BP-2]
    // size: 1
    unsigned char done;
}

// module: DESIGN
// size: 0xa5
// addr: 09F0:0B83
int pick_power_up(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x140
// addr: 09F0:0C28
int pick_warp(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x58d
// addr: 09F0:0D68
void pick_switch(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // register: DI
    // size: 2
    int j;
    // register: SI
    // size: 2
    int l;
    // stack: [BP-4]
    // size: 2
    int m;
    // stack: [BP-5]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x2d2
// addr: 09F0:12F5
void pick_rtrip(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // register: SI
    // size: 2
    int l;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x2d2
// addr: 09F0:15C7
void pick_etrip(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // register: SI
    // size: 2
    int l;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x89
// addr: 09F0:1899
void load_tag_sprites(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int s;
    // stack: [BP-2]
    // size: 2
    int pos;
}

// module: DESIGN
// size: 0x124
// addr: 09F0:1922
void pick_mtag(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 2
    int l;
    // stack: [BP-5]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x2f2
// addr: 09F0:1A46
void pick_mtrig(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 2
    int j;
    // register: DI
    // size: 2
    int l;
    // stack: [BP-6]
    // size: 2
    int x;
    // stack: [BP-8]
    // size: 2
    int y;
    // stack: [BP-10]
    // size: 2
    int mpos;
    // stack: [BP-12]
    // size: 2
    int start;
    // stack: [BP-13]
    // size: 1
    unsigned char key;
}

// module: DESIGN
// size: 0x11b6
// addr: 09F0:1D38
void design(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
    // stack: [BP-2]
    // size: 1
    unsigned char done;
    // register: SI
    // size: 2
    int x;
    // register: DI
    // size: 2
    int y;
    // stack: [BP-4]
    // size: 2
    int i;
}
#include "common.h"

// module: PLAY
// size: 0xd3
// addr: 0CDE:000E
void scan_monster_shot_hits(void)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int hx1;
    // stack: [BP-4]
    // size: 2
    int hx2;
    // stack: [BP-6]
    // size: 2
    int hy1;
    // stack: [BP-8]
    // size: 2
    int hy2;
}

// module: PLAY
// size: 0xe0
// addr: 0CDE:00E1
void scan_monster_collisions(void)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int hx1;
    // stack: [BP-4]
    // size: 2
    int hx2;
    // stack: [BP-6]
    // size: 2
    int hy1;
    // stack: [BP-8]
    // size: 2
    int hy2;
}

// module: PLAY
// size: 0xa0
// addr: 0CDE:01C1
void smart_bomb_monsters(void)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int mx1;
    // stack: [BP-4]
    // size: 2
    int my1;
    // stack: [BP-6]
    // size: 2
    int expy;
    // stack: [BP-8]
    // size: 2
    int expx;
}

// module: PLAY
// size: 0x1c5
// addr: 0CDE:0261
void scan_for_monster_hits(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int j;
    // stack: [BP-2]
    // size: 2
    int mx1;
    // stack: [BP-4]
    // size: 2
    int mx2;
    // stack: [BP-6]
    // size: 2
    int sx;
    // stack: [BP-8]
    // size: 2
    int sy;
    // stack: [BP-10]
    // size: 2
    int my1;
    // stack: [BP-12]
    // size: 2
    int my2;
    // stack: [BP-14]
    // size: 2
    int expy;
    // stack: [BP-16]
    // size: 2
    int expx;
}

// module: PLAY
// size: 0x9e
// addr: 0CDE:0426
void clip_monsters(void)
{
    // register: DX
    // size: 2
    int i;
    // register: SI
    // size: 2
    int kill;
}

// module: PLAY
// size: 0x3fa
// addr: 0CDE:04C4
int new_monster(int spr_num, int x, int y, int offset)
{
    // register: DI
    // size: 2
    // int spr_num;
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int sn;
}

// module: PLAY
// size: 0x17c
// addr: 0CDE:08D1
int new_shot(int x, int y, int d, int wait, int tag, int sn)
{
    // register: SI
    // size: 2
    // int sn;
    // register: DI
    // size: 2
    // int tag;
    // register: CX
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int xp;
}

// module: PLAY
// size: 0x1e7
// addr: 0CDE:0A4D
void update_shots(void)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int kill;
    // stack: [BP-4]
    // size: 2
    int mx;
    // stack: [BP-6]
    // size: 2
    int my;
}

// module: PLAY
// size: 0x93
// addr: 0CDE:0C34
void show_hitbar(int i)
{
    // register: SI
    // size: 2
    // int i;
    // stack: [BP-2]
    // size: 2
    int nb;
    // stack: [BP-4]
    // size: 2
    int c;
}

// module: PLAY
// size: 0x349
// addr: 0CDE:0CC7
void update_boss3(int i)
{
    // register: SI
    // size: 2
    // int i;
    // stack: [BP-2]
    // size: 2
    int mx;
    // stack: [BP-4]
    // size: 2
    int my;
    // stack: [BP-6]
    // size: 2
    int sn;
    // register: DI
    // size: 2
    int d;
}

// module: PLAY
// size: 0x275
// addr: 0CDE:1010
void update_boss4(void)
{
    // register: DI
    // size: 2
    int mx;
    // stack: [BP-2]
    // size: 2
    int my;
    // register: SI
    // size: 2
    int sn;
}

// module: PLAY
// size: 0xcef
// addr: 0CDE:1285
void update_monsters(void)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int reset;
    // stack: [BP-4]
    // size: 2
    int x;
    // stack: [BP-6]
    // size: 2
    int y;
    // stack: [BP-8]
    // size: 2
    int ox;
    // stack: [BP-10]
    // size: 2
    int oy;
    // stack: [BP-12]
    // size: 2
    int mpos;
    // register: DI
    // size: 2
    int wmpos;
    // stack: [BP-14]
    // size: 2
    int mx;
    // stack: [BP-16]
    // size: 2
    int my;
    // stack: [BP-17]
    // size: 1
    unsigned char mxw;
    // stack: [BP-18]
    // size: 1
    unsigned char myl;
    // stack: [BP-19]
    // size: 1
    unsigned char sn;
}

// module: PLAY
// size: 0x124
// addr: 0CDE:1F84
void update_twinks(void)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // register: SI
    // size: 2
    int c;
    // stack: [BP-6]
    // size: 2
    int clr;
}

// module: PLAY
// size: 0x58
// addr: 0CDE:20A8
void new_twink(int x, int y)
{
}

// module: PLAY
// size: 0x37
// addr: 0CDE:2100
void flash_screen(void)
{
}

// module: PLAY
// size: 0x189
// addr: 0CDE:2137
void load_sprites(void)
{
    // register: SI
    // size: 2
    int s;
    // stack: [BP-2]
    // size: 2
    int pos;
    // register: DI
    // size: 2
    unsigned int i;
    // stack: [BP-4]
    // size: 2
    unsigned int pe;
}

// module: PLAY
// size: 0xf7
// addr: 0CDE:22C0
void draw_sprite_nocheck(int snum, int x, int y, int dir, int frm)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    unsigned int spnt;
    // stack: [BP-4]
    // size: 2
    unsigned int dpnt;
    // stack: [BP-5]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0x174
// addr: 0CDE:23B7
void draw_sprite(int snum, int xw, int x, int y, int dir, int frm)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 2
    int j;
    // register: DI
    // size: 2
    int px;
    // stack: [BP-6]
    // size: 2
    int py;
    // stack: [BP-8]
    // size: 2
    unsigned int spnt;
    // stack: [BP-10]
    // size: 2
    unsigned int dpnt;
    // stack: [BP-11]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0xc6
// addr: 0CDE:252B
void draw_wsprite_nocheck(int snum, int x, int y, int dir, int frm)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    unsigned int spnt;
    // register: DI
    // size: 2
    unsigned int dpnt;
    // stack: [BP-3]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0x141
// addr: 0CDE:25F1
void draw_wsprite(int snum, int xw, int x, int y, int dir, int frm)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int j;
    // register: SI
    // size: 2
    int px;
    // stack: [BP-4]
    // size: 2
    int py;
    // stack: [BP-6]
    // size: 2
    unsigned int spnt;
    // stack: [BP-8]
    // size: 2
    unsigned int dpnt;
    // stack: [BP-9]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0xc6
// addr: 0CDE:2732
void draw_rsprite_nocheck(int snum, int x, int y, int dir, int frm)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    unsigned int spnt;
    // register: DI
    // size: 2
    unsigned int dpnt;
    // stack: [BP-3]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0x141
// addr: 0CDE:27F8
void draw_rsprite(int snum, int xw, int x, int y, int dir, int frm)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int j;
    // register: SI
    // size: 2
    int px;
    // stack: [BP-4]
    // size: 2
    int py;
    // stack: [BP-6]
    // size: 2
    unsigned int spnt;
    // stack: [BP-8]
    // size: 2
    unsigned int dpnt;
    // stack: [BP-9]
    // size: 1
    unsigned char code;
}

// module: PLAY
// size: 0x2b6
// addr: 0CDE:2939
void get_coords(void)
{
    // stack: [BP-2]
    // size: 2
    int oldscry;
    // stack: [BP-4]
    // size: 2
    int scrydif;
    // stack: [BP-6]
    // size: 2
    int oldscrx;
    // stack: [BP-8]
    // size: 2
    int scrxdif;
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int j;
}

// module: PLAY
// size: 0x243
// addr: 0CDE:2BEF
void do_element_animation(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // register: SI
    // size: 2
    int e;
    // stack: [BP-6]
    // size: 2
    int ne;
    // register: DI
    // size: 2
    int mpos;
}

// module: PLAY
// size: 0x85
// addr: 0CDE:2E32
void process_monster_reserve(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int mpos;
    // stack: [BP-2]
    // size: 2
    int e;
    // stack: [BP-4]
    // size: 2
    int x;
    // stack: [BP-6]
    // size: 2
    int y;
}

// module: PLAY
// size: 0xff
// addr: 0CDE:2EB7
void new_explosion(int x, int y)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int j;
}

// module: PLAY
// size: 0x162
// addr: 0CDE:2FB6
void update_explosions(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int j;
}

// module: PLAY
// size: 0x172
// addr: 0CDE:3118
void do_fast_digit(int base, int digit)
{
    // register: DX
    // size: 2
    int sbase;
    // register: CX
    // size: 2
    int dbase;
}

// module: PLAY
// size: 0x1f6
// addr: 0CDE:328A
void do_fast_key(int base, int image)
{
    // register: DX
    // size: 2
    int sbase;
    // register: CX
    // size: 2
    int dbase;
}

// module: PLAY
// size: 0x19a
// addr: 0CDE:3480
void show_panel_stats(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int l;
}

// module: PLAY
// size: 0x45
// addr: 0CDE:361A
void count_crystals(void)
{
    // register: CX
    // size: 2
    int i;
}

// module: PLAY
// size: 0x8a
// addr: 0CDE:365F
void new_stag(int x, int y, int num)
{
    // register: SI
    // size: 2
    // int num;
    // register: CX
    // size: 2
    int i;
}

// module: PLAY
// size: 0x7f
// addr: 0CDE:36E9
void update_stags(void)
{
    // register: SI
    // size: 2
    int i;
}

// module: PLAY
// size: 0xb0
// addr: 0CDE:3768
void do_pause(void)
{
    // register: SI
    // size: 2
    int sy;
    // stack: [BP-2]
    // size: 2
    int xl;
    // register: DI
    // size: 2
    int sx;
}

// module: PLAY
// size: 0x158
// addr: 0CDE:3818
void do_wiznote(int num)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int nl;
    // stack: [BP-2]
    // size: 2
    int sy;
    // stack: [BP-4]
    // size: 2
    int xl;
    // stack: [BP-6]
    // size: 2
    int sx;
    // stack: [BP-8]
    // size: 2
    int l;
}

// module: PLAY
// size: 0xb54
// addr: 0CDE:3970
void do_function_check(void)
{
    // stack: [BP-2]
    // size: 2
    int mpos;
    // stack: [BP-4]
    // size: 2
    int i;
    // register: DI
    // size: 2
    int j;
    // stack: [BP-6]
    // size: 2
    int k;
    // stack: [BP-8]
    // size: 2
    int l;
    // stack: [BP-10]
    // size: 2
    int m;
    // stack: [BP-12]
    // size: 2
    int ok;
    // stack: [BP-14]
    // size: 2
    int v;
    // stack: [BP-16]
    // size: 2
    int pm;
    // stack: [BP-18]
    // size: 2
    int x;
    // stack: [BP-20]
    // size: 2
    int y;
    // stack: [BP-22]
    // size: 2
    int keep;
    // register: SI
    // size: 2
    int vv;
    // stack: [BP-24]
    // size: 2
    int xx;
    // stack: [BP-26]
    // size: 2
    int yy;
    // stack: [BP-28]
    // size: 2
    int z;
}

// module: PLAY
// size: 0x2223
// addr: 0CDE:44C4
int play(int demomode)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int s;
    // stack: [BP-8]
    // size: 2
    int exitcode;
    // register: DI
    // size: 2
    int mpos;
    // stack: [BP-10]
    // size: 2
    int mpos2;
    // stack: [BP-11]
    // size: 1
    unsigned char done;
    // stack: [BP-12]
    // size: 1
    unsigned char do_anm;
    // stack: [BP-16]
    // size: 4
    long gametimer;
}
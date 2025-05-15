#ifndef __TYPES_H__
#define __TYPES_H__

// size: 956
struct struct_31
{
    // offset: 0 (2 bytes)
    int soundfx;
    // offset: 2 (2 bytes)
    int music;
    // offset: 4 (2 bytes)
    int joystick;
    // offset: 6 (2 bytes)
    unsigned int jxmin;
    // offset: 8 (2 bytes)
    unsigned int jxmax;
    // offset: 10 (2 bytes)
    unsigned int jymin;
    // offset: 12 (2 bytes)
    unsigned int jymax;
    // offset: 14 (8 bytes)
    unsigned char pckey[8];
    // offset: 22 (18 bytes)
    int game[9];
    // offset: 40 (18 bytes)
    int level[9];
    // offset: 58 (18 bytes)
    int skill[9];
    // offset: 76 (234 bytes)
    unsigned char gname[9][26];
    // offset: 310 (9 bytes)
    unsigned char firepower[9];
    // offset: 320 (36 bytes)
    long score[9];
    // offset: 356 (520 bytes)
    unsigned char hname[4][5][26];
    // offset: 876 (80 bytes)
    long hiscore[4][5];
};

// size: 4
struct struct_46
{
    // offset: 0 (2 bytes)
    int xw;
    // offset: 2 (2 bytes)
    int yw;
};

// size: 724
struct struct_59
{
    // offset: 0 (1 bytes)
    unsigned char defaultbkg;
    // offset: 1 (1 bytes)
    unsigned char switchoff;
    // offset: 2 (1 bytes)
    unsigned char switchon;
    // offset: 3 (1 bytes)
    unsigned char bustblock;
    // offset: 4 (720 bytes)
    unsigned char v[240][3];
};

// size: 8
struct struct_62
{
    // offset: 0 (2 bytes)
    int bdrop_num;
    // offset: 2 (2 bytes)
    int startx;
    // offset: 4 (2 bytes)
    int starty;
    // offset: 6 (2 bytes)
    int shot_freq;
};

// size: 8
struct struct_70
{
    // offset: 0 (4 bytes)
    long ofs;
    // offset: 4 (4 bytes)
    long len;
};

// size: 128
typedef struct PCXHEAD
{
    // offset: 0 (1 bytes)
    unsigned char manufacturer;
    // offset: 1 (1 bytes)
    unsigned char version;
    // offset: 2 (1 bytes)
    unsigned char encoding;
    // offset: 3 (1 bytes)
    unsigned char bytes_per_pixel;
    // offset: 4 (2 bytes)
    int xmin;
    // offset: 6 (2 bytes)
    int ymin;
    // offset: 8 (2 bytes)
    int xmax;
    // offset: 10 (2 bytes)
    int ymax;
    // offset: 12 (2 bytes)
    int hres;
    // offset: 14 (2 bytes)
    int vres;
    // offset: 16 (48 bytes)
    unsigned char palette[48];
    // offset: 64 (1 bytes)
    unsigned char reserved;
    // offset: 65 (1 bytes)
    unsigned char colour_planes;
    // offset: 66 (2 bytes)
    int bytes_per_line;
    // offset: 68 (2 bytes)
    int palette_type;
    // offset: 70 (58 bytes)
    unsigned char filler[58];
} PCXHEAD;

// size: 1686
struct struct_98
{
    // offset: 0 (2 bytes)
    int num;
    // offset: 2 (2 bytes)
    int lspacing;
    // offset: 4 (2 bytes)
    int bspacing;
    // offset: 6 (80 bytes)
    int attrb[40];
    // offset: 86 (1600 bytes)
    unsigned char lines[20][80];
};

// size: 32
struct struct_115
{
    // offset: 0 (16 bytes)
    int mnum[8];
    // offset: 16 (16 bytes)
    int rpos[8];
};

// size: 24
struct struct_118
{
    // offset: 0 (2 bytes)
    int mnum;
    // offset: 2 (2 bytes)
    int tokill;
    // offset: 4 (2 bytes)
    int hshotplus;
    // offset: 6 (2 bytes)
    int vshotplus;
    // offset: 8 (2 bytes)
    int vo;
    // offset: 10 (2 bytes)
    int shotfollow;
    // offset: 12 (2 bytes)
    int mustface;
    // offset: 14 (2 bytes)
    int canshoot;
    // offset: 16 (2 bytes)
    int stopshoot;
    // offset: 18 (2 bytes)
    int wobble;
    // offset: 20 (2 bytes)
    int sink;
    // offset: 22 (2 bytes)
    int type;
};

// size: 12
struct struct_120
{
    // offset: 0 (2 bytes)
    int keytype;
    // offset: 2 (2 bytes)
    int restore;
    // offset: 4 (2 bytes)
    int dlx;
    // offset: 6 (2 bytes)
    int dty;
    // offset: 8 (2 bytes)
    int drx;
    // offset: 10 (2 bytes)
    int dby;
};

// size: 22
struct struct_124
{
    // offset: 0 (1 bytes)
    unsigned char effect;
    // offset: 2 (8 bytes)
    int condnum[4];
    // offset: 10 (4 bytes)
    unsigned char condstate[4];
    // offset: 14 (2 bytes)
    int dlx;
    // offset: 16 (2 bytes)
    int dty;
    // offset: 18 (2 bytes)
    int drx;
    // offset: 20 (2 bytes)
    int dby;
};

// size: 4
struct struct_128
{
    // offset: 0 (2 bytes)
    int src;
    // offset: 2 (2 bytes)
    int dest;
};

// size: 42
struct struct_130
{
    // offset: 0 (36 bytes)
    unsigned char tag[36];
    // offset: 36 (2 bytes)
    int add2score;
    // offset: 38 (1 bytes)
    unsigned char add2health;
    // offset: 39 (1 bytes)
    unsigned char add2shots;
    // offset: 40 (1 bytes)
    unsigned char powermode;
};

// size: 504
struct struct_153
{
    // offset: 0 (2 bytes)
    int lx;
    // offset: 2 (2 bytes)
    int rx;
    // offset: 4 (500 bytes)
    unsigned char text[10][50];
};

// size: 220
struct struct_159
{
    // offset: 0 (4 bytes)
    long fpos;
    // offset: 4 (21 bytes)
    unsigned char name[21];
    // offset: 26 (2 bytes)
    int xw;
    // offset: 28 (2 bytes)
    int yl;
    // offset: 30 (2 bytes)
    int frs;
    // offset: 32 (2 bytes)
    int fre;
    // offset: 34 (2 bytes)
    int mfrs;
    // offset: 36 (2 bytes)
    int mfre;
    // offset: 38 (2 bytes)
    int jfrs;
    // offset: 40 (2 bytes)
    int jfre;
    // offset: 42 (2 bytes)
    int afrs;
    // offset: 44 (2 bytes)
    int afre;
    // offset: 46 (2 bytes)
    int sxw;
    // offset: 48 (2 bytes)
    int syl;
    // offset: 50 (2 bytes)
    int sys;
    // offset: 52 (2 bytes)
    int sfrs;
    // offset: 54 (2 bytes)
    int sfre;
    // offset: 56 (2 bytes)
    unsigned int codesize;
    // offset: 58 (2 bytes)
    unsigned int datasize;
    // offset: 60 (80 bytes)
    unsigned int codeofs[2][20];
    // offset: 140 (80 bytes)
    unsigned int dataofs[2][20];
};

// size: 6
struct struct_172
{
    // offset: 0 (1 bytes)
    unsigned char ukey;
    // offset: 1 (1 bytes)
    unsigned char lkey;
    // offset: 2 (1 bytes)
    unsigned char rkey;
    // offset: 3 (1 bytes)
    unsigned char fkey;
    // offset: 4 (1 bytes)
    unsigned char jkey;
};

// size: 24
typedef struct Jdefines
{
    // offset: 0 (2 bytes)
    unsigned int joyMinX;
    // offset: 2 (2 bytes)
    unsigned int joyMinY;
    // offset: 4 (2 bytes)
    unsigned int threshMinX;
    // offset: 6 (2 bytes)
    unsigned int threshMinY;
    // offset: 8 (2 bytes)
    unsigned int threshMaxX;
    // offset: 10 (2 bytes)
    unsigned int threshMaxY;
    // offset: 12 (2 bytes)
    unsigned int joyMaxX;
    // offset: 14 (2 bytes)
    unsigned int joyMaxY;
    // offset: 16 (2 bytes)
    unsigned int joyMultXL;
    // offset: 18 (2 bytes)
    unsigned int joyMultYL;
    // offset: 20 (2 bytes)
    unsigned int joyMultXH;
    // offset: 22 (2 bytes)
    unsigned int joyMultYH;
} Jdefines;

typedef long fpos_t;
typedef long ptrdiff_t;
typedef long clock_t;
typedef long time_t;
typedef unsigned int size_t;
typedef unsigned char (*line_t)[80];

#endif
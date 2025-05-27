#ifndef __TYPES_H__
#define __TYPES_H__

// size: 956
typedef struct config_t
{
    // offset: 0 (2 bytes)
    int16_t soundfx;
    // offset: 2 (2 bytes)
    int16_t music;
    // offset: 4 (2 bytes)
    int16_t joystick;
    // offset: 6 (2 bytes)
    uint16_t jxmin;
    // offset: 8 (2 bytes)
    uint16_t jxmax;
    // offset: 10 (2 bytes)
    uint16_t jymin;
    // offset: 12 (2 bytes)
    uint16_t jymax;
    // offset: 14 (8 bytes)
    unsigned char pckey[8];
    // offset: 22 (18 bytes)
    int16_t game[9];
    // offset: 40 (18 bytes)
    int16_t level[9];
    // offset: 58 (18 bytes)
    int16_t skill[9];
    // offset: 76 (234 bytes)
    unsigned char gname[9][26];
    // offset: 310 (9 bytes)
    unsigned char firepower[9];
    // offset: 320 (36 bytes)
    int32_t score[9];
    // offset: 356 (520 bytes)
    unsigned char hname[GAME_COUNT][5][26];
    // offset: 876 (80 bytes)
    int32_t hiscore[GAME_COUNT][5];
} config_t;

// size: 4
typedef struct grphdr_t
{
    // offset: 0 (2 bytes)
    int16_t xw;
    // offset: 2 (2 bytes)
    int16_t yw;
} grphdr_t;

// size: 724
typedef struct anminfo_t
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
} anminfo_t;

// size: 8
typedef struct lvlinfo_t
{
    // offset: 0 (2 bytes)
    int16_t bdrop_num;
    // offset: 2 (2 bytes)
    int16_t startx;
    // offset: 4 (2 bytes)
    int16_t starty;
    // offset: 6 (2 bytes)
    int16_t shot_freq;
} lvlinfo_t;

// size: 8
typedef struct struct_70
{
    // offset: 0 (4 bytes)
    long ofs;
    // offset: 4 (4 bytes)
    long len;
} struct_70;

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
    int16_t xmin;
    // offset: 6 (2 bytes)
    int16_t ymin;
    // offset: 8 (2 bytes)
    int16_t xmax;
    // offset: 10 (2 bytes)
    int16_t ymax;
    // offset: 12 (2 bytes)
    int16_t hres;
    // offset: 14 (2 bytes)
    int16_t vres;
    // offset: 16 (48 bytes)
    unsigned char palette[48];
    // offset: 64 (1 bytes)
    unsigned char reserved;
    // offset: 65 (1 bytes)
    unsigned char colour_planes;
    // offset: 66 (2 bytes)
    int16_t bytes_per_line;
    // offset: 68 (2 bytes)
    int16_t palette_type;
    // offset: 70 (58 bytes)
    unsigned char filler[58];
} PCXHEAD;

// size: 1686
typedef struct inf_t
{
    // offset: 0 (2 bytes)
    int16_t num;
    // offset: 2 (2 bytes)
    int16_t lspacing;
    // offset: 4 (2 bytes)
    int16_t bspacing;
    // offset: 6 (80 bytes)
    int16_t attrb[40];
    // offset: 86 (1600 bytes)
    unsigned char lines[20][80];
} inf_t;

// size: 32
typedef struct trigger_t
{
    // offset: 0 (16 bytes)
    int16_t mnum[8];
    // offset: 16 (16 bytes)
    int16_t rpos[8];
} trigger_t;

// size: 24
typedef struct tag_t
{
    // offset: 0 (2 bytes)
    int16_t mnum;
    // offset: 2 (2 bytes)
    int16_t tokill;
    // offset: 4 (2 bytes)
    int16_t hshotplus;
    // offset: 6 (2 bytes)
    int16_t vshotplus;
    // offset: 8 (2 bytes)
    int16_t vo;
    // offset: 10 (2 bytes)
    int16_t shotfollow;
    // offset: 12 (2 bytes)
    int16_t mustface;
    // offset: 14 (2 bytes)
    int16_t canshoot;
    // offset: 16 (2 bytes)
    int16_t stopshoot;
    // offset: 18 (2 bytes)
    int16_t wobble;
    // offset: 20 (2 bytes)
    int16_t sink;
    // offset: 22 (2 bytes)
    int16_t type;
} tag_t;

// size: 12
typedef struct trip_t
{
    // offset: 0 (2 bytes)
    int16_t keytype;
    // offset: 2 (2 bytes)
    int16_t restore;
    // offset: 4 (2 bytes)
    int16_t dlx;
    // offset: 6 (2 bytes)
    int16_t dty;
    // offset: 8 (2 bytes)
    int16_t drx;
    // offset: 10 (2 bytes)
    int16_t dby;
} trip_t;

// size: 22
typedef struct switch_t
{
    // offset: 0 (1 bytes)
    unsigned char effect;
    // offset: 2 (8 bytes)
    int16_t condnum[4];
    // offset: 10 (4 bytes)
    unsigned char condstate[4];
    // offset: 14 (2 bytes)
    int16_t dlx;
    // offset: 16 (2 bytes)
    int16_t dty;
    // offset: 18 (2 bytes)
    int16_t drx;
    // offset: 20 (2 bytes)
    int16_t dby;
} switch_t;

// size: 4
typedef struct warp_t
{
    // offset: 0 (2 bytes)
    int16_t src;
    // offset: 2 (2 bytes)
    int16_t dest;
} warp_t;

// size: 42
typedef struct ups_t
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
} ups_t;

// size: 504
typedef struct wiznote_t
{
    // offset: 0 (2 bytes)
    int16_t lx;
    // offset: 2 (2 bytes)
    int16_t rx;
    // offset: 4 (500 bytes)
    unsigned char text[10][50];
} wiznote_t;

// size: 220
typedef struct sprite_t
{
    // offset: 0 (4 bytes)
    int32_t fpos;
    // offset: 4 (21 bytes)
    unsigned char name[21];
    // offset: 26 (2 bytes)
    int16_t xw;
    // offset: 28 (2 bytes)
    int16_t yl;
    // offset: 30 (2 bytes)
    int16_t frs;
    // offset: 32 (2 bytes)
    int16_t fre;
    // offset: 34 (2 bytes)
    int16_t mfrs;
    // offset: 36 (2 bytes)
    int16_t mfre;
    // offset: 38 (2 bytes)
    int16_t jfrs;
    // offset: 40 (2 bytes)
    int16_t jfre;
    // offset: 42 (2 bytes)
    int16_t afrs;
    // offset: 44 (2 bytes)
    int16_t afre;
    // offset: 46 (2 bytes)
    int16_t sxw;
    // offset: 48 (2 bytes)
    int16_t syl;
    // offset: 50 (2 bytes)
    int16_t sys;
    // offset: 52 (2 bytes)
    int16_t sfrs;
    // offset: 54 (2 bytes)
    int16_t sfre;
    // offset: 56 (2 bytes)
    uint16_t codesize;
    // offset: 58 (2 bytes)
    uint16_t datasize;
    // offset: 60 (80 bytes)
    uint16_t codeofs[2][20];
    // offset: 140 (80 bytes)
    uint16_t dataofs[2][20];
} sprite_t;

// size: 6
typedef struct struct_172
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
} struct_172;

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

typedef unsigned char (*line_t)[VGA_PLANE_WIDTH];

#endif
#include "common.h"

// module: MENUS
// size: 0x84
// addr: 05E0:000D
int get_menu_joystick(void)
{
    // register: SI
    // size: 2
    int exitcode;
}

// module: MENUS
// size: 0x91
// addr: 05E0:0091
void update_icon(int x, int y)
{
    // stack: [BP-2]
    // size: 2
    int xc;
    // register: SI
    // size: 2
    int xx;
    // register: DI
    // size: 2
    int yc;
}

// module: MENUS
// size: 0x31b
// addr: 05E0:0122
void update_stars(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int x;
    // stack: [BP-2]
    // size: 2
    int y;
}

// module: MENUS
// size: 0x192
// addr: 05E0:043D
void new_stars(void)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int x;
    // stack: [BP-2]
    // size: 2
    int y;
}

// module: MENUS
// size: 0x13b
// addr: 05E0:05CF
void pstrs(int x, int y, int color, unsigned char *str)
{
    // register: SI
    // size: 2
    // int x;
    // stack: [BP-1]
    // size: 1
    unsigned char ch;
    // stack: [BP-2]
    // size: 1
    unsigned char c;
    // stack: [BP-3]
    // size: 1
    unsigned char s;
    // register: DI
    // size: 2
    int px;
    // stack: [BP-6]
    // size: 2
    int py;
    // stack: [BP-8]
    // size: 2
    int maxx;
    // stack: [BP-10]
    // size: 2
    int shift;
    // stack: [BP-12]
    // size: 2
    int ofs;
    // stack: [BP-14]
    // size: 2
    unsigned int word;
}

// module: MENUS
// size: 0x132
// addr: 05E0:070A
void pstrwiznote(int x, int y, int clr, unsigned char *str)
{
    // register: SI
    // size: 2
    // int x;
    // stack: [BP-1]
    // size: 1
    unsigned char ch;
    // stack: [BP-2]
    // size: 1
    unsigned char c;
    // stack: [BP-3]
    // size: 1
    unsigned char s;
    // register: DI
    // size: 2
    int px;
    // stack: [BP-6]
    // size: 2
    int py;
    // stack: [BP-8]
    // size: 2
    int maxx;
    // stack: [BP-10]
    // size: 2
    int shift;
    // stack: [BP-12]
    // size: 2
    int ofs;
    // stack: [BP-14]
    // size: 2
    unsigned int word;
}

// module: MENUS
// size: 0x16a
// addr: 05E0:083C
void pstr(int x, int y, int color, unsigned char *str)
{
    // register: SI
    // size: 2
    // int x;
    // stack: [BP-1]
    // size: 1
    unsigned char ch;
    // stack: [BP-2]
    // size: 1
    unsigned char c;
    // stack: [BP-3]
    // size: 1
    unsigned char s;
    // stack: [BP-4]
    // size: 1
    unsigned char black;
    // register: DI
    // size: 2
    int px;
    // stack: [BP-6]
    // size: 2
    int py;
    // stack: [BP-8]
    // size: 2
    int maxx;
    // stack: [BP-10]
    // size: 2
    int clr;
    // stack: [BP-12]
    // size: 2
    int shift;
    // stack: [BP-14]
    // size: 2
    int ofs;
    // stack: [BP-16]
    // size: 2
    unsigned int word;
}

// module: MENUS
// size: 0x91
// addr: 05E0:09A6
int pstrlen(unsigned char *str)
{
    // register: DX
    // size: 1
    unsigned char ch;
    // stack: [BP-1]
    // size: 1
    unsigned char c;
    // register: SI
    // size: 2
    int px;
    // stack: [BP-4]
    // size: 2
    int py;
    // stack: [BP-6]
    // size: 2
    int maxx;
    // register: DI
    // size: 2
    int x;
}

// module: MENUS
// size: 0x4e
// addr: 05E0:0A37
void pstr_hilite(int x, int y, int hc, int nc, unsigned char *str)
{
    // register: DI
    // size: 2
    // int y;
    // register: SI
    // size: 2
    // int x;
    // stack: [BP-82]
    // size: 81
    unsigned char dummy[81];
}

// module: MENUS
// size: 0x39
// addr: 05E0:0A85
void pstrsh(int x, int y, int c, unsigned char *str)
{
    // register: DI
    // size: 2
    // int y;
    // register: SI
    // size: 2
    // int x;
}

// module: MENUS
// size: 0x79
// addr: 05E0:0ABE
void pstrol(int x, int y, int c, unsigned char *str)
{
    // register: DI
    // size: 2
    // int y;
    // register: SI
    // size: 2
    // int x;
}

// module: MENUS
// size: 0x79
// addr: 05E0:0B37
void pstrol2(int x, int y, int c, unsigned char *str)
{
    // register: DI
    // size: 2
    // int y;
    // register: SI
    // size: 2
    // int x;
}

// module: MENUS
// size: 0x58
// addr: 05E0:0BB0
void ptstr(int x, int y, int fc, int bc, int len, unsigned char *str)
{
    // register: SI
    // size: 2
    unsigned int i;
    // register: DI
    // size: 2
    unsigned int tb;
}

// module: MENUS
// size: 0x1c
// addr: 05E0:0C08
void clrtscrn(void)
{
}

// module: MENUS
// size: 0x5a
// addr: 05E0:0C24
void blank(int lx, int ty, int rx, int by, int fc, int bc)
{
    // stack: [BP-2]
    // size: 2
    unsigned int tb;
    // register: DI
    // size: 2
    unsigned int to;
    // register: SI
    // size: 2
    unsigned int x;
}

// module: MENUS
// size: 0x249
// addr: 05E0:0C7E
void load_menu(int menunum)
{
    // register: DI
    // size: 2
    // int menunum;
    // register: SI
    // size: 2
    int i;
}

// module: MENUS
// size: 0xce
// addr: 05E0:0EC7
void do_line_menu(unsigned char *msg, int fn)
{
    // register: DI
    // size: 2
    // int fn;
    // register: SI
    // size: 2
    int x;
    // stack: [BP-2]
    // size: 2
    int y;
}

// module: MENUS
// size: 0x101
// addr: 05E0:0F95
void do_title_line_menu(unsigned char *tit, unsigned char *msg, int fn)
{
    // register: DI
    // size: 2
    // int fn;
    // register: SI
    // size: 2
    int x;
    // stack: [BP-2]
    // size: 2
    int y;
}

// module: MENUS
// size: 0x81
// addr: 05E0:1096
unsigned char get_any_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x7f
// addr: 05E0:1117
unsigned char get_yesno_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x81
// addr: 05E0:1196
unsigned char get_number_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x2a6
// addr: 05E0:1217
void do_def_menu(int kn)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // register: DI
    // size: 2
    int x;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x1f7
// addr: 05E0:14BD
void do_key_menu(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-3]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x1bd
// addr: 05E0:16B4
void do_menu(void)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int x;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-4]
    // size: 2
    int s;
}

// module: MENUS
// size: 0x11c
// addr: 05E0:1871
int is_high(int g, long s)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int j;
}

// module: MENUS
// size: 0x3c6
// addr: 05E0:198D
void get_hiscore(int g, int slot)
{
    // register: SI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int x;
    // register: DI
    // size: 2
    int y;
    // stack: [BP-4]
    // size: 2
    int s;
    // stack: [BP-6]
    // size: 2
    int sy;
    // stack: [BP-8]
    // size: 2
    int sclr;
    // stack: [BP-9]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x20a
// addr: 05E0:1D53
void do_show_hiscores(int demomode)
{
    // register: DI
    // size: 2
    int i;
    // stack: [BP-2]
    // size: 2
    int x;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-4]
    // size: 2
    int s;
    // stack: [BP-6]
    // size: 2
    int g;
    // stack: [BP-7]
    // size: 1
    signed char k;
    // stack: [BP-12]
    // size: 4
    long counter;
}

// module: MENUS
// size: 0x3d
// addr: 05E0:1F5D
void record_iconpos(void)
{
}

// module: MENUS
// size: 0x254
// addr: 05E0:1FA7
unsigned char get_menu_key(int ismain)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int s;
    // stack: [BP-4]
    // size: 2
    int t;
    // stack: [BP-8]
    // size: 4
    long counter;
}

// module: MENUS
// size: 0x1c
// addr: 05E0:21FB
unsigned char do_main_menu(void)
{
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2217
unsigned char do_begin_menu(void)
{
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2233
unsigned char do_game_options(void)
{
}

// module: MENUS
// size: 0x1c
// addr: 05E0:224F
unsigned char do_level_options(void)
{
}

// module: MENUS
// size: 0x1c
// addr: 05E0:226B
unsigned char do_skill_options(void)
{
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2287
unsigned char do_play_menu(void)
{
}

// module: MENUS
// size: 0x5c
// addr: 05E0:22A3
void do_message_menu(unsigned char *msg)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x5f5
// addr: 05E0:22FF
void save_game(void)
{
    // stack: [BP-2]
    // size: 2
    int exitcode;
    // stack: [BP-3]
    // size: 1
    signed char key;
    // stack: [BP-4]
    // size: 1
    signed char lkey;
    // stack: [BP-6]
    // size: 2
    int x;
    // stack: [BP-8]
    // size: 2
    int y;
    // register: DI
    // size: 2
    int i;
    // register: SI
    // size: 2
    int gs;
    // stack: [BP-10]
    // size: 2
    int sy;
    // stack: [BP-36]
    // size: 26
    unsigned char savename[26];
}

// module: MENUS
// size: 0x37e
// addr: 05E0:28F4
int restore_game(void)
{
    // stack: [BP-2]
    // size: 2
    int exitcode;
    // stack: [BP-3]
    // size: 1
    signed char key;
    // stack: [BP-6]
    // size: 2
    int x;
    // register: SI
    // size: 2
    int y;
    // register: DI
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int gs;
}

// module: MENUS
// size: 0x3d
// addr: 05E0:2C72
int confirm_quit(void)
{
    // stack: [BP-1]
    // size: 1
    signed char i;
    // register: SI
    // size: 2
    int exitcode;
}

// module: MENUS
// size: 0x136
// addr: 05E0:2CAF
int calibrate_joystick(void)
{
    // stack: [BP-2]
    // size: 2
    int exitcode;
    // register: SI
    // size: 2
    unsigned int jb;
    // stack: [BP-4]
    // size: 2
    unsigned int xmin;
    // stack: [BP-6]
    // size: 2
    unsigned int xmax;
    // stack: [BP-8]
    // size: 2
    unsigned int ymin;
    // stack: [BP-10]
    // size: 2
    unsigned int ymax;
}

// module: MENUS
// size: 0xae
// addr: 05E0:2DE5
void calibrate_from_game(void)
{
    // stack: [BP-2]
    // size: 2
    int capg;
    // stack: [BP-4]
    // size: 2
    int cvpg;
}

// module: MENUS
// size: 0xae
// addr: 05E0:2E93
void save_menu(void)
{
    // stack: [BP-2]
    // size: 2
    int capg;
    // stack: [BP-4]
    // size: 2
    int cvpg;
}

// module: MENUS
// size: 0xc1
// addr: 05E0:2F41
int restore_menu(void)
{
    // stack: [BP-2]
    // size: 2
    int capg;
    // stack: [BP-4]
    // size: 2
    int cvpg;
    // register: SI
    // size: 2
    int exitcode;
}

// module: MENUS
// size: 0xc1
// addr: 05E0:3002
int quit_menu(void)
{
    // stack: [BP-2]
    // size: 2
    int capg;
    // stack: [BP-4]
    // size: 2
    int cvpg;
    // register: SI
    // size: 2
    int exitcode;
}

// module: MENUS
// size: 0x1f0
// addr: 05E0:30C3
void do_info_screen(int page, int limit)
{
    // register: SI
    // size: 2
    int i;
    // register: DI
    // size: 2
    int y;
    // stack: [BP-82]
    // size: 81
    unsigned char dline[81];
    // stack: [BP-104]
    // size: 21
    unsigned char dummy[21];
}

// module: MENUS
// size: 0xea
// addr: 05E0:32B3
int get_page_key(int page, int limit)
{
    // register: DI
    // size: 2
    // int limit;
    // register: SI
    // size: 2
    // int page;
    // stack: [BP-1]
    // size: 1
    unsigned char key;
}

// module: MENUS
// size: 0x39
// addr: 05E0:339D
void do_ordering_info(void)
{
    // register: SI
    // size: 2
    int page;
}

// module: MENUS
// size: 0x27
// addr: 05E0:33D6
void do_cantplay_info(void)
{
}

// module: MENUS
// size: 0xe8
// addr: 05E0:33FD
void do_credits(void)
{
    // register: SI
    // size: 2
    int page;
    // register: DI
    // size: 2
    int quit;
    // stack: [BP-4]
    // size: 4
    long gametimer;
}

// module: MENUS
// size: 0xac
// addr: 05E0:34E5
void do_previews(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;
    // register: SI
    // size: 2
    int page;
}

// module: MENUS
// size: 0x1b2
// addr: 05E0:3591
void do_help(int insidegame)
{
    // register: DI
    // size: 2
    // int insidegame;
    // stack: [BP-1]
    // size: 1
    unsigned char key;
    // register: SI
    // size: 2
    int page;
    // stack: [BP-4]
    // size: 2
    int quit;
    // stack: [BP-6]
    // size: 2
    int capg;
    // stack: [BP-8]
    // size: 2
    int cvpg;
    // stack: [BP-12]
    // size: 4
    long gametimer;
}

// module: MENUS
// size: 0x246
// addr: 05E0:3743
int play_menu(void)
{
    // stack: [BP-1]
    // size: 1
    signed char select;
    // register: SI
    // size: 2
    int exitcode;
    // register: DI
    // size: 2
    int i;
    // stack: [BP-4]
    // size: 2
    int capg;
    // stack: [BP-6]
    // size: 2
    int cvpg;
}

// module: MENUS
// size: 0x5b9
// addr: 05E0:39A0
int do_eval(int didit, int tra, int trf, int mnstrs, int mnstrhts)
{
    // register: DI
    // size: 2
    // int didit;
    // register: SI
    // size: 2
    int y;
    // stack: [BP-2]
    // size: 2
    int gottime;
    // stack: [BP-4]
    // size: 2
    unsigned int yt;
    // stack: [BP-8]
    // size: 4
    long bonus;
    // stack: [BP-12]
    // size: 4
    float pcnt;
}

// module: MENUS
// size: 0x102
// addr: 05E0:3F59
void do_winscrn1(void)
{
}
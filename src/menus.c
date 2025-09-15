#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "common.h"
#include "joystick.h"
#include "gr.h"
#include "hocus.h"
#include "fileio.h"
#include "menus.h"
#include "util.h"
#include "soundfx.h"

// addr: 192E:0A34
// size: 72
unsigned int time2beat[GAME_COUNT][LEVEL_COUNT] = {
    {0x78, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9},
    {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9},
    {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9},
    {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9}};

// addr: 192E:0A7C
// size: 2
int icon_frame = 0;

// addr: 192E:0A7E
// size: 2
int riconpos = 0;

// addr: 192E:0A80
// size: 2
int siconpos = 0;

// addr: 192E:0A82
// size: 36
unsigned char *footers[9] = {
    "Use UP/DOWN/LETTER to move - RETURN to select",
    "Use UP/DOWN/LETTER to move - RETURN to select",
    "Press any key to continue",
    "Press Y for yes - N for no - ESC to exit",
    "Use UP/DOWN/NUMBER to move - RETURN to select",
    "ESC to exit",
    "Enter name then press RETURN",
    "Press LETTER to select - ESC to exit",
    "Use UP/DOWN to move - RETURN to select"};

// addr: 192E:0AA6
// size: 2
int mainmenuip = 0;

// addr: 192E:0AA8
// size: 40
unsigned char *mainmenu[10] = {
    "Begin a new voyage!",
    "Change game options",
    "Restore an old game",
    "Instructions",
    "Legends and hints!",
    "Demonstration!",
    "High scores",
    "Preview future levels",
    "Ordering Information",
    "Quit - return to DOS"};

// addr: 192E:0AD0
// size: 2
int beginmenuip = 0;

// addr: 192E:0AD2
// size: 20
unsigned char *beginmenu[5] = {
    "Which game do you want to play?",
    "Time Tripping",
    "Shattered Worlds",
    "Warped and Weary",
    "Destination Home"};

// addr: 192E:0AE6
// size: 2
int gameopmenuip = 0;

// addr: 192E:0AE8
// size: 16
unsigned char *gameopmenu[4] = {
    "Sound is now off",
    "Music is now off",
    "Joystick is now off",
    "Define key controls"};

// addr: 192E:0AF8
// size: 2
int levelmenuip = 0;

// addr: 192E:0AFA
// size: 40
unsigned char *levelmenu[10] = {
    "Which level do you want to play?",
    "1) Level #1",
    "2) Level #2",
    "3) Level #3",
    "4) Level #4",
    "5) Level #5",
    "6) Level #6",
    "7) Level #7",
    "8) Level #8",
    "9) Boss Level!"};

// addr: 192E:0B22
// size: 2
int skillmenuip = 1;

// addr: 192E:0B24
// size: 16
unsigned char *skillmenu[4] = {
    "Choose a skill level",
    "Easy game - good for beginners",
    "Moderate - a resonable challenge",
    "Hard - the ultimate battle!"};

// addr: 192E:0B34
// size: 28
unsigned char *playmenu[7] = {
    "How to play Hocus Pocus",
    "Trapped! - restart level",
    "Save this game",
    "Restore an old game",
    "Change game options",
    "Back to the action!",
    "Quit to Main Menu"};

// addr: 192E:0B50
// size: 32
unsigned char *keymenu[8] = {
    "Left",
    "Right",
    "Jump",
    "Fire",
    "Up",
    "Down",
    "Scroll up",
    "Scroll down"};

// addr: 192E:0B70
// size: 4
int *colortextbase = (int *)0xb8000000;

// addr: 192E:0B74
// size: 18
int colors[9] = {
    192, 200, 208, 216, 224, 232, 112, 104, 208};

// addr: 192E:0B86
// size: 2
int mjoywait = 0;

// module: MENUS
// size: 0x84
// addr: 05E0:000D
int get_menu_joystick(void)
{
    // register: SI
    // size: 2
    int exitcode;

    exitcode = 0;
    if (game_config.joystick != 0)
    {
        if (mjoywait == 0)
        {
            JoyX = JoyY = button1 = button2 = 0;
            JOY_PollButtons();
            JOY_PollMovement();
            if (JoyX == 0x32)
            {
                exitcode = 4;
            }
            if (JoyX == -50)
            {
                exitcode = 5;
            }
            if (JoyY == -50)
            {
                exitcode = 1;
            }
            if (JoyY == 0x32)
            {
                exitcode = 2;
            }
            if ((button1 != 0) || (button2 != 0))
            {
                exitcode = 3;
            }
            if (exitcode != 0)
            {
                mjoywait = 0xf;
            }
            else
            {
                mjoywait = 0;
            }
        }
        else
        {
            mjoywait--;
        }
    }
    return exitcode;
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

    xc = (icon_frame / 5) * 4;
    latches(1);
    enable_pixels(0xf);
    for (yc = 0; yc < 0xf; yc++)
    {
        for (xx = 0; xx < 4; xx++)
        {
            ((line_t)vgap[0])[yc + y][x + xx] = ((line_t)vgap[3])[yc + 0xb4][xc + xx];
        }
    }
    latches(0);
    icon_frame++;
    if (icon_frame >= 0x28)
    {
        icon_frame = 0;
    }
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

    for (i = 0; i < 0x4b; i++)
    {
        x = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][0]) / 1000000) + 0xA0;
        y = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][1]) / 1000000) + 0x70;

        if (pixel_clr(x, y) >= 0xf0)
        {
            pixel(x, y, 0);
        }
        star_rad[i] += star_radplus[i];
        star_clrcnt[i] += star_clrplus[i];

        if (star_clrcnt[i] > 0x7F)
        {
            star_clrcnt[i] = 0x7F;
        }

        x = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][0]) / 1000000) + 0xA0;
        y = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][1]) / 1000000) + 0x70;

        if (x < 0 | x > 0x13f | y < 0 | y > 199)
        {
            do
            {
                star_deg[i] = (((long int)rand() * 0x168) / 0x8000);
                star_rad[i] = (((long int)rand() * 0xA0) / 0x8000);
                x = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][0]) / 1000000) + 0xA0;
                y = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][1]) / 1000000) + 0x70;
            } while ((x < 0) | (x > 0x13f) | (y < 0) | (y > 199));
            star_radplus[i] = (((long int)rand() * 5) / 0x8000) + 1;
            star_clrcnt[i] = 0;
            star_clrplus[i] = (((long int)rand() * 5) / 0x8000) + 1;
        }
        if (pixel_clr(x, y) == 0)
        {
            pixel(x, y, (star_clrcnt[i] >> 3) + 0xf0);
        }
    }
    wait_for_retrace();
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

    srand(time(0));
    for (i = 0; i < 0x4b; i++)
    {
        do
        {
            star_deg[i] = (((long int)rand() * 0x168) / 0x8000);
            star_rad[i] = (((long int)rand() * 0xA0) / 0x8000);
            x = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][0]) / 1000000) + 0xA0;
            y = ((star_rad[i] * l_sine_cosine_table[star_deg[i]][1]) / 1000000) + 0x70;
        } while ((x < 0) | (x > 0x13f) | (y < 0) | (y > 199));
        star_radplus[i] = (((long int)rand() * 5) / 0x8000) + 1;
        star_clrcnt[i] = 0;
        star_clrplus[i] = (((long int)rand() * 5) / 0x8000) + 1;
    }
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

    latches(0);
    outportb(0x3c4, 2);
    while (*str != '\0')
    {
        ch = *str;
        if ((ch >= '!') && (ch <= 'z'))
        {
            ch += 0xDF;
            maxx = 0;
            ofs = y * VGA_PLANE_WIDTH + (x >> VGA_PLANE_SHIFT);
            for (py = 0; py < 8; py++)
            {
                c = *(font + ch * 8 + py);
                s = c;
                for (px = 0; px < 8; px++)
                {
                    if (((c & 1) != 0) && (px > maxx))
                    {
                        maxx = px;
                    }
                    c >>= 1;
                }
                shift = x % 4;
                word = s;
                word <<= 8;
                word >>= (4 - shift);
                outportb(0x3c5, word >> 4);
                *(vga + ofs) = color;
                outportb(0x3c5, word >> 8);
                *(vga + ofs + 1) = color;
                outportb(0x3c5, word >> 12);
                *(vga + ofs + 2) = color;
                ofs += VGA_PLANE_WIDTH;
            }
            x += (maxx + 2);
        }
        else
        {
            if (ch == 0x20)
            {
                x += 4;
            }
        }
        str++;
    }
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

    outportb(0x3c4, 2);
    while (*str != '\0')
    {
        ch = *str;
        if ((ch >= '!') && (ch <= 'z'))
        {
            ch += 0xDF;
            maxx = 0;
            ofs = y * VGA_PLANE_WIDTH + (x >> VGA_PLANE_SHIFT);
            for (py = 0; py < 8; py++)
            {
                c = *(font + ch * 8 + py);
                s = c;
                for (px = 0; px < 8; px++)
                {
                    if (((c & 1) != 0) && (px > maxx))
                    {
                        maxx = px;
                    }
                    c >>= 1;
                }
                shift = x % 4;
                word = s;
                word <<= 8;
                word >>= (4 - shift);
                outportb(0x3c5, word >> 4);
                *(vga + ofs) = clr;
                outportb(0x3c5, word >> 8);
                *(vga + ofs + 1) = clr;
                outportb(0x3c5, word >> 12);
                *(vga + ofs + 2) = clr;
                ofs += VGA_PLANE_WIDTH;
            }
            x += (maxx + 2);
        }
        else
        {
            if (ch == 0x20)
            {
                x += 4;
            }
        }
        str++;
    }
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

    latches(0);
    outportb(0x3c4, 2);
    if (color == 0)
    {
        black = 1;
    }
    else
    {
        black = 0;
        color--;
    }
    while (*str != '\0')
    {
        ch = *str;
        if ((ch >= '!') && (ch <= 'z'))
        {
            ch += 0xDF;
            maxx = 0;
            ofs = y * VGA_PLANE_WIDTH + (x >> VGA_PLANE_SHIFT);
            for (py = 0; py < 8; py++)
            {
                if (black != 0)
                {
                    clr = 0x80;
                }
                else
                {
                    clr = colors[color] + py;
                }
                c = *(font + ch * 8 + py);
                s = c;
                for (px = 0; px < 8; px++)
                {
                    if (((c & 1) != 0) && (px > maxx))
                    {
                        maxx = px;
                    }
                    c >>= 1;
                }
                shift = x % 4;
                word = s;
                word <<= 8;
                word >>= (4 - shift);
                outportb(0x3c5, word >> 4);
                *(vga + ofs) = clr;
                outportb(0x3c5, word >> 8);
                *(vga + ofs + 1) = clr;
                outportb(0x3c5, word >> 12);
                *(vga + ofs + 2) = clr;
                ofs += VGA_PLANE_WIDTH;
            }
            x += (maxx + 2);
        }
        else
        {
            if (ch == 0x20)
            {
                x += 4;
            }
        }
        str++;
    }
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
    int x = 0;

    while (*str != '\0')
    {
        ch = *str;
        if ((ch >= '!') && (ch <= 'z'))
        {
            ch += 0xDF;
            maxx = 0;
            for (py = 0; py < 8; py++)
            {
                c = *(font + ch * 8 + py);
                for (px = 0; px < 8; px++)
                {
                    if (((c & 1) != 0) && (px > maxx))
                    {
                        maxx = px;
                    }
                    c >>= 1;
                }
            }
            x += (maxx + 2);
        }
        else
        {
            if (ch == 0x20)
            {
                x += 4;
            }
        }
        str++;
    }
    return x;
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

    strcpy(dummy, str);
    dummy[1] = 0;
    pstr(x, y, nc, str);
    pstr(x, y, hc, dummy);
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

    pstr(x + 1, y + 1, 0, str);
    pstr(x, y, c, str);
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

    pstrs(x + 1, y, 0xfe, str);
    pstrs(x - 1, y, 0xfe, str);
    pstrs(x, y + 1, 0xfe, str);
    pstrs(x, y - 1, 0xfe, str);
    pstr(x, y, c, str);
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
    pstrs(x + 1, y, 1, str);
    pstrs(x - 1, y, 1, str);
    pstrs(x, y + 1, 1, str);
    pstrs(x, y - 1, 1, str);
    pstr(x, y, c, str);
}

// module: MENUS
// size: 0x58
// addr: 05E0:0BB0
void ptstr(int x, int y, int fc, int bc, int len, unsigned char *str)
{
    // register: SI
    // size: 2
    register unsigned int i;
    // register: DI
    // size: 2
    register unsigned int tb;

    i = y * VGA_PLANE_WIDTH + x;
    tb = (bc << 4 | fc) << 8;
    while ((*str != '\0') && (len-- != 0))
    {
        textbase[i] = tb | *str;
        str++;
        i++;
    }
}

// module: MENUS
// size: 0x1c
// addr: 05E0:0C08
void clrtscrn(void)
{
    setmem(textbase, 4000, 0);
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
    register unsigned int to;
    // register: SI
    // size: 2
    register unsigned int x;

    tb = (bc << 4 | fc) << 8;
    to = ty * VGA_PLANE_WIDTH;
    while (ty <= by)
    {
        for (x = lx; x <= rx; x++)
        {
            *(textbase + to + x) = tb;
        }
        ty++;
        to += VGA_PLANE_WIDTH;
    }
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

    gmenunum = menunum;
    if (menunum == 0)
    {
        for (i = 0; i < 10; i++)
        {
            menu_item_labels[i] = mainmenu[i];
        }
        menu_item_num = 10;
        menu_footer = 0;
        menu_first_title = 0;
        siconpos = mainmenuip;
    }
    if (menunum == 2)
    {
        for (i = 0; i < 4; i++)
        {
            menu_item_labels[i] = gameopmenu[i];
        }
        menu_item_num = 4;
        menu_footer = 1;
        menu_first_title = 0;
        strcpy(menu_item_labels[0], "Sound is now ");
        if (game_config.soundfx)
        {
            strcat(menu_item_labels[0], "on ");
        }
        else
        {
            strcat(menu_item_labels[0], "off");
        }
        strcpy(menu_item_labels[1], "Music is now ");
        if (game_config.music)
        {
            strcat(menu_item_labels[1], "on ");
        }
        else
        {
            strcat(menu_item_labels[1], "off");
        }
        strcpy(menu_item_labels[2], "Joystick is now ");
        if (game_config.joystick)
        {
            strcat(menu_item_labels[2], "on ");
        }
        else
        {
            strcat(menu_item_labels[2], "off");
        }
        siconpos = gameopmenuip;
    }
    if (menunum == 1)
    {
        for (i = 0; i < 5; i++)
        {
            menu_item_labels[i] = beginmenu[i];
        }
        menu_item_num = 5;
        menu_footer = 1;
        menu_first_title = 1;
        siconpos = beginmenuip;
    }
    if (menunum == 3)
    {
        for (i = 0; i < 10; i++)
        {
            menu_item_labels[i] = levelmenu[i];
        }
        menu_item_num = 10;
        menu_footer = 1;
        menu_first_title = 1;
        siconpos = levelmenuip;
    }
    if (menunum == 4)
    {
        for (i = 0; i < 4; i++)
        {
            menu_item_labels[i] = skillmenu[i];
        }
        menu_item_num = 4;
        menu_footer = 1;
        menu_first_title = 1;
        siconpos = skillmenuip;
    }
    if (menunum == 5)
    {
        for (i = 0; i < 7; i++)
        {
            menu_item_labels[i] = playmenu[i];
        }
        menu_item_num = 7;
        menu_footer = 1;
        menu_first_title = 0;
        siconpos = playmenuip;
    }
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    x = pstrlen(msg);
    x = (SCREEN_WIDTH - x) / 2;
    y = 107;
    pstr(x, y, 5, msg);
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[fn])) / 2, 0xbc, 4, footers[fn]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    fade_in(0x14);
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    x = pstrlen(tit);
    x = (SCREEN_WIDTH - x) / 2;
    y = 0x61;
    pstr(x, y, 5, tit);
    x = pstrlen(msg);
    x = (SCREEN_WIDTH - x) / 2;
    pstr(x, y + 0x14, 3, msg);
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[fn])) / 2, 0xbc, 4, footers[fn]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    fade_in(0x14);
}

// module: MENUS
// size: 0x81
// addr: 05E0:1096
unsigned char get_any_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;

    while (kbhit() != 0)
    {
        getch();
    }
    do
    {
        key = get_menu_joystick();
        if (key == 3)
        {
            fade_out(0x14);
            return 0;
        }
        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            else
            {
                key = toupper(key);
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    return 0xff;
                }
            }
            fade_out(0x14);
            return 0;
        }
        update_stars();
    } while (1);
}

// module: MENUS
// size: 0x7f
// addr: 05E0:1117
unsigned char get_yesno_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;

    while (kbhit() != 0)
    {
        getch();
    }
    do
    {
        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            else
            {
                key = toupper(key);
                if ((key == 'Y') || (key == 'N'))
                {
                    fade_out(0x14);
                    return key;
                }
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    return 0xff;
                }
            }
        }
        update_stars();
    } while (1);
}

// module: MENUS
// size: 0x81
// addr: 05E0:1196
unsigned char get_number_key(void)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;

    while (kbhit() != 0)
    {
        getch();
    }
    do
    {
        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            else
            {
                key = toupper(key);
                if ((key >= '1') && (key <= '9'))
                {
                    fade_out(0x14);
                    return key - '1';
                }
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    return 0xff;
                }
            }
        }
        update_stars();
    } while (1);
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x48;
    strcpy(dline, "Select new key for: ");
    strcat(dline, keymenu[kn]);
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 5, dline);
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[7])) / 2, 0xbc, 4, footers[7]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    for (i = 0; i < 6; i++)
    {
        x = 0x1B;
        strcpy(dline, " ");
        dline[0] = i + 'A';
        pstr(x, y, 4, dline);
        pstr(x + 0xa, y, 2, "-");
        pstr(x + 0x14, y, 2, key_label[i]);
        x = 0x7d;
        strcpy(dline, " ");
        dline[0] = i + 'G';
        pstr(x, y, 4, dline);
        pstr(x + 0xa, y, 2, "-");
        pstr(x + 0x14, y, 2, key_label[i + 6]);
        x = 0xc8;
        strcpy(dline, " ");
        dline[0] = i + 'M';
        pstr(x, y, 4, dline);
        pstr(x + 0xa, y, 2, "-");
        pstr(x + 0x14, y, 2, key_label[i + 12]);
        y += 0xa;
    }
    fade_in(0x14);
    while (kbhit() != 0)
    {
        getch();
    }
    do
    {
        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            else
            {
                key = toupper(key);
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    return;
                }
                if ((key >= 'A') && (key <= 'R'))
                {
                    pc_key[kn] = key + 0xBF;
                    fade_out(0x14);
                    return;
                }
            }
        }
        update_stars();
    } while (1);
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

start:
    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x3e;
    pstr((SCREEN_WIDTH - pstrlen("Select a key to define")) / 2, y, 5, "Select a key to define");
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[7])) / 2, 0xbc, 4, footers[7]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    for (i = 0; i < 8; i++)
    {
        strcpy(dline, " ");
        dline[0] = i + 'A';
        pstr(0x46, y, 4, dline);
        pstr(0x50, y, 2, "-");
        pstr(0x5a, y, 2, keymenu[i]);
        pstr((0xfa - pstrlen(key_label[pc_key[i]])), y, 3, key_label[pc_key[i]]);
        y += 0xa;
    }
    fade_in(0x14);
    while (kbhit() != 0)
    {
        getch();
    }
    do
    {
        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            else
            {
                key = toupper(key);
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    return;
                }
                if ((key >= 'A') && (key <= 'H'))
                {
                    fade_out(0x14);
                    do_def_menu(key - 'A');
                    goto start;
                }
            }
        }
        update_stars();
    } while (1);
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    if (menu_first_title != 0)
    {
        s = 1;
    }
    else
    {
        s = 0;
    }

    x = 0;
    for (i = s; i < menu_item_num; i++)
    {
        y = pstrlen(menu_item_labels[i]);
        if (y > x)
        {
            x = y;
        }
    }
    x = (SCREEN_WIDTH - x) / 2;
    if (menu_first_title != 0)
    {
        y = ((0x90 - ((menu_item_num + 1) * 10)) / 2) + 0x28;
        pstr((SCREEN_WIDTH - pstrlen(menu_item_labels[0])) / 2, y, 5, menu_item_labels[0]);
        y += 0x14;
    }
    else
    {
        y = ((0x90 - (menu_item_num * 10)) / 2) + 0x28;
    }
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[menu_footer])) / 2, 0xbc, 4, footers[menu_footer]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    iconx = (x - 0x18) / 4;
    iconpos = 0;
    for (i = s; i < menu_item_num; i++)
    {
        pstr_hilite(x, y, 4, 2, menu_item_labels[i]);
        icony[iconpos] = y - 4;
        iconpos++;
        y += 10;
    }
    iconmax = iconpos;
    iconpos = 0;
    fade_in(0x14);
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

    for (i = 0; i < 5; i++)
    {
        if (game_config.hiscore[g][i] < s)
        {
            for (j = 3; j >= i; j--)
            {
                strcpy(game_config.hname[g][j + 1], game_config.hname[g][j]);
                game_config.hiscore[g][j + 1] = game_config.hiscore[g][j];
            }
            strcpy(game_config.hname[g][i], "");
            game_config.hiscore[g][i] = s;
            return i + 1;
        }
    }
    return 0;
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x48;
    strcpy(dline, "High Scores For Game ");
    strcat(dline, itoa(g + 1, dumnum, 10));
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 5, dline);
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[6])) / 2, 0xbc, 4, footers[6]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    for (i = 0; i < 5; i++)
    {
        s = 3;
        if (i == 0)
        {
            s = 4;
        }
        x = 0x1B;
        pstr(x, y, s, game_config.hname[g][i]);
        strcpy(dline, ltoa(game_config.hiscore[g][i], dumnum, 10));
        pstr((0x122 - pstrlen(dline)), y, s, dline);
        if (i == slot)
        {
            sy = y;
            sclr = s;
        }
        y += 10;
        if (i == 0)
        {
            y += 10;
        }
    }
    fade_in(0x14);
    key = 0;
    strcpy(dumnum, " ");
    while (kbhit() != 0)
    {
        getch();
    }

    while (key != KEY_RETURN)
    {
        pstr(0x1b, sy, sclr, game_config.hname[g][slot]);
        i = strlen(game_config.hname[g][slot]);
        x = pstrlen(game_config.hname[g][slot]) + 0x1b;
        dumnum[0] = 0x5f;
        pstr(x, sy, 2, dumnum);
        do
        {
            if (kbhit() != 0)
            {
                key = getch();
                if (!key)
                {
                    getch();
                }
                else
                {
                    if ((key >= KEY_SPACE) && (key <= 'z') && (i < 0x19))
                    {
                        blankpixelbox(x, sy, x + 10, sy + 9);
                        game_config.hname[g][slot][i] = key;
                        i++;
                        game_config.hname[g][slot][i] = 0;
                        break;
                    }
                    if ((key == 8) && (i != 0))
                    {
                        blankpixelbox(x, sy, x + 10, sy + 9);
                        y = pstrlen(game_config.hname[g][slot]) + 0x1b;
                        i--;
                        game_config.hname[g][slot][i] = 0;
                        x = pstrlen(game_config.hname[g][slot]) + 0x1b;
                        blankpixelbox(x, sy, y, sy + 9);
                        break;
                    }
                    if (key == KEY_RETURN)
                    {
                        break;
                    }
                }
            }
            update_stars();
        } while (1);
    }
    save_file_from_byte_pointer(1, &game_config);
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

    g = 0;
    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x48;
    strcpy(dline, "High Scores For Game ");
    strcat(dline, itoa(g + 1, dumnum, 10));
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 5, dline);
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[2])) / 2, 0xbc, 4, footers[2]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    for (i = 0; i < 5; i++)
    {
        s = 3;
        if (i == 0)
        {
            s = 4;
        }
        x = 0x1B;
        pstr(x, y, s, game_config.hname[g][i]);
        strcpy(dline, ltoa(game_config.hiscore[g][i], dumnum, 10));
        pstr((0x122 - pstrlen(dline)), y, s, dline);
        y += 10;
        if (i == 0)
        {
            y += 10;
        }
    }
    fade_in(0x14);
    if (demomode == 0)
    {
        k = get_any_key();
        if (k == -1)
        {
            return;
        }
    }
    else
    {
        counter = clk_times;
        while ((clk_times - counter < 0x9c4) && kbhit() == 0)
        {
            update_stars();
        }

        if (kbhit() != 0)
        {
            while (kbhit() != 0)
            {
                getch();
            }
            return;
        }
    }
}

// module: MENUS
// size: 0x3d
// addr: 05E0:1F5D
void record_iconpos(void)
{
    switch (gmenunum)
    {
    case 0:
        mainmenuip = iconpos;
        break;
    case 2:
        gameopmenuip = iconpos;
        break;
    case 1:
        beginmenuip = iconpos;
        break;
    case 3:
        levelmenuip = iconpos;
        break;
    case 5:
        playmenuip = iconpos;
        break;
    }
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

    t = 0;
    counter = clk_times;
    iconpos = siconpos;
    while (kbhit() != 0)
    {
        getch();
    }
    if (menu_first_title != 0)
    {
        s = 1;
    }
    else
    {
        s = 0;
    }

    do
    {
        key = get_menu_joystick();
        if (key == 1)
        {
            key = KEY_UP;
            goto label1;
        }

        if (key == 2)
        {
            key = KEY_DOWN;
            goto label1;
        }

        if (key == 3)
        {
            key = KEY_RETURN;
            goto label2;
        }

        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                key = getch();
            label1:
                if (key == KEY_UP)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos--;
                    if (iconpos < 0)
                    {
                        iconpos = iconmax - 1;
                    }
                    record_iconpos();
                }
                if (key == KEY_DOWN)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos++;
                    if (iconpos >= iconmax)
                    {
                        iconpos = 0;
                    }
                    record_iconpos();
                }
                key = 0;
            }
            else
            {
                key = toupper(key);
                for (i = s; i < menu_item_num; i++)
                {
                    if (menu_item_labels[i][0] == key)
                    {
                        blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                        iconpos = i - s;
                        record_iconpos();
                    }
                }
            label2:
                if (key == KEY_RETURN)
                {
                    fade_out(0x14);
                    return iconpos;
                }
                if ((key == KEY_ESCAPE) && (menu_footer != 0) && (menu_footer != 3))
                {
                    fade_out(0x14);
                    return 0xff;
                }
            }
        }
        update_icon(iconx, icony[iconpos]);
        update_stars();
        if ((ismain != 0) && (clk_times - counter > 0x445C))
        {
            if (t == 0)
            {
                do_credits();
                load_menu(0);
                do_menu();
                counter = clk_times;
                t = 1;
            }
            else
            {
                fade_out(0x14);
                return 5;
            }
        }
    } while (1);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:21FB
unsigned char do_main_menu(void)
{
    load_menu(0);
    do_menu();
    return get_menu_key(1);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2217
unsigned char do_begin_menu(void)
{
    load_menu(1);
    do_menu();
    return get_menu_key(0);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2233
unsigned char do_game_options(void)
{
    load_menu(2);
    do_menu();
    return get_menu_key(0);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:224F
unsigned char do_level_options(void)
{
    load_menu(3);
    do_menu();
    return get_menu_key(0);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:226B
unsigned char do_skill_options(void)
{
    load_menu(4);
    do_menu();
    return get_menu_key(0);
}

// module: MENUS
// size: 0x1c
// addr: 05E0:2287
unsigned char do_play_menu(void)
{
    load_menu(5);
    do_menu();
    return get_menu_key(0);
}

// module: MENUS
// size: 0x5c
// addr: 05E0:22A3
void do_message_menu(unsigned char *msg)
{
    // stack: [BP-1]
    // size: 1
    unsigned char key;

    do_line_menu(msg, 2);
    while (kbhit())
    {
        getch();
    }
    do
    {
        if (kbhit())
        {
            key = getch();
            if (!key)
            {
                getch();
            }
            fade_out(0x14);
            return;
        }
        update_stars();
    } while (1);
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

    exitcode = 0;
    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x3B;
    strcpy(dline, "Select SAVE slot");
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 5, dline);
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xB8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[4])) / 2, 0xbc, 4, footers[4]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    iconpos = 0;
    iconx = 4;
    for (i = 0; i < 9; i++)
    {
        x = 0x23;
        strcpy(dline, itoa(i + 1, dumnum, 10));
        pstr(x, y, 4, dline);
        x += 10;
        strcpy(dline, game_config.gname[i]);
        pstr(x, y, 3, dline);
        icony[iconpos] = y - 4;
        iconpos++;
        y += 10;
    }
    iconmax = iconpos;
    iconpos = siconpos;
    fade_in(0x14);
    key = 0;
    while (key != KEY_RETURN)
    {
        key = get_menu_joystick();
        if (key == 1)
        {
            key = KEY_UP;
            goto label1;
        }

        if (key == 2)
        {
            key = KEY_DOWN;
            goto label1;
        }

        if (key == 3)
        {
            key = KEY_RETURN;
            goto label2;
        }

        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                key = getch();
            label1:
                if (key == KEY_UP)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos--;
                    if (iconpos < 0)
                    {
                        iconpos = iconmax - 1;
                    }
                    siconpos = iconpos;
                }
                if (key == KEY_DOWN)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos++;
                    if (iconpos >= iconmax)
                    {
                        iconpos = 0;
                    }
                    siconpos = iconpos;
                }
            }
            else
            {
                if ((key >= '1') && (key <= '9'))
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos = key - 49;
                    siconpos = iconpos;
                }
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    goto exit;
                }
            label2:
                if (key == KEY_RETURN)
                {
                    gs = iconpos;
                    sy = icony[iconpos] + 4;
                    strcpy(savename, game_config.gname[gs]);
                    if (game_config.game[gs] == -1)
                    {
                        strcpy(game_config.gname[gs], "");
                        blankpixelbox(0x2d, sy, 0x13F, sy + 9);
                    }
                    lkey = 0;
                    strcpy(dumnum, " ");
                    while (kbhit())
                    {
                        getch();
                    }
                    while ((lkey != KEY_RETURN) && (lkey != KEY_ESCAPE))
                    {
                        pstr(0x2d, sy, 3, game_config.gname[gs]);
                        i = strlen(game_config.gname[gs]);
                        x = pstrlen(game_config.gname[gs]) + 0x2d;
                        dumnum[0] = '_';
                        pstr(x, sy, 2, dumnum);
                        do
                        {
                            if (kbhit() != 0)
                            {
                                lkey = getch();
                                if (!lkey)
                                {
                                    getch();
                                }
                                else
                                {
                                    if ((lkey >= KEY_SPACE) && (lkey <= 'z') && (i < 0x19))
                                    {
                                        blankpixelbox(x, sy, x + 10, sy + 9);
                                        game_config.gname[gs][i] = lkey;
                                        i++;
                                        game_config.gname[gs][i] = '\0';
                                        break;
                                    }
                                    if ((lkey == 8) && (i != 0))
                                    {
                                        blankpixelbox(x, sy, x + 10, sy + 9);
                                        y = pstrlen(game_config.gname[gs]) + 0x2d;
                                        i--;
                                        game_config.gname[gs][i] = '\0';
                                        x = pstrlen(game_config.gname[gs]) + 0x2d;
                                        blankpixelbox(x, sy, y, sy + 9);
                                        break;
                                    }
                                    if ((lkey == KEY_RETURN))
                                    {
                                        break;
                                    }
                                    if ((lkey == KEY_ESCAPE))
                                    {
                                        strcpy(game_config.gname[gs], savename);
                                        blankpixelbox(0x2d, sy, 0x13f, sy + 9);
                                        pstr(0x2d, sy, 3, game_config.gname[gs]);
                                        key = 0;
                                        break;
                                    }
                                }
                            }
                            update_icon(iconx, icony[iconpos]);
                            update_stars();
                        } while (1);
                    }
                }
            }
        }
        update_icon(iconx, icony[iconpos]);
        update_stars();
    }
    if (key == KEY_RETURN)
    {
        game_config.game[gs] = game;
        game_config.level[gs] = level;
        game_config.skill[gs] = skill;
        game_config.score[gs] = score;
        save_file_from_byte_pointer(1, &game_config);
        exitcode = 1;
        fade_out(0x14);
    }
exit:
    return exitcode;
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

    exitcode = 0;
    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    y = 0x3B;
    strcpy(dline, "Select RESTORE slot");
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 5, dline);
    y += 0x14;
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xB8);
    pstrsh((SCREEN_WIDTH - pstrlen(footers[4])) / 2, 0xbc, 4, footers[4]);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    iconpos = 0;
    iconx = 4;
    for (i = 0; i < 9; i++)
    {
        x = 0x23;
        strcpy(dline, itoa(i + 1, dumnum, 10));
        pstr(x, y, 4, dline);
        x += 10;
        strcpy(dline, game_config.gname[i]);
        pstr(x, y, 3, dline);
        icony[iconpos] = y - 4;
        iconpos++;
        y += 10;
    }
    iconmax = iconpos;
    iconpos = riconpos;
    fade_in(0x14);
    key = 0;
    while (key != KEY_RETURN)
    {
        key = get_menu_joystick();
        if (key == 1)
        {
            key = KEY_UP;
            goto label1;
        }

        if (key == 2)
        {
            key = KEY_DOWN;
            goto label1;
        }

        if (key == 3)
        {
            key = KEY_RETURN;
            goto label2;
        }

        if (kbhit() != 0)
        {
            key = getch();
            if (!key)
            {
                key = getch();
            label1:
                if (key == KEY_UP)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos--;
                    if (iconpos < 0)
                    {
                        iconpos = iconmax - 1;
                    }
                    riconpos = iconpos;
                }
                if (key == KEY_DOWN)
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos++;
                    if (iconpos >= iconmax)
                    {
                        iconpos = 0;
                    }
                    riconpos = iconpos;
                }
            }
            else
            {
                if ((key >= '1') && (key <= '9'))
                {
                    blankpixelbox(iconx * 4, icony[iconpos], iconx * 4 + 0xf, icony[iconpos] + 0xe);
                    iconpos = key - 49;
                    riconpos = iconpos;
                }
                if (key == KEY_ESCAPE)
                {
                    fade_out(0x14);
                    goto exit;
                }
            label2:
                if (key == KEY_RETURN)
                {
                    gs = iconpos;
                    if (game_config.game[gs] == -1)
                    {
                        key = 0;
                    }
                }
            }
        }
        update_icon(iconx, icony[iconpos]);
        update_stars();
    }
    if (key == KEY_RETURN)
    {
        load_file_to_byte_pointer(OFFSET_CONFIG, &game_config);
        game = game_config.game[gs];
        level = game_config.level[gs];
        skill = game_config.skill[gs];
        score = game_config.score[gs];
        exitcode = 1;
        fade_out(0x14);
    }
exit:
    return exitcode;
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

    exitcode = 0;
    do_title_line_menu("Reminder: Save your game before quitting", "Quit game?", 3);
    i = get_yesno_key();
    if ((i != -1) && (i != 'N'))
    {
        exitcode = 1;
    }
    return exitcode;
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

    exitcode = 0;
    (void)exitcode;
    while (kbhit())
    {
        getch();
    }
    do_line_menu("Move joystick to upper left and press button 0", 5);
    do
    {
        jb = JOY_Buttons();
        update_stars();
        if (kbhit() && getch() == KEY_ESCAPE)
        {
            return 0;
        }
    } while ((jb & 1) == 0);
    JOY_GetPosition(joystickport, &xmin, &ymin);
    fade_out(0x14);
    while (kbhit())
    {
        getch();
    }
    do_line_menu("Move joystick to lower right and press button 1", 5);
    do
    {
        jb = JOY_Buttons();
        update_stars();
        if (kbhit() && getch() == KEY_ESCAPE)
        {
            return 0;
        }
    } while ((jb & 2) == 0);
    JOY_GetPosition(joystickport, &xmax, &ymax);
    fade_out(0x14);
    while (JOY_Buttons())
        ;
    game_config.jxmin = xmin;
    game_config.jxmax = xmax;
    game_config.jymin = ymin;
    game_config.jymax = ymax;
    if ((xmin != xmax) && (ymin != ymax))
    {
        JOY_SetUp(joystickport, xmin, xmax, ymin, ymax);
    }
    else
    {
        return 0;
    }
    return 1;
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

    disable_key_handler();
    capg = apg;
    cvpg = vpg;
    fade_out(0x14);
    MCPY(savepalette, palette, sizeof(palette));
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    calibrate_joystick();
    MCPY(palette, savepalette, sizeof(palette));
    scopy(0, 1);
    setvpage(cvpg);
    setapage(capg);
    fade_in(1);
    install_key_handler();
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

    disable_key_handler();
    capg = apg;
    cvpg = vpg;
    fade_out(0x14);
    MCPY(savepalette, palette, sizeof(palette));
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    save_game();
    MCPY(palette, savepalette, sizeof(palette));
    scopy(0, 1);
    setvpage(cvpg);
    setapage(capg);
    fade_in(1);
    install_key_handler();
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

    disable_key_handler();
    capg = apg;
    cvpg = vpg;
    fade_out(0x14);
    MCPY(savepalette, palette, sizeof(palette));
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    exitcode = restore_game();
    if (exitcode == 0)
    {
        MCPY(palette, savepalette, sizeof(palette));
        scopy(0, 1);
        setvpage(cvpg);
        setapage(capg);
        fade_in(1);
    }
    else
    {
        clearscreen();
    }
    install_key_handler();
    return exitcode;
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

    disable_key_handler();
    capg = apg;
    cvpg = vpg;
    fade_out(0x14);
    MCPY(savepalette, palette, sizeof(palette));
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    exitcode = confirm_quit();
    if (exitcode == 0)
    {
        MCPY(palette, savepalette, sizeof(palette));
        scopy(0, 1);
        setvpage(cvpg);
        setapage(capg);
        fade_in(1);
    }
    else
    {
        clearscreen();
    }
    install_key_handler();
    return exitcode;
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

    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xb8);
    if (limit == 1)
    {
        strcpy(dline, footers[2]);
    }
    else
    {
        strcpy(dline, "Page ");
        strcat(dline, itoa(page + 1, dummy, 10));
        strcat(dline, " of ");
        strcat(dline, itoa(limit, dummy, 10));
        if (page == 0)
        {
            strcat(dline, " - Press PGDN - ESC to cancel");
        }
        else
        {
            if (limit - 1 == page)
            {
                strcat(dline, " - Press PGUP - ESC to cancel");
            }
            else
            {
                strcat(dline, " - Press PGUP/PGDN - ESC to cancel");
            }
        }
    }
    pstrsh((SCREEN_WIDTH - pstrlen(dline)) / 2, 0xbc, 4, dline);
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);

    for (i = 0, y = 0; i < inf.num; i++)
    {
        if (strlen(inf.lines[i]) == 0)
        {
            y += inf.bspacing;
        }
        else
        {
            y += inf.lspacing;
        }
    }
    y = ((0x90 - y) / 2) + 0x28;
    for (i = 0; i < inf.num; i++)
    {
        pstr((SCREEN_WIDTH - pstrlen(inf.lines[i])) / 2, y, inf.attrb[i * 2 + 1], inf.lines[i]);
        if (strlen(inf.lines[i]) == 0)
        {
            y += inf.bspacing;
        }
        else
        {
            y += inf.lspacing;
        }
    }
    fade_in(0x14);
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

    while (kbhit())
    {
        getch();
    }

    do
    {
        key = get_menu_joystick();
        if ((key == 1) || (key == 5))
        {
            key = KEY_PGUP;
            goto label;
        }
        if ((key == 2) || (key == 4))
        {
            key = KEY_PGDN;
            goto label;
        }
        if (kbhit())
        {
            key = getch();
            if (!key)
            {
                key = getch();
                if (limit == 1)
                {
                    page = -1;
                    break;
                }
            label:
                if ((key == KEY_PGUP) || (key == KEY_LEFT))
                {
                    if ((page != 0))
                    {
                        page--;
                        break;
                    }
                }
                if ((key == KEY_PGDN) || (key == KEY_RIGHT))
                {
                    if (limit - 1 > page)
                    {
                        page++;
                        break;
                    }
                }
                if ((key == KEY_HOME))
                {
                    if (page != 0)
                    {
                        page = 0;
                        break;
                    }
                }
                if ((key == KEY_END))
                {
                    if (limit - 1 > page)
                    {
                        page = limit - 1;
                        break;
                    }
                }
            }
            else if ((key == KEY_ESCAPE) || (limit == 1))
            {
                page = -1;
                break;
            }
        }
        update_stars();
    } while (1);
    fade_out(0x14);
    return page;
}

// module: MENUS
// size: 0x39
// addr: 05E0:339D
void do_ordering_info(void)
{
    // register: SI
    // size: 2
    int page;

    page = 0;
    do
    {
        load_file_to_byte_pointer(page + OFFSET_ORDER, &inf);
        do_info_screen(page, 0x16);
        page = get_page_key(page, 0x16);
    } while (page != -1);
}

// module: MENUS
// size: 0x27
// addr: 05E0:33D6
void do_cantplay_info(void)
{
    load_file_to_byte_pointer(OFFSET_REGISTER, &inf);
    do_info_screen(0, 1);
    get_any_key();
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

    page = 0;
    quit = 0;
    fade_out(0x14);

    while ((page < CREDIT_COUNT) && !quit)
    {
        load_pcx(page + OFFSET_CREDIT, 0);
        fade_in(0x14);
        gametimer = clk_times;
        while ((clk_times - gametimer) < 3000)
        {
            update_stars();
            if (kbhit() != 0)
            {
                quit = 1;
                break;
            }
            if (game_config.joystick != 0)
            {
                button1 = button2 = 0;
                JOY_PollButtons();
                if ((button1 != 0) || (button2 != 0))
                {
                    quit = 1;
                    break;
                }
            }
        }
        fade_out(0xf);
        while (kbhit() != 0)
        {
            getch();
        }
        page++;
    }
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
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

    for (page = 0; page < PREVIEW_COUNT; page++)
    {
        show_bin(page + OFFSET_PREVIEW);
        while (kbhit() != 0)
        {
            getch();
        }
        fade_in(0x14);
        do
        {
            key = get_menu_joystick();
            if (key == 3)
            {
                break;
            }
            if (kbhit() != 0)
            {
                key = getch();
                break;
            }
        } while (1);
        fade_out(0x14);
        while (kbhit() != 0)
        {
            getch();
        }
        if (key == KEY_ESCAPE)
        {
            break;
        }
    }
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
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

    if (insidegame != 0)
    {
        disable_key_handler();
        capg = apg;
        cvpg = vpg;
        fade_out(0x14);
        MCPY(savepalette, palette, sizeof(palette));
        clear_palette();
        restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
        restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
        clear_palette();
        setapage(0);
        clearscreen();
        setvpage(0);
    }

    if (game_config.joystick != 0)
    {
        page = 1;
    }
    else
    {
        page = 0;
    }
    quit = 0;
    (void)quit;
    while (page < HELP_COUNT)
    {
        load_pcx(page + OFFSET_HELP, 0);
        fade_in(0x14);
        gametimer = clk_times;
        (void)gametimer;
        key = 0;
        while (1)
        {
            update_stars();
            if (kbhit() != 0)
            {
                key = getch();
                break;
            }
            if (game_config.joystick != 0)
            {
                button1 = button2 = 0;
                JOY_PollButtons();
                if ((button1 != 0) || (button2 != 0))
                {
                    break;
                }
            }
        }

        fade_out(0xf);
        while (kbhit() != 0)
        {
            getch();
        }
        if (key == KEY_ESCAPE)
        {
            break;
        }
        page++;
        if (page == 1)
        {
            page = 2;
        }
    }

    if (insidegame != 0)
    {
        MCPY(palette, savepalette, sizeof(palette));
        scopy(0, 1);
        setvpage(cvpg);
        setapage(capg);
        fade_in(1);
        install_key_handler();
    }
    else
    {
        clear_palette();
        restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
        restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    }
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

    disable_key_handler();
    capg = apg;
    cvpg = vpg;
    fade_out(0x14);
    MCPY(savepalette, palette, sizeof(palette));
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
    exitcode = 0;
    select = 0;
    while (select != -1)
    {
        select = do_play_menu();
        switch (select)
        {
        case 0:
            do_help(0);
            break;
        case 1:
            exitcode = 1;
            goto exit;
            break;
        case 3:
            if (restore_game())
            {
                exitcode = 3;
            }
            else
            {
                exitcode = 0;
            }
            goto exit;
        case 2:
            save_game();
            exitcode = 0;
            goto exit;
            break;
        case 5:
            goto exit;
            break;
        case 4:
        label:
            if ((adlib == 0) && (blaster == 0))
            {
                game_config.music = 0;
            }
            select = do_game_options();
            switch (select)
            {
            case 0:
                if ((blaster != 0) && (game_config.soundfx == 0))
                {
                    game_config.soundfx = 1;
                }
                else if (blaster != 0)
                {
                    game_config.soundfx = 0;
                }
                else
                {
                    game_config.soundfx = !game_config.soundfx;
                }
                goto label;
            case 1:
                if ((adlib == 0) && (blaster == 0))
                {
                    game_config.music = 0;
                    do_message_menu("Music requires a sound card");
                }
                else
                {
                    game_config.music = !game_config.music;
                }
                if ((game_config.music == 0) && (adlib != 0))
                {
                    SD_MusicOff();
                }
                else
                {
                    play_imf_file(MUSIC_TITLE);
                }
                goto label;
            case 2:
                game_config.joystick = !game_config.joystick;
                if ((game_config.joystick != 0) && (!calibrate_joystick()))
                {
                    game_config.joystick = 0;
                }
                goto label;
            case 3:
                do_key_menu();
                for (i = 0; i < 8; i++)
                {
                    game_config.pckey[i] = pc_key[i];
                }
                break;
            }

            if ((adlib == 0) && (blaster == 0))
            {
                game_config.music = 0;
            }
            save_file_from_byte_pointer(1, &game_config);
            exitcode = 0;
            goto exit;
            break;

        case 6:
            if (confirm_quit())
            {
                exitcode = 2;
                goto exit;
            }
            break;
        }
    }
exit:
    if (exitcode == 0)
    {
        MCPY(palette, savepalette, sizeof(palette));
        scopy(0, 1);
        setvpage(cvpg);
        setapage(capg);
        fade_in(1);
    }
    else
    {
        clearscreen();
    }
    install_key_handler();
    return exitcode;
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

    (void)mnstrs;
    (void)mnstrhts;
    yt = total_ticks / 560;
    y = ((0x90 - ((didit * 0x28) + 0x40)) / 2) + 0x28;
    bonus = 0;
    clear_palette();
    setapage(0);
    clearscreen();
    setvpage(0);
    if (didit)
    {
        strcpy(dline, "Castle complete - congratulations!");
    }
    else
    {
        strcpy(dline, "Tough break - you'll get it next time!");
    }

    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 4, dline);
    y += 16;
    strcpy(dline, "Results for Level ");
    strcat(dline, itoa(level + 1, dumnum, 10));
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 2, dline);
    y += 0x18;
    strcpy(dline, "Treasures found: ");
    strcat(dline, itoa(trf, dumnum, 10));
    strcat(dline, "  Treasures available: ");
    strcat(dline, itoa(tra, dumnum, 10));
    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 3, dline);
    y += 16;
    if (trf == 0)
    {
        pcnt = 0.0;
    }
    else
    {
        pcnt = ((float)trf / (float)tra) * 100.0;
    }
    strcpy(dline, "Accuracy: ");
    strcat(dline, itoa(pcnt, dumnum, 10));
    strcat(dline, "%  ");
    if (didit)
    {
        if (pcnt >= 100.0)
        {
            if (skill == 0)
            {
                strcat(dline, "BONUS 25,000 points!");
                bonus += 25000;
            }
            if (skill == 1)
            {
                strcat(dline, "BONUS 50,000 points!");
                bonus += 50000;
            }
            if (skill >= 2)
            {
                strcat(dline, "BONUS 75,000 points!");
                bonus += 75000;
            }
        }
        else
        {
            strcat(dline, "Less than 100% - NO BONUS");
        }
    }
    else
    {
        strcat(dline, "Castle not complete");
    }

    pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 2, dline);
    y += 24;
    score += bonus;

    if (didit)
    {
        strcpy(dline, "Time to beat: ");
        strcat(dline, itoa(time2beat[game][level], dumnum, 10));
        strcat(dline, "  Your time: ");
        strcat(dline, itoa(yt, dumnum, 10));
        pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 3, dline);
        y += 16;
        gottime = 0;
        if (time2beat[game][level] > yt)
        {
            if (skill == 0)
            {
                strcpy(dline, "BONUS 25,000 points!");
                bonus += 25000;
            }
            if (skill == 1)
            {
                strcpy(dline, "BONUS 50,000 points!");
                bonus += 50000;
            }
            if (skill >= 2)
            {
                strcpy(dline, "BONUS 75,000 points!");
                bonus += 75000;
            }
            gottime = 1;
        }
        else
        {
            strcpy(dline, "Not fast enough - NO BONUS");
        }
        pstr((SCREEN_WIDTH - pstrlen(dline)) / 2, y, 2, dline);
        y += 24;
    }
    restore_graphics_fragment(OFFSET_BOTTOM, 0, 0xB8);
    pstrsh((SCREEN_WIDTH - pstrlen("Press any key")) / 2, 0xbc, 4, "Press any key");
    restore_graphics_fragment(OFFSET_HOCUS, 0, 0);
    fade_in(0x14);
    y = 0;
    while (kbhit() != 0)
    {
        getch();
    }
    if (game_config.joystick != 0)
    {
        do
        {
            button1 = button2 = 0;
            JOY_PollButtons();
            update_stars();
        } while ((button1 != 0) || (button2 != 0));
    }
    while (y == 0)
    {
        if (game_config.joystick != 0)
        {
            button1 = button2 = 0;
            JOY_PollButtons();
            if ((button1 != 0) || (button2 != 0))
            {
                y = 1;
            }
        }
        if (kbhit() != 0)
        {
            y = 1;
        }
        update_stars();
    }
    while (kbhit() != 0)
    {
        getch();
    }
    fade_out(0x14);
    if (((pcnt < 100.0) || (gottime == 0)) && (didit != 0))
    {
        do_line_menu("Score not perfect - want to retry?", 3);
        if (get_yesno_key() == 'Y')
        {
            y = 1;
        }
        else
        {
            y = 0;
        }
        return y;
    }
    return 0;
}

// module: MENUS
// size: 0x102
// addr: 05E0:3F59
void do_winscrn1(void)
{
    setapage(2);
    clearscreen();
    setvpage(2);
    setapage(1);
    load_pcx(OFFSET_WIN, 0);
    memcpy(temppal, palette, sizeof(palette));
    setapage(0);
    load_pcx(OFFSET_WARP, 0);
    load_and_play_VOC(OFFSET_SOUND+3);
    setvpage(0);
    fade_in(0x3c);
    fade_in_white();
    clearscreen();
    fade_out(1);
    memcpy(palette, temppal, sizeof(palette));
    setvpage(1);
    fade_in(0x3c);
    while (snoozekey(1000) == 0)
        ;
    fade_out(0x14);
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
}
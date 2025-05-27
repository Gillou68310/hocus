#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "gr.h"
#include "menus.h"
#include "fileio.h"
#include "soundfx.h"

#define LAYER_BKG 0
#define LAYER_SLD 1
#define LAYER_FNC 2
#define LAYER_COUNT 3

// addr: 192E:13B6
// size: 12
unsigned char *mode_label[LAYER_COUNT] = {
    "[BKG]",
    "[SLD]",
    "[FNC]"};

// addr: 192E:13C2
// size: 966
ups_t ups[UPS_COUNT] = {
    {"Ruby", 100, 0, 0, 0},
    {"Diamond", 250, 0, 0, 0},
    {"Goblet", 500, 0, 0, 0},
    {"Crown", 1000, 0, 0, 0},
    {"Heal (green)", 0, 15, 0, 0},
    {"Crystal", 0, 0, 0, 1},
    {"Hurt", 0, 0, 0, 2},
    {"Add shot", 0, 0, 1, 0},
    {"Invisible (black)", 0, 0, 0, 3},
    {"Super jump (yellow)", 0, 0, 0, 4},
    {"Super shot (white)", 0, 0, 0, 5},
    {"Smart bomb", 0, 0, 0, 6},
    {"Silver Key", 0, 0, 0, 7},
    {"Gold Key", 0, 0, 0, 8},
    {"Kill", 0, 0, 0, 9},
    {"Wizard note", 0, 0, 0, 10},
    {"Laser Shot", 0, 0, 0, 11},
    {"Unused", 0, 0, 0, 0},
    {"Unused", 0, 0, 0, 0},
    {"Unused", 0, 0, 0, 0},
    {"Unused", 0, 0, 0, 0},
    {"Unused", 0, 0, 0, 0},
    {"Unused", 0, 0, 0, 0}};

// addr: 192E:1788
// size: 80
int plat_pcx_ofs[GAME_COUNT][LEVEL_COUNT] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 3, 0},
    {4, 4, 5, 5, 6, 6, 7, 7, 7, 0},
    {8, 8, 9, 9, 10, 10, 11, 11, 11, 0},
    {12, 12, 13, 13, 14, 14, 15, 15, 15, 0}};

// addr: 192E:17D8
// size: 80
int lvl_info_ofs[GAME_COUNT][LEVEL_COUNT] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 0},
    {9, 10, 11, 12, 13, 14, 15, 16, 17, 0},
    {18, 19, 20, 21, 22, 23, 24, 25, 26, 0},
    {27, 28, 29, 30, 31, 32, 33, 34, 35, 0}};

// addr: 192E:1828
// size: 80
int bdrop_pcxpal_ofs[GAME_COUNT][LEVEL_COUNT] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 3, 0},
    {4, 4, 5, 5, 6, 6, 7, 7, 7, 0},
    {8, 8, 9, 9, 10, 10, 11, 11, 11, 0},
    {12, 12, 13, 13, 14, 14, 15, 15, 15, 0}};

// module: DESIGN
// size: 0x1a
// addr: 09F0:0004
void set_all_layers(int on)
{
    // register: DX
    // size: 2
    int i;
    for (i = 0; i < LAYER_COUNT; i++)
    {
        layer[i] = on;
    }
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

    strcpy(dline, itoa(game, dummy, 10));
    strcat(dline, ":");
    strcat(dline, itoa(level, dummy, 10));
    strcat(dline, "/");
    strcat(dline, itoa(dx, dummy, 10));
    strcat(dline, ":");
    strcat(dline, itoa(dy, dummy, 10));
    strcat(dline, "/");
    strcat(dline, itoa(dy * 0xf0 + dx, dummy, 10));
    strcat(dline, "/");
    strcat(dline, mode_label[mode]);
    if (layer[LAYER_BKG] != 0)
    {
        strcat(dline, "/BKG");
    }
    if (layer[LAYER_SLD] != 0)
    {
        strcat(dline, "/SLD");
    }
    if (layer[LAYER_FNC] != 0)
    {
        strcat(dline, "/FNC");
    }
    if (block != 0)
    {
        strcat(dline, "-BLK-");
    }
    clearbox(0, 0xa0, 0x4f, 0xc7);
    pstrs(0, 0xa0, 3, dline);
    i = *(fnc + dy * 0xf0 + dx);

    if (i == FNC_NONE)
    {
        return;
    }

    if ((i >= FNC_UPS_START) && (i <= FNC_UPS_END))
    {
        pstr(0, 0xa8, 2, ups[i].tag);
    }
    else if ((i >= FNC_WARPS_START) && (i <= FNC_WARPS_END))
    {
        strcpy(dline, "Warp ");
        strcat(dline, itoa(i - (FNC_WARPS_START - 1), dumnum, 10));
        if ((dy * 0xf0 + dx) == warps[i - FNC_WARPS_START].src)
        {
            strcat(dline, " SRC");
        }
        else
        {
            strcat(dline, " DEST");
        }
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= FNC_SWITCHES_START) && (i <= FNC_SWITCHES_END))
    {
        strcpy(dline, "Switch ");
        strcat(dline, itoa(i - (FNC_SWITCHES_START - 1), dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= FNC_RTRIPS_START) && (i <= FNC_RTRIPS_END))
    {
        strcpy(dline, "Restore Trip ");
        strcat(dline, itoa(i - (FNC_RTRIPS_START - 1), dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= FNC_ETRIPS_START) && (i <= FNC_ETRIPS_END))
    {
        strcpy(dline, "Blank (erase) Trip ");
        strcat(dline, itoa(i - (FNC_ETRIPS_START - 1), dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= FNC_SPRITES_START) && (i <= FNC_SPRITES_END))
    {
        strcpy(dline, sprite[i - FNC_SPRITES_START].name);
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= FNC_MTRIGGERS_START) && (i <= FNC_MTRIGGERS_END))
    {
        strcpy(dline, "Monster trigger ");
        strcat(dline, itoa(i - (FNC_MTRIGGERS_START - 1), dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
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

#ifdef TARGET_DOS
    latches(0);
    enable_pixels(0xf);
    for (i = 0; i < 4; i++)
    {
        //*(vga + (y * 16) * VGA_PLANE_WIDTH + x * 4 + i) = c;
        ((line_t)vga)[y * 16][x * 4 + i] = c;
    }
    for (i = 0; i < 4; i++)
    {
        //*(vga + (y * 16 + 0xf) * VGA_PLANE_WIDTH + x * 4 + i) = c;
        ((line_t)vga)[y * 16 + 0xf][x * 4 + i] = c;
    }
#else
    memset(&((line_t)vga)[y * 16][x * 16], c, 16);
    memset(&((line_t)vga)[y * 16 + 0xf][x * 16], c, 16);
#endif
}

// module: DESIGN
// size: 0xc9
// addr: 09F0:04FD
void trim_coords(void)
{
    if (block != 0)
    {
        if (dy < bty)
        {
            dy = bty;
        }
        if (dx < blx)
        {
            dx = blx;
        }
        brx = dx;
        bby = dy;
    }
    if (dx < 0)
    {
        dx = 0;
    }
    if (dx > 0xef)
    {
        dx = 0xef;
    }
    if (dy < 0)
    {
        dy = 0;
    }
    if (dy > 0x3b)
    {
        dy = 0x3b;
    }
    if (dx < 10)
    {
        sdx = 0;
    }
    else if (dx > 0xe6)
    {
        sdx = 0xdc;
    }
    else
    {
        sdx = dx - 10;
    }
    if (dy < 5)
    {
        sdy = 0;
    }
    else if (dy > 0x37)
    {
        sdy = 0x32;
    }
    else
    {
        sdy = dy - 5;
    }
    mofs = dy * 0xf0 + dx;
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

    trim_coords();
    showswitchrange = 0;
    v = *(fnc + dy * 0xf0 + dx);
    if ((v >= FNC_SWITCHES_START) && (v <= FNC_SWITCHES_END))
    {
        showswitchrange = 1;
        v -= FNC_SWITCHES_START;
        slx = switches[v].dlx;
        sty = switches[v].dty;
        srx = switches[v].drx;
        sby = switches[v].dby;
    }
    else if ((v >= FNC_RTRIPS_START) && (v <= FNC_RTRIPS_END))
    {
        vv = v - FNC_RTRIPS_START;
        if ((rtrips[vv].dlx != -1) &&
            (rtrips[vv].drx != -1) &&
            (rtrips[vv].dty != -1) &&
            (rtrips[vv].dby != -1))
        {
            showswitchrange = 1;
            v -= FNC_RTRIPS_START;
            slx = rtrips[v].dlx;
            sty = rtrips[v].dty;
            srx = rtrips[v].drx;
            sby = rtrips[v].dby;
        }
    }
    else if ((v >= FNC_ETRIPS_START) && (v <= FNC_ETRIPS_END))
    {
        vv = v - FNC_ETRIPS_START;
        if ((etrips[vv].dlx != -1) &&
            (etrips[vv].drx != -1) &&
            (etrips[vv].dty != -1) &&
            (etrips[vv].dby != -1))
        {
            showswitchrange = 1;
            v -= FNC_ETRIPS_START;
            slx = etrips[v].dlx;
            sty = etrips[v].dty;
            srx = etrips[v].drx;
            sby = etrips[v].dby;
        }
    }
    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 0x14; x++)
        {
            blank = 1;
            ofs = ((sdy + y) * 0xf0) + sdx + x;
            latches(1);
            enable_pixels(0xf);
            if ((layer[LAYER_BKG] != 0) && (bkg[ofs] != 0xff))
            {
                v = bkg[ofs];
                blank = 0;
                for (py = 0; py < 16; py++)
                {
#ifdef TARGET_DOS
                    MCPY(&((line_t)vga)[y * 16 + py][x * 4], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 4], 4);
#else
                    MCPY(&((line_t)vga)[y * 16 + py][x * 16], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 16], 16);
#endif
                }
            }
            if ((layer[LAYER_SLD] != 0) && (sld[ofs] != 0xff))
            {
                v = sld[ofs];
                blank = 0;
                for (py = 0; py < 16; py++)
                {
#ifdef TARGET_DOS
                    MCPY(&((line_t)vga)[y * 16 + py][x * 4], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 4], 4);
#else
                    MCPY(&((line_t)vga)[y * 16 + py][x * 16], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 16], 16);
#endif
                }
            }
            if (blank != 0)
            {
                clearbox(x * 4, y * 16, x * 4 + 3, y * 16 + 0xf);
            }
            if ((block != 0) && (blx <= (sdx + x)) && ((sdx + x) <= brx) &&
                (bty <= (sdy + y)) && ((sdy + y) <= bby))
            {
                show_marker_cursor(x, y, 2);
            }
            if ((showswitchrange) && (slx <= (sdx + x)) && ((sdx + x) <= srx) &&
                                                               (sty <= (sdy + y)) && ((sdy + y) <= sby))
            {
                show_marker_cursor(x, y, 0x58);
            }
            if (layer[LAYER_FNC] != 0)
            {
                v = fnc[ofs];
                if ((v >= FNC_UPS_START) && (v <= FNC_UPS_END))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= FNC_WARPS_START) && (v <= FNC_WARPS_END))
                {
                    show_marker_cursor(x, y, 16);
                }
                if ((v >= FNC_SWITCHES_START) && (v <= FNC_SWITCHES_END))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= FNC_RTRIPS_START) && (v <= FNC_RTRIPS_END))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= FNC_ETRIPS_START) && (v <= FNC_ETRIPS_END))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= FNC_SPRITES_START) && (v <= FNC_SPRITES_END))
                {
                    show_marker_cursor(x, y, 0x58);
                }
                if ((v >= FNC_MTRIGGERS_START) && (v <= FNC_MTRIGGERS_END))
                {
                    show_marker_cursor(x, y, 0x70);
                }
            }
        }
    }
    show_marker_cursor(dx - sdx, dy - sdy, 2);
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

    done = 0;
    setapage(1);
    setvpage(1);
    while (!done)
    {
        show_marker_cursor(palette_pnt % 0x14, palette_pnt / 0x14, 2);
        key = getch();
        scopy(1, 2);
        if (!key)
        {
            key = getch();
            if (key == KEY_RIGHT)
            {
                palette_pnt++;
            }
            if (key == KEY_LEFT)
            {
                palette_pnt--;
            }
            if (key == KEY_UP)
            {
                palette_pnt -= 0x14;
            }
            if (key == KEY_DOWN)
            {
                palette_pnt += 0x14;
            }
            if (palette_pnt < 0)
            {
                palette_pnt = 0;
            }
            if (palette_pnt > 0x9f)
            {
                palette_pnt = 0x9f;
            }
        }
        else
        {
            done = 1;
        }
    }
    setapage(0);
    setvpage(0);
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

    for (i = 0; i < UPS_COUNT; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, ups[i].tag);
        pstr(0, i * 8, 3, dline);
    }
    while (1)
    {
    loop:
        key = getch();
        if (!key)
        {
            getch();
            goto loop;
        }

        if (key == KEY_ESCAPE)
        {
            return -1;
        }
        if ((key >= 'a') && (key < 'x'))
        {
            return key - 'a';
        }
    }
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

    for (i = 0; i < WARPS_COUNT; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Warp ");

        strcat(dline, itoa(i + 1, dumnum, 10));
        strcat(dline, " ");
        strcat(dline, itoa(warps[i].src, dumnum, 10));
        strcat(dline, " ");
        strcat(dline, itoa(warps[i].dest, dumnum, 10));
        pstr(0, i * 8, 3, dline);
    }
    while (1)
    {
    loop:
        key = getch();
        if (!key)
        {
            getch();
            goto loop;
        }

        if (key == KEY_ESCAPE)
        {
            return -1;
        }
        if ((key >= 'a') && (key < 'k'))
        {
            return key - 'a' + FNC_WARPS_START;
        }
    }
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

    for (i = 0; i < SWITCHES_COUNT; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Switch ");
        strcat(dline, itoa(i + 1, dumnum, 10));
        l = 0;
        for (j = 0; j < 4; j++)
        {
            if (switches[i].condnum[j] != -1)
            {
                l = 1;
            }
        }
        if (l)
        {
            strcat(dline, " used");
        }
        pstr(0, i * 8, 3, dline);
    }
    while (1)
    {
    loop:
        key = getch();
        if (!key)
        {
            getch();
            goto loop;
        }
        if (key == KEY_ESCAPE)
        {
            break;
        }

        if ((key >= 'a') && (key < 'x'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + FNC_SWITCHES_START;
            switches[l].dlx = blx;
            switches[l].dty = bty;
            switches[l].drx = brx;
            switches[l].dby = bby;
            do
            {
            loop2:
                show_design_screen();
                make_status_line();
                strcpy(dline, "Switch ");
                strcat(dline, itoa(l + 1, dumnum, 10));
                strcat(dline, " ");
                if (!switches[l].effect)
                {
                    strcat(dline, "erase");
                }
                else
                {
                    strcat(dline, "restore");
                }
                pstr(0, 0, 3, dline);
                strcpy(dline, "");
                for (j = 0; j < 4; j++)
                {
                    strcat(dline, itoa(switches[l].condnum[j], dumnum, 10));
                    strcat(dline, "=");
                    if (switches[l].condstate[j] == anminfo.switchon)
                    {
                        strcat(dline, "on ");
                    }
                    else
                    {
                        strcat(dline, "off ");
                    }
                }
                pstr(0, 9, 3, dline);
                strcpy(dline, itoa(switches[l].dlx, dumnum, 10));
                strcat(dline, ",");
                strcat(dline, itoa(switches[l].dty, dumnum, 10));
                strcat(dline, ",");
                strcat(dline, itoa(switches[l].drx, dumnum, 10));
                strcat(dline, ",");
                strcat(dline, itoa(switches[l].dby, dumnum, 10));
                pstr(0, 0x12, 3, dline);
                pstr(0, 0x1b, 3, "Press e to erase switch");
                pstr(0, 0x24, 3, "Press 0 to 3 to assign switch number");
                pstr(0, 0x2d, 3, "Press t to toggle effect");
                pstr(0, 0x36, 3, "Press ESC to exit");
                key = getch();
                if (!key)
                {
                    getch();
                    goto loop2;
                }
                if (key == 't')
                {
                    switches[l].effect = !switches[l].effect;
                }
                if (key == 'e')
                {
                    for (j = 0; j < 4; j++)
                    {
                        switches[l].condnum[j] = -1;
                        switches[l].condstate[j] = anminfo.switchoff;
                    }
                    switches[l].dlx = switches[l].dty = switches[l].drx = switches[l].dby = 0;
                    switches[l].effect = 0;
                }
                if ((key >= '0') && (key <= '3'))
                {
                    show_design_screen();
                    pstr(0, 0, 3, "Define condition for result");
                    pstr(0, 0x12, 3, "Press 0 for OFF");
                    pstr(0, 0x1b, 3, "Press 1 for ON");
                    m = key - '0';
                    if (getch() == '0')
                    {
                        switches[l].condstate[m] = anminfo.switchoff;
                    }
                    else
                    {
                        switches[l].condstate[m] = anminfo.switchon;
                    }
                    switches[l].condnum[m] = dy * 0xf0 + dx;
                }
                if (key == KEY_ESCAPE)
                {
                    return;
                }
            } while (1);
        }
    }
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

    for (i = 0; i < RTRIPS_COUNT; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Restore Trip ");
        strcat(dline, itoa(i + 1, dumnum, 10));
        l = 0;
        if (rtrips[i].dlx != -1)
        {
            l = 1;
        }
        if (rtrips[i].drx != -1)
        {
            l = 1;
        }
        if (rtrips[i].dty != -1)
        {
            l = 1;
        }
        if (rtrips[i].dby != -1)
        {
            l = 1;
        }

        if (l)
        {
            strcat(dline, " used");
        }
        if (l)
        {
            if (rtrips[i].keytype == 0)
            {
                strcat(dline, " No key");
            }
            if (rtrips[i].keytype == 1)
            {
                strcat(dline, " Silver key");
            }
            if (rtrips[i].keytype == 2)
            {
                strcat(dline, " Gold key");
            }
        }
        pstr(0, i * 8, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key != KEY_ESCAPE)
    {
        if ((key >= 'a') && (key < 'z'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + FNC_RTRIPS_START;
            rtrips[l].restore = *(bkg + dy * 0xf0 + dx);
            rtrips[l].dlx = blx;
            rtrips[l].dty = bty;
            rtrips[l].drx = brx;
            rtrips[l].dby = bby;
            show_design_screen();
            pstr(0, 0, 3, "Press: 0=no key 1=silver key 2=gold key");
            do
            {
            loop1:
                key = getch();
                if (!key)
                {
                    getch();
                    goto loop1;
                }
                if ((key >= '0') && (key <= '2'))
                {
                    rtrips[l].keytype = key - '0';
                    break;
                }
            } while (1);
        }
        if ((key >= 'A') && (key < 'Z'))
        {
            l = key - 'A';
            rtrips[l].dlx = -1;
            rtrips[l].dty = -1;
            rtrips[l].drx = -1;
            rtrips[l].dby = -1;
        }
    }
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

    for (i = 0; i < ETRIPS_COUNT; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Blank Trip ");
        strcat(dline, itoa(i + 1, dumnum, 10));
        l = 0;
        if (etrips[i].dlx != -1)
        {
            l = 1;
        }
        if (etrips[i].drx != -1)
        {
            l = 1;
        }
        if (etrips[i].dty != -1)
        {
            l = 1;
        }
        if (etrips[i].dby != -1)
        {
            l = 1;
        }

        if (l)
        {
            strcat(dline, " used");
        }
        if (l)
        {
            if (etrips[i].keytype == 0)
            {
                strcat(dline, " No key");
            }
            if (etrips[i].keytype == 1)
            {
                strcat(dline, " Silver key");
            }
            if (etrips[i].keytype == 2)
            {
                strcat(dline, " Gold key");
            }
        }
        pstr(0, i * 8, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key != KEY_ESCAPE)
    {
        if ((key >= 'a') && (key < 'z'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + FNC_ETRIPS_START;
            etrips[l].restore = *(bkg + dy * 0xf0 + dx);
            etrips[l].dlx = blx;
            etrips[l].dty = bty;
            etrips[l].drx = brx;
            etrips[l].dby = bby;
            show_design_screen();
            pstr(0, 0, 3, "Press: 0=no key 1=silver key 2=gold key");
            do
            {
            loop1:
                key = getch();
                if (!key)
                {
                    getch();
                    goto loop1;
                }
                if ((key >= '0') && (key <= '2'))
                {
                    etrips[l].keytype = key - '0';
                    break;
                }
            } while (1);
        }
        if ((key >= 'A') && (key < 'Z'))
        {
            l = key - 'A';
            etrips[l].dlx = -1;
            etrips[l].dty = -1;
            etrips[l].drx = -1;
            etrips[l].dby = -1;
        }
    }
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

    s = 0;
    for (i = 0; i < 5; i++)
    {
        if (mtags[i].mnum != -1)
        {
            pos = mtags[i].mnum;
            point_to_data_record(0x4e);
            fseek(databasefp, (pos * sizeof(sprite_t)), 1);
            fread(&sprite[s], sizeof(sprite_t), 1, databasefp);
            s++;
        }
    }
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

    for (i = 0; i < MTAGS_COUNT; i++)
    {
        if (mtags[i].mnum != -1)
        {
            strcpy(dline, " ) ");
            dline[0] = i + 'A';
            strcat(dline, sprite[i].name);
            strcat(dline, " ");
            strcat(dline, itoa(mtags[i].type, dumnum, 10));
            pstr(0, i * 8, 3, dline);
        }
        else
        {
            break;
        }
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key == KEY_ESCAPE)
    {
        return;
    }
    if ((key >= 'a') && (key < 'a' + i))
    {
        l = key - 'a';
        *(fnc + dy * 0xf0 + dx) = l + FNC_SPRITES_START;
    }
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

    start = 0;
    for (i = 0; i < 25; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Monster trigger ");
        strcat(dline, itoa(start + i + 1, dumnum, 10));
        l = 0;
        for (j = 0; j < 8; j++)
        {
            if (mtriggers[start + i].mnum[j] != -1)
            {
                l = 1;
            }
        }
        if (l)
        {
            strcat(dline, " used");
        }
        pstr(0, i * 8, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key == KEY_ESCAPE)
    {
        return;
    }
    if ((key >= 'a') && (key < 'z'))
    {
        l = start + key - 'a';
        *(fnc + dy * 0xf0 + dx) = l + FNC_MTRIGGERS_START;
        j = 0;
        for (y = bty; y <= bby; y++)
        {
            for (x = blx; x <= brx; x++)
            {
                mpos = y * 0xf0 + x;
                if ((fnc[mpos] >= FNC_SPRITES_START) && (fnc[mpos] <= FNC_SPRITES_END))
                {
                    mtriggers[l].rpos[j] = mpos;
                    mtriggers[l].mnum[j] = fnc[mpos] - FNC_SPRITES_START;
                    j++;
                    if (j > 7)
                    {
                        j = 7;
                    }
                }
            }
        }
        show_design_screen();
        for (j = 0; j < 8; j++)
        {
            if (mtriggers[l].mnum[j] != -1)
            {
                strcpy(dline, " ) ");
                dline[0] = j + '0';
                strcat(dline, sprite[mtriggers[l].mnum[j]].name);
                strcat(dline, " ");
                strcat(dline, itoa(mtriggers[l].rpos[j], dumnum, 10));
                pstr(0, j * 8, 3, dline);
            }
            else
            {
                pstr(0, j * 8, 3, "Dip");
            }
        }
        getch();
    }
    if ((key >= 'A') && (key < 'Z'))
    {
        l = key - 'A';
        for (j = 0; j < 8; j++)
        {
            mtriggers[l].mnum[j] = -1;
        }
    }
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

    done = 0;
    turn_on_palette();
    if (adlib != 0)
    {
        SD_MusicOff();
    }
    dlevel = game * 9 + level;
    set_all_layers(1);
    mode = 0;
    palette_pnt = 0;
    blx = brx = bty = bby = 0;
    block = 0;
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_LVLINFO, &lvlinfo);
    dx = lvlinfo.startx;
    dy = lvlinfo.starty;
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_ANMINFO, &anminfo);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_WARPS, warps);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SWITCHES, switches);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_RTRIPS, rtrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_ETRIPS, etrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTAGS, mtags);
    load_tag_sprites();
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTRIGGERS, mtriggers);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_BKG, bkg);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLD, sld);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLDSAV, sldsav);
    memcpy(sld, sldsav, 0x3840);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_FNC, fnc);
    setmem(swe, 0x3840, 0);
    setapage(1);
    load_pcx(plat_pcx_ofs[game][level] + 0x49, 0);
    read_pels(palette, 0, 0x100);
    scopy(2, 1);
    setapage(0);
    setvpage(0);
    while (!done)
    {
        show_design_screen();
        make_status_line();
        key = getch();
        if (!key)
        {
            key = getch();
            if (key == KEY_ALT_U)
            {
                x = pick_power_up();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                }
            }
            if (key == KEY_ALT_W)
            {
                x = pick_warp();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                    warps[x - FNC_WARPS_START].src = dy * 0xf0 + dx;
                }
            }
            if (key == KEY_ALT_E)
            {
                x = pick_warp();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                    warps[x - FNC_WARPS_START].dest = dy * 0xf0 + dx;
                }
            }
            if (key == KEY_ALT_Z)
            {
                x = dy * 0xf0 + dx;
                y = fnc[x];
                if ((y >= FNC_WARPS_START) && (y <= FNC_WARPS_END))
                {
                    if (warps[y - FNC_WARPS_START].src == x)
                    {
                        dy = warps[y - FNC_WARPS_START].dest / 0xf0;
                        dx = warps[y - FNC_WARPS_START].dest % 0xf0;
                    }
                    else if (warps[y - FNC_WARPS_START].dest == x)
                    {
                        dy = warps[y - FNC_WARPS_START].src / 0xf0;
                        dx = warps[y - FNC_WARPS_START].src % 0xf0;
                    }
                }
            }
            if (key == KEY_ALT_S)
            {
                pick_switch();
            }
            if (key == KEY_ALT_R)
            {
                pick_rtrip();
            }
            if (key == KEY_ALT_B)
            {
                pick_etrip();
            }
            if (key == KEY_ALT_M)
            {
                pick_mtag();
            }
            if (key == KEY_ALT_T)
            {
                pick_mtrig();
            }
            if (key == KEY_LEFT)
            {
                dx--;
            }
            if (key == KEY_RIGHT)
            {
                dx++;
            }
            if (key == KEY_UP)
            {
                dy--;
            }
            if (key == KEY_DOWN)
            {
                dy++;
            }
            if (key == KEY_HOME)
            {
                dx--;
                dy--;
            }
            if (key == KEY_PGUP)
            {
                dx++;
                dy--;
            }
            if (key == KEY_PGDN)
            {
                dx++;
                dy++;
            }
            if (key == KEY_END)
            {
                dx--;
                dy++;
            }
            if (key == KEY_F1)
            {
                mode++;
                if (mode >= 3)
                {
                    mode = 0;
                }
            }
            if (key == KEY_F2)
            {
                layer[LAYER_BKG] = !layer[LAYER_BKG];
            }
            if (key == KEY_F3)
            {
                layer[LAYER_SLD] = !layer[LAYER_SLD];
            }
            if (key == KEY_F4)
            {
                layer[LAYER_FNC] = !layer[LAYER_FNC];
            }
            if (key == KEY_F6)
            {
                *(fnc + dy * 0xf0 + dx) = FNC_UPS_HURT;
            }
            if (key == KEY_F7)
            {
                *(fnc + dy * 0xf0 + dx) = FNC_UPS_KILL;
            }
            if (key == KEY_F10)
            {
                done = 1;
            }
        }
        else
        {
            if (key == '4')
            {
                dx -= 10;
            }
            if (key == '6')
            {
                dx += 10;
            }
            if (key == '8')
            {
                dy -= 5;
            }
            if (key == '2')
            {
                dy += 5;
            }
            if (key == '7')
            {
                dx -= 10;
                dy -= 5;
            }
            if (key == '9')
            {
                dx += 10;
                dy -= 5;
            }
            if (key == '3')
            {
                dx += 10;
                dy += 5;
            }
            if (key == '1')
            {
                dx -= 10;
                dy += 5;
            }
            if (key == 'p')
            {
                pick_from_palette();
            }
            if (key == KEY_SPACE)
            {
                if (mode == 0)
                {
                    *(bkg + dy * 0xf0 + dx) = palette_pnt;
                }
                if (mode == 1)
                {
                    *(sld + dy * 0xf0 + dx) = palette_pnt;
                }
            }
            if (key == 'e')
            {
                if (mode == 0)
                {
                    *(bkg + dy * 0xf0 + dx) = -1;
                }
                if (mode == 1)
                {
                    *(sld + dy * 0xf0 + dx) = -1;
                }
                if (mode == 2)
                {
                    *(fnc + dy * 0xf0 + dx) = FNC_NONE;
                }
            }
            if (key == 's')
            {
                lvlinfo.startx = dx;
                lvlinfo.starty = dy;
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_LVLINFO, &lvlinfo);
                strcpy(dline, "LVLINF");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, &lvlinfo, sizeof(lvlinfo));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_WARPS, warps);
                strcpy(dline, "WARPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, warps, sizeof(warps));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SWITCHES, switches);
                strcpy(dline, "SWITCH");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, switches, sizeof(switches));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_RTRIPS, rtrips);
                strcpy(dline, "RTRIPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, rtrips, sizeof(rtrips));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_ETRIPS, etrips);
                strcpy(dline, "ETRIPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, etrips, sizeof(etrips));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTAGS, mtags);
                strcpy(dline, "MTAGS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, mtags, sizeof(mtags));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTRIGGERS, mtriggers);
                strcpy(dline, "MTRIGS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, mtriggers, sizeof(mtriggers));
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_BKG, bkg);
                strcpy(dline, "BKG");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, bkg, 0x3840);
                memcpy(sldsav, sld, 0x3840);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLDSAV, sldsav);
                strcpy(dline, "SLDSAV");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, sldsav, 0x3840);
                for (i = 0; i < SWITCHES_COUNT; i++)
                {
                    x = 0;
                    for (y = 0; y < 4; y++)
                    {
                        if (switches[i].condnum[y] != -1)
                        {
                            x = 1;
                        }
                    }
                    if (x && switches[i].effect)
                    {
                        for (y = switches[i].dty; y <= switches[i].dby; y++)
                        {
                            for (x = switches[i].dlx; x <= switches[i].drx; x++)
                            {
                                *(sld + y * 0xf0 + x) = -1;
                            }
                        }
                    }
                }
                for (i = 0; i < RTRIPS_COUNT; i++)
                {
                    x = 0;
                    if (rtrips[i].dlx != -1)
                    {
                        x = 1;
                    }
                    if (rtrips[i].drx != -1)
                    {
                        x = 1;
                    }
                    if (rtrips[i].dty != -1)
                    {
                        x = 1;
                    }
                    if (rtrips[i].dby != -1)
                    {
                        x = 1;
                    }
                    if (x)
                    {
                        for (y = rtrips[i].dty; y <= rtrips[i].dby; y++)
                        {
                            for (x = rtrips[i].dlx; x <= rtrips[i].drx; x++)
                            {
                                *(sld + y * 0xf0 + x) = 0xff;
                            }
                        }
                    }
                }
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLD, sld);
                strcpy(dline, "SLD");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, sld, 0x3840);
                memcpy(sld, sldsav, 0x3840);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + OFFSET_FNC, fnc);
                strcpy(dline, "FNC");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, fnc, 0x7080);
            }
            if ((key == 'b') && (mode != 2))
            {
                block = !block;
                if (block != 0)
                {
                    blx = dx;
                    bty = dy;
                    brx = dx;
                    bby = dy;
                }
            }
            if ((key == 'f') && (mode != 2))
            {
                for (y = bty; y <= bby; y++)
                {
                    for (x = blx; x <= brx; x++)
                    {
                        if (mode == 0)
                        {
                            *(bkg + y * 0xf0 + x) = palette_pnt;
                        }
                        else
                        {
                            *(sld + y * 0xf0 + x) = palette_pnt;
                        }
                    }
                }
            }
            if ((key == 'c') && (((brx - blx) + dx) < 0xf0) && (((bby - bty) + dy) < 0x3c))
            {
                for (y = bty; y <= bby; y++)
                {
                    for (x = blx; x <= brx; x++)
                    {
                        if (layer[LAYER_BKG] != 0)
                        {
                            *(bkg + ((dy + y) - bty) * 0xf0 + dx + x - blx) = *(bkg + y * 0xf0 + x);
                        }
                        if (layer[LAYER_SLD] != 0)
                        {
                            *(sld + ((dy + y) - bty) * 0xf0 + dx + x - blx) = *(sld + y * 0xf0 + x);
                        }
                        if (layer[LAYER_FNC] != 0)
                        {
                            *(fnc + ((dy + y) - bty) * 0xf0 + dx + x - blx) = *(fnc + y * 0xf0 + x);
                        }
                    }
                }
            }
            if ((key == 'w'))
            {
                for (y = bty; y <= bby; y++)
                {
                    for (x = blx; x <= brx; x++)
                    {
                        if (mode == 0)
                        {
                            *(bkg + y * 0xf0 + x) = -1;
                        }
                        else
                        {
                            *(sld + y * 0xf0 + x) = -1;
                        }
                    }
                }
            }
        }
    }
    play_imf_file(199);
}
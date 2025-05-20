#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <mem.h>
#include "common.h"
#include "gr.h"
#include "menus.h"
#include "fileio.h"
#include "soundfx.h"

// addr: 192E:13B6
// size: 12
unsigned char *mode_label[3] = {
    "[BKG]",
    "[SLD]",
    "[FNC]"};

// addr: 192E:13C2
// size: 966
struct struct_130 ups[23] = {
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
int plat_pcx_ofs[4][10] = {
    {0, 0, 1, 1, 2, 2, 3, 3, 3, 0},
    {4, 4, 5, 5, 6, 6, 7, 7, 7, 0},
    {8, 8, 9, 9, 10, 10, 11, 11, 11, 0},
    {12, 12, 13, 13, 14, 14, 15, 15, 15, 0}};

// addr: 192E:17D8
// size: 80
int lvl_info_ofs[4][10] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 0},
    {9, 10, 11, 12, 13, 14, 15, 16, 17, 0},
    {18, 19, 20, 21, 22, 23, 24, 25, 26, 0},
    {27, 28, 29, 30, 31, 32, 33, 34, 35, 0}};

// addr: 192E:1828
// size: 80
int bdrop_pcxpal_ofs[4][10] = {
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
    for (i = 0; i < 3; i++)
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
    strcat(dline, itoa(dy * 0xF0 + dx, dummy, 10));
    strcat(dline, "/");
    strcat(dline, mode_label[mode]);
    if (layer[0] != 0)
    {
        strcat(dline, "/BKG");
    }
    if (layer[1] != 0)
    {
        strcat(dline, "/SLD");
    }
    if (layer[2] != 0)
    {
        strcat(dline, "/FNC");
    }
    if (block != 0)
    {
        strcat(dline, "-BLK-");
    }
    clearbox(0, 0xa0, 0x4f, 199);
    pstrs(0, 0xa0, 3, dline);
    i = *(fnc + dy * 240 + dx);

    if (i == 0x7530)
        return;

    if ((i >= 0) && (i <= 0x16))
    {
        pstr(0, 0xA8, 2, &ups[i]);
    }
    else if ((i >= 0x17) && (i <= 0x20))
    {
        strcpy(dline, "Warp ");
        strcat(dline, itoa(i - 22, dumnum, 10));
        if ((dy * 240 + dx) == warps[i - 23].src)
        {
            strcat(dline, " SRC");
        }
        else
        {
            strcat(dline, " DEST");
        }
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= 0x21) && (i <= 0x37))
    {
        strcpy(dline, "Switch ");
        strcat(dline, itoa(i - 0x20, dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= 0x38) && (i <= 0x50))
    {
        strcpy(dline, "Restore Trip ");
        strcat(dline, itoa(i - 0x37, dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= 0x51) && (i <= 0x69))
    {
        strcpy(dline, "Blank (erase) Trip ");
        strcat(dline, itoa(i - 0x50, dumnum, 10));
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= 0x6a) && (i <= 0x73))
    {
        strcpy(dline, sprite[i - 0x6a].name);
        pstr(0, 0xA8, 3, dline);
    }
    else if ((i >= 0x74) && (i <= 0x16d))
    {
        strcpy(dline, "Monster trigger ");
        strcat(dline, itoa(i - 0x73, dumnum, 10));
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

    latches(0);
    enable_pixels(0xf);
    for (i = 0; i < 4; i++)
    {
        //*(vga + (y * 16) * 0x50 + x * 4 + i) = c;
        ((line_t)vga)[y * 16][x * 4 + i] = c;
    }
    for (i = 0; i < 4; i++)
    {
        //*(vga + (y * 0x10 + 0xf) * 0x50 + x * 4 + i) = c;
        ((line_t)vga)[y * 16 + 0xf][x * 4 + i] = c;
    }
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
    if ((v >= '!') && (v <= '7'))
    {
        showswitchrange = 1;
        v -= '!';
        slx = switches[v].dlx;
        sty = switches[v].dty;
        srx = switches[v].drx;
        sby = switches[v].dby;
    }
    else if ((v >= '8') && (v <= 'P'))
    {
        vv = v - '8';
        if ((rtrips[vv].dlx != -1) &&
            (rtrips[vv].drx != -1) &&
            (rtrips[vv].dty != -1) &&
            (rtrips[vv].dby != -1))
        {
            showswitchrange = 1;
            v -= '8';
            slx = rtrips[v].dlx;
            sty = rtrips[v].dty;
            srx = rtrips[v].drx;
            sby = rtrips[v].dby;
        }
    }
    else if ((v >= 'Q') && (v <= 'i'))
    {
        vv = v - 'Q';
        if ((etrips[vv].dlx != -1) &&
            (etrips[vv].drx != -1) &&
            (etrips[vv].dty != -1) &&
            (etrips[vv].dby != -1))
        {
            showswitchrange = 1;
            v -= 'Q';
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
            if ((layer[0] != 0) && (bkg[ofs] != 0xff))
            {
                v = bkg[ofs];
                blank = 0;
                for (py = 0; py < 16; py++)
                {
                    MCPY(&((line_t)vga)[y * 16 + py][x * 4], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 4], 4);
                }
            }
            if ((layer[1] != 0) && (sld[ofs] != 0xff))
            {
                v = sld[ofs];
                blank = 0;
                for (py = 0; py < 16; py++)
                {
                    MCPY(&((line_t)vga)[y * 16 + py][x * 4], &((line_t)vgap[1])[(v / 0x14) * 16 + py][(v % 0x14) * 4], 4);
                }
            }
            if (blank != 0)
            {
                clearbox(x << 2, y << 4, x * 4 + 3, y * 0x10 + 0xf);
            }
            if ((((block != 0) && (blx <= (sdx + x))) && ((sdx + x) <= brx)) &&
                ((bty <= (sdy + y) && ((sdy + y) <= bby))))
            {
                show_marker_cursor(x, y, 2);
            }
            if (((showswitchrange) && (slx <= (sdx + x))) && (((sdx + x) <= srx &&
                                                               ((sty <= (sdy + y) && ((sdy + y) <= sby))))))
            {
                show_marker_cursor(x, y, 0x58);
            }
            if (layer[2] != 0)
            {
                v = fnc[ofs];
                if ((v >= 0) && (v <= 0x16))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= 0x17) && (v <= 0x20))
                {
                    show_marker_cursor(x, y, 0x10);
                }
                if ((v >= 0x21) && (v <= 0x37))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= 0x38) && (v <= 0x50))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= 0x51) && (v <= 0x69))
                {
                    show_marker_cursor(x, y, 8);
                }
                if ((v >= 0x6a) && (v <= 0x73))
                {
                    show_marker_cursor(x, y, 0x58);
                }
                if ((v >= 0x74) && (v <= 0x16d))
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
            if (key == 'M')
            {
                palette_pnt++;
            }
            if (key == 'K')
            {
                palette_pnt--;
            }
            if (key == 'H')
            {
                palette_pnt -= 0x14;
            }
            if (key == 'P')
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

    for (i = 0; i < 0x17; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, ups[i].tag);
        pstr(0, i << 3, 3, dline);
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

        if (key == 0x1b)
            return -1;
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

    for (i = 0; i < 10; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Warp ");

        strcat(dline, itoa(i + 1, dumnum, 10));
        strcat(dline, " ");
        strcat(dline, itoa(warps[i].src, dumnum, 10));
        strcat(dline, " ");
        strcat(dline, itoa(warps[i].dest, dumnum, 10));
        pstr(0, i << 3, 3, dline);
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

        if (key == 0x1b)
            return -1;
        if ((key >= 'a') && (key < 'k'))
        {
            return key - 'J';
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

    for (i = 0; i < 0x17; i++)
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
        pstr(0, i << 3, 3, dline);
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
        if (key == 0x1b)
            break;

        if ((key >= 'a') && (key < 'x'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + '!';
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
                if (key == 0x1b)
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

    for (i = 0; i < 0x19; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Restore Trip ");
        strcat(dline, itoa(i + 1, dumnum, 10));
        l = 0;
        if (rtrips[i].dlx != -1)
            l = 1;
        if (rtrips[i].drx != -1)
            l = 1;
        if (rtrips[i].dty != -1)
            l = 1;
        if (rtrips[i].dby != -1)
            l = 1;

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
        pstr(0, i << 3, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key != 0x1b)
    {
        if ((key >= 'a') && (key < 'z'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + '8';
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

    for (i = 0; i < 0x19; i++)
    {
        strcpy(dline, " ) ");
        dline[0] = i + 'A';
        strcat(dline, "Blank Trip ");
        strcat(dline, itoa(i + 1, dumnum, 10));
        l = 0;
        if (etrips[i].dlx != -1)
            l = 1;
        if (etrips[i].drx != -1)
            l = 1;
        if (etrips[i].dty != -1)
            l = 1;
        if (etrips[i].dby != -1)
            l = 1;

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
        pstr(0, i << 3, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key != 0x1b)
    {
        if ((key >= 'a') && (key < 'z'))
        {
            l = key - 'a';
            *(fnc + dy * 0xf0 + dx) = l + 'Q';
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
            fseek(databasefp, (pos * sizeof(struct struct_159)), 1);
            fread(&sprite[s], sizeof(struct struct_159), 1, databasefp);
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

    for (i = 0; i < 10; i++)
    {
        if (mtags[i].mnum != -1)
        {
            strcpy(dline, " ) ");
            dline[0] = i + 'A';
            strcat(dline, sprite[i].name);
            strcat(dline, " ");
            strcat(dline, itoa(mtags[i].type, dumnum, 10));
            pstr(0, i << 3, 3, dline);
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
    if (key == 0x1b)
    {
        return;
    }
    if ((key >= 'a') && (key < 'a' + i))
    {
        l = key - 'a';
        *(fnc + dy * 0xf0 + dx) = l + 'j';
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
    for (i = 0; i < 0x19; i++)
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
        pstr(0, i << 3, 3, dline);
    }
loop:
    key = getch();
    if (!key)
    {
        getch();
        goto loop;
    }
    if (key == 0x1b)
    {
        return;
    }
    if ((key >= 'a') && (key < 'z'))
    {
        l = start + key - 'a';
        *(fnc + dy * 0xf0 + dx) = l + 't';
        j = 0;
        for (y = bty; y <= bby; y++)
        {
            for (x = blx; x <= brx; x++)
            {
                mpos = y * 0xf0 + x;
                if ((fnc[mpos] >= 'j') && (fnc[mpos] <= 's'))
                {
                    mtriggers[l].rpos[j] = mpos;
                    mtriggers[l].mnum[j] = fnc[mpos] - 'j';
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
                pstr(0, j << 3, 3, dline);
            }
            else
            {
                pstr(0, j << 3, 3, "Dip");
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
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x4f, &lvlinfo);
    dx = lvlinfo.startx;
    dy = lvlinfo.starty;
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x58, &anminfo.defaultbkg);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x6a, warps);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x73, &switches[0].effect);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x7c, rtrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x85, etrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x8e, mtags);
    load_tag_sprites();
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0x97, mtriggers);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0xa0, bkg);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0xa9, sld);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0xb2, sldsav);
    memcpy(sld, sldsav, 0x3840);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + 0xbb, fnc);
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
            if (key == 0x16)
            {
                x = pick_power_up();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                }
            }
            if (key == 0x11)
            {
                x = pick_warp();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                    warps[x - 23].src = dy * 0xf0 + dx;
                }
            }
            if (key == 0x12)
            {
                x = pick_warp();
                if (x != -1)
                {
                    *(fnc + dy * 0xf0 + dx) = x;
                    warps[x - 23].dest = dy * 0xf0 + dx;
                }
            }
            if (key == ',')
            {
                x = dy * 0xf0 + dx;
                y = fnc[x];
                if ((y >= 0x17) && (y <= 0x20))
                {
                    if (warps[y - 23].src == x)
                    {
                        dy = warps[y - 23].dest / 0xf0;
                        dx = warps[y - 23].dest % 0xf0;
                    }
                    else if (warps[y - 23].dest == x)
                    {
                        dy = warps[y - 23].src / 0xf0;
                        dx = warps[y - 23].src % 0xf0;
                    }
                }
            }
            if (key == '\x1f')
            {
                pick_switch();
            }
            if (key == '\x13')
            {
                pick_rtrip();
            }
            if (key == '0')
            {
                pick_etrip();
            }
            if (key == '2')
            {
                pick_mtag();
            }
            if (key == '\x14')
            {
                pick_mtrig();
            }
            if (key == 'K')
            {
                dx--;
            }
            if (key == 'M')
            {
                dx++;
            }
            if (key == 'H')
            {
                dy--;
            }
            if (key == 'P')
            {
                dy++;
            }
            if (key == 'G')
            {
                dx--;
                dy--;
            }
            if (key == 'I')
            {
                dx++;
                dy--;
            }
            if (key == 'Q')
            {
                dx++;
                dy++;
            }
            if (key == 'O')
            {
                dx--;
                dy++;
            }
            if (key == ';')
            {
                mode++;
                if (mode >= 3)
                    mode = 0;
            }
            if (key == '<')
            {
                layer[0] = !layer[0];
            }
            if (key == '=')
            {
                layer[1] = !layer[1];
            }
            if (key == '>')
            {
                layer[2] = !layer[2];
            }
            if (key == '@')
            {
                *(fnc + dy * 0xf0 + dx) = 6;
            }
            if (key == 'A')
            {
                *(fnc + dy * 0xf0 + dx) = 0xe;
            }
            if (key == 'D')
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
            if (key == ' ')
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
                    *(fnc + dy * 0xf0 + dx) = 30000;
                }
            }
            if (key == 's')
            {
                lvlinfo.startx = dx;
                lvlinfo.starty = dy;
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x4f, &lvlinfo);
                strcpy(dline, "LVLINF");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, &lvlinfo, 8);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x6a, warps);
                strcpy(dline, "WARPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, warps, 0x28);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x73, &switches[0].effect);
                strcpy(dline, "SWITCH");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, &switches[0].effect, 0x1fa);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x7c, rtrips);
                strcpy(dline, "RTRIPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, rtrips, 300);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x85, etrips);
                strcpy(dline, "ETRIPS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, etrips, 300);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x8e, mtags);
                strcpy(dline, "MTAGS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, mtags, 0xf0);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0x97, mtriggers);
                strcpy(dline, "MTRIGS");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, mtriggers, 8000);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0xa0, bkg);
                strcpy(dline, "BKG");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, bkg, 0x3840);
                memcpy(sldsav, sld, 0x3840);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0xb2, sldsav);
                strcpy(dline, "SLDSAV");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, sldsav, 0x3840);
                for (i = 0; i < 0x17; i++)
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
                for (i = 0; i < 0x19; i++)
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
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0xa9, sld);
                strcpy(dline, "SLD");
                strcat(dline, itoa(game + 1, dumnum, 10));
                strcat(dline, itoa(level + 1, dumnum, 10));
                strcat(dline, ".LVL");
                save_disk_file(dline, sld, 0x3840);
                memcpy(sld, sldsav, 0x3840);
                save_file_from_byte_pointer(lvl_info_ofs[game][level] + 0xbb, fnc);
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
                        if (layer[0] != 0)
                        {
                            *(bkg + ((dy + y) - bty) * 0xf0 + dx + x - blx) = *(bkg + y * 0xf0 + x);
                        }
                        if (layer[1] != 0)
                        {
                            *(sld + ((dy + y) - bty) * 0xf0 + dx + x - blx) = *(sld + y * 0xf0 + x);
                        }
                        if (layer[2] != 0)
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
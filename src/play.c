#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "play.h"
#include "play2.h"
#include "gr.h"
#include "util.h"
#include "fileio.h"
#include "soundfx.h"
#include "design.h"
#include "joystick.h"
#include "menus.h"

int song2play[GAME_COUNT][LEVEL_COUNT] = {
    {3, 3, 4, 4, 0, 0, 2, 2, 2},
    {9, 9, 7, 7, 8, 8, 1, 1, 1},
    {4, 4, 0, 0, 7, 7, 6, 6, 6},
    {2, 2, 8, 8, 9, 9, 5, 5, 5}};

int lrelev[GAME_COUNT][LEVEL_COUNT+1][2] = {
    {{-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1}},
    {{-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1},
     {-1, -1}},
    {{78, 79},
     {78, 79},
     {62, 63},
     {62, 63},
     {40, 41},
     {40, 41},
     {85, 86},
     {85, 86},
     {85, 86},
     {-1, -1}},
    {{58, 59},
     {58, 59},
     {122, 123},
     {122, 123},
     {70, 71},
     {70, 71},
     {60, 61},
     {60, 61},
     {60, 61},
     {-1, -1}}};

int b4x[4] = {
    128, 128, 113, 128};

int b4y[4] = {
    54, 48, 42, 36};

int b4m[4] = {
    13088, 11648, 10193, 8768};

int b4d[4] = {
    1, 1, 0, 1};

int b4s[4] = {
    600, 400, 200, -1};

int hsjumpadd[25] = {
    -16, -16, -16, -16, -8, -8, -4, -4, -4, -2, -1, -1, 0, 1, 1, 2, 4, 4, 4, 8, 8, 16, 16, 16, 16};

int hnjumpadd[19] = {
    -16, -8, -8, -4, -4, -4, -2, -1, -1, 0, 1, 1, 2, 4, 4, 4, 8, 8, 16};

int hurtpower[4] = {
    -8, -14, -20, 0};

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

    hx1 = hxbpos + 3;
    hx2 = hxbpos + 2;
    hy1 = hylpos + 0x19;
    hy2 = hylpos + 6;
    for (i = 0; i < 8; i++)
    {
        if ((sc_life[i] != -1) && (sc_pause[i] == 0) &&
            (ouchcnt == 0) && (hinvis == 0) && (sc_x[i] <= hx1) &&
            (hx2 <= sc_x[i] + sc_xw[i] - 1) &&
            (sc_y[i] <= hy1) && (hy2 <= sc_y[i] + sc_yl[i] - 1))
        {
            health += hurtpower[skill];
            ouchcnt = 0x14;
            play_game_sound(8);
            sc_life[i] = -1;
        }
    }
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

    hx1 = hxbpos + 3;
    hx2 = hxbpos + 2;
    hy1 = hylpos + 0x19;
    hy2 = hylpos + 6;
    for (i = 0; i < 8; i++)
    {
        if ((mc_type[i] != -1) && (ouchcnt == 0) && (hinvis == 0) &&
            (mc_x[i] <= hx1) && (hx2 <= mc_x[i] + mc_xw[i] - 1) &&
            (mc_y[i] <= hy1) && (hy2 <= mc_y[i] + mc_yl[i] - 1))
        {
            if ((mc_ohits[i] > 0x14) && (skill != 3))
            {
                health = 0;
            }
            else
            {
                health += hurtpower[skill] * 2;
                ouchcnt = 0x14;
                play_game_sound(8);
            }
        }
    }
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

    for (i = 0; i < 8; i++)
    {
        if (mc_type[i] != -1)
        {
            mx1 = mc_x[i] - scrx * 2;
            my1 = mc_y[i] - scry * 16;
            expx = (mx1 + (mc_xw[i] / 2)) * 4;
            expy = (my1 + (mc_yl[i] / 2));
            new_explosion(expx, expy);
            play_game_sound(10);
            mc_type[i] = -1;
            monstershit++;
        }
    }
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

    for (i = 0; i < 8; i++)
    {
        if (mc_type[i] != -1)
        {
            mx1 = mc_x[i] - scrx * 2;
            mx2 = (mx1 + mc_xw[i]) - 1;
            my1 = mc_y[i] - scry * 16;
            my2 = (my1 + mc_yl[i]) - 1;
            expx = (mx1 + (mc_xw[i] / 2)) * 4;
            expy = (my1 + (mc_yl[i] / 2));
            for (j = 0; j < 5; j++)
            {
                sx = hfirex[j];
                sy = hfirey[j] + 2;
                if ((sx != -99) && (sx >= mx1) && (sx <= mx2) &&
                    (sy >= my1) && (sy <= my2))
                {
                    new_explosion(expx, expy);
                    if (hfirelaser[j] == 0)
                    {
                        hfirex[j] = -99;
                        hfireaway--;
                    }
                    if (mc_hits[i] == -2)
                    {
                        mc_hits[i] = -1;
                        smart_bomb_monsters();
                    }
                    else if (mc_hits[i] != -1)
                    {
                        if ((mc_hits[i] != 0) && (hfirelaser[j] == 0))
                        {
                            mc_hits[i]--;
                            mc_flash[i] = 10;
                        }
                        else
                        {
                            play_game_sound(10);
                            new_explosion(expx, expy);
                            new_explosion(expx, expy);
                            new_explosion(expx, expy);
                            mc_type[i] = -1;
                            fnc[mc_org[i]] = FNC_NONE;
                            monstershit++;
                        }
                    }
                }
            }
        }
    }
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

    for (i = 0; i < 8; i++)
    {
        if (mc_type[i] != -1)
        {
            kill = 0;
            if (mc_x[i] < (scrx * 2 - 0x32))
            {
            label:
                kill = 1;
            }
            else
            {
                if (mc_x[i] > (scrx * 2 + 0x78))
                {
                    goto label;
                }
                if (mc_y[i] < (scry * 16 - 0x78))
                {
                    goto label;
                }
                if (mc_y[i] > (scry * 16 + 0x1fe))
                {
                    kill = 1;
                }
            }
            if ((kill) && (mc_ohits[i] < 500))
            {
                mc_type[i] = -1;
                mc_org[i] = -1;
            }
        }
    }
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

    for (i = 0; i < 8; i++)
    {
        if (mc_type[i] == -1)
        {
            break;
        }
    }
    if (i == 8)
    {
        return 0;
    }

    sn = spr_num + 4;
    mc_begin[i] = 0x14;
    mc_shooting[i] = 0;
    mc_vo[i] = mtags[spr_num].vo;
    mc_snum[i] = sn;
    mc_mnum[i] = spr_num;
    mc_type[i] = mtags[spr_num].type;
    mc_mustface[i] = mtags[spr_num].mustface;
    mc_canshoot[i] = mtags[spr_num].canshoot;
    mc_stopshoot[i] = mtags[spr_num].stopshoot;
    mc_seek[i] = mtags[spr_num].shotfollow;
    mc_sink[i] = mtags[spr_num].sink;
    mc_x[i] = x;
    mc_y[i] = y;
    mc_yl[i] = sprite[sn].yl;
    mc_hits[i] = mtags[spr_num].tokill;
    mc_ohits[i] = mc_hits[i];
    mc_xw[i] = sprite[sn].xw;
    if (x > hxbpos)
    {
        mc_dir[i] = 1;
    }
    else
    {
        mc_dir[i] = 0;
    }
    if (mc_type[i] == 2)
    {
        mc_dir[i] = 0;
    }
    mc_frm[i] = 0;
    mc_flash[i] = 0;
    mc_org[i] = offset;
    mc_speed[i] = 1;
    mc_cnt[i] = 1;
    mc_charge[i] = 0;
    mc_jump[i] = -99;
    switch (mc_type[i])
    {
    case 8:
        mc_xp[i] = x;
        mc_sink[i] = myrnd(10) + 10;
        break;
    case 2:
        do
        {
            mc_xp[i] = myrnd(2) - myrnd(2);
            mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
        } while ((mc_xp[i] == 0) && (mc_yp[i] == 0));
        mc_mdly[i] = myrnd(0x14);
        break;
    case 3:
        do
        {
            mc_xp[i] = myrnd(2) - myrnd(2);
            mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
        } while ((mc_xp[i] == 0) && (mc_yp[i] == 0));
        mc_mdly[i] = myrnd(0x14);
        break;
    case 6:
        do
        {
            mc_xp[i] = myrnd(2) - myrnd(2);
            mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
        } while (mc_xp[i] == 0);
        mc_mdly[i] = myrnd(0x14);
        break;
    case 0:
        if (mc_dir[i] == 0)
        {
            mc_xp[i] = 1;
        }
        else
        {
            mc_xp[i] = -1;
        }
        mc_yp[i] = 0;
        break;
    case 7:
        if (mc_dir[i] == 0)
        {
            mc_xp[i] = 1;
        }
        else
        {
            mc_xp[i] = -1;
        }
        mc_yp[i] = 0;
        break;
    case 1:
        if (mc_dir[i] == 0)
        {
            mc_xp[i] = 1;
        }
        else
        {
            mc_xp[i] = -1;
        }
        mc_yp[i] = 0;
        break;
    case 4:
        mc_xp[i] = 0;
        mc_yp[i] = 0;
        mc_dir[i] = 0;
        mc_frm[i] = 0;
        play_game_sound(0xB);
        break;
    case 5:
        mc_xp[i] = 0;
        mc_yp[i] = 0;
        mc_frm[i] = 0;
        break;
    }
    return 1;
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

    for (i = 0; i < 8; i++)
    {
        if (sc_life[i] == -1)
        {
            break;
        }
    }
    if (i == 8)
    {
        return 0;
    }

    sc_pause[i] = wait;
    sc_dir[i] = 0;
    xp = 0;
    sc_wobble[i] = mtags[tag].wobble;
    if (d != 0)
    {
        if (x <= hxbpos)
        {
            xp = sprite[sn].xw;
            sc_dir[i] = 0;
        }
        else
        {
            xp = 0;
            sc_dir[i] = 1;
        }
    }
    sc_xw[i] = sprite[sn].sxw;
    sc_yl[i] = sprite[sn].syl + 3;
    sc_frm[i] = sprite[sn].sfrs;
    sc_fend[i] = sprite[sn].sfre;
    sc_life[i] = 30000;
    sc_x[i] = x + xp;
    sc_y[i] = y + sprite[sn].sys;
    sc_spr[i] = sn;
    sc_xp[i] = mtags[tag].hshotplus;
    sc_yp[i] = mtags[tag].vshotplus;
    sc_seek[i] = mtags[tag].shotfollow;
    sc_bounce[i] = 0;
    return 1;
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

    for (i = 0; i < 8; i++)
    {
        if (sc_life[i] != -1)
        {
            if (sc_pause[i] == 0)
            {
                mx = sc_x[i] - scrx * 2;
                my = sc_y[i] - scry * 16;
                kill = 0;
                if ((mx < -10) || (mx > 80) || (my < -20) || (my > 160))
                {
                    kill = 1;
                }
                if (*(sld + (sc_y[i] / 16) * 0xf0 + sc_x[i] / 4) != 0xff)
                {
                    kill = 2;
                }
                if (kill != 0)
                {
                    sc_life[i] = -1;
                    if (kill == 2)
                    {
                        new_explosion(mx * 4 + 8, my + 8);
                    }
                }
                else
                {
                    draw_sprite(sc_spr[i], sprite[sc_spr[i]].xw, mx, my, sc_dir[i], sc_frm[i]);
                    if (sc_frm[i] < sc_fend[i])
                    {
                        sc_frm[i]++;
                    }
                    if (sc_dir[i] == 0)
                    {
                        sc_x[i] += sc_xp[i];
                    }
                    else
                    {
                        sc_x[i] -= sc_xp[i];
                    }
                    if (sc_seek[i] != 0)
                    {
                        if (sc_x[i] < hxbpos)
                        {
                            sc_x[i]++;
                        }
                        else if (hxbpos < sc_x[i])
                        {
                            sc_x[i]--;
                        }
                    }
                    sc_y[i] += sc_yp[i];
                    if (sc_wobble[i] != 0)
                    {
                        sc_y[i] += (myrnd(2) - myrnd(2));
                    }
                }
            }
            else
            {
                sc_pause[i]--;
            }
        }
    }
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

    latches(0);
    enable_pixels(0xf);
    nb = ((float)mc_hits[i] / (float)mc_ohits[i]) * 78.0;
    for (i = 0; i < nb; i++)
    {
        c = 0x6F - (i / 10);
        // TODO: Is this correct?
        ((line_t)vga)[0x98][i + 1] = c;
        ((line_t)vga)[0x99][i + 1] = c;
        ((line_t)vga)[0x9A][i + 1] = c;
    }
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

    sn = mc_snum[i];
    show_hitbar(i);
    if (mc_begin[i] != 0)
    {
        mx = mc_x[i] - scrx * 2 + mc_xw[i] / 2;
        my = mc_y[i] - scry * 16 + mc_yl[i] / 2;
        if (myrnd(5) == 0)
        {
            new_twink(mx + myrnd(0x3) - myrnd(0x3), my + myrnd(0xc) - myrnd(0xc));
        }
        mc_begin[i]--;
    }
    else
    {
        mx = mc_x[i] - scrx * 2;
        my = mc_y[i] - scry * 16;
        if (mc_flash[i] % 2 != 0)
        {
            if (mc_frm[i] < 2)
            {
                mc_dir[i] = 0;
                d = mc_frm[i];
            }
            else
            {
                mc_dir[i] = 1;
                d = mc_frm[i] - 2;
            }
            draw_rsprite(sn, sprite[sn].xw, mx, my, mc_dir[i], d);
        }
        else
        {
            if (mc_frm[i] < 2)
            {
                mc_dir[i] = 0;
                d = mc_frm[i];
            }
            else
            {
                mc_dir[i] = 1;
                d = mc_frm[i] - 2;
            }
            draw_sprite(sn, sprite[sn].xw, mx, my, mc_dir[i], d);
        }
        if (mc_flash[i] != 0)
        {
            mc_flash[i]--;
        }
        if ((mc_frm[i] == 1) && (myrnd(10) == 0) && (hxbpos < mc_x[i]))
        {
            new_shot(mc_x[i], mc_y[i], 1, 0, mc_mnum[i], sn);
        }
        if (mc_sink[i] == 0)
        {
            mc_sink[i] = myrnd(10) + 10;
            if (mc_x[i] < mc_xp[i])
            {
                d = mc_xp[i] - mc_x[i];
                if (d >= 5)
                {
                    mc_x[i]++;
                    mc_frm[i]--;
                }
                else
                {
                    if (myrnd(2) == 0)
                    {
                        mc_x[i]++;
                        mc_frm[i]--;
                    }
                    else
                    {
                        mc_x[i]--;
                        mc_frm[i]++;
                    }
                }
            }
            else
            {
                d = mc_x[i] - mc_xp[i];
                if (d >= 5)
                {
                    mc_x[i]--;
                    mc_frm[i]++;
                }
                else
                {
                    if (myrnd(2) == 0)
                    {
                        mc_x[i]--;
                        mc_frm[i]++;
                    }
                    else
                    {
                        mc_x[i]++;
                        mc_frm[i]--;
                    }
                }
            }
        }
        if (mc_frm[i] > 3)
        {
            mc_frm[i] = 0;
        }
        if (mc_frm[i] < 0)
        {
            mc_frm[i] = 3;
        }
        mc_sink[i]--;
    }
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

    sn = mc_snum[0];
    show_hitbar(0);
    if (mc_begin[0] != 0)
    {
        mx = mc_x[0] - scrx * 2 + mc_xw[0] / 2;
        my = mc_y[0] - scry * 16 + mc_yl[0] / 2;
        if (myrnd(5) == 0)
        {
            new_twink(mx + myrnd(0x3) - myrnd(0x3), my + myrnd(0xc) - myrnd(0xc));
        }
        mc_begin[0]--;
    }
    else
    {
        if (mc_x[0] > hxbpos)
        {
            mc_dir[0] = 1;
        }
        else
        {
            mc_dir[0] = 0;
        }
        mx = mc_x[0] - scrx * 2;
        my = mc_y[0] - scry * 16;
        if (mc_flash[0] % 2 != 0)
        {
            draw_rsprite(sn, sprite[sn].xw, mx, my, mc_dir[0], mc_frm[0]);
        }
        else
        {
            draw_sprite(sn, sprite[sn].xw, mx, my, mc_dir[0], mc_frm[0]);
        }
        if (mc_flash[0] != 0)
        {
            mc_flash[0]--;
        }
        if (mc_seek[0] == 0)
        {
            if (mc_vo[0] == 0)
            {
                mc_frm[0] = 1;
                mc_vo[0] = 1;
                mc_seek[0] = 4;
            }
            else if (mc_vo[0] == 1)
            {
                mc_vo[0] = 2;
                mc_seek[0] = 1;
                new_shot(mc_x[0], mc_y[0], 1, 0, mc_mnum[0], sn);
            }
            else if (mc_vo[0] == 2)
            {
                mc_frm[0] = 0;
                mc_vo[0] = 0;
                mc_seek[0] = myrnd(0x2d) + 5;
            }
        }
        else
        {
            mc_seek[0]--;
        }
        if ((mc_hits[0] < b4s[b4p]) && (b4p < 4))
        {
            if (mc_vo[0] < 3)
            {
                mc_vo[0] = 3;
                mc_seek[0] = 0x14;
                mc_frm[0] = 2;
                play_game_sound(5);
            }
            else if (mc_seek[0] == 0)
            {
                b4p++;
                mc_type[0] = -1;
                new_monster(0, (b4x[b4p] * 4), (b4y[b4p] * 16), b4m[b4p]);
                mc_hits[0] = b4d[b4p + 3];
                mc_dir[0] = b4d[b4p];
                mc_xp[0] = 0;
                mc_seek[0] = myrnd(0x32) + 5;
                mc_vo[0] = 0;
            }
        }
    }
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

    for (i = 0; i < 8; i++)
    {
        if (mc_type[i] != -1)
        {
            if (mc_type[i] == 8)
            {
                update_boss3(i);
                continue;
            }
            if (mc_type[i] == 99)
            {
                update_boss4();
                continue;
            }
            if (mc_ohits[i] > 0x14)
            {
                show_hitbar(i);
            }
            if (mc_begin[i] == 0)
            {
                sn = mc_snum[i];
                if (mc_cnt[i] == 0)
                {
                    ox = mc_x[i];
                    oy = mc_y[i];
                    if (mc_jump[i] != -99)
                    {
                        mc_y[i] += mc_jump[i];
                        mc_jump[i]++;
                        if (mc_jump[i] == 7)
                        {
                            mc_jump[i] = -99;
                            mc_frm[i] = 0;
                        }
                    }
                    else
                    {
                        mc_x[i] += mc_xp[i];
                        mc_y[i] += mc_yp[i];
                        if (mc_jump[i] == -99)
                        {
                            mpos = mc_y[i] / 16 * 0xF0 + mc_x[i] / 4;
                            if (mc_dir[i] == 0)
                            {
                                mpos++;
                            }
                            wmpos = mpos;
                            mxw = mc_xw[i] / 4;
                            if ((mc_x[i] % 4))
                            {
                                mxw++;
                            }
                            myl = mc_yl[i] / 16;
                            if ((mc_y[i] % 16))
                            {
                                myl++;
                            }
                            reset = 0;
                            for (y = 0; y < myl; y++)
                            {
                                wmpos = (mc_y[i] / 16 + y) * 0xF0 + mc_x[i] / 4;
                                for (x = 0; x < mxw; x++)
                                {
                                    if (sld[wmpos] != 0xff)
                                    {
                                        reset = 1;
                                    }
                                    wmpos++;
                                }
                            }
                        }
                    }
                    switch (mc_type[i])
                    {
                    case 2:
                        if (mc_mdly[i] <= 0)
                        {
                            reset = 1;
                        }
                        if (reset != 0)
                        {
                            mc_x[i] = ox;
                            mc_y[i] = oy;
                            mc_mdly[i] = myrnd(0x1E) + 5;
                            do
                            {
                                if (mc_seek[i] == 0)
                                {
                                    mc_xp[i] = myrnd(2) - myrnd(2);
                                }
                                else
                                {
                                    if (mc_x[i] > hxbpos)
                                    {
                                        mc_xp[i] = -myrnd(2);
                                    }
                                    else
                                    {
                                        mc_xp[i] = myrnd(2);
                                    }
                                }
                                mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
                            } while ((mc_xp[i] == 0) && (mc_yp[i] == 0));
                        }
                        mc_mdly[i]--;
                        break;
                    case 3:
                        if (mc_mdly[i] <= 0)
                        {
                            reset = 1;
                        }
                        if (reset != 0)
                        {
                            mc_x[i] = ox;
                            mc_y[i] = oy;
                            mc_mdly[i] = myrnd(0x1E) + 5;
                            do
                            {
                                mc_xp[i] = myrnd(2) - myrnd(2);
                                mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
                            } while ((mc_xp[i] == 0) && (mc_yp[i] == 0));

                            if (mc_x[i] > hxbpos)
                            {
                                mc_dir[i] = 1;
                            }
                            else
                            {
                                mc_dir[i] = 0;
                            }
                        }
                        mc_mdly[i]--;
                        break;
                    case 6:
                        if (mc_mdly[i] <= 0)
                        {
                            reset = 1;
                        }

                        if (mc_x[i] > hxbpos)
                        {
                            mc_dir[i] = 1;
                        }
                        else
                        {
                            mc_dir[i] = 0;
                        }

                        if (reset != 0)
                        {
                            mc_x[i] = ox;
                            mc_y[i] = oy;
                            mc_mdly[i] = myrnd(0x1E) + 5;
                            do
                            {
                                mc_xp[i] = myrnd(2) - myrnd(2);
                                mc_yp[i] = (myrnd(2) - myrnd(2)) * 4;
                                mc_xp[i] *= 2;
                            } while ((mc_xp[i] == 0));
                        }
                        mc_mdly[i]--;
                        break;
                    case 0:
                        wmpos = mpos + myl * 0xf0;
                        if (mc_dir[i] == 0)
                        {
                            wmpos += mxw - 2;
                        }
                        if (sld[wmpos] == 0xff)
                        {
                            reset = 1;
                        }

                        if (reset != 0)
                        {
                            mc_x[i] = ox;
                            mc_y[i] = oy;
                            mc_dir[i] = !mc_dir[i];

                            if (mc_dir[i] == 0)
                            {
                                mc_xp[i] = 1;
                            }
                            else
                            {
                                mc_xp[i] = -1;
                            }
                        }
                        if (myrnd(0x14) == 0)
                        {
                            if (mc_x[i] > hxbpos)
                            {
                                mc_dir[i] = 1;
                            }
                            else
                            {
                                mc_dir[i] = 0;
                            }

                            if (mc_dir[i] == 0)
                            {
                                mc_xp[i] = 1;
                            }
                            else
                            {
                                mc_xp[i] = -1;
                            }
                        }
                        break;
                    case 7:
                        if (mc_jump[i] != -99)
                        {
                            wmpos = mpos + myl * 0xf0;
                            if (mc_dir[i] == 0)
                            {
                                wmpos += mxw - 2;
                            }

                            if (sld[wmpos] == 0xff)
                            {
                                reset = 1;
                            }

                            if (reset != 0)
                            {
                                mc_x[i] = ox;
                                mc_y[i] = oy;
                                mc_dir[i] = !mc_dir[i];
                                if (mc_dir[i] == 0)
                                {
                                    mc_xp[i] = 1;
                                }
                                else
                                {
                                    mc_xp[i] = -1;
                                }
                            }
                            if (myrnd(0x14) == 0)
                            {
                                if (mc_x[i] > hxbpos)
                                {
                                    mc_dir[i] = 1;
                                }
                                else
                                {
                                    mc_dir[i] = 0;
                                }

                                if (mc_dir[i] == 0)
                                {
                                    mc_xp[i] = 1;
                                }
                                else
                                {
                                    mc_xp[i] = -1;
                                }
                            }
                        }
                        else
                        {
                            for (i = 0; i < 5; i++)
                            {
                                if (hfirex[i] != -99)
                                {
                                    // TODO: Is this correct?
                                    if (abs(((hfirex[i] - mc_x[i]) < 10)))
                                    {
                                        mc_jump[i] = -6;
                                    }
                                }
                            }
                        }
                        break;
                    case 1:
                        wmpos = mpos + myl * 0xf0;
                        if (mc_dir[i] == 0)
                        {
                            wmpos += mxw - 2;
                        }
                        if (sld[wmpos] == 0xff)
                        {
                            reset = 1;
                        }

                        if (reset != 0)
                        {
                            mc_x[i] = ox;
                            mc_y[i] = oy;
                            mc_dir[i] = !mc_dir[i];
                            if (mc_dir[i] == 0)
                            {
                                mc_xp[i] = 1;
                            }
                            else
                            {
                                mc_xp[i] = -1;
                            }
                        }
                        if (myrnd(0x14) == 0)
                        {
                            if (mc_x[i] > hxbpos)
                            {
                                mc_dir[i] = 1;
                                mc_charge[i] = myrnd(0xf) + 10;
                                if (sprite[sn].afrs != -1)
                                {
                                    mc_frm[i] = sprite[sn].afrs;
                                }
                            }
                            else
                            {
                                mc_dir[i] = 0;
                                mc_charge[i] = myrnd(0xf) + 10;
                                if (sprite[sn].afrs != -1)
                                {
                                    mc_frm[i] = sprite[sn].afrs;
                                }
                            }
                            if (mc_dir[i] == 0)
                            {
                                mc_xp[i] = 1;
                            }
                            else
                            {
                                mc_xp[i] = -1;
                            }
                        }
                        break;
                    case 5:
                        if (mc_x[i] > hxbpos)
                        {
                            mc_dir[i] = 1;
                        }
                        else
                        {
                            mc_dir[i] = 0;
                        }
                        break;
                    }
                    mc_frm[i]++;
                    if (mc_charge[i] != 0)
                    {
                        if (sprite[sn].afrs != -1)
                        {
                            if (sprite[sn].afre < mc_frm[i])
                            {
                                mc_frm[i] = sprite[sn].afrs;
                            }
                        }
                        else
                        {
                            if (sprite[sn].mfre < mc_frm[i])
                            {
                                mc_frm[i] = sprite[sn].mfrs;
                            }
                        }
                    }
                    else
                    {
                        if (mc_shooting[i] != 0)
                        {
                            if (sprite[sn].afre < mc_frm[i])
                            {
                                mc_shooting[i] = 0;
                                mc_frm[i] = sprite[sn].mfrs;
                            }
                        }
                        else
                        {
                            if (sprite[sn].mfre < mc_frm[i])
                            {
                                mc_frm[i] = sprite[sn].mfrs;
                            }
                        }
                    }
                    if (mc_charge[i] == 0)
                    {
                        mc_cnt[i] = mc_speed[i];
                    }
                    else
                    {
                        mc_cnt[i] = 0;
                        mc_charge[i]--;
                    }
                }
                else
                {
                    mc_cnt[i]--;
                }
                if ((mc_canshoot[i] != 0) && (myrnd(lvlinfo.shot_freq) == 0))
                {
                    x = sprite[sn].afre - sprite[sn].afre + 1;
                    y = 0;
                    mc_shooting[i] = 1;
                    if (mtags[mc_mnum[i]].hshotplus != 0)
                    {
                        if (mc_mustface[i] != 0)
                        {
                            if (mc_type[i] == 5)
                            {
                                x = sprite[sn].afre - sprite[sn].afrs;
                            }
                            if ((mc_x[i] <= hxbpos) && (mc_dir[i] == 0))
                            {
                                y = new_shot(mc_x[i], mc_y[i], 1, x, mc_mnum[i], sn);
                            }
                            else if ((mc_x[i] > hxbpos) && (mc_dir[i] != 0))
                            {
                                y = new_shot(mc_x[i], mc_y[i], 1, x, mc_mnum[i], sn);
                            }
                        }
                        else
                        {
                            if (mc_x[i] <= hxbpos)
                            {
                                y = new_shot(mc_x[i], mc_y[i], 1, x, mc_mnum[i], sn);
                            }
                            else
                            {
                                y = new_shot(mc_x[i], mc_y[i], 1, x, mc_mnum[i], sn);
                            }
                        }
                    }
                    else
                    {
                        y = new_shot(mc_x[i] + mc_vo[i], mc_y[i] + mc_yl[i], 0, x, mc_mnum[i], sn);
                    }
                    if (y == 0)
                    {
                        mc_shooting[i] = 0;
                    }
                    if (sprite[sn].afrs != -1)
                    {
                        mc_frm[i] = sprite[sn].afrs;
                    }
                }
                if (mc_jump[i] != -99)
                {
                    mc_frm[i] = sprite[sn].jfrs;
                }
                mx = mc_x[i] - (scrx * 2);
                my = mc_y[i] - (scry * 16);

                if ((mc_flash[i] % 2))
                {
                    draw_rsprite(sn, sprite[sn].xw, mx, my, mc_dir[i], mc_frm[i]);
                }
                else
                {
                    draw_sprite(sn, sprite[sn].xw, mx, my, mc_dir[i], mc_frm[i]);
                }
                if (mc_flash[i] != 0)
                {
                    mc_flash[i]--;
                }
            }
            if (mc_begin[i] != 0)
            {
                mx = (mc_x[i] - (scrx * 2)) + (mc_xw[i] / 2);
                my = (mc_y[i] - (scry * 16)) + (mc_yl[i] / 2);
                if (myrnd(5) == 0)
                {
                    new_twink(mx + myrnd(0x3) - myrnd(0x3), my + myrnd(0xc) - myrnd(0xc));
                }
                mc_begin[i]--;
            }
        }
    }
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

    latches(0);
    for (i = 0; i < 8; i++)
    {
        x = twinkpos[i][0];
        y = twinkpos[i][1];
        c = twinkpos[i][2];
        clr = twinkpos[i][3];
        if (c != 0)
        {
            if ((c == 9) || (c == 1))
            {
                draw_sprite(3, sprite[3].xw, x, y, clr, 0);
            }
            if ((c == 8) || (c == 2))
            {
                draw_sprite(3, sprite[3].xw, x, y, clr, 1);
            }
            if ((c == 7) || (c == 3))
            {
                draw_sprite(3, sprite[3].xw, x, y, clr, 2);
            }
            if ((c == 6) || (c == 4))
            {
                draw_sprite(3, sprite[3].xw, x, y, clr, 3);
            }
            if (c == 5)
            {
                draw_sprite(3, sprite[3].xw, x, y, clr, 4);
            }
            twinkpos[i][2]--;
        }
    }
}

// module: PLAY
// size: 0x58
// addr: 0CDE:20A8
void new_twink(int x, int y)
{
    twinkpos[twinknum][0] = x;
    twinkpos[twinknum][1] = y;
    twinkpos[twinknum][2] = 9;
    twinkpos[twinknum][3] = myrnd(2);
    twinknum++;
    if (twinknum >= 8)
    {
        twinknum = 0;
    }
}

// module: PLAY
// size: 0x37
// addr: 0CDE:2100
void flash_screen(void)
{
    latches(0);
    setmem(vga, 0x3200, 0x77 - flash_flag);
    flash_flag--;
    latches(1);
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

    for (s = 0; s < SPRITES_COUNT; s++)
    {
        if (sload[s] != -1)
        {
            pos = sload[s];
            point_to_data_record(OFFSET_SPRITES);
            fseek(databasefp, (pos * sizeof(sprite_t)), 1);
            fread(&sprite[s], sizeof(sprite_t), 1, databasefp);
            point_to_data_record(OFFSET_SPRITES);
            fseek(databasefp, sprite[s].fpos, 1);
            fread(spr_code[s], sprite[s].codesize, 1, databasefp);
            setapage(2);
            fread(buf64, sprite[s].datasize, 1, databasefp);
            latches(0);
            sdatabase[s] = sprbase >> 2;
            pe = sprbase + sprite[s].datasize;
            for (i = sprbase; i < pe; i++)
            {
                pixel(i % SCREEN_WIDTH, i / SCREEN_WIDTH, *(&buf64[i] - sprbase));
            }
            sprbase += sprite[s].datasize;
        }
    }
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

    i = sprite[snum].codeofs[dir][frm];
    spnt = sdatabase[snum] + sprite[snum].dataofs[dir][frm];
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        goto start;
    }
    else if (code == 1)
    {
        dpnt += *(int16_t *)&spr_code[snum][i];
        i += 2;
        goto start;
    }
    else if (code == 2)
    {
        vga[dpnt] = vgap[2][spnt];
        spnt++;
        dpnt++;
        goto start;
    }
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

    px = py = 0;
    i = sprite[snum].codeofs[dir][frm];
    spnt = sdatabase[snum] + sprite[snum].dataofs[dir][frm];
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        px = py = 0;
        goto start;
    }
    else if (code == 1)
    {
        j = *(int16_t *)&spr_code[snum][i];
        i += 2;
        dpnt += j;
        px += j;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
    else if (code == 2)
    {
        if (px + x >= 0 && px + x < 0x50 && py + y >= 0 && py + y < 0xA0)
        {
            vga[dpnt] = vgap[2][spnt];
        }
        spnt++;
        dpnt++;
        px++;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
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

    i = sprite[snum].codeofs[dir][frm];
    spnt = whitedata;
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        goto start;
    }
    else if (code == 1)
    {
        dpnt += *(int16_t *)&spr_code[snum][i];
        i += 2;
        goto start;
    }
    else if (code == 2)
    {
        vga[dpnt] = vgap[2][spnt];
        dpnt++;
        goto start;
    }
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

    px = py = 0;
    i = sprite[snum].codeofs[dir][frm];
    spnt = whitedata;
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        px = py = 0;
        goto start;
    }
    else if (code == 1)
    {
        j = *(int16_t *)&spr_code[snum][i];
        i += 2;
        dpnt += j;
        px += j;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
    else if (code == 2)
    {
        if (px + x >= 0 && px + x < 0x50 && py + y >= 0 && py + y < 0xA0)
        {
            vga[dpnt] = vgap[2][spnt];
        }
        dpnt++;
        px++;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
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

    i = sprite[snum].codeofs[dir][frm];
    spnt = reddata;
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        goto start;
    }
    else if (code == 1)
    {
        dpnt += *(int16_t *)&spr_code[snum][i];
        i += 2;
        goto start;
    }
    else if (code == 2)
    {
        vga[dpnt] = vgap[2][spnt];
        dpnt++;
        goto start;
    }
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

    px = py = 0;
    i = sprite[snum].codeofs[dir][frm];
    spnt = reddata;
    dpnt = y * VGA_PLANE_WIDTH + x;
    latches(1);
start:
    code = spr_code[snum][i++];
    if (code == 0)
    {
        enable_pixels(spr_code[snum][i]);
        dpnt = y * VGA_PLANE_WIDTH + x;
        i++;
        px = py = 0;
        goto start;
    }
    else if (code == 1)
    {
        j = *(int16_t *)&spr_code[snum][i];
        i += 2;
        dpnt += j;
        px += j;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
    else if (code == 2)
    {
        if (px + x >= 0 && px + x < 0x50 && py + y >= 0 && py + y < 0xA0)
        {
            vga[dpnt] = vgap[2][spnt];
        }
        dpnt++;
        px++;
        if (px > xw)
        {
            py += px / 0x50;
            px = px % 0x50;
        }
        goto start;
    }
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

    oldscry = scry;
    oldscrx = scrx;
    hxbpos = hxpos * 2;
    hypos = hylpos / 16;
    scrxh = 0;
    if (snapcoords != 0)
    {
        if ((hxpos - 0x14) < 0)
        {
            scrx = 0;
        }
        else
        {
            if ((hxpos + 0x14) >= 0x1e0)
            {
                scrx = 0x1b8;
            }
            else
            {
                scrx = hxpos - 0x14;
                if (hxpos % 2 != 0)
                {
                    scrxh = 1;
                }
            }
        }
    }
    else
    {
        if ((hxpos - 0x14) < 0)
        {
            scrx = 0;
        }
        else
        {
            if ((hxpos + 0x14) >= 0x1e0)
            {
                scrx = 0x1b8;
            }
            else
            {
                if (scrx < (hxpos - 0x14))
                {
                    scrx++;
                }
                else if ((hxpos - 0x14) < scrx)
                {
                    scrx--;
                }
                if (hxpos % 2 != 0)
                {
                    scrxh = 1;
                }

                scrxdif = (oldscrx - scrx) * 8;
                for (i = 0; i < 8; i++)
                {
                    if (expcnt[i] > 0)
                    {
                        for (j = 0; j < 16; j++)
                        {
                            exppos[i][j][0] += scrxdif;
                        }
                    }
                }
                scrxdif /= 4;
                for (i = 0; i < 10; i++)
                {
                    stag[i][0] += scrxdif;
                }
                for (i = 0; i < 8; i++)
                {
                    twinkpos[i][0] += scrxdif;
                }
            }
        }
    }

    hxmpos = hxpos / 2;
    scrmx = scrx / 2;
    hstopjump = 0;
    if (snapcoords == 0)
    {
        if (hjump == 0)
        {
            if (hypos - ylevel < 0)
            {
                scry = 0;
            }
            else if ((hypos + (10 - ylevel)) >= 0x3c)
            {
                scry = 0x32;
            }
            else
            {
                if (scry < (hypos - ylevel))
                {
                    scry++;
                    hstopjump = 1;
                }
                else if ((hypos - ylevel) < scry)
                {
                    scry--;
                    hstopjump = 1;
                }
            }
            scrydif = (oldscry - scry) * 16;
            for (i = 0; i < 5; i++)
            {
                hfirey[i] += scrydif;
            }
            for (i = 0; i < 8; i++)
            {
                if (expcnt[i] > 0)
                {
                    for (j = 0; j < 16; j++)
                    {
                        exppos[i][j][1] += scrydif;
                    }
                }
            }
            for (i = 0; i < 10; i++)
            {
                stag[i][1] += scrydif;
            }
            for (i = 0; i < 8; i++)
            {
                twinkpos[i][1] += scrydif;
            }
        }
    }
    else if (hjump == 0)
    {
        if (hypos - ylevel < 0)
        {
            scry = 0;
        }
        else if ((hypos + ylevel) >= 0x3c)
        {
            scry = 0x32;
        }
        else
        {
            scry = hypos - ylevel;
        }
    }
    hxbspos = (hxpos - scrx) * 2;
    hylspos = hylpos - scry * 16;
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

    switchcnt--;
    mpos = scry * 0xf0 + scrmx;
    for (y = 0; y < 10; y++)
    {
        for (x = 0; x < 0x15; x++)
        {
            e = swe[mpos];
            if (e != 0)
            {
                if (switchcnt == 0)
                {
                    if (e == 1)
                    {
                        sld[mpos] = 0xff;
                        swe[mpos] = 0;
                    }
                    else if (e == 2)
                    {
                        sld[mpos] = sldsav[mpos];
                        swe[mpos] = 0;
                    }
                }
                else
                {
                    rndnum++;
                    if (rndnum > 999)
                    {
                        rndnum = 0;
                    }

                    ne = rnd[rndnum] % 3;
                    if (ne == 0)
                    {
                        if (e == 1)
                        {
                            sld[mpos] = 0xff;
                            swe[mpos] = 0;
                            if (x < 0x14)
                            {
                                new_twink(x * 4 - scrxh * 2, y * 16);
                            }
                        }
                        else if (e == 2)
                        {
                            sld[mpos] = sldsav[mpos];
                            swe[mpos] = 0;
                            if (x < 0x14)
                            {
                                new_twink(x * 4 - scrxh * 2, y * 16);
                            }
                        }
                    }
                }
            }
            e = bkg[mpos];
            ne = e;
            if ((e < 0xf0) && (anminfo.v[e][2] != 0))
            {
                if (anminfo.v[e][2] == 1)
                {
                    ne++;
                    if (anminfo.v[e][1] < ne)
                    {
                        ne = anminfo.v[e][0];
                    }
                }
                else if (anminfo.v[e][2] == 2)
                {
                    if (anminfo.v[e][0] != e)
                    {
                        ne++;
                        if (anminfo.v[e][1] < ne)
                        {
                            ne = anminfo.v[e][0];
                        }
                    }
                    else
                    {
                        rndnum++;
                        if (rndnum > 999)
                        {
                            rndnum = 0;
                        }
                        if ((rnd[rndnum] % 0x14) == 0)
                        {
                            ne++;
                        }
                    }
                }
                bkg[mpos] = ne;
            }
            mpos++;
        }
        mpos += 0xdb;
    }
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

    for (i = 0; i < 0x20; i++)
    {
        if (mr_offset[i] != -1)
        {
            mpos = mr_offset[i];
            e = fnc[mpos];
            y = mpos / 0xf0;
            x = mpos % 0xf0;
            if (e != FNC_NONE)
            {
                if (new_monster(e - FNC_SPRITES_START, x * 4, y * 16, mpos) != 0)
                {
                    mr_offset[i] = -1;
                }
            }
        }
    }
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

    expcnt[expnum] = 16;
    for (i = 0; i < 16; i++)
    {
        exppos[expnum][i][0] = x;
        expmisc[expnum][i][0] = myrnd(10) - myrnd(10);
        exppos[expnum][i][1] = y;
        expmisc[expnum][i][1] = -(myrnd(7) + 5);
        j = myrnd(2);
        if (j == 0)
        {
            expmisc[expnum][i][2] = 0x70;
        }
        else
        {
            expmisc[expnum][i][2] = 0x60;
        }
    }
    expnum++;
    if (expnum >= 8)
    {
        expnum = 0;
    }
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

    latches(0);
    outportb(0x3c4, 2);
    for (i = 0; i < 8; i++)
    {
        if (expcnt[i] > 0)
        {
            for (j = 0; j < 16; j++)
            {
                exppos[i][j][1] += expmisc[i][j][1];
                expmisc[i][j][1]++;
                exppos[i][j][0] += expmisc[i][j][0];
                if (!expcnt[i] % 4)
                {
                    expmisc[i][j][2]++;
                }
                x = exppos[i][j][0];
                y = exppos[i][j][1];
                if ((x >= 0) && (x <= 319) && (y >= 0) && (y <= 159))
                {
                    outportb(0x3c5, 1 << (x % 4));
                    ((line_t)vga)[y][x >> 2] = expmisc[i][j][2];
                    //*(vga+y*VGA_PLANE_WIDTH+(x>>2)) = expmisc[i][j][2];
                }
            }
            expcnt[i]--;
        }
    }
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

    dbase = digit * 2 + 0x3200;
    sbase = base;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
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

    dbase = image * 2 + 0x3216;
    sbase = base;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
    vga[sbase] = vgap[3][dbase];
    sbase++;
    dbase++;
    vga[sbase] = vgap[3][dbase];
    sbase += 0x4f;
    dbase += 0x4f;
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

    do_fast_digit(0x3979, level + 1);
    ltoa(score, dumnum, 10);
    l = 0;
    while (dumnum[l] != 0)
    {
        l++;
    }
    for (i = 0; i < l; i++)
    {
        do_fast_digit((0x38EA - l) + i * 2, dumnum[i] - '0');
    }
    if (health > 100)
    {
        health = 100;
    }
    if (health < 0)
    {
        health = 0;
    }
    itoa(health, dumnum, 10);
    l = 0;
    while (dumnum[l] != 0)
    {
        l++;
    }
    for (i = 0; i < 3; i++)
    {
        do_fast_digit((0x38F6) + i * 2, 10);
    }
    for (i = 0; i < l; i++)
    {
        do_fast_digit((0x38FC - l * 2) + i * 2, dumnum[i] - '0');
    }
    itoa(crystals_found, dumnum, 10);
    do_fast_digit(0x3907, dumnum[0] - '0');
    itoa(crystals, dumnum, 10);
    do_fast_digit(0x390b, dumnum[0] - '0');
    do_fast_key(0x38c5, 2);
    do_fast_key(0x38c7, 2);
    if ((hskey + hgkey) > 1)
    {
        do_fast_key(0x38c5, 0);
        do_fast_key(0x38c7, 1);
    }
    if ((hskey + hgkey) == 1)
    {
        if (hskey != 0)
        {
            do_fast_key(0x38c6, 0);
        }
        else
        {
            do_fast_key(0x38c6, 1);
        }
    }
}

// module: PLAY
// size: 0x45
// addr: 0CDE:361A
void count_crystals(void)
{
    // register: CX
    // size: 2
    int i;

    crystals = 0;
    for (i = 0; i < 0x3840; i++)
    {
        if ((fnc[i] < (FNC_UPS_END + 1)) && (ups[fnc[i]].powermode == 1))
        {
            crystals++;
        }
    }
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

    for (i = 0; i < 10; i++)
    {
        if (stag[i][3] == 0)
        {
            if (num > 4)
            {
                stag[i][4] = 1;
                num -= 5;
            }
            else
            {
                stag[i][4] = 0;
            }
            stag[i][0] = x;
            stag[i][1] = y;
            stag[i][2] = num;
            stag[i][3] = 0x11;
            break;
        }
    }
}

// module: PLAY
// size: 0x7f
// addr: 0CDE:36E9
void update_stags(void)
{
    // register: SI
    // size: 2
    int i;

    for (i = 0; i < 10; i++)
    {
        if (stag[i][3] != 0)
        {
            draw_sprite(1, sprite[1].xw, stag[i][0], stag[i][1], stag[i][4], stag[i][2]);
            stag[i][1] -= 2;
            stag[i][3]--;
        }
    }
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

    xl = pstrlen("Game Paused");
    setapage(vpg);
    sy = 0x4c;
    sx = 0xa0 - (xl / 2);
    pstrwiznote(sx + 1, sy + 1, 1, "Game Paused");
    pstrwiznote(sx, sy, 0x68, "Game Paused");
    if (game_config.joystick != 0)
    {
        gkey = 0x80;
        while ((button1 == 0) && (button2 == 0) && (gkey >= 0x80))
        {
            JOY_PollButtons();
        }
    }
    else
    {
        while (gkey < 0x80)
            ;
        while (gkey >= 0x80)
            ;
    }

    setapage(!vpg);
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

    xl = 0;
    nl = 0;
    for (i = 0; i < 10; i++)
    {
        l = pstrlen(wiznotes[num].text[i]);
        if (l != 0)
        {
            if (l > xl)
            {
                xl = l;
            }
            nl++;
        }
        else
        {
            break;
        }
    }
    setapage(vpg);
    sy = 0x50 - nl * 12;
    sx = 0xA0 - xl / 2;

    for (i = 0; i < nl; i++)
    {
        pstrwiznote(sx + 1, sy + i * 12 + 1, 1, wiznotes[num].text[i]);
        pstrwiznote(sx, sy + i * 12, 0x68, wiznotes[num].text[i]);
    }

    if (indemo == 0)
    {
        if (game_config.joystick != 0)
        {
            gkey = 0x80;
            while ((button1 == 0) && (button2 == 0) && (gkey >= 0x80))
            {
                JOY_PollButtons();
            }
        }
        else
        {
            while (gkey < 0x80)
                ;
            while (gkey >= 0x80)
                ;
        }
    }
    else
    {
        snooze(8000);
    }
    setapage(!vpg);
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

    mpos = hypos * 0xf0 + (hxpos + 1) / 2;
    x = hxbspos - 1;
    y = hylspos - 16;
    if (ouchcnt != 0)
    {
        ouchcnt--;
    }
    uppressed = 0;
    i = 0;
    while (i < 2)
    {
        v = fnc[mpos];
        keep = 0;
        if (v != FNC_NONE)
        {
            if (v < (FNC_UPS_END + 1))
            {
                pm = ups[v].powermode;
                if ((ups[v].add2health != 0) && (health < 100))
                {
                    play_game_sound(1);
                }
                else
                {
                    if (ups[v].add2health != 0)
                    {
                        keep = 1;
                    }
                    else
                    {
                        if (ups[v].add2score != 0)
                        {
                            treasuresfound++;
                            vv = ups[v].add2score;
                            if (vv == 100)
                            {
                                new_stag(x, y, 0);
                            }
                            else if (vv == 250)
                            {
                                new_stag(x, y, 1);
                            }
                            else if (vv == 500)
                            {
                                new_stag(x, y, 2);
                            }
                            else if (vv == 1000)
                            {
                                new_stag(x, y, 3);
                            }
                            else if (vv == 5000)
                            {
                                new_stag(x, y, 4);
                            }
                            play_game_sound(2);
                        }
                        else if (pm == 1)
                        {
                            crystals_found++;
                            flash_flag = 8;
                            play_game_sound(3);
                        }
                        else if (pm == 2)
                        {
                            keep = 1;
                            if ((ouchcnt == 0) && (hinvis == 0))
                            {
                                health += hurtpower[skill];
                                ouchcnt = 0x14;
                                play_game_sound(8);
                            }
                        }
                        else if (pm == 9)
                        {
                            if ((hinvis == 0) && (skill != 3))
                            {
                                health = 0;
                            }
                            keep = 1;
                        }
                        else if (pm == 3)
                        {
                            hinvis = 0x190;
                            new_twink(hxbspos - 1, hylspos);
                            new_twink(hxbspos + 4, hylspos);
                            new_twink(hxbspos - 1, hylspos + 16);
                            new_twink(hxbspos + 4, hylspos + 16);
                            ouchcnt = 0;
                            play_game_sound(5);
                            new_stag(x, y, 8);
                        }
                        else if (pm == 4)
                        {
                            if (hjumphigh == 0)
                            {
                                hjumphigh = 1;
                                htwinkletoes = 0x19;
                                play_game_sound(9);
                                new_stag(x, y, 7);
                            }
                            else
                            {
                                keep = 1;
                            }
                        }
                        else if (pm == 5)
                        {
                            if (hsupershot == 0)
                            {
                                holdshots = hfirepower;
                                hfirepower = 5;
                            }
                            hsupershot = 0x258;
                            play_game_sound(9);
                            new_stag(x, y, 9);
                        }
                        else if (pm == 7)
                        {
                            hskey = 1;
                            play_game_sound(9);
                            new_stag(x, y, 5);
                        }
                        else if (pm == 8)
                        {
                            hgkey = 1;
                            play_game_sound(9);
                            new_stag(x, y, 5);
                        }
                        else if (pm == 10)
                        {
                            keep = 1;
                            if (ukey != 0)
                            {
                                for (x = 0; x < 10; x++)
                                {
                                    if ((wiznotes[x].rx == hypos) && (abs(wiznotes[x].lx - hxmpos) < 3))
                                    {
                                        latches(0);
                                        enable_pixels(0xf);
                                        play_game_sound(4);
                                        do_wiznote(x);
                                        uppressed = 1;
                                        latches(1);
                                        enable_pixels(0xf);
                                    }
                                }
                                ukey = 0;
                            }
                        }
                        else if (pm == 11)
                        {
                            hlaser = 3;
                            play_game_sound(9);
                            hlaserdisplay = 1;
                            hlaserdisplaycnt = 5;
                        }
                    }
                }
                if (ups[v].add2shots != 0)
                {
                    play_game_sound(9);
                }

                hfirepower += ups[v].add2shots;
                if (hfirepower > 5)
                {
                    hfirepower = 5;
                }

                if (hsupershot != 0)
                {
                    holdshots += ups[v].add2shots;
                    if (holdshots > 5)
                    {
                        holdshots = 5;
                    }
                }
                score += ups[v].add2score;
                health += ups[v].add2health;
                if (keep == 0)
                {
                    fnc[mpos] = FNC_NONE;
                    bkg[mpos] = anminfo.defaultbkg;
                }
            }
            else if (v < (FNC_WARPS_END + 1))
            {
                if (warps[v - FNC_WARPS_START].src == mpos)
                {
                    hinwarp = 1;
                    vv = v - 23;
                    hwarpdy = (warps[vv].dest / 0xf0) * 16;
                    hwarpdx = (warps[vv].dest % 0xf0) * 2;
                    hfrm = sprite[0].frs;
                    hjump = 0;
                    hylpos = (hylpos / 16) * 16;
                    fnc[mpos] = FNC_NONE;
                    bkg[mpos] = anminfo.defaultbkg;
                    play_game_sound(4);
                    new_stag(x, y, 6);
                }
            }
            else if (v < (FNC_SWITCHES_END + 1))
            {
                if (ukey != 0)
                {
                    ukey = 0;
                    if (bkg[mpos] == anminfo.switchoff)
                    {
                        bkg[mpos] = anminfo.switchon;
                    }
                    else
                    {
                        bkg[mpos] = anminfo.switchoff;
                    }
                    vv = v - FNC_SWITCHES_START;
                    for (j = 0; j < 4; j++)
                    {
                        if (switches[vv].condnum[j] != -1)
                        {
                            j = 99;
                            break;
                        }
                    }
                    ok = 0;
                    if (j == 99)
                    {
                        ok = 1;
                        for (j = 0; j < 4; j++)
                        {
                            if (switches[vv].condnum[j] != -1)
                            {
                                if ((switches[vv].condstate[j] == anminfo.switchoff) && (bkg[switches[vv].condnum[j]] != anminfo.switchoff))
                                {
                                    ok = 0;
                                }
                                if ((switches[vv].condstate[j] == anminfo.switchon) && (bkg[switches[vv].condnum[j]] != anminfo.switchon))
                                {
                                    ok = 0;
                                }
                            }
                        }
                        if (ok)
                        {
                            play_game_sound(7);
                            switchcnt = 0x19;
                            for (yy = switches[vv].dty; yy <= switches[vv].dby; yy++)
                            {
                                for (xx = switches[vv].dlx; xx <= switches[vv].drx; xx++)
                                {
                                    z = switches[vv].effect;
                                    if (z == 0)
                                    {
                                        if (*(sld + yy * 0xf0 + xx) != 0xff)
                                        {
                                            *(swe + yy * 0xf0 + xx) = 1;
                                        }
                                    }
                                    else
                                    {
                                        if (*(sldsav + yy * 0xf0 + xx) != 0xff)
                                        {
                                            *(swe + yy * 0xf0 + xx) = 2;
                                        }
                                    }
                                }
                            }
                            for (j = 0; j < 4; j++)
                            {
                                switches[vv].condnum[j] = -1;
                            }
                        }
                        else
                        {
                            play_game_sound(6);
                        }
                    }
                    else
                    {
                        play_game_sound(6);
                    }
                }
            }
            else if (v < (FNC_RTRIPS_END + 1))
            {
                vv = v - FNC_RTRIPS_START;
                j = 0;
                if (rtrips[vv].keytype == 0)
                {
                    j = 1;
                }
                if ((rtrips[vv].keytype == 1) && (hskey != 0))
                {
                    j = 2;
                }
                if ((rtrips[vv].keytype == 2) && (hgkey != 0))
                {
                    j = 3;
                }

                if (j != 0)
                {
                    play_game_sound(7);
                    switchcnt = 10;
                    for (yy = rtrips[vv].dty; yy <= rtrips[vv].dby; yy++)
                    {
                        for (xx = rtrips[vv].dlx; xx <= rtrips[vv].drx; xx++)
                        {
                            if (*(sldsav + yy * 0xf0 + xx) != 0xff)
                            {
                                *(swe + yy * 0xf0 + xx) = 2;
                            }
                        }
                    }
                    fnc[mpos] = FNC_NONE;
                    if (rtrips[vv].keytype == 0)
                    {
                        bkg[mpos] = rtrips[vv].restore;
                    }
                    else
                    {
                        bkg[mpos] = anminfo.defaultbkg;
                    }

                    if (j > 1)
                    {
                        new_twink((mpos % 0xf0 - scrmx) * 4, (mpos / 0xf0 - scry) * 16);
                    }
                }
                if (j == 2)
                {
                    hskey = 0;
                }
                if (j == 3)
                {
                    hgkey = 0;
                }
            }
            else if (v < (FNC_ETRIPS_END + 1))
            {
                vv = v - FNC_ETRIPS_START;
                j = 0;
                if (etrips[vv].keytype == 0)
                {
                    j = 1;
                }
                if ((etrips[vv].keytype == 1) && (hskey != 0))
                {
                    j = 2;
                }
                if ((etrips[vv].keytype == 2) && (hgkey != 0))
                {
                    j = 3;
                }

                if (j != 0)
                {
                    play_game_sound(7);
                    switchcnt = 10;
                    for (yy = etrips[vv].dty; yy <= etrips[vv].dby; yy++)
                    {
                        for (xx = etrips[vv].dlx; xx <= etrips[vv].drx; xx++)
                        {
                            if (*(sld + yy * 0xf0 + xx) != 0xff)
                            {
                                *(swe + yy * 0xf0 + xx) = 1;
                            }
                        }
                    }
                    fnc[mpos] = FNC_NONE;
                    if (etrips[vv].keytype == 0)
                    {
                        bkg[mpos] = etrips[vv].restore;
                    }
                    else
                    {
                        bkg[mpos] = anminfo.defaultbkg;
                    }

                    if (j > 1)
                    {
                        new_twink((mpos % 0xf0 - scrmx) * 4, (mpos / 0xf0 - scry) * 16);
                    }
                }
                if (j == 2)
                {
                    hskey = 0;
                }
                if (j == 3)
                {
                    hgkey = 0;
                }
            }
            else if (v < (FNC_SPRITES_END + 1))
            {
            }
            else if (v <= FNC_MTRIGGERS_END)
            {
                vv = v - FNC_MTRIGGERS_START;
                for (j = 0; j < 8; j++)
                {
                    ok = mtriggers[vv].rpos[j];
                    if (fnc[ok] != FNC_NONE)
                    {
                        for (k = 0; k < 0x20; k++)
                        {
                            if (mr_offset[k] == -1)
                            {
                                m = 1;
                                for (l = 0; l < 8; l++)
                                {
                                    if (mc_org[l] == ok)
                                    {
                                        m = 0;
                                    }
                                }
                                for (l = 0; l < 0x20; l++)
                                {
                                    if (mr_offset[l] == ok)
                                    {
                                        m = 0;
                                    }
                                }
                                if (m != 0)
                                {
                                    mr_offset[k] = ok;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        i++;
        mpos += 0xf0;
        y += 16;
    }
}

// module: PLAY
// size: 0x2223
// addr: 0CDE:44C4
int play(int demomode)
{
    // register: SI
    // size: 2
    register int i;
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
    register int mpos;
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

    exitcode = 0;
start:
    lelevator = lrelev[game][level][0];
    relevator = lrelev[game][level][1];
    conshoot = conup = 0;
    demonum = 0;
    if (demomode == 2)
    {
        indemo = 1;
    }
    else
    {
        indemo = 0;
    }
    setapage(0);
    clearscreen();
    setapage(1);
    clearscreen();
    setvpage(0);
    play_imf_file(song2play[game][level] + (OFFSET_MUSIC+1));
    do_anm = 0;
    flash_flag = 0;
    hinwarp = 0;
    twinknum = 0;
    ouchcnt = 0;
    hfireaway = 0;
    hinvis = 0;
    hjumphigh = 0;
    hsupershot = 0;
    hdead = 0;
    hskey = hgkey = 0;
    htwinkletoes = 0;
    hlaser = 0;
    hwalking = 0;
    ylevel = 5;
    scrolldelay = 0;
    playlevel = game * 9 + level;
    hfirenum = 0;

    for (i = 0; i < 5; i++)
    {
        hfirex[i] = -99;
    }

    expnum = 0;

    for (i = 0; i < 8; i++)
    {
        expcnt[i] = -1;
    }

    for (i = 0; i < 8; i++)
    {
        twinkpos[i][2] = 0;
    }

    for (i = 0; i < 10; i++)
    {
        stag[i][3] = 0;
    }

    for (i = 0; i < 0x20; i++)
    {
        mr_offset[i] = -1;
    }

    for (i = 0; i < 8; i++)
    {
        mc_type[i] = -1;
    }

    for (i = 0; i < 8; i++)
    {
        mc_org[i] = -1;
    }

    for (i = 0; i < 8; i++)
    {
        sc_life[i] = -1;
    }

    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_LVLINFO, &lvlinfo);
    hxpos = lvlinfo.startx * 2;
    hylpos = lvlinfo.starty * 16;
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_ANMINFO, &anminfo);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_WIZNOTES, wiznotes);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_WARPS, warps);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SWITCHES, switches);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_RTRIPS, rtrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_ETRIPS, etrips);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTAGS, mtags);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_MTRIGGERS, mtriggers);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_BKG, bkg);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLD, sld);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_SLDSAV, sldsav);
    load_file_to_byte_pointer(lvl_info_ofs[game][level] + OFFSET_FNC, fnc);
    setmem(swe, 0x3840, 0);
    treasures = treasuresfound = 0;

    for (i = 0; i < 0x3840; i++)
    {
        x = fnc[i];
        if ((x >= FNC_UPS_START) && (x <= FNC_UPS_END) && (ups[x].add2score != 0))
        {
            treasures++;
        }
    }

    monsters = monstershit = 0;

    for (i = 0; i < 0x3840; i++)
    {
        x = fnc[i];
        if ((x >= FNC_SPRITES_START) && (x <= FNC_SPRITES_END) && (mtags[x - FNC_SPRITES_START].tokill != -1))
        {
            monsters++;
        }
    }
    setapage(3);
    load_pcx(plat_pcx_ofs[game][level] + OFFSET_TILE, 1);
    read_pels(palette, 0, 0x100);

    s = 0;
    for (i = 0; i < 0x118; i++)
    {
        latches(0);
        if (pixel_clr((i % 0x14) * 16, (i / 0x14) * 16) == 0xff)
        {
            sprbase = s * 4;
            break;
        }
        latches(1);
        enable_pixels(0xf);
        for (y = 0; y < 16; y++)
        {
            for (x = 0; x < 4; x++)
            {
                vgap[2][s] = ((line_t)vga)[(y + (i / 0x14) * 16)][(i % 0x14) * 4 + x];
                // vgap[2][s] = *(vga + (y + (i / 0x14) * 16) * VGA_PLANE_WIDTH + (i % 0x14) * 4 + x);
                s++;
            }
        }
    }

    vgap[2][sprbase >> 2] = 0x60;
    whitedata = sprbase >> 2;
    sprbase += 4;
    vgap[2][sprbase >> 2] = 0x70;
    reddata = sprbase >> 2;
    sprbase += 4;

    for (i = 0; i < 10; i++)
    {
        sload[i] = -1;
    }

    sload[0] = 0;
    sload[1] = 1;
    sload[2] = 3;
    sload[3] = 2;

    x = 0;
    for (i = 0; i < 6; i++)
    {
        if (mtags[i].mnum != -1)
        {
            sload[x + 4] = mtags[i].mnum;
            x++;
        }
    }
    load_sprites();
    setapage(3);
    load_pcx(bdrop_pcxpal_ofs[game][level] + OFFSET_BACKPCX, 0);
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 1);
    restore_palette_fragment(bdrop_pcxpal_ofs[game][level] + OFFSET_BACKPAL, 0x80, 1);
    restore_graphics_fragment(OFFSET_HUDSTUFF, 0, 0xa0);
    restore_graphics_fragment(OFFSET_BULLIT, 0, 0xb4);
    fade_out(1);
    setapage(0);
    restore_graphics_fragment(OFFSET_NEW_HUD, 0, 0xa0);
    setapage(1);
    restore_graphics_fragment(OFFSET_NEW_HUD, 0, 0xa0);
    setapage(0);
    restore_graphics_fragment(OFFSET_NEW_HUD, 0, 0xa0);
    setapage(1);
    restore_graphics_fragment(OFFSET_NEW_HUD, 0, 0xa0);
    count_crystals();
    crystals_found = 0;
    health = 100;
    hxpos = lvlinfo.startx * 2;
    hylpos = lvlinfo.starty * 16;
    hfrm = sprite[0].frs;
    hdir = 0;
    hjump = 0;
    hfall = 0;
    snapcoords = 1;
    get_coords();
    snapcoords = 0;

    if (demomode == 2)
    {
        load_file_to_byte_pointer(level / 2 + OFFSET_DEMO, buf64);
        demolimit = *(int16_t *)buf64;
    }
    if ((game == 3) && (level == 8))
    {
        b4p = 0;
        new_monster(0, b4x[0] * 4, b4y[0] * 16, b4m[0]);
        mc_dir[0] = b4d[0];
        mc_xp[0] = 0;
        mc_sink[0] = 100;
        mc_seek[0] = myrnd(0x14) + 10;
        mc_vo[0] = 0;
    }
    install_key_handler();
    rndnum = 0;
    setapage(1);
    setvpage(0);
    done = 0;
    turn_on_palette();
    clk_times = gametimer = 0;
    while (!done)
    {
        setapage(!apg);
        setvpage(!vpg);
        wait_for_retrace();
        while ((clk_times - gametimer) < 0x18)
            ;
        gametimer = clk_times;
        get_coords();
        latches(1);
        enable_pixels(0xf);
        if (hinwarp == 0)
        {
            do_function_check();
        }
        if (flash_flag)
        {
            flash_screen();
        }
        else
        {
            if (scrxh != 0)
            {
                show_screen_h(vga, vgap[2], sld, bkg, scry * 0xf0 + scrmx);
                asm_show_background_h(vgap[3], vga);
            }
            else
            {
                show_screen(vga, vgap[2], sld, bkg, scry * 0xf0 + scrmx);
                asm_show_background(vgap[3], vga);
            }
        }
        show_panel_stats();
        if ((health == 0) && (hdead == 0))
        {
            hdead = 0x5a;
            hinvis = 30000;
            clear_keys();
        }
        if (hdead != 0)
        {
            hdead--;
            if ((myrnd(4) == 0) && (hdead > 0x19))
            {
                new_explosion((hxbspos * 4 + myrnd(10) + 12) - myrnd(10), (hylspos + myrnd(10) + 16) - myrnd(10));
                new_twink((hxbspos + myrnd(3)) - myrnd(3), (hylspos + myrnd(12)) - myrnd(12));
                new_explosion((hxbspos * 4 + myrnd(10) + 12) - myrnd(10), (hylspos + myrnd(10) + 16) - myrnd(10));
                new_twink((hxbspos + myrnd(3)) - myrnd(3), (hylspos + myrnd(12)) - myrnd(12));
                play_game_sound(10);
            }
        }
        if ((crystals == crystals_found) && (hdone == 0))
        {
            hdone = 0x5a;
            hinvis = 30000;
            clear_keys();
            smart_bomb_monsters();
        }
        if (hdone != 0)
        {
            hdone--;
            if ((myrnd(7) == 0) && (hdone > 0x19))
            {
                new_twink((hxbspos + myrnd(3)) - myrnd(3), (hylspos + myrnd(0xc)) - myrnd(0xc));
                new_twink((hxbspos + myrnd(3)) - myrnd(3), (hylspos + myrnd(0xc)) - myrnd(0xc));
                play_game_sound(9);
            }
        }
        if (hinvis == 0)
        {
            if (hinwarp == 0)
            {
                if (conshoot != 0)
                {
                    if ((conup != 0) && (hwalking == 0))
                    {
                        hfrm = sprite[0].afrs + 1;
                    }
                    else if (hwalking == 0)
                    {
                        hfrm = sprite[0].afrs;
                    }
                }
                if (hjump != 0)
                {
                    hfrm = sprite[0].jfrs;
                }
                if ((hjump != 0) && (hjumppos > hjumpposmid))
                {
                    hfrm = sprite[0].jfre;
                }
                if (hfall != 0)
                {
                    hfrm = sprite[0].jfre;
                }
                if (hylspos < 0)
                {
                    draw_sprite(0, sprite[0].xw, hxbspos, hylspos, hdir, hfrm);
                }
                if (ouchcnt % 2 != 0)
                {
                    if (hylspos < 0)
                    {
                        draw_rsprite(0, sprite[0].xw, hxbspos, hylspos, hdir, hfrm);
                    }
                    else
                    {
                        draw_rsprite_nocheck(0, hxbspos, hylspos, hdir, hfrm);
                    }
                }
                else if (hsupershot % 2 != 0)
                {
                    if (hylspos < 0)
                    {
                        draw_wsprite(0, sprite[0].xw, hxbspos, hylspos, hdir, hfrm);
                    }
                    else
                    {
                        draw_wsprite_nocheck(0, hxbspos, hylspos, hdir, hfrm);
                    }
                }
                else
                {
                    if (hylspos < 0)
                    {
                        draw_sprite(0, sprite[0].xw, hxbspos, hylspos, hdir, hfrm);
                    }
                    else
                    {
                        draw_sprite_nocheck(0, hxbspos, hylspos, hdir, hfrm);
                    }
                }
            }
            else if (hinwarp < 5)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 0);
            }
            else if (hinwarp < 10)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 1);
            }
            else if (hinwarp < 15)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 2);
            }
            else if (hinwarp < 20)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 3);
            }
            else if (hinwarp <= 25)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos + myrnd(2) - myrnd(2), hdir, 4);
            }
            else if (hinwarp < 30)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 3);
            }
            else if (hinwarp < 35)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 2);
            }
            else if (hinwarp < 40)
            {
                draw_sprite_nocheck(2, hxbspos, hylspos, hdir, 1);
            }
            if (htwinkletoes != 0)
            {
                new_twink((hxbspos + myrnd(7) - 2), hylspos + myrnd(10) + 0x14);
                if (hjumphigh == 0)
                {
                    htwinkletoes--;
                }
            }
            if (hlaser != 0)
            {
                if (hlaserdisplay != 0)
                {
                    for (i = 0; i < hlaser; i++)
                    {
                        draw_sprite(0, sprite[0].sxw, hxbspos + 1, (hylspos - 4) - i * 5, 0, sprite[0].sfrs);
                    }
                }
                hlaserdisplaycnt--;
                if (hlaserdisplaycnt == 0)
                {
                    hlaserdisplaycnt = 5;
                    hlaserdisplay = !hlaserdisplay;
                }
            }
        }
        else
        {
            hinvis--;
            if (hinvis == 0)
            {
                play_game_sound(4);
            }
        }
        scan_for_monster_hits();
        scan_monster_shot_hits();
        scan_monster_collisions();
        process_monster_reserve();
        update_shots();
        update_monsters();
        clip_monsters();
        update_explosions();
        update_stags();
        update_twinks();
        if (do_anm)
        {
            do_element_animation();
        }
        do_anm = !do_anm;
        if (demomode == 1)
        {
            demo.fkey = 0;
            demo.jkey = 0;
            demo.ukey = 0;
            demo.lkey = 0;
            demo.rkey = 0;
        }
        if (demomode == 2)
        {
            memcpy(&demo, &((struct_172 *)(buf64 + sizeof(int)))[demonum], sizeof(struct_172));
            fkey = demo.fkey;
            jkey = demo.jkey;
            lkey = demo.lkey;
            rkey = demo.rkey;
            ukey = demo.ukey;
            if (fkey)
            {
                fkeyclr = 0;
            }
            else
            {
                fkeyclr = 1;
            }
            if (ukey)
            {
                ukeyclr = 0;
            }
            else
            {
                ukeyclr = 1;
            }
            demonum++;
        }
        if (!fkeyclr)
        {
            conshoot = 1;
        }
        else
        {
            conshoot = 0;
        }
        if (!ukeyclr)
        {
            conup = 1;
        }
        else
        {
            conup = 0;
        }

        if ((hinwarp == 0) && (hdead == 0) && (hdone == 0) &&
            (game_config.joystick != 0) && (indemo == 0))
        {
            lkey = rkey = ukey = dkey = 0;
            JoyX = JoyY = button1 = button2 = 0;
            JOY_PollButtons();
            JOY_PollMovement();
            if (JoyX == -50)
            {
                lkey = 1;
            }
            if (JoyX == 50)
            {
                rkey = 1;
            }
            if ((JoyY == -50) && (ukeyclr != 0))
            {
                ukey = 1;
                ukeyclr = 0;
                conup = 1;
            }
            if (JoyY != -50)
            {
                ukeyclr = 1;
                conup = 0;
            }
            if (JoyY == 50)
            {
                dkey = 1;
            }
            if (button1 != 0)
            {
                conshoot = 1;
            }
            else
            {
                conshoot = 0;
            }

            if (button1 == 0)
            {
                fkey = 0;
                fkeyclr = 1;
            }
            if ((button1 != 0) && (fkeyclr != 0))
            {
                fkey = 1;
                fkeyclr = 0;
            }
            if (button2 == 0)
            {
                jkey = 0;
                jkeyclr = 1;
            }
            if ((button2 != 0) && (jkeyclr != 0))
            {
                jkey = 1;
                jkeyclr = 0;
            }
        }
        if ((hinwarp == 0) && (fkey != 0))
        {
            if (demomode == 1)
            {
                demo.fkey = 1;
            }
            if (hsupershot == 0)
            {
                fkey = 0;
            }
            for (hfirenum = 0; (hfirenum < 5 && (hfirex[hfirenum] != -99)); hfirenum++)
                ;
            if ((hfirenum < 5) && (hfireaway < hfirepower))
            {
                hfireaway++;
                if (hlaser != 0)
                {
                    hlaser--;
                    hfirelaser[hfirenum] = 1;
                }
                else
                {
                    hfirelaser[hfirenum] = 0;
                }
                if (conup != 0)
                {
                    hfireup[hfirenum] = 1;
                    hfirex[hfirenum] = hxbspos + 1;
                    hfirey[hfirenum] = hylspos;
                }
                else
                {
                    hfireup[hfirenum] = 0;
                    if (hdir != 0)
                    {
                        hfirex[hfirenum] = hxbspos - 1;
                    }
                    else
                    {
                        hfirex[hfirenum] = hxbspos + 2;
                    }
                    hfirey[hfirenum] = hylspos + sprite[0].sys;
                }
                hfired[hfirenum] = hdir;
                hfirenum++;
                if (hfirenum > 4)
                {
                    hfirenum = 0;
                }
                play_game_sound(0);
            }
        }
        if (hsupershot != 0)
        {
            hsupershot--;
        }
        if (hsupershot == 1)
        {
            hsupershot = 0;
            hfirepower = holdshots;
        }
        for (i = 0; i < 5; i++)
        {
            if (hfirex[i] != -99)
            {
                if (hfireup[i] == 0)
                {
                    if (hfired[i] == 0)
                    {
                        mpos = ((hfirey[i] / 16 + scry) * 0xf0) +
                               (hfirex[i] / 4) + scrmx + 1;
                        if (sld[mpos] == anminfo.bustblock)
                        {
                            sld[mpos] = -1;
                            new_twink((hfirex[i] + 2 - scrxh * 2), hfirey[i] - 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos + 0xf0) == anminfo.bustblock)
                        {
                            *(sld + mpos + 0xf0) = -1;
                            new_twink((hfirex[i] + 2 - scrxh * 2), hfirey[i] + 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos + 1) == anminfo.bustblock)
                        {
                            *(sld + mpos + 1) = -1;
                            new_twink((hfirex[i] + 6 - scrxh * 2), hfirey[i] - 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos + (0xf0 + 1)) == anminfo.bustblock)
                        {
                            *(sld + mpos + (0xf0 + 1)) = -1;
                            new_twink((hfirex[i] + 6 - scrxh * 2), hfirey[i] + 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if ((sld[mpos] != 0xff) || (*(sld + mpos + 1) != 0xff))
                        {
                            new_explosion((hfirex[i] * 4 + 0x18), hfirey[i] + 10);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else
                        {
                            if (hfireup[i] != 0)
                            {
                                hfirey[i] -= 16;
                            }
                            else
                            {
                                hfirex[i] += 4;
                            }
                            if ((hfirex[i] > 0x4f) || (hfirey[i] < 0))
                            {
                                hfirex[i] = -99;
                                hfireaway--;
                            }
                            else
                            {
                                if (hfireup[i])
                                {
                                    draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs + 1);
                                }
                                else
                                {
                                    draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs);
                                }
                            }
                        }
                    }
                    else
                    {
                        mpos = ((hfirey[i] / 16 + scry) * 0xf0) +
                               (hfirex[i] / 4) + scrmx;
                        if (sld[mpos] == anminfo.bustblock)
                        {
                            sld[mpos] = -1;
                            new_twink((hfirex[i] - 2 - scrxh * 2), hfirey[i] - 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos + 0xf0) == anminfo.bustblock)
                        {
                            *(sld + mpos + 0xf0) = -1;
                            new_twink((hfirex[i] - 2 - scrxh * 2), hfirey[i] + 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos - 1) == anminfo.bustblock)
                        {
                            *(sld + mpos - 1) = -1;
                            new_twink((hfirex[i] - 4 - scrxh * 2), hfirey[i] - 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if (*(sld + mpos + (0xf0 - 1)) == anminfo.bustblock)
                        {
                            *(sld + mpos + (0xf0 - 1)) = -1;
                            new_twink((hfirex[i] - 4 - scrxh * 2), hfirey[i] + 8);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else if ((sld[mpos] != 0xff) || (*(sld + mpos + 1) != 0xff))
                        {
                            new_explosion((hfirex[i] * 4), hfirey[i] + 2);
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else
                        {
                            if (hfireup[i] != 0)
                            {
                                hfirey[i] -= 16;
                            }
                            else
                            {
                                hfirex[i] -= 4;
                            }
                            if ((hfirex[i] < -3) || (hfirey[i] < 0))
                            {
                                hfirex[i] = -99;
                                hfireaway--;
                            }
                            else
                            {
                                if (hfireup[i])
                                {
                                    draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs + 1);
                                }
                                else
                                {
                                    draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs);
                                }
                            }
                        }
                    }
                }
                else
                {
                    if (hfired[i] == 0)
                    {
                        mpos = ((hfirey[i] / 16 + scry) * 0xf0) +
                               (hfirex[i] / 4) + scrmx;
                    }
                    else
                    {
                        mpos = ((hfirey[i] / 16 + scry) * 0xf0) +
                               (hfirex[i] / 4) + scrmx + 1;
                    }
                    if (sld[mpos] != 0xff)
                    {
                        new_explosion((hfirex[i] * 4) + 8, hfirey[i] + 2);
                        hfirex[i] = -99;
                        hfireaway--;
                    }
                    else
                    {
                        if (hfireup[i] != 0)
                        {
                            hfirey[i] -= 16;
                        }
                        else
                        {
                            hfirex[i] += 4;
                        }
                        if ((hfirex[i] > 0x4f) || (hfirey[i] < 0))
                        {
                            hfirex[i] = -99;
                            hfireaway--;
                        }
                        else
                        {
                            if (hfireup[i])
                            {
                                draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs + 1);
                            }
                            else
                            {
                                draw_sprite(0, sprite[0].sxw, hfirex[i], hfirey[i], hfired[i], sprite[0].sfrs);
                            }
                        }
                    }
                }
            }
        }
        if (hinwarp == 0)
        {
            if ((jkey != 0) && (hjump == 0) && (hstopjump == 0) && (hfall == 0))
            {
                if (demomode == 1)
                {
                    demo.jkey = 1;
                }
                jkey = 0;
                hjump = 1;
                ylevel = 5;
                hjumppos = 0;
                if (hjumphigh == 0)
                {
                    hjumpadd = hnjumpadd;
                    hjumpposmid = 9;
                    hjumpposlimit = 0x13;
                }
                else
                {
                    hjumphigh = 0;
                    hjumpadd = hsjumpadd;
                    hjumpposmid = 0xc;
                    hjumpposlimit = 0x19;
                    play_game_sound(4);
                }
            }
            if ((hjump != 0) && (hdead == 0) && (hdone == 0))
            {
                if (hjumppos < hjumpposlimit)
                {
                    hylpos += hjumpadd[hjumppos];
                    hypos = hylpos / 16;
                    mpos = (hypos * 0xf0 + (hxpos + 1) / 2);
                    if (sld[mpos] != 0xff)
                    {
                        hjumppos = (hjumpposlimit - 1) - hjumppos;
                        hylpos += hjumpadd[hjumppos];
                        hypos = hylpos / 16;
                    }
                    hjumppos++;
                    if (hjumppos >= hjumpposlimit)
                    {
                        hjump = 0;
                    }
                }
                else
                {
                    hjump = 0;
                }
            }
            mpos = (hypos * 0xf0 + (hxpos + 1) / 2) + 0xf0 * 2;
            if (sld[mpos] != 0xff)
            {
                if ((hjump != 0) && (hjumppos >= hjumpposmid))
                {
                    hjump = 0;
                    hylpos = hypos * 16;
                }
                hfall = 0;
            }
            else
            {
                if ((hjump == 0) && (hdead == 0) && (hdone == 0))
                {
                    hylpos += 16;
                    if (*(sld + mpos + 0xf0) == 0xff)
                    {
                        hfall = 1;
                    }
                }
            }
            hmleft = hmright = hwuleft = hwuright = 0;
            mpos = (hypos * 0xf0 + hxpos / 2);
            i = hylpos % 16;
            if (i == 0)
            {
                if ((*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) == 0xff))
                {
                    hmleft = 1;
                }
                if ((*(sld + mpos - 0xf0) == 0xff) && (*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) != 0xff))
                {
                    hwuleft = 1;
                }
                mpos = (hypos * 0xf0 + (hxpos + 2) / 2);
                if ((*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) == 0xff))
                {
                    hmright = 1;
                }
                if ((*(sld + mpos - 0xf0) == 0xff) && (*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) != 0xff))
                {
                    hwuright = 1;
                }
            }
            else
            {
                if ((*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) == 0xff) && (*(sld + mpos + 0xf0 * 2) == 0xff))
                {
                    hmleft = 1;
                }
                if ((*(sld + mpos - 0xf0) == 0xff) && (*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) != 0xff))
                {
                    hwuleft = 1;
                }
                mpos = (hypos * 0xf0 + (hxpos + 2) / 2);
                if ((*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) == 0xff) && (*(sld + mpos + 0xf0 * 2) == 0xff))
                {
                    hmright = 1;
                }
                if ((*(sld + mpos - 0xf0) == 0xff) && (*(sld + mpos) == 0xff) && (*(sld + mpos + 0xf0) != 0xff))
                {
                    hwuright = 1;
                }
            }
            if ((hfall != 0) || (hjump != 0))
            {
                hwuleft = hwuright = 0;
            }
            hwalking = 0;
            if ((lkey != 0) && (hxpos != 0))
            {
                if (demomode == 1)
                {
                    demo.lkey = 1;
                }
                if (hdir == 0)
                {
                    hdir = 1;
                }
                else if (hmleft != 0)
                {
                    hxpos--;
                    hwalking = 1;
                    hfrm++;
                    if (hfrm > sprite[0].mfre)
                    {
                        hfrm = sprite[0].mfrs;
                    }
                }
                else if (hwuleft != 0)
                {
                    hxpos--;
                    hylpos -= 16;
                    hwalking = 1;
                    hfrm++;
                    if (hfrm > sprite[0].mfre)
                    {
                        hfrm = sprite[0].mfrs;
                    }
                }
            }
            if ((rkey != 0) && (hxpos < 0x1dd))
            {
                if (demomode == 1)
                {
                    demo.rkey = 1;
                }
                if (hdir != 0)
                {
                    hdir = 0;
                }
                else if (hmright != 0)
                {
                    hxpos++;
                    hwalking = 1;
                    hfrm++;
                    if (hfrm > sprite[0].mfre)
                    {
                        hfrm = sprite[0].mfrs;
                    }
                }
                else if (hwuright != 0)
                {
                    hxpos++;
                    hylpos -= 16;
                    hwalking = 1;
                    hfrm++;
                    if (hfrm > sprite[0].mfre)
                    {
                        hfrm = sprite[0].mfrs;
                    }
                }
            }
            if ((uppressed == 0) && (lelevator != -1))
            {
                i = 0;
                mpos = (hypos * 0xf0 + (hxpos + 1) / 2) + 0xf0 * 2;
                if ((sld[mpos] == lelevator) || (sld[mpos] == relevator))
                {
                    if (sld[mpos] == relevator)
                    {
                        mpos--;
                    }
                    if ((cukey != 0) || (ukey != 0))
                    {
                        if (demomode == 1)
                        {
                            demo.ukey = 1;
                        }
                        mpos -= 0xf0 * 3;
                        ukey = 0;
                        ukeyclr = 1;
                        if ((*(sld + mpos) == 0xff) && (*(sld + mpos + 1) == 0xff))
                        {
                            hylpos -= 16;
                            mpos += 0xf0 * 3;
                            mpos2 = mpos - 0xf0;
                            *(sld + mpos2) = sld[mpos];
                            sld[mpos] = 0xff;
                            *(sld + mpos2 + 1) = *(sld + mpos + 1);
                            *(sld + mpos + 1) = 0xff;
                        }
                    }
                    else
                    {
                        if (dkey != 0)
                        {
                            mpos += 0xf0;
                            if ((sld[mpos] == 0xff) && (*(sld + mpos + 1) == 0xff))
                            {
                                hylpos += 16;
                                mpos2 = mpos - 0xf0;
                                *(sld + mpos) = sld[mpos2];
                                sld[mpos2] = 0xff;
                                *(sld + mpos + 1) = *(sld + mpos2 + 1);
                                *(sld + mpos2 + 1) = 0xff;
                            }
                        }
                    }
                }
            }
            if ((hwalking == 0) && (!conshoot))
            {
                hfrm = sprite[0].frs;
            }
        }
        else
        {
            if ((hwarpdx == hxpos) && (hwarpdy == hylpos))
            {
                if (hinwarp == 0x19)
                {
                    play_game_sound(5);
                }
                if (hinwarp == 0x28)
                {
                    hinwarp = 0;
                }
                else
                {
                    hinwarp++;
                }
            }
            else if (hinwarp < 0x19)
            {
                hinwarp++;
            }
            if (hinwarp == 0x19)
            {
                if (hylpos < hwarpdy)
                {
                    hylpos += 16;
                }
                if (hylpos > hwarpdy)
                {
                    hylpos -= 16;
                }
                if (hxpos < hwarpdx)
                {
                    hxpos++;
                }
                if (hxpos > hwarpdx)
                {
                    hxpos--;
                }
            }
        }
        if ((pgdnkey != 0) && (ylevel > 0) && (scrolldelay == 0))
        {
            ylevel--;
            scrolldelay = 0;
        }
        if ((pgupkey != 0) && (ylevel < 8) && (scrolldelay == 0))
        {
            ylevel++;
            scrolldelay = 0;
        }
        if (scrolldelay != 0)
        {
            scrolldelay--;
        }
        if (pause != 0)
        {
            pause = 0;
            do_pause();
        }
        if ((demomode == 2) && (demonum >= demolimit))
        {
            done = 1;
        }
        if (qkey != 0)
        {
            if (demomode > 0)
            {
                done = 1;
            }
            else
            {
                i = play_menu();
                if (i == 1)
                {
                    hdone = hdead = 0;
                    done = 2;
                }
                if (i == 2)
                {
                    exitcode = -1;
                    done = 1;
                }
                if (i == 3)
                {
                    hdone = hdead = 0;
                    done = 3;
                }
            }
        }
        if (f2key != 0)
        {
            save_menu();
            f2key = 0;
        }
        if (f3key != 0)
        {
            if (restore_menu() != 0)
            {
                disable_key_handler();
                goto start;
            }
            f3key = 0;
        }
        if (f10key != 0)
        {
            if (quit_menu() != 0)
            {
                exitcode = -1;
                done = 1;
            }
            f10key = 0;
        }
        if (helpkey != 0)
        {
            do_help(1);
            helpkey = 0;
        }
        if (calkey != 0)
        {
            if (game_config.joystick != 0)
            {
                calibrate_from_game();
            }
            calkey = 0;
        }
        if (muskey != 0)
        {
            muskey = 0;
            game_config.music = !game_config.music;
            if ((adlib != 0) || (blaster != 0))
            {
                if (game_config.music == 0)
                {
                    SD_MusicOff();
                }
                else
                {
                    play_imf_file(song2play[game][level] + (OFFSET_MUSIC+1));
                }
            }
            if ((adlib == 0) && (blaster == 0))
            {
                game_config.music = 0;
            }
            save_file_from_byte_pointer(1, &game_config);
        }
        if (sndkey != 0)
        {
            sndkey = 0;
            game_config.soundfx = !game_config.soundfx;
            save_file_from_byte_pointer(1, &game_config);
        }
        if (hdead == 1)
        {
            done = 1;
        }
        if (hdone == 1)
        {
            done = 1;
        }
        if (demomode == 1)
        {
            if (ukey != 0)
            {
                demo.ukey = 1;
            }
            memcpy(&((struct_172 *)(buf64 + sizeof(int16_t)))[demonum], &demo, sizeof(struct_172));
            demonum++;
        }
    }
    disable_key_handler();
    total_ticks = clk_times;
    if (demomode == 1)
    {
        *((int16_t *)buf64) = demonum;
        save_disk_file("demo13.lvl", buf64, demonum * sizeof(struct_172) + sizeof(int16_t));
    }
    fade_out(0x14);
    if (done != 2)
    {
        restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
        restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);
        play_imf_file(MUSIC_TITLE);
    }
    if (hdone == 1)
    {
        if (do_eval(1, treasures, treasuresfound, monsters, monstershit) == 1)
        {
            done = 2;
        }
        exitcode = 1;
    }
    if (hdead == 1)
    {
        do_eval(0, treasures, treasuresfound, monsters, monstershit);
        exitcode = 0;
    }
    if (done == 2)
    {
        score = 0;
        hfirepower = 1;
        goto start;
    }
    if (done == 3)
    {
        goto start;
    }
    return exitcode;
}
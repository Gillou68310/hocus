#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "joystick.h"
#include "fileio.h"
#include "soundfx.h"
#include "gr.h"
#include "util.h"
#include "menus.h"
#include "play.h"
#include "joystick.h"

void title(void);

// addr: 192E:0094
// size: 1888
struct_70 db[236] = {
    {0x0, 0x2d0},
    {0x2d0, 0x3bc},
    {0x68c, 0x78e5},
    {0x7f71, 0x98b9},
    {0x1182a, 0x11e82},
    {0x236ac, 0xb40},
    {0x241ec, 0x7d0},
    {0x249bc, 0x180},
    {0x24b3c, 0x180},
    {0x24cbc, 0x1404},
    {0x260c0, 0x30c4},
    {0x29184, 0x544},
    {0x296c8, 0x3204},
    {0x2c8cc, 0x3204},
    {0x2fad0, 0x784},
    {0x30254, 0x279e},
    {0x329f2, 0x2612},
    {0x35004, 0x11d2},
    {0x361d6, 0x1766},
    {0x3793c, 0x202a},
    {0x39966, 0x191e},
    {0x3b284, 0x1dff},
    {0x3d083, 0x1684},
    {0x3e707, 0x1bf4},
    {0x402fb, 0x1c26},
    {0x41f21, 0x26cc},
    {0x445ed, 0x1571},
    {0x45b5e, 0x3175},
    {0x48cd3, 0x2904},
    {0x4b5d7, 0x297c},
    {0x4df53, 0x301b},
    {0x50f6e, 0x2a7b},
    {0x539e9, 0xfd00},
    {0x636e9, 0xfd00},
    {0x733e9, 0xfd00},
    {0x830e9, 0xfd00},
    {0x92de9, 0xfd00},
    {0xa2ae9, 0xfd00},
    {0xb27e9, 0xfd00},
    {0xc24e9, 0xfd00},
    {0xd21e9, 0xfd00},
    {0xe1ee9, 0xfd00},
    {0xf1be9, 0x696},
    {0xf227f, 0x696},
    {0xf2915, 0x696},
    {0xf2fab, 0x696},
    {0xf3641, 0x696},
    {0xf3cd7, 0x696},
    {0xf436d, 0x696},
    {0xf4a03, 0x696},
    {0xf5099, 0x696},
    {0xf572f, 0x696},
    {0xf5dc5, 0x696},
    {0xf645b, 0x696},
    {0xf6af1, 0x696},
    {0xf7187, 0x696},
    {0xf781d, 0x696},
    {0xf7eb3, 0x696},
    {0xf8549, 0x696},
    {0xf8bdf, 0x696},
    {0xf9275, 0x696},
    {0xf990b, 0x696},
    {0xf9fa1, 0x696},
    {0xfa637, 0x696},
    {0xfaccd, 0x696},
    {0xfb363, 0x180},
    {0xfb4e3, 0x180},
    {0xfb663, 0x180},
    {0xfb7e3, 0x180},
    {0xfb963, 0x84d0},
    {0x103e33, 0xbbd5},
    {0x10fa08, 0x8298},
    {0x117ca0, 0xb107},
    {0x122da7, 0x4598},
    {0x12733f, 0x6e8d},
    {0x12e1cc, 0x7564},
    {0x135730, 0x4e58},
    {0x13a588, 0x9951},
    {0x143ed9, 0x5d273},
    {0x1a114c, 0x8},
    {0x1a1154, 0x8},
    {0x1a115c, 0x8},
    {0x1a1164, 0x8},
    {0x1a116c, 0x8},
    {0x1a1174, 0x8},
    {0x1a117c, 0x8},
    {0x1a1184, 0x8},
    {0x1a118c, 0x8},
    {0x1a1194, 0x2d4},
    {0x1a1468, 0x2d4},
    {0x1a173c, 0x2d4},
    {0x1a1a10, 0x2d4},
    {0x1a1ce4, 0x2d4},
    {0x1a1fb8, 0x2d4},
    {0x1a228c, 0x2d4},
    {0x1a2560, 0x2d4},
    {0x1a2834, 0x2d4},
    {0x1a2b08, 0x13b0},
    {0x1a3eb8, 0x13b0},
    {0x1a5268, 0x13b0},
    {0x1a6618, 0x13b0},
    {0x1a79c8, 0x13b0},
    {0x1a8d78, 0x13b0},
    {0x1aa128, 0x13b0},
    {0x1ab4d8, 0x13b0},
    {0x1ac888, 0x13b0},
    {0x1adc38, 0x28},
    {0x1adc60, 0x28},
    {0x1adc88, 0x28},
    {0x1adcb0, 0x28},
    {0x1adcd8, 0x28},
    {0x1add00, 0x28},
    {0x1add28, 0x28},
    {0x1add50, 0x28},
    {0x1add78, 0x28},
    {0x1adda0, 0x1fa},
    {0x1adf9a, 0x1fa},
    {0x1ae194, 0x1fa},
    {0x1ae38e, 0x1fa},
    {0x1ae588, 0x1fa},
    {0x1ae782, 0x1fa},
    {0x1ae97c, 0x1fa},
    {0x1aeb76, 0x1fa},
    {0x1aed70, 0x1fa},
    {0x1aef6a, 0x12c},
    {0x1af096, 0x12c},
    {0x1af1c2, 0x12c},
    {0x1af2ee, 0x12c},
    {0x1af41a, 0x12c},
    {0x1af546, 0x12c},
    {0x1af672, 0x12c},
    {0x1af79e, 0x12c},
    {0x1af8ca, 0x12c},
    {0x1af9f6, 0x12c},
    {0x1afb22, 0x12c},
    {0x1afc4e, 0x12c},
    {0x1afd7a, 0x12c},
    {0x1afea6, 0x12c},
    {0x1affd2, 0x12c},
    {0x1b00fe, 0x12c},
    {0x1b022a, 0x12c},
    {0x1b0356, 0x12c},
    {0x1b0482, 0xf0},
    {0x1b0572, 0xf0},
    {0x1b0662, 0xf0},
    {0x1b0752, 0xf0},
    {0x1b0842, 0xf0},
    {0x1b0932, 0xf0},
    {0x1b0a22, 0xf0},
    {0x1b0b12, 0xf0},
    {0x1b0c02, 0xf0},
    {0x1b0cf2, 0x1f40},
    {0x1b2c32, 0x1f40},
    {0x1b4b72, 0x1f40},
    {0x1b6ab2, 0x1f40},
    {0x1b89f2, 0x1f40},
    {0x1ba932, 0x1f40},
    {0x1bc872, 0x1f40},
    {0x1be7b2, 0x1f40},
    {0x1c06f2, 0x1f40},
    {0x1c2632, 0x3840},
    {0x1c5e72, 0x3840},
    {0x1c96b2, 0x3840},
    {0x1ccef2, 0x3840},
    {0x1d0732, 0x3840},
    {0x1d3f72, 0x3840},
    {0x1d77b2, 0x3840},
    {0x1daff2, 0x3840},
    {0x1de832, 0x3840},
    {0x1e2072, 0x3840},
    {0x1e58b2, 0x3840},
    {0x1e90f2, 0x3840},
    {0x1ec932, 0x3840},
    {0x1f0172, 0x3840},
    {0x1f39b2, 0x3840},
    {0x1f71f2, 0x3840},
    {0x1faa32, 0x3840},
    {0x1fe272, 0x3840},
    {0x201ab2, 0x3840},
    {0x2052f2, 0x3840},
    {0x208b32, 0x3840},
    {0x20c372, 0x3840},
    {0x20fbb2, 0x3840},
    {0x2133f2, 0x3840},
    {0x216c32, 0x3840},
    {0x21a472, 0x3840},
    {0x21dcb2, 0x3840},
    {0x2214f2, 0x7080},
    {0x228572, 0x7080},
    {0x22f5f2, 0x7080},
    {0x236672, 0x7080},
    {0x23d6f2, 0x7080},
    {0x244772, 0x7080},
    {0x24b7f2, 0x7080},
    {0x252872, 0x7080},
    {0x2598f2, 0x7080},
    {0x260972, 0xeac},
    {0x26181e, 0x3140},
    {0x26495e, 0x251c},
    {0x266e7a, 0x2cd4},
    {0x269b4e, 0x2618},
    {0x26c166, 0x2ed4},
    {0x26f03a, 0x3020},
    {0x27205a, 0x3af8},
    {0x275b52, 0x3e70},
    {0x2799c2, 0x2e44},
    {0x27c806, 0x6dd4},
    {0x2835da, 0x3cd3},
    {0x2872ad, 0x3e8},
    {0x287695, 0x23d8},
    {0x289a6d, 0x4168},
    {0x28dbd5, 0x48fa},
    {0x2924cf, 0x2be1},
    {0x2950b0, 0x1be1},
    {0x296c91, 0x190},
    {0x296e21, 0x2535},
    {0x299356, 0xc8},
    {0x29941e, 0xc2a},
    {0x29a048, 0x190},
    {0x29a1d8, 0x1001},
    {0x29b1d9, 0x3e8},
    {0x29b5c1, 0xda2},
    {0x29c363, 0x3e8},
    {0x29c74b, 0x1639},
    {0x29dd84, 0x4b0},
    {0x29e234, 0x169e},
    {0x29f8d2, 0x50},
    {0x29f922, 0x23cb},
    {0x2a1ced, 0x3e8},
    {0x2a20d5, 0x179b},
    {0x2a3870, 0x190},
    {0x2a3a00, 0x2659},
    {0x2a6059, 0x4b0},
    {0x2a6509, 0x10e9},
    {0x2a75f2, 0x3e8},
    {0x2a79da, 0xfa0}};

// addr: 192E:07F4
// size: 2
unsigned int _stklen = 0x7d00;

// addr: 192E:07F6
// size: 2
int reg = 0;

// addr: 192E:07F8
// size: 18
unsigned char keys[18] = {
    0x2a, 0x36, 0x1d, 0x38, 0x3a, 0x39, 0x1c, 0x52, 0x53, 0x47, 0x4f, 0x49, 0x51, 0x48, 0x50, 0x4b, 0x4d, 0x4c};

// addr: 192E:080A
// size: 72
unsigned char *key_label[18] = {
    "Left shift",
    "Right shift",
    "Ctrl",
    "Alt",
    "Caps",
    "Space",
    "Enter",
    "Insert",
    "Delete",
    "Home",
    "End",
    "Page up",
    "Page down",
    "Up arrow",
    "Down arrow",
    "Left arrow",
    "Right arrow",
    "Cursor 5"};

// addr: 192E:0852
// size: 8
unsigned char pc_key[8] = {
    0xf, 0x10, 0x2, 0x3, 0xd, 0xe, 0xb, 0xc};

// addr: 192E:085A
// size: 8
unsigned char *errmsg[2] = {
    "Out of memory",
    "Cannot open file"};

// addr: 192E:0862
// size: 4
unsigned char *textscreen = (unsigned char *)0xb8000000;

// addr: 192E:0866
// size: 4
unsigned char *vgabase = (unsigned char *)0xa0000000;

// addr: 192E:086A
// size: 72
int VOC_priority[12][3] = {
    {213, 214, 10},
    {215, 216, 5},
    {217, 218, 0},
    {223, 224, 100},
    {219, 220, 50},
    {221, 222, 50},
    {225, 226, 10},
    {227, 228, 20},
    {229, 230, 15},
    {231, 232, 15},
    {233, 234, 20},
    {207, 208, 200}};

// module: HOCUS
// size: 0x5
// addr: 049E:000A
void make_pc_sounds(void)
{
}

// module: HOCUS
// size: 0x33f
// addr: 049E:000F
void new_program(void)
{
    // register: SI
    // size: 2
    int i;

    GRAVISenabled = 1;
    JOY_Initialize();
    srand(time(0x0));
    open_database();
    kick_on_adlib_and_blaster();
    read_pels(palette, 0, 0x100);
    fade_out(0x8c);
    setvga();
    alloc_bytes(&bkg, 0x3840, "M");
    alloc_bytes(&sld, 0x3840, "M");
    alloc_bytes(&sldsav, 0x3840, "M");
    alloc_words(&fnc, 0x7080, "M");
    alloc_bytes(&swe, 0x3840, "M");
    alloc_bytes(&buf64, 64000, "1");
    alloc_words(&imf_music, 32000, "2");

    for (i = 0; i < 0xc; i++)
    {
        if (blaster != 0)
        {
            alloc_bytes(&sfx_mem[i], db[VOC_priority[i][0]].len, "3");
        }
        else
        {
            alloc_words(&pcs_mem[i], db[VOC_priority[i][1]].len, "3");
        }
    }

    alloc_bytes(&font, db[0].len, "4");
    for (i = 0; i < 10; i++)
    {
        alloc_bytes(&spr_code[i], 0x23a6, "5");
    }
    pcs_sample = -1;
    pcs_sampleplaying = 0;

    for (i = 0; i < 0xc; i++)
    {
        if (blaster != 0)
        {
            load_file_to_byte_pointer(VOC_priority[i][0], sfx_mem[i]);
        }
        else
        {
            load_file_to_byte_pointer(VOC_priority[i][1], pcs_mem[i]);
            pcs_sample_length[i] = db[VOC_priority[i][1]].len / 2;
        }
    }

    load_file_to_byte_pointer(OFFSET_FONT, font);
    load_file_to_byte_pointer(OFFSET_SINCOS, sine_cosine_table);
    load_file_to_byte_pointer(OFFSET_RANDOM, rnd);
    load_file_to_byte_pointer(OFFSET_CONFIG, &game_config);

    for (i = 0; i < 8; i++)
    {
        pc_key[i] = game_config.pckey[i];
    }

    if ((game_config.jxmin != game_config.jxmax) && (game_config.jymin != game_config.jymax))
    {
        JOY_SetUp(joystickport, game_config.jxmin, game_config.jxmax, game_config.jymin, game_config.jymax);
    }
    rndnum = 0;

    for (i = 0; i < 360; i++)
    {
        l_sine_cosine_table[i][0] = sine_cosine_table[i][0] * 1000000.0;
        l_sine_cosine_table[i][1] = sine_cosine_table[i][1] * 1000000.0;
    }
    new_stars();
    snoozekey(700);
}

// module: HOCUS
// size: 0x4c0
// addr: 049E:034E
void main(int argc, unsigned char **argv)
{
    // stack: [BP-1]
    // size: 1
    signed char select;
    // stack: [BP-2]
    // size: 1
    signed char done;
    // register: DI
    // size: 2
    int result;
    // register: SI
    // size: 2
    int i;

    done = 0;
    nocard = noblaster = 0;

    if (argc == 2)
    {
        strupr(argv[1]);
        if (!strcmp(argv[1], "NOBLASTER"))
        {
            noblaster = 1;
        }
        if (!strcmp(argv[1], "NOCARD"))
        {
            nocard = 1;
        }
    }
    new_program();
    title();
    clear_palette();
    restore_palette_fragment(OFFSET_GAMEPAL, 0, 0);
    restore_palette_fragment(OFFSET_MENUPAL, 0x80, 0);

    while (!done)
    {
        setapage(3);
        restore_graphics_fragment(OFFSET_BULLIT, 0, 0xb4);
        select = do_main_menu();
        switch (select)
        {
        case 0:
            select = do_begin_menu();

            if (select != -1)
            {
                if ((reg == 0) && (select >= 1) && (select <= 3))
                {
                    do_cantplay_info();
                }
                else
                {
                    game = select;
                    level = 0;
                    select = do_skill_options();

                    if (select != -1)
                    {
                        skill = select;
                        score = 0;

                    label1:
                        hfirepower = 1;
                        oldscore = score;
                        result = play(0);

                        if (result == 1)
                        {
                            if (level == 8)
                            {
                                do_winscrn1();
                                i = is_high(game, score);
                                if (i)
                                {
                                    get_hiscore(game, i - 1);
                                }
                            }
                            else
                            {
                                level++;
                                goto label1;
                            }
                        }
                        else if (result == 0)
                        {
                            score = oldscore;
                            goto label1;
                        }
                        else if (result == -1)
                        {
                            i = is_high(game, score);
                            if (i)
                            {
                                get_hiscore(game, i - 1);
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (restore_game())
            {
                goto label1;
            }
            break;
        case 1:
        label2:
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
                goto label2;
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
                goto label2;
            case 2:
                game_config.joystick = !game_config.joystick;
                if ((game_config.joystick != 0) && (!calibrate_joystick()))
                {
                    game_config.joystick = 0;
                }
                goto label2;
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
            break;
        case 6:
            do_show_hiscores(0);
            break;
        case 3:
            do_help(0);
            break;
        case 4:
            break;
        case 5:
            game = 0;
            level = (((long int)rand() * 5) / 0x8000) * 2;
            skill = 1;
            score = 0;
            hfirepower = 1;
            play(2);
            break;
        case 8:
            do_ordering_info();
            break;
        case 7:
            do_previews();
            break;
        case 9:
            done = 1;
            break;
        }
    }
    setapage(0);
    setvpage(0);
    srand(time(0x0));
    show_bin((((long int)rand() * 10) / 0x8000) + OFFSET_PREVIEW);
    restore_graphics_fragment(OFFSET_OLD_HUD, 0, 0xA0);
    strcpy(dline, "Check out the entire 4 game series!");
    pstrol2((SCREEN_WIDTH - pstrlen(dline)) / 2, 0xAA, 7, dline);
    strcpy(dline, "Order Hocus Pocus today!");
    pstrol2((SCREEN_WIDTH - pstrlen(dline)) / 2, 0xB7, 7, dline);
    fade_in(0x14);
    while (kbhit() != 0)
    {
        getch();
    }
    snoozekey(0x1388);
    fade_out(0x14);
    while (kbhit() != 0)
    {
        getch();
    }
    normal_exit();
}
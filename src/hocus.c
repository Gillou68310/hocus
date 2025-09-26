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
db_t db[DB_COUNT] = {
#include "db.c"
};

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
int VOC_priority[SOUND_COUNT][3] = {
    {DB_SOUND6, DB_SOUND6+1, 10},
    {DB_SOUND7, DB_SOUND7+1, 5},
    {DB_SOUND8, DB_SOUND8+1, 0},
    {DB_SOUND11, DB_SOUND11+1, 100},
    {DB_SOUND9, DB_SOUND9+1, 50},
    {DB_SOUND10, DB_SOUND10+1, 50},
    {DB_SOUND12, DB_SOUND12+1, 10},
    {DB_SOUND13, DB_SOUND13+1, 20},
    {DB_SOUND14, DB_SOUND14+1, 15},
    {DB_SOUND15, DB_SOUND15+1, 15},
    {DB_SOUND16, DB_SOUND16+1, 20},
    {DB_SOUND1, DB_SOUND1+1, 200}};

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

    for (i = 0; i < SOUND_COUNT; i++)
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
        alloc_bytes(&spr_code[i], SPR_CODE_SIZE, "5");
    }
    pcs_sample = -1;
    pcs_sampleplaying = 0;

    for (i = 0; i < SOUND_COUNT; i++)
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

    load_file_to_byte_pointer(DB_FONT, font);
    load_file_to_byte_pointer(DB_SINCOS, sine_cosine_table);
    load_file_to_byte_pointer(DB_RANDOM, rnd);
    load_file_to_byte_pointer(DB_CONFIG, &game_config);

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
    restore_palette_fragment(DB_GAMEPAL, 0, 0);
    restore_palette_fragment(DB_MENUPAL, 0x80, 0);

    while (!done)
    {
        setapage(3);
        restore_graphics_fragment(DB_BULLIT, 0, 0xb4);
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
                    play_imf_file(DB_MUSIC_TITLE);
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
    show_bin((((long int)rand() * 10) / 0x8000) + DB_PREVIEW);
    restore_graphics_fragment(DB_OLD_HUD, 0, 0xA0);
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
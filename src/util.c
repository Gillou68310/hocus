#include <stdlib.h>
#include <malloc.h>
#include "common.h"
#include "menus.h"
#include "gr.h"
#include "fileio.h"
#include "soundfx.h"
#include "util.h"
#include "hocus.h"

// addr: 192E:A9AC
// size: 4
void(interrupt *oldk_handler)(void);

#ifndef VERSION_PROTO
unsigned int TickBase = 0x8c;
int word_3A1E6;
int word_3A1E4;
int word_3A1E2;

void SDL_t0Service(task *task)
{
    (void)task;
    clk_times++;
    if (pcs_sample != -1)
    {
        sound(pcs_mem[pcs_sample][pcs_sample_pnt]);
        pcs_sample_pnt += 4;
        if (pcs_sample_length[pcs_sample] <= pcs_sample_pnt)
        {
            pcs_sample = -1;
            pcs_sampleplaying = 0;
            nosound();
        }
    }
}

void start_audio_task(void)
{
    audio_task = TS_ScheduleTask(SDL_t0Service, 0x8C, 1, &clk_times);
    TS_Dispatch();
}

void stop_audio_task(void)
{
    TS_Terminate(audio_task);
#if VERSION_11 || VERSION_DEMO11
    TS_Shutdown();
#endif
}
#endif

// module: UTIL
// size: 0x60
// addr: 14B9:0009
void snooze(int micros)
{
    // register: SI
    // size: 2
    // int micros;
    // stack: [BP-4]
    // size: 4
    unsigned long st;

    micros = (micros / 1000.0) * TickBase;
    st = clk_times;

    while ((clk_times - st) < micros)
        ;
    return;
}

// module: UTIL
// size: 0x8c
// addr: 14B9:0069
int snoozekey(int micros)
{
    // register: SI
    // size: 2
    // int micros;
    // stack: [BP-4]
    // size: 4
    unsigned long st;
    // register: DI
    // size: 2
    int rc = 0;

    micros = (micros / 1000.0) * TickBase;
    st = clk_times;

    while (((clk_times - st) < micros) && (kbhit() == 0) && (get_menu_joystick() != 3))
    {
#if VERSION_PROTO
        ;
#else
        wait_for_retrace();
#endif
    }

    while (kbhit() != 0)
    {
        getch();
        rc = 1;
    }
    return rc;
}

// module: UTIL
// size: 0x46
// addr: 14B9:00F5
void clear_keys(void)
{
    cukey = ukey = dkey = lkey = rkey = fkey = jkey = qkey = pgupkey = pgdnkey = 0;
    ukeyclr = jkeyclr = fkeyclr = 1;
#if VERSION_PROTO
    f2key = f3key = f10key = helpkey = calkey = 0;
#else
    f2key = f3key = f10key = helpkey = calkey = key_342AB = 0;
#endif
    pause = 0;
}

#ifndef VERSION_PROTO
void flush_keyboard(void)
{
    // stack: [BP-16]
    // size: 16
    union REGS regs;

    regs.h.ah = 0xc;
    regs.h.al = 0;
    int86(0x21, &regs, &regs);
}
#endif

// module: UTIL
// size: 0x30
// addr: 14B9:013B
void install_key_handler(void)
{
#if VERSION_PROTO
    clear_keys();
    asm cli;
    oldk_handler = getvect(9);
    setvect(9, key_handler);
    asm sti;
#else
    char *i;
    char *j;
    // TODO
    i = 0x417;
    j = 0x418;
    DISABLE_INTERRUPTS();
    oldk_handler = getvect(9);
    setvect(9, key_handler);
    word_3A1E6 = 0;
    clear_keys();
    *i = 0;
    *j = 0;
    ENABLE_INTERRUPTS();
#endif
}

// module: UTIL
// size: 0x1b
// addr: 14B9:016B
void disable_key_handler(void)
{
#if VERSION_PROTO
    asm cli;
    setvect(9, oldk_handler);
    asm sti;
#else
    DISABLE_INTERRUPTS();
    setvect(9, oldk_handler);
    ENABLE_INTERRUPTS();
#endif
}

// module: UTIL
// size: 0x2d8
// addr: 14B9:0186
void interrupt key_handler(void)
{
    // register: CX
    // size: 1
    unsigned char i;

    gkey = inportb(0x60);
    i = inportb(0x61);
    outportb(0x61, i | 0x80);
    outportb(0x61, i);
#if VERSION_PROTO
    if ((hdead == 0) && (hdone == 0) && (indemo == 0))
#else
    if ((game_config.joystick == 0) && (hdead == 0) && (hdone == 0) && (indemo == 0))
#endif
    {
        if (gkey < 0x80)
        {
            anykey = 1;
        }
        if ((keys[pc_key[4]] == gkey) && (ukeyclr != 0))
        {
            cukey = 1;
            ukey = 1;
            ukeyclr = 0;
        }
        if (gkey == keys[pc_key[4]] + 0x80)
        {
            cukey = 0;
            ukey = 0;
            ukeyclr = 1;
        }
        if (keys[pc_key[5]] == gkey)
        {
            dkey = 1;
        }
        if (gkey == keys[pc_key[5]] + 0x80)
        {
            dkey = 0;
        }
        if (keys[pc_key[0]] == gkey)
        {
            lkey = 1;
        }
        if (gkey == keys[pc_key[0]] + 0x80)
        {
            lkey = 0;
        }
        if (keys[pc_key[1]] == gkey)
        {
            rkey = 1;
        }
        if (gkey == keys[pc_key[1]] + 0x80)
        {
            rkey = 0;
        }
        if ((keys[pc_key[2]] == gkey) && (jkeyclr != 0))
        {
            jkey = 1;
            jkeyclr = 0;
        }
        if (gkey == keys[pc_key[2]] + 0x80)
        {
            jkey = 0;
            jkeyclr = 1;
        }
        if ((keys[pc_key[3]] == gkey) && (fkeyclr != 0))
        {
            fkey = 1;
            fkeyclr = 0;
        }
        if (gkey == keys[pc_key[3]] + 0x80)
        {
            fkey = 0;
            fkeyclr = 1;
        }
    }
#ifndef VERSION_PROTO
    if (gkey == 0x21)
    {
        word_3A1E6 = 0;
    }
    if (gkey == 0x10)
    {
        word_3A1E6 = 0;
    }
    if (gkey == 0x30)
    {
        word_3A1E6 = 0;
    }
    word_3A1E6 += gkey;
    if ((word_3A1E6) == 0x5BA)
    {
        word_3A1E6 = 0;
        health = 0x64;
    }
    if ((word_3A1E6) == 0x3d6)
    {
        hskey = 1;
        hgkey = 1;
    }
#if VERSION_10 || VERSION_11
    if ((word_3A1E6) == 0x378)
    {
        if (hsupershot == 0)
        {
            holdshots = hfirepower;
            hfirepower = 5;
        }
        hsupershot = 600;
    }
    if ((word_3A1E6) == 0x4d8)
    {
        if (hlaser == 0)
        {
            hlaser = 3;
        }
        hlaserdisplay = 1;
        hlaserdisplaycnt = 5;
    }
#endif
#endif
    if (gkey == 0x19)
    {
        pause = 1;
    }
    if (keys[pc_key[6]] == gkey)
    {
        pgupkey = 1;
    }
    if (gkey == keys[pc_key[6]] + 0x80)
    {
        pgupkey = 0;
    }
    if (keys[pc_key[7]] == gkey)
    {
        pgdnkey = 1;
    }
    if (gkey == keys[pc_key[7]] + 0x80)
    {
        pgdnkey = 0;
    }
#if VERSION_PROTO
    if ((gkey == 0x3b) || (gkey == 1))
#else
    if (gkey == 1)
#endif
    {
        qkey = 1;
    }
#if VERSION_PROTO
    if ((gkey == 0xbb) || (gkey == 0x81))
#else
    if (gkey == 0x81)
#endif
    {
        qkey = 0;
    }
    if (gkey == 0x3c)
    {
        f2key = 1;
    }
    if (gkey == 0x3d)
    {
        f3key = 1;
    }
    if (gkey == 0x44)
    {
        f10key = 1;
    }
#if VERSION_PROTO
    if (gkey == 0x23)
#else
    if (gkey == 0x3b)
#endif
    {
        helpkey = 1;
    }
    if (gkey == 0x2e)
    {
        calkey = 1;
    }
    if (gkey == 0x32)
    {
        muskey = 1;
    }
    if (gkey == 0x1f)
    {
        sndkey = 1;
    }
#ifndef VERSION_PROTO
    if (gkey == 0x2f)
    {
        key_342AB = 1;
    }
#endif
    outportb(0x20, 0x20);
}

#if VERSION_PROTO
// module: UTIL
// size: 0x28
// addr: 14B9:045E
void flush_keyboard(void)
{
    // stack: [BP-16]
    // size: 16
    union REGS regs;

    regs.h.ah = 0xc;
    regs.h.al = 0;
    int86(0x21, &regs, &regs);
}
#endif

// module: UTIL
// size: 0x30
// addr: 14B9:0486
void test_khandler(void)
{
    install_key_handler();
    gkey = 0;
    while (1)
    {
        if (gkey == 1)
        {
            break;
        }
        printf("%d\n", gkey);
    }
    disable_key_handler();
}

// module: UTIL
// size: 0x29
// addr: 14B9:04B6
int myrnd(int limit)
{
    rndnum++;
    if (999 < rndnum)
    {
        rndnum = 0;
    }
    return rnd[rndnum] % limit;
}

// module: UTIL
// size: 0x7c
// addr: 14B9:04DF
void normal_exit(void)
{
    // stack: [BP-4]
    // size: 4
    unsigned char *textscreen;

    textscreen = (unsigned char *)0xb8000000;
#if VERSION_PROTO
    settext();
    gotoxy(1, 0x18);
    read_pels(palette, 0, 0x100);
    clear_palette();
    load_file_to_byte_pointer(OFFSET_DOSMSG, textscreen);
    fade_in(0x1e);
    load_and_play_VOC(OFFSET_SOUND + 5);
    while (SB_VOCPlaying() != 0)
        ;
    kill_sound_drivers();
    close_database();
#else
    open_database();
    settext();
    clrscr();
    gotoxy(1, 0x18);
    read_pels(palette, 0, 0x100);
    clear_palette();
#if VERSION_DEMO10 || VERSION_DEMO11
    load_file_to_byte_pointer(OFFSET_DOSSHARE, buf64);
#else
    load_file_to_byte_pointer(OFFSET_DOSREG, buf64);
#endif
    MCPY(textscreen, buf64, 4000);
    fade_in(0x1e);
    kill_sound_drivers();
    close_database();
    stop_audio_task();
#endif
}

#ifndef VERSION_PROTO
void nomem_exit(void)
{
    settext();
    clrscr();
    kill_sound_drivers();
    stop_audio_task();
    printf(
#if VERSION_10 || VERSION_DEMO10
        "Not enough memory to run Hocus Pocus Version 1.0\n\n"
#else
        "Not enough memory to run Hocus Pocus.\n\n"
#endif
        "You need 580,000 (567 KB) to run Hocus Pocus. Try the following\n"
        "remedies to increase your amount of free memory.\n\n"
        "1) Do not run Hocus Pocus using a DOS Shell program.\n"
        "2) Load DOS into high memory. (DOS V5.0+)\n"
        "3) Remove any unused TSR programs or load them into high memory.\n"
        "4) Do not run Hocus Pocus from Windows.\n\n"
        "Please run HP-HELP for more information.\n\n"
        "Apogee Software");
    gotoxy(1, 0x18);
    exit(3);
}
#endif

// module: UTIL
// size: 0x31
// addr: 14B9:055B
void terminate(unsigned char *str)
{
    kill_sound_drivers();
#if VERSION_PROTO
    close_database();
#endif
    settext();
    printf("%s\n", str);
    exit(3);
}

// module: UTIL
// size: 0x40
// addr: 14B9:058C
void terminate_emsg(int emsg, unsigned char *str2)
{
    kill_sound_drivers();
#if VERSION_PROTO
    close_database();
#endif
    settext();
    printf("%s [%s]\n", errmsg[emsg], str2);
    exit(3);
}

// module: UTIL
// size: 0x30
// addr: 14B9:05CC
void alloc_bytes(unsigned char **buf, long bytes, unsigned char *id)
{
    if ((*buf = _fmalloc(bytes)) == NULL)
    {
#if VERSION_PROTO
        terminate_emsg(0, id);
#else
        (void)id;
        nomem_exit();
#endif
    }
}

// module: UTIL
// size: 0x30
// addr: 14B9:05FC
void alloc_words(int16_t **buf, long words, unsigned char *id)
{
    if ((*buf = _fmalloc(words)) == NULL)
    {
#if VERSION_PROTO
        terminate_emsg(0, id);
#else
        (void)id;
        nomem_exit();
#endif
    }
}

// module: UTIL
// size: 0x30
// addr: 14B9:062C
void alloc_dwords(int32_t **buf, long dwords, unsigned char *id)
{
    if ((*buf = _fmalloc(dwords)) == NULL)
    {
#if VERSION_PROTO
        terminate_emsg(0, id);
#else
        (void)id;
        nomem_exit();
#endif
    }
}

// module: UTIL
// size: 0x3a
// addr: 14B9:065C
void get_offset_length(int db_rec, long *offset, long *length)
{
    // register: SI
    // size: 2
    // int db_rec;

    *offset = db[db_rec].ofs;
    *length = db[db_rec].len;
}

// module: UTIL
// size: 0x1e
// addr: 14B9:0696
void get_offset(int db_rec, long *offset)
{
    *offset = db[db_rec].ofs;
}

#ifndef VERSION_PROTO
void joy_23E9E()
{
    char i;
    char cond1, cond2;

    if (game_config.joystick != 0)
    {

        JoyX = JoyY = 0;
        DISABLE_INTERRUPTS();
        outportb(0x201, 0);
        asm in al, dx;
        asm mov[i], al;

        if ((i & 0x10) != 0)
        {
            button1 = 0;
        }
        else
        {
            button1 = 1;
        }

        if ((i & 0x20) != 0)
        {
            button2 = 0;
        }
        else
        {
            button2 = 1;
        }
#if VERSION_11 || VERSION_DEMO11
        if ((i & 0x40) != 0)
        {
            button3 = 0;
        }
        else
        {
            button3 = 1;
        }
        if ((i & 0x80) != 0)
        {
            button4 = 0;
        }
        else
        {
            button4 = 1;
        }
#endif

        do
        {
            asm in al, dx;
            asm mov[i], al;
            if ((i & 1) != 0)
            {
                cond1 = 1;
                JoyX++;
            }
            else
            {
                cond1 = 0;
            }

            if ((i & 2) != 0)
            {
                cond2 = 1;
                JoyY++;
            }
            else
            {
                cond2 = 0;
            }
        } while (cond1 || cond2);

        ENABLE_INTERRUPTS();

        joy_34B02 = joy_34B00 = joy_34AFE = joy_34AFC = 0;
        if (JoyX <= game_config.jxmin)
        {
            if (word_3A1E4 == 5)
            {
                joy_34B02 = 1;
            }
            else
            {
                word_3A1E4 = 5;
            }
        }
        if (JoyX >= game_config.jxmax)
        {
            if (word_3A1E4 == 4)
            {
                joy_34B00 = 1;
            }
            else
            {
                word_3A1E4 = 4;
            }
        }
        if (JoyY <= game_config.jymin)
        {
            if (word_3A1E2 == 1)
            {
                joy_34AFE = 1;
            }
            else
            {
                word_3A1E2 = 1;
            }
        }
        if (JoyY >= game_config.jymax)
        {
            if (word_3A1E2 == 2)
            {
                joy_34AFC = 1;
            }
            else
            {
                word_3A1E2 = 2;
            }
        }
    }
}

void joy_23F9D()
{
    char i;
    char cond1, cond2;

    if (game_config.joystick != 0)
    {
        JoyX = JoyY = 0;
        DISABLE_INTERRUPTS();

        outportb(0x201, 0);
        asm in al, dx;
        asm mov[i], al;

        if ((i & 0x10) != 0)
        {
            button1 = 0;
        }
        else
        {
            button1 = 1;
        }

        if ((i & 0x20) != 0)
        {
            button2 = 0;
        }
        else
        {
            button2 = 1;
        }
#if VERSION_11 || VERSION_DEMO11
        if ((i & 0x40) != 0)
        {
            button3 = 0;
        }
        else
        {
            button3 = 1;
        }
        if ((i & 0x80) != 0)
        {
            button4 = 0;
        }
        else
        {
            button4 = 1;
        }
#endif

        do
        {
            asm in al, dx;
            asm mov[i], al;

            if ((i & 1) != 0)
            {
                cond1 = 1;
                JoyX++;
            }
            else
            {
                cond1 = 0;
            }

            if ((i & 2) != 0)
            {
                cond2 = 1;
                JoyY++;
            }
            else
            {
                cond2 = 0;
            }
        } while (cond1 || cond2);

        ENABLE_INTERRUPTS();

        game_config.joyx = JoyX;
        game_config.jxmin = JoyX / 3;
        game_config.jxmax = JoyX + JoyX / 3;
        game_config.joyy = JoyY;
        game_config.jymin = JoyY / 3;
        game_config.jymax = JoyY + JoyY / 3;
    }
    word_3A1E4 = 0;
    word_3A1E2 = 0;
    joy_34B02 = joy_34B00 = joy_34AFE = joy_34AFC = button1 = button2 = 0;
}
#endif
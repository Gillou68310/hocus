#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include "common.h"
#include "menus.h"
#include "gr.h"
#include "fileio.h"
#include "soundfx.h"
#include "util.h"

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
        ;

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
    f2key = f3key = f10key = helpkey = calkey = 0;
    pause = 0;
}

// module: UTIL
// size: 0x30
// addr: 14B9:013B
void install_key_handler(void)
{
    clear_keys();
    asm cli;
    oldk_handler = getvect(9);
    setvect(9, key_handler);
    asm sti;
}

// module: UTIL
// size: 0x1b
// addr: 14B9:016B
void disable_key_handler(void)
{
    asm cli;
    setvect(9, oldk_handler);
    asm sti;
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
    if (((hdead == 0) && (hdone == 0)) && (indemo == 0))
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
    if ((gkey == 0x3b) || (gkey == 1))
    {
        qkey = 1;
    }
    if ((gkey == 0xbb) || (gkey == 0x81))
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
    if (gkey == 0x23)
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
    outportb(0x20, 0x20);
}

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
    settext();
    gotoxy(1, 0x18);
    read_pels(palette, 0, 0x100);
    clear_palette();
    load_file_to_byte_pointer(0xeb, textscreen);
    fade_in(0x1e);
    load_and_play_VOC(0xd4);
    while (SB_VOCPlaying() != 0)
        ;
    kill_sound_drivers();
    close_database();
}

// module: UTIL
// size: 0x31
// addr: 14B9:055B
void terminate(unsigned char *str)
{
    kill_sound_drivers();
    close_database();
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
    close_database();
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
        terminate_emsg(0, id);
    }
}

// module: UTIL
// size: 0x30
// addr: 14B9:05FC
void alloc_words(int **buf, long words, unsigned char *id)
{
    if ((*buf = _fmalloc(words)) == NULL)
    {
        terminate_emsg(0, id);
    }
}

// module: UTIL
// size: 0x30
// addr: 14B9:062C
void alloc_dwords(long **buf, long dwords, unsigned char *id)
{
    if ((*buf = _fmalloc(dwords)) == NULL)
    {
        terminate_emsg(0, id);
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
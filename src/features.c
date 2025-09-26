#include "common.h"
#include "gr.h"
#include "soundfx.h"
#include "util.h"
#include "hocus.h"
#include "menus.h"

// module: FEATURES
// size: 0xa9
// addr: 09E5:000B
void title(void)
{
#if PROTO
    fade_out(40);
    setapage(0);
    setvpage(0);
    load_pcx(DB_APOGEE, 0);
    play_imf_file(DB_MUSIC_FANFARE);
    fade_in(20);
    snoozekey(6000);
    fade_out(30);
    play_imf_file(DB_MUSIC_TITLE);
    setapage(0);
    setvpage(0);
    load_pcx(DB_TITLE, 0);
    fade_in(40);
    load_and_play_VOC(DB_SOUND1);
    snoozekey(4000);
    fade_out(30);
#else
    fade_out(40);
    setapage(0);
    setvpage(0);
#ifndef DEMO
    load_pcx(DB_PIRACY, 0);
    fade_in(20);
#if FINAL
    snoozekey(15000);
    fade_out(20);
#else
    get_any_key();
#endif
    setapage(0);
    setvpage(0);
#endif
    load_pcx(DB_APOGEE, 0);
    play_imf_file(DB_MUSIC_FANFARE, 0);
    fade_in(20);
    snoozekey(9000);
    fade_out(30);
    play_imf_file(DB_MUSIC_TITLE, 1);
    setapage(0);
    setvpage(0);
    load_pcx(DB_TITLE, 0);
#ifndef DEMO
    if (hocus_2E70E)
        restore_graphics_fragment(DB_REGIST, 0, 0xbc);
#endif
    fade_in(40);
    load_and_play_VOC(DB_SOUND1);
    snoozekey(4000);
    fade_out(30);
#endif
}
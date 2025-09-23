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
    fade_out(40);
    setapage(0);
    setvpage(0);
#if VERSION_10 || VERSION_11
    load_pcx(OFFSET_PIRACY, 0);
    fade_in(20);
#if VERSION_10
    get_any_key();
#elif VERSION_11
    snoozekey(15000);
    fade_out(20);
#endif
    setapage(0);
    setvpage(0);
#endif
    load_pcx(OFFSET_APOGEE, 0);
#if VERSION_PROTO
    play_imf_file(MUSIC_FANFARE);
#else
    play_imf_file(MUSIC_FANFARE, 0);
#endif
    fade_in(20);
#if VERSION_PROTO
    snoozekey(6000);
#else
    snoozekey(9000);
#endif
    fade_out(30);
#if VERSION_PROTO
    play_imf_file(MUSIC_TITLE);
#else
    play_imf_file(MUSIC_TITLE, 1);
#endif
    setapage(0);
    setvpage(0);
    load_pcx(OFFSET_TITLE, 0);
#if VERSION_10 || VERSION_11
    if (word_2E70E)
        restore_graphics_fragment(OFFSET_REGIST, 0, 0xbc);
#endif
    fade_in(40);
    load_and_play_VOC(OFFSET_SOUND + 0);
    snoozekey(4000);
    fade_out(30);
}
#include "common.h"
#include "gr.h"
#include "soundfx.h"
#include "util.h"
#include "hocus.h"
#include "menus.h"

#ifdef PROTO
// module: FEATURES
// size: 0xa9
// addr: 09E5:000B
void title(void)
{
    fade_out(0x28);
    setapage(0);
    setvpage(0);
    load_pcx(2, 0);
    play_imf_file(0xc4);
    fade_in(0x14);
    snoozekey(6000);
    fade_out(0x1e);
    play_imf_file(199);
    setapage(0);
    setvpage(0);
    load_pcx(3, 0);
    fade_in(0x28);
    load_and_play_VOC(0xcf);
    snoozekey(4000);
    fade_out(0x1e);
}
#else
void title(void)
{
    fade_out(0x28);
    setapage(0);
    setvpage(0);
    load_pcx(0x11, 0);
    fade_in(0x14);
    get_any_key();
    setapage(0);
    setvpage(0);
    load_pcx(1, 0);
    play_imf_file(598, 0);
    fade_in(0x14);
    snoozekey(9000);
    fade_out(0x1e);
    play_imf_file(601, 1);
    setapage(0);
    setvpage(0);
    load_pcx(2, 0);
    if (word_2E70E)
        restore_graphics_fragment(0x3, 0, 0xbc);
    fade_in(0x28);
    load_and_play_VOC(610);
    snoozekey(4000);
    fade_out(0x1e);
}
#endif
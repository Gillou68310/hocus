#include "common.h"
#include "gr.h"
#include "soundfx.h"
#include "util.h"
#include "hocus.h"

// module: FEATURES
// size: 0xa9
// addr: 09E5:000B
void title(void)
{
    fade_out(40);
    setapage(0);
    setvpage(0);
    load_pcx(OFFSET_APOGEE, 0);
    play_imf_file(MUSIC_FANFARE);
    fade_in(20);
    snoozekey(6000);
    fade_out(30);
    play_imf_file(MUSIC_TITLE);
    setapage(0);
    setvpage(0);
    load_pcx(OFFSET_TITLE, 0);
    fade_in(40);
    load_and_play_VOC(OFFSET_SOUND+0);
    snoozekey(4000);
    fade_out(30);
}
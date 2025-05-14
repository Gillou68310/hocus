#include "common.h"

// module: SOUNDFX
// size: 0xe
// addr: 146F:000C
void pascal OB(unsigned int porta, unsigned char abyte)
{
}

// module: SOUNDFX
// size: 0x42
// addr: 146F:001A
void alOut(unsigned char n, unsigned char b)
{
}

// module: SOUNDFX
// size: 0x2e
// addr: 146F:005C
void pascal SDL_SETTIMER0(int speed)
{
}

// module: SOUNDFX
// size: 0xbc
// addr: 146F:008A
void pascal SDL_ALSERVICE(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
}

// module: SOUNDFX
// size: 0x8c
// addr: 146F:0146
void interrupt SDL_t0Service(void)
{
}

// module: SOUNDFX
// size: 0x1e
// addr: 146F:01D2
void SDL_SetTimerSpeed(void)
{
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:01F0
void SD_MusicOff(void)
{
    // stack: [BP-2]
    // size: 2
    int i;
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:022A
void SD_Startup(void)
{
}

// module: SOUNDFX
// size: 0x24
// addr: 146F:0264
void SD_Shutdown(void)
{
}

// module: SOUNDFX
// size: 0x58
// addr: 146F:0288
void pascal SD_STARTMUSIC(int *musicp)
{
}

// module: SOUNDFX
// size: 0x9d
// addr: 146F:02E0
void play_game_sound(int snd_num)
{
    // register: SI
    // size: 2
    // int snd_num;
}

// module: SOUNDFX
// size: 0x25
// addr: 146F:037D
void play_VOC(unsigned char *vocptr)
{
}

// module: SOUNDFX
// size: 0x64
// addr: 146F:03A2
void kick_on_adlib_and_blaster(void)
{
    // stack: [BP-4]
    // size: 4
    unsigned char *sberr;
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:0406
void load_and_play_VOC(int db_record)
{
}

// module: SOUNDFX
// size: 0x5b
// addr: 146F:0440
void play_imf_file(int db_rec)
{
    // stack: [BP-4]
    // size: 4
    long offset;
    // stack: [BP-8]
    // size: 4
    long length;
}

// module: SOUNDFX
// size: 0xe
// addr: 146F:049B
void kill_sound_drivers(void)
{
}
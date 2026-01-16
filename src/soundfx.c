#include <stdlib.h>
#include "common.h"
#include "util.h"
#include "fileio.h"
#include "hocus.h"

#ifndef PROTO
#include "music.h"
#include "fx_man.h"

void play_game_sound(int snd_num)
{
    if (game_config.soundfx != 0)
    {
        if (blaster != 0)
        {
            FX_PlayVOC((fx_voc*)sfx_mem[snd_num], 0xff, 7, VOC_priority[snd_num][2]);
        }
        else
        {
            if(snd_num >= 14)
            {
                return;
            }
            if ((pcs_sampleplaying == 0) || (current_sound_priority <= VOC_priority[snd_num][2]))
            {
                current_sound_priority = VOC_priority[snd_num][2];
                pcs_sample = snd_num;
                pcs_sample_pnt = 0;
                pcs_sampleplaying = 1;
            }
        }
    }
}

void play_VOC(unsigned char *vocptr)
{
     FX_PlayVOC((fx_voc*)vocptr, 0xff, 7, 1);
}

void kick_on_adlib_and_blaster(void)
{
    fx_device device;
    int ret;
    
#if FINAL
    printf("\nHOCUS POCUS Version 1.1\n");
#else
    printf("\nHOCUS POCUS Version 1.0\n");
#endif

    adlib = blaster = 1;
    if (nocard != 0){
        adlib = blaster = 0;
        return;
    }

    if(game_config.fx_card != -1)
    {
        ret = FX_SetupCard(game_config.fx_card,&device);
        if(ret != FX_Ok)
        {
            blaster = 0;
            printf("\n%s\n", FX_ErrorString(FX_Error));
            exit(3);
        }
        ret = FX_Init(game_config.fx_card, game_config.fx_voices, game_config.fx_samplebits);
        if(ret != FX_Ok)
        {
            blaster = 0;
            printf("\n%s\n", FX_ErrorString(FX_Error));
            exit(3);
        }
        FX_SetVolume(game_config.fx_vol);
    }
    else
    {
        blaster = 0;
    }
    if(game_config.music_card != -1)
    {
        ret = MUSIC_Init(game_config.music_card,game_config.music_addr);
        if(ret != MUSIC_Ok)
        {
            adlib = 0;
            printf("\n%s\n", MUSIC_ErrorString(MUSIC_Error));
            exit(3);
        }
        MUSIC_SetVolume(game_config.music_vol);
    }
    else
    {
        adlib = 0;
        game_config.music = 0;
    }
}

void load_and_play_VOC(int db_record)
{
    open_database();
    load_file_to_byte_pointer(db_record, buf64);
    close_database();

    if ((blaster != 0) && (game_config.soundfx != 0))
    {
        FX_PlayVOC((fx_voc*)buf64, 0xff, 7, 1);
    }
}

void play_imf_file(int db_rec, int loopflag)
{
    long offset;
    long length;

    open_database();
    get_offset_length(db_rec, &offset, &length);
    if ((game_config.music != 0) && (adlib != 0))
    {
        load_to_byte_pointer(offset, length, imf_music);
        MUSIC_PlaySong((unsigned char*)imf_music, loopflag);
    }
    close_database();
}

void SD_MusicOff(void)
{
    MUSIC_StopSong();
}

void kill_sound_drivers(void)
{
    FX_Shutdown();
    MUSIC_Shutdown();
}
#else
#define TIMER_INTERRUPT 8

// addr: 192E:1CE8
// size: 2
unsigned int TickBase = 0x230;

// addr: 192E:A9A8
// size: 4
long alTimeCount;

// addr: 192E:A9A6
// size: 1
unsigned char sqActive;

// addr: 192E:A9A2
// size: 4
int16_t *sqHack;

// addr: 192E:A99E
// size: 4
int16_t *sqHackPtr;

// addr: 192E:A99C
// size: 2
int sqHackLen;

// addr: 192E:A99A
// size: 2
int sqHackSeqLen;

// addr: 192E:A996
// size: 4
long sqHackTime;

// addr: 192E:A992
// size: 4
void(interrupt *t0OldService)(void);

// addr: 192E:A990
// size: 2
unsigned int the_song_length;

// module: SOUNDFX
// size: 0xe
// addr: 146F:000C
void pascal OB(unsigned int porta, unsigned char abyte)
{
    outportb(porta, abyte);
}

// module: SOUNDFX
// size: 0x42
// addr: 146F:001A
void alOut(unsigned char n, unsigned char b)
{
    DISABLE_INTERRUPTS();

    // Write address register
    asm mov dx, 0x388;
    asm mov al, [n];
    asm out dx, al;

    // Wait for at least 3.3 usecs by executing 6 IN instructions
    // (as recommended in the AdLib documentation)
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;

    // Write data register
    asm mov dx, 0x389;
    asm mov al, [b];
    asm out dx, al;

    ENABLE_INTERRUPTS();

    // Wait for at least 23 usecs by executing 35 IN instructions
    // (as recommended in the AdLib documentation)
    asm mov dx, 0x388;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;

    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;

    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;

    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
    asm in al, dx;
}

// module: SOUNDFX
// size: 0x2e
// addr: 146F:005C
void pascal SDL_SETTIMER0(int speed)
{
    OB(0x43, 0x36);
    OB(0x40, speed);
    OB(0x40, (speed >> 8));
}

// module: SOUNDFX
// size: 0xbc
// addr: 146F:008A
void pascal SDL_ALSERVICE(void)
{
    // stack: [BP-2]
    // size: 2
    int i;

    if (!sqActive)
    {
        return;
    }

    while ((sqHackLen != 0) && (sqHackTime <= alTimeCount))
    {
        i = *sqHackPtr;
        sqHackPtr++;
        sqHackTime = alTimeCount + *sqHackPtr;
        sqHackPtr++;
        alOut(i, (i >> 8));
        sqHackLen -= 4;
    }
    alTimeCount++;
    if (sqHackLen == 0)
    {
        musiclooped++;
        sqHackPtr = sqHack;
        sqHackLen = sqHackSeqLen;
        alTimeCount = sqHackTime = 0;
    }
}

// module: SOUNDFX
// size: 0x8c
// addr: 146F:0146
void interrupt SDL_t0Service(void)
{
    if (AdLibPresent != 0)
    {
        SDL_ALSERVICE();
    }
    clk_times++;
    if (pcs_sample != -1)
    {
        sound(pcs_mem[pcs_sample][pcs_sample_pnt]);
        pcs_sample_pnt++;
        if (pcs_sample_length[pcs_sample] <= pcs_sample_pnt)
        {
            pcs_sample = -1;
            pcs_sampleplaying = 0;
            nosound();
        }
    }
    OB(0x20, 0x20);
}

// module: SOUNDFX
// size: 0x1e
// addr: 146F:01D2
void SDL_SetTimerSpeed(void)
{
    SDL_SETTIMER0((1192030L / TickBase));
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:01F0
void SD_MusicOff(void)
{
    // stack: [BP-2]
    // size: 2
    int i;

    alOut(0xbd, 0);
    for (i = 0; i < 10; i++)
    {
        alOut(i + 0xb1, 0);
    }
    sqActive = 0;
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:022A
void SD_Startup(void)
{
    t0OldService = getvect(TIMER_INTERRUPT);
    setvect(TIMER_INTERRUPT, SDL_t0Service);
    alTimeCount = 0;
    SDL_SetTimerSpeed();
}

// module: SOUNDFX
// size: 0x24
// addr: 146F:0264
void SD_Shutdown(void)
{
    SD_MusicOff();
    SDL_SETTIMER0(0);
    setvect(TIMER_INTERRUPT, t0OldService);
}

// module: SOUNDFX
// size: 0x58
// addr: 146F:0288
void pascal SD_STARTMUSIC(int16_t *musicp)
{
    SD_MusicOff();
    if (game_config.music != 0)
    {
        musiclooped = 0;
        sqHackPtr = sqHack = musicp;
        sqHackSeqLen = sqHackLen = the_song_length;
        sqHackTime = 0;
        alTimeCount = 0;
        sqActive = 1;
    }
}

// module: SOUNDFX
// size: 0x9d
// addr: 146F:02E0
void play_game_sound(int snd_num)
{
    // register: SI
    // size: 2
    // int snd_num;
    if (game_config.soundfx != 0)
    {
        if (blaster != 0)
        {
            if ((SB_VOCPlaying() == 0) || (current_sound_priority <= VOC_priority[snd_num][2]))
            {
                current_sound_priority = VOC_priority[snd_num][2];
                SB_PlayVOC(sfx_mem[snd_num], 1);
            }
        }
        else
        {
            if ((pcs_sampleplaying == 0) || (current_sound_priority <= VOC_priority[snd_num][2]))
            {
                current_sound_priority = VOC_priority[snd_num][2];
                pcs_sample = snd_num;
                pcs_sample_pnt = 0;
                pcs_sampleplaying = 1;
            }
        }
    }
}

// module: SOUNDFX
// size: 0x25
// addr: 146F:037D
void play_VOC(unsigned char *vocptr)
{
    if ((blaster != 0) && (game_config.soundfx != 0))
    {
        SB_PlayVOC(vocptr, 1);
    }
}

// module: SOUNDFX
// size: 0x64
// addr: 146F:03A2
void kick_on_adlib_and_blaster(void)
{
    // stack: [BP-4]
    // size: 4
    unsigned char *sberr;

    adlib = blaster = 0;
    SD_Startup();
    sberr = SB_Startup(getenv("BLASTER"));
    if (sberr != NULL)
    {
        terminate(sberr);
    }
    if (nocard == 0)
    {
        adlib = AdLibPresent;
        if (noblaster == 0)
        {
            blaster = SoundBlasterPresent;
        }
    }
}

// module: SOUNDFX
// size: 0x3a
// addr: 146F:0406
void load_and_play_VOC(int db_record)
{
    load_file_to_byte_pointer(db_record, buf64);
    if ((blaster != 0) && (game_config.soundfx != 0))
    {
        SB_PlayVOC(buf64, 1);
    }
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

    get_offset_length(db_rec, &offset, &length);
    if ((game_config.music != 0) && (adlib != 0))
    {
        load_to_byte_pointer(offset, length, imf_music);
        the_song_length = length;
        SD_STARTMUSIC(imf_music);
    }
}

// module: SOUNDFX
// size: 0xe
// addr: 146F:049B
void kill_sound_drivers(void)
{
    SD_Shutdown();
    SB_Shutdown();
}
#endif
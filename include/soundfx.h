#ifndef __SOUNDFX_H__
#define __SOUNDFX_H__

#ifdef PROTO
void play_imf_file(int db_rec);
#else
void play_imf_file(int db_rec, int);
#endif

void play_game_sound(int snd_num);
void play_VOC(unsigned char *vocptr);
void kick_on_adlib_and_blaster(void);
void load_and_play_VOC(int db_record);
void SD_MusicOff(void);
void kill_sound_drivers(void);

extern unsigned int TickBase;

#endif
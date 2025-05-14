#ifndef __SOUNDFX_H__
#define __SOUNDFX_H__

void pascal OB(unsigned int porta, unsigned char abyte);
void alOut(unsigned char n, unsigned char b);
void pascal SDL_SETTIMER0(int speed);
void pascal SDL_ALSERVICE(void);
void interrupt SDL_t0Service(void);
void SDL_SetTimerSpeed(void);
void SD_MusicOff(void);
void SD_Startup(void);
void SD_Shutdown(void);
void pascal SD_STARTMUSIC(int *musicp);
void play_game_sound(int snd_num);
void play_VOC(unsigned char *vocptr);
void kick_on_adlib_and_blaster(void);
void load_and_play_VOC(int db_record);
void play_imf_file(int db_rec);
void kill_sound_drivers(void);

#endif
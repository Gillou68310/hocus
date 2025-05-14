#ifndef __PLAY_H__
#define __PLAY_H__

void scan_monster_shot_hits(void);
void scan_monster_collisions(void);
void smart_bomb_monsters(void);
void scan_for_monster_hits(void);
void clip_monsters(void);
int new_monster(int spr_num, int x, int y, int offset);
int new_shot(int x, int y, int d, int wait, int tag, int sn);
void update_shots(void);
void show_hitbar(int i);
void update_boss3(int i);
void update_boss4(void);
void update_monsters(void);
void update_twinks(void);
void new_twink(int x, int y);
void flash_screen(void);
void load_sprites(void);
void draw_sprite_nocheck(int snum, int x, int y, int dir, int frm);
void draw_sprite(int snum, int xw, int x, int y, int dir, int frm);
void draw_wsprite_nocheck(int snum, int x, int y, int dir, int frm);
void draw_wsprite(int snum, int xw, int x, int y, int dir, int frm);
void draw_rsprite_nocheck(int snum, int x, int y, int dir, int frm);
void draw_rsprite(int snum, int xw, int x, int y, int dir, int frm);
void get_coords(void);
void do_element_animation(void);
void process_monster_reserve(void);
void new_explosion(int x, int y);
void update_explosions(void);
void do_fast_digit(int base, int digit);
void do_fast_key(int base, int image);
void show_panel_stats(void);
void count_crystals(void);
void new_stag(int x, int y, int num);
void update_stags(void);
void do_pause(void);
void do_wiznote(int num);
void do_function_check(void);
int play(int demomode);

#endif
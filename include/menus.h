#ifndef __MENUS_H__
#define __MENUS_H__

int get_menu_joystick(void);
void update_icon(int x, int y);
void update_stars(void);
void new_stars(void);
void pstrs(int x, int y, int color, unsigned char *str);
void pstrwiznote(int x, int y, int clr, unsigned char *str);
// void pstr(int x, int y, int color, unsigned char *str);
int pstrlen(unsigned char *str);
void pstr_hilite(int x, int y, int hc, int nc, unsigned char *str);
void pstrsh(int x, int y, int c, unsigned char *str);
void pstrol(int x, int y, int c, unsigned char *str);
void pstrol2(int x, int y, int c, unsigned char *str);
void ptstr(int x, int y, int fc, int bc, int len, unsigned char *str);
void clrtscrn(void);
void blank(int lx, int ty, int rx, int by, int fc, int bc);
void load_menu(int menunum);
void do_line_menu(unsigned char *msg, int fn);
void do_title_line_menu(unsigned char *tit, unsigned char *msg, int fn);
unsigned char get_any_key(void);
unsigned char get_yesno_key(void);
unsigned char get_number_key(void);
void do_def_menu(int kn);
void do_key_menu(void);
void do_menu(void);
int is_high(int g, long s);
void get_hiscore(int g, int slot);
void do_show_hiscores(int demomode);
void record_iconpos(void);
unsigned char get_menu_key(int ismain);
unsigned char do_main_menu(void);
unsigned char do_begin_menu(void);
unsigned char do_game_options(void);
unsigned char do_level_options(void);
unsigned char do_skill_options(void);
unsigned char do_play_menu(void);
void do_message_menu(unsigned char *msg);
void save_game(void);
int restore_game(void);
int confirm_quit(void);
int calibrate_joystick(void);
void calibrate_from_game(void);
void save_menu(void);
int restore_menu(void);
int quit_menu(void);
void do_info_screen(int page, int limit);
int get_page_key(int page, int limit);
void do_ordering_info(void);
void do_cantplay_info(void);
void do_credits(void);
void do_previews(void);
void do_help(int insidegame);
int play_menu(void);
int do_eval(int didit, int tra, int trf, int mnstrs, int mnstrhts);
void do_winscrn1(void);

#endif
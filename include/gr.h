#ifndef __GR_H__
#define __GR_H__

void settext(void);
void setvpage(int page);
void setapage(int page);
void wait_for_retrace(void);
void setreadplane(unsigned char plane);
void screen(unsigned char on);
void enable_pixels(unsigned char mask);
void latches(int on);
void setvga(void);
void scopy(int dest, int src);
void copyblock(int sp, int lx, int ty, int rx, int by, int dp, int dx, int dy);
void clearscreen(void);
void clearbox(int lx, int ty, int rx, int by);
int pixel_clr(int x, int y);
void pixel(int x, int y, int c);
void blankpixelbox(int lx, int ty, int rx, int by);
void write_pels(unsigned char *rgb, unsigned char pel_start, int pel_count);
void read_pels(unsigned char *rgb, unsigned char pel_start, int pel_count);
void fade_out(int scans);
void fade_in(int scans);
void fade_in_white(void);
void clear_palette(void);
void turn_on_palette(void);
void unpackpcxfile(void);
void load_pcx(int db_rec, int setpal);
void capture_screen(void);
void show_bin(int db_rec);
void restore_graphics_fragment(int db_rec, int sx, int sy);
void restore_palette_fragment(int db_rec, int s, int setpal);

#ifndef VERSION_PROTO
void gr_15D8E(int page);
#endif

#if VERSION_11 || VERSION_DEMO11
int load_pcx_from_file(char *path);
#endif

#endif
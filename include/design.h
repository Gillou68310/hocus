#ifndef __DESIGN_H__
#define __DESIGN_H__

void set_all_layers(int on);
void make_status_line(void);
void show_marker_cursor(int x, int y, int c);
void trim_coords(void);
void show_design_screen(void);
void pick_from_palette(void);
int pick_power_up(void);
int pick_warp(void);
void pick_switch(void);
void pick_rtrip(void);
void pick_etrip(void);
void load_tag_sprites(void);
void pick_mtag(void);
void pick_mtrig(void);
void design(void);

extern struct struct_130 ups[23];
extern int plat_pcx_ofs[4][10];
extern int lvl_info_ofs[4][10];
extern int bdrop_pcxpal_ofs[4][10];

#endif
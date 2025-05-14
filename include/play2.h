#ifndef __PLAY2_H__
#define __PLAY2_H__

void asm_show_background(unsigned char *srcp, unsigned char *destp);
void asm_show_background_h(unsigned char *srcp, unsigned char *destp);
void show_background(void);
void show_background_h(void);
void show_screen(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx);
void show_screen_h(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx);

#endif
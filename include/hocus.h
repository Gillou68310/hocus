#ifndef __HOCUS_H__
#define __HOCUS_H__

void make_pc_sounds(void);
void new_program(void);

extern db_t db[236];
extern unsigned char keys[18];
extern unsigned char *key_label[18];
extern unsigned char pc_key[8];
extern unsigned char *errmsg[2];
extern unsigned char *vgabase;
extern int VOC_priority[SOUND_COUNT][3];
#ifndef PROTO
extern int hocus_2E70E;
#endif

#endif
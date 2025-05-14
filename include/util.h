#ifndef __UTIL_H__
#define __UTIL_H__

void snooze(int micros);
int snoozekey(int micros);
void clear_keys(void);
void install_key_handler(void);
void disable_key_handler(void);
void interrupt key_handler(void);
void flush_keyboard(void);
void test_khandler(void);
int myrnd(int limit);
void normal_exit(void);
void terminate(unsigned char *str);
void terminate_emsg(int emsg, unsigned char *str2);
void alloc_bytes(unsigned char **buf, long bytes, unsigned char *id);
void alloc_words(int **buf, long words, unsigned char *id);
void alloc_dwords(long **buf, long dwords, unsigned char *id);
void get_offset_length(int db_rec, long *offset, long *length);
void get_offset(int db_rec, long *offset);

#endif
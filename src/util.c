#include "common.h"

// module: UTIL
// size: 0x60
// addr: 14B9:0009
void snooze(int micros)
{
    // register: SI
    // size: 2
    // int micros;
    // stack: [BP-4]
    // size: 4
    unsigned long st;
}

// module: UTIL
// size: 0x8c
// addr: 14B9:0069
int snoozekey(int micros)
{
    // register: SI
    // size: 2
    // int micros;
    // stack: [BP-4]
    // size: 4
    unsigned long st;
    // register: DI
    // size: 2
    int rc;
}

// module: UTIL
// size: 0x46
// addr: 14B9:00F5
void clear_keys(void)
{
}

// module: UTIL
// size: 0x30
// addr: 14B9:013B
void install_key_handler(void)
{
}

// module: UTIL
// size: 0x1b
// addr: 14B9:016B
void disable_key_handler(void)
{
}

// module: UTIL
// size: 0x2d8
// addr: 14B9:0186
void interrupt key_handler(void)
{
    // register: CX
    // size: 1
    unsigned char i;
}

// module: UTIL
// size: 0x28
// addr: 14B9:045E
void flush_keyboard(void)
{
    // stack: [BP-16]
    // size: 16
    union REGS regs;
}

// module: UTIL
// size: 0x30
// addr: 14B9:0486
void test_khandler(void)
{
}

// module: UTIL
// size: 0x29
// addr: 14B9:04B6
int myrnd(int limit)
{
}

// module: UTIL
// size: 0x7c
// addr: 14B9:04DF
void normal_exit(void)
{
    // stack: [BP-4]
    // size: 4
    unsigned char *textscreen;
}

// module: UTIL
// size: 0x31
// addr: 14B9:055B
void terminate(unsigned char *str)
{
}

// module: UTIL
// size: 0x40
// addr: 14B9:058C
void terminate_emsg(int emsg, unsigned char *str2)
{
}

// module: UTIL
// size: 0x30
// addr: 14B9:05CC
void alloc_bytes(unsigned char **buf, long bytes, unsigned char *id)
{
}

// module: UTIL
// size: 0x30
// addr: 14B9:05FC
void alloc_words(int **buf, long words, unsigned char *id)
{
}

// module: UTIL
// size: 0x30
// addr: 14B9:062C
void alloc_dwords(long **buf, long dwords, unsigned char *id)
{
}

// module: UTIL
// size: 0x3a
// addr: 14B9:065C
void get_offset_length(int db_rec, long *offset, long *length)
{
    // register: SI
    // size: 2
    // int db_rec;
}

// module: UTIL
// size: 0x1e
// addr: 14B9:0696
void get_offset(int db_rec, long *offset)
{
}
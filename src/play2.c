#include "common.h"

// module: PLAY2
// size: 0x2ac
// addr: 134C:0007
void asm_show_background(unsigned char *srcp, unsigned char *destp)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // stack: [BP-10]
    // size: 2
    int bofs;
    // stack: [BP-12]
    // size: 2
    int ofs;
    // stack: [BP-14]
    // size: 2
    int bxs;
}

// module: PLAY2
// size: 0x5b7
// addr: 134C:02B3
void asm_show_background_h(unsigned char *srcp, unsigned char *destp)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // stack: [BP-10]
    // size: 2
    int ofs;
    // stack: [BP-12]
    // size: 2
    int bofs;
    // stack: [BP-14]
    // size: 2
    int bxs;
}

// module: PLAY2
// size: 0x241
// addr: 134C:086A
void show_background(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // register: SI
    // size: 2
    int bofs;
    // register: DI
    // size: 2
    int ofs;
    // stack: [BP-10]
    // size: 2
    int bxs;
}

// module: PLAY2
// size: 0x48b
// addr: 134C:0AAB
void show_background_h(void)
{
    // stack: [BP-2]
    // size: 2
    int x;
    // stack: [BP-4]
    // size: 2
    int y;
    // stack: [BP-6]
    // size: 2
    int i;
    // stack: [BP-8]
    // size: 2
    int mpos;
    // register: DI
    // size: 2
    int ofs;
    // register: SI
    // size: 2
    int bofs;
    // stack: [BP-10]
    // size: 2
    int bxs;
}

// module: PLAY2
// size: 0xd0
// addr: 134C:0F36
void show_screen(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx)
{
}

// module: PLAY2
// size: 0x236
// addr: 134C:1006
void show_screen_h(unsigned char *vdest, unsigned char *vsrc, unsigned char *msld, unsigned char *mbkg, int mbx)
{
}
#include "common.h"

// module: JOYSTICK
// size: 0x62
// addr: 15F5:0005
int JOY_Start(unsigned int joy)
{
    // register: SI
    // size: 2
    // unsigned int joy;
    // stack: [BP-2]
    // size: 2
    unsigned int x;
    // stack: [BP-4]
    // size: 2
    unsigned int y;
}

// module: JOYSTICK
// size: 0x10
// addr: 15F5:0067
void JOY_ShutDownStick(unsigned int joy)
{
}

// module: JOYSTICK
// size: 0x92
// addr: 15F5:0077
void JOY_SetScale(unsigned int joy)
{
    // stack: [BP-4]
    // size: 4
    Jdefines *def;
}

// module: JOYSTICK
// size: 0xb4
// addr: 15F5:0109
void JOY_SetUp(unsigned int joy, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy)
{
    // register: DI
    // size: 2
    unsigned int d;
    // register: SI
    // size: 2
    unsigned int r;
    // stack: [BP-4]
    // size: 4
    Jdefines *def;
}

// module: JOYSTICK
// size: 0x18
// addr: 15F5:01BD
unsigned char JOY_Buttons(void)
{
    // register: BX
    // size: 2
    unsigned int joybits;
}

// module: JOYSTICK
// size: 0x9d
// addr: 15F5:01D5
void JOY_GetPosition(unsigned int joy, unsigned int *xp, unsigned int *yp)
{
    // stack: [BP-1]
    // size: 1
    unsigned char xb;
    // stack: [BP-2]
    // size: 1
    unsigned char yb;
    // stack: [BP-3]
    // size: 1
    unsigned char xs;
    // stack: [BP-4]
    // size: 1
    unsigned char ys;
    // stack: [BP-6]
    // size: 2
    unsigned int x;
    // stack: [BP-8]
    // size: 2
    unsigned int y;
}

// module: JOYSTICK
// size: 0x1a3
// addr: 15F5:0272
void JOY_GetDelta(unsigned int joy, int *dx, int *dy)
{
    // register: SI
    // size: 2
    // unsigned int joy;
    // stack: [BP-2]
    // size: 2
    unsigned int x;
    // stack: [BP-4]
    // size: 2
    unsigned int y;
    // stack: [BP-8]
    // size: 4
    Jdefines *def;
}

// module: JOYSTICK
// size: 0x27
// addr: 15F5:0415
unsigned int JOY_GetButtons(unsigned int joy)
{
    // register: BX
    // size: 2
    unsigned int result;
}

// module: JOYSTICK
// size: 0x6e
// addr: 15F5:043C
void JOY_PollButtons(void)
{
    // register: SI
    // size: 2
    int buttons;
}

// module: JOYSTICK
// size: 0x4f
// addr: 15F5:04AA
void JOY_PollMovement(void)
{
    // stack: [BP-2]
    // size: 2
    int joyx;
    // stack: [BP-4]
    // size: 2
    int joyy;
}

// module: JOYSTICK
// size: 0x32
// addr: 15F5:04F9
void JOY_Initialize(void)
{
    // register: SI
    // size: 2
    int i;
}

// module: JOYSTICK
// size: 0xae
// addr: 15F5:052B
int JOY_Calibrate(int joystickport)
{
    // register: SI
    // size: 2
    // int joystickport;
    // stack: [BP-2]
    // size: 2
    unsigned int xmin;
    // stack: [BP-4]
    // size: 2
    unsigned int ymin;
    // stack: [BP-6]
    // size: 2
    unsigned int xmax;
    // stack: [BP-8]
    // size: 2
    unsigned int ymax;
    // register: DI
    // size: 2
    unsigned int jb;
}
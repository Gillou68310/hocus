#include "common.h"
#include "joystick.h"

// addr: 192E:1DE2
// size: 2
int joystickenabled = 1;

// addr: 192E:1DE4
// size: 2
int joystickport = 0;

// addr: 192E:1DE6
// size: 2
int GRAVISenabled = 0;

// addr: 192E:AA1E
// size: 48
Jdefines JoyDefs[2];

// addr: 192E:AA1A
// size: 4
int JoyStickHere[2];

// addr: 192E:AA18
// size: 2
int JoyX;

// addr: 192E:AA16
// size: 2
int JoyY;

// addr: 192E:AA14
// size: 2
int button1;

// addr: 192E:AA12
// size: 2
int button2;

// addr: 192E:AA10
// size: 2
int button3;

// addr: 192E:AA0E
// size: 2
int button4;

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

    JOY_GetPosition(joy, &x, &y);
    if ((x == 0x0) || (x > 4990) || (y == 0x0) || (y > 4990))
    {
        return 0;
    }
    else
    {
        JOY_SetUp(joy, 0, (x * 2), 0, (y * 2));
        return 1;
    }
}

// module: JOYSTICK
// size: 0x10
// addr: 15F5:0067
void JOY_ShutDownStick(unsigned int joy)
{
    JoyStickHere[joy] = 0;
}

// module: JOYSTICK
// size: 0x92
// addr: 15F5:0077
void JOY_SetScale(unsigned int joy)
{
    // stack: [BP-4]
    // size: 4
    Jdefines *def;

    def = &JoyDefs[joy];
    def->joyMultXL = 0x8000 / (def->threshMinX - def->joyMinX);
    def->joyMultXH = 0x8000 / (def->joyMaxX - def->threshMaxX);
    def->joyMultYL = 0x8000 / (def->threshMinY - def->joyMinY);
    def->joyMultYH = 0x8000 / (def->joyMaxY - def->threshMaxY);
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

    def = &JoyDefs[joy];
    def->joyMinX = minx;
    def->joyMaxX = maxx;
    r = maxx - minx;
    d = (r / 3);
    def->threshMinX = ((r >> 1) - d) + minx;
    def->threshMaxX = ((r >> 1) + d) + minx;
    def->joyMinY = miny;
    def->joyMaxY = maxy;
    r = maxy - miny;
    d = (r / 3);
    def->threshMinY = ((r >> 1) - d) + miny;
    def->threshMaxY = ((r >> 1) + d) + miny;
    JOY_SetScale(joy);
}

// module: JOYSTICK
// size: 0x18
// addr: 15F5:01BD
unsigned char JOY_Buttons(void)
{
    // register: BX
    // size: 2
    unsigned int joybits;

    joybits = inportb(0x201);
    joybits >>= 4;
    joybits ^= 0xf;
    return joybits;
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

    x = y = 0;

    xs = (joy != 0) ? 2 : 0;
    xb = 1 << xs;
    ys = (joy != 0) ? 3 : 1;
    yb = 1 << ys;

    asm pushf;
    asm push si;
    asm push di;
    asm cli;
    asm mov dx, 0x201;
    asm in al, dx;
    asm out dx, al;
    asm mov ah, [xb];
    asm mov ch, [yb];
    asm xor si, si;
    asm xor di, di;
    asm xor bh, bh;
    asm push bp;
    asm mov bp, 0x1388;
loop:
    asm in al, dx;
    asm dec bp;
    asm je end;
    asm mov bl, al;
    asm and bl, ah;
    asm add si, bx;
    asm mov cl, bl;
    asm mov bl, al;
    asm and bl, ch;
    asm add di, bx;
    asm add cl, bl;
    asm jne loop;
end:
    asm pop bp;
    asm mov cl, [xs];
    asm shr si, cl;
    asm mov cl, [ys];
    asm shr di, cl;
    asm mov[x], si;
    asm mov[y], di;
    asm pop di;
    asm pop si;
    asm popf;

    *xp = x;
    *yp = y;
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

    JOY_GetPosition(joy, &x, &y);
    def = &JoyDefs[joy];
    if (x < def->threshMinX)
    {
        if (x < def->joyMinX)
        {
            x = def->joyMinX;
        }
        x = -(x - def->threshMinX);
        x *= def->joyMultXL;
        x >>= 8;
        *dx = (x > 127) ? -127 : -x;
    }
    else if (x > def->threshMaxX)
    {
        if (x > def->joyMaxX)
        {
            x = def->joyMaxX;
        }
        x = (x - def->threshMaxX);
        x *= def->joyMultXH;
        x >>= 8;
        *dx = (x > 127) ? 127 : x;
    }
    else
    {
        *dx = 0;
    }

    if (y < def->threshMinY)
    {
        if (y < def->joyMinY)
        {
            y = def->joyMinY;
        }
        y = -(y - def->threshMinY);
        y *= def->joyMultYL;
        y >>= 8;
        *dy = (y > 0x7F) ? -0x7F : -y;
    }
    else if (y > def->threshMaxY)
    {
        if (y > def->joyMaxY)
        {
            y = def->joyMaxY;
        }
        y = (y - def->threshMaxY);
        y *= def->joyMultYH;
        y >>= 8;
        *dy = (y > 0x7F) ? 0x7F : y;
    }
    else
    {
        *dy = 0;
    }
}

// module: JOYSTICK
// size: 0x27
// addr: 15F5:0415
unsigned int JOY_GetButtons(unsigned int joy)
{
    // register: BX
    // size: 2
    unsigned int result;

    result = inportb(0x201);
    result >>= (joy != 0) ? 6 : 4;
    result &= 3;
    result ^= 3;
    return result;
}

// module: JOYSTICK
// size: 0x6e
// addr: 15F5:043C
void JOY_PollButtons(void)
{
    // register: SI
    // size: 2
    int buttons;

    buttons = JOY_Buttons();
    if ((joystickport != 0) && (GRAVISenabled == 0))
    {
        if ((buttons & 4) != 0)
        {
            button1 = 1;
        }
        if ((buttons & 8) != 0)
        {
            button2 = 1;
        }
    }
    else
    {
        if ((buttons & 1) != 0)
        {
            button1 = 1;
        }
        if ((buttons & 2) != 0)
        {
            button2 = 1;
        }
        if (GRAVISenabled != 0)
        {
            if ((buttons & 4) != 0)
            {
                button3 = 1;
            }
            if ((buttons & 8) != 0)
            {
                button4 = 1;
            }
        }
    }
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

    JOY_GetDelta(joystickport, &joyx, &joyy);
    if (joyx > 64)
    {
        JoyX += 50;
    }
    else if (joyx < -64)
    {
        JoyX -= 50;
    }
    if (joyy > 0x40)
    {
        JoyY += 50;
    }
    else if (joyy < -64)
    {
        JoyY -= 50;
    }
}

// module: JOYSTICK
// size: 0x32
// addr: 15F5:04F9
void JOY_Initialize(void)
{
    // register: SI
    // size: 2
    int i;

    for (i = 0; i < 2; i++)
    {
        JoyStickHere[i] = JOY_Start(i);
    }
    if (JoyStickHere[joystickport] == 0)
    {
        joystickenabled = 0;
    }
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

    printf("Calibrate Joystick\n\n");
    printf("Move joystick to upper left and press button 0\n");
    do
    {
        jb = JOY_Buttons();
    } while ((jb & 1) == 0);
    JOY_GetPosition(joystickport, &xmin, &ymin);
    printf("Move joystick to lower right and press button 1\n");
    do
    {
        jb = JOY_Buttons();
    } while ((jb & 2) == 0);
    JOY_GetPosition(joystickport, &xmax, &ymax);

    while (JOY_Buttons() != 0)
        ;

    if ((xmin != xmax) && (ymin != ymax))
    {
        JOY_SetUp(joystickport, xmin, xmax, ymin, ymax);
    }
    else
    {
        return 0;
    }
    return 1;
}
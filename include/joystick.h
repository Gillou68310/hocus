#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

int JOY_Start(unsigned int joy);
void JOY_ShutDownStick(unsigned int joy);
void JOY_SetScale(unsigned int joy);
void JOY_SetUp(unsigned int joy, unsigned int minx, unsigned int maxx, unsigned int miny, unsigned int maxy);
// unsigned char JOY_Buttons(void);
void JOY_GetPosition(unsigned int joy, unsigned int *xp, unsigned int *yp);
void JOY_GetDelta(unsigned int joy, int *dx, int *dy);
unsigned int JOY_GetButtons(unsigned int joy);
void JOY_PollButtons(void);
void JOY_PollMovement(void);
void JOY_Initialize(void);
int JOY_Calibrate(int joystickport);

extern int joystickport;
extern int GRAVISenabled;
extern Jdefines JoyDefs[2];
extern int JoyStickHere[2];
extern int JoyX;
extern int JoyY;
extern int button1;
extern int button2;
extern int button3;
extern int button4;

#endif
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>
typedef int int16_t;
typedef unsigned int uint16_t;
typedef long int32_t;
typedef unsigned long uint32_t;

#include "defs.h"
#include "types.h"
#include "globals.h"

void MCPY(unsigned char *dst, unsigned char *src, int size);
void SET320X200(void);

#endif
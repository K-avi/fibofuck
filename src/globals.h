
#ifndef GLOBALS_H
#define GLOBALS_H

#include "environment.h"
#include "fibo.h"
#include "stack.h"

extern S_STACK * stack;
extern unsigned char progempty;
extern S_ENVIRONMENT * environment;

extern int ** sizeArrPtr;

#define _size_sizeArr_default 65

extern int default_keyval;

#endif
#ifndef EXEC_H 
#define EXEC_H

#include "ast.h"
#include "fibo.h"
#include "stack.h"
#include "environment.h"

extern int exec( S_ENVIRONMENT * environment, S_STACK * stack , program* progr , unsigned char * printcheck);



#endif
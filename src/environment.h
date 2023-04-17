#ifndef ENV_C
#define ENV_C

#include "fibo.h"

typedef struct env{
    HEAP_SET * heap_set;
    S_NODE * curnode; //points to a node in the heap
    int curTree; //point to a l_entry index in the heap
}S_ENVIRONMENT;

extern S_ENVIRONMENT * initEnv(unsigned size);
extern void freeEnv(S_ENVIRONMENT * env);
extern void envDump( S_ENVIRONMENT * env);

#endif
#ifndef HEAP_H
#define HEAP_H

#include "skew.h"

#define _set_size_default 30
#define _set_realloc_default 10

typedef struct entry{
    S_NODE * skHeap; 
    unsigned nbElem;
}L_ENTRY;


typedef struct list{

    L_ENTRY** entrylist; 
    
    unsigned minIndex;
    unsigned nbelem; 
    
}HEAP_SET;

#endif
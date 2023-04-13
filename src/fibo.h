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
    
    unsigned minIndex; //the index of the heap which has the min element of the heap as it's root
    unsigned nbelem; //sum of every element in every heap
    unsigned size; //current max size of the set
    unsigned nbRoot;  //number of indexes currently used
    
}HEAP_SET;

#endif
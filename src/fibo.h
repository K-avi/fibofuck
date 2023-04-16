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
    
    int minIndex; //the index of the heap which has the min element of the heap as it's root
    unsigned nbelem; //sum of every element in every heap
    unsigned size; //current max size of the set
    unsigned nbRoot;  //number of indexes currently used
    
}HEAP_SET;


/* heap allocation */
extern HEAP_SET* initSet(unsigned size);
extern void freeSet(HEAP_SET * set);
extern void reallocSet(HEAP_SET * set, unsigned size); 

/* heap manipulation */

extern void insertKey(HEAP_SET * set, int key);
extern void removeSet(HEAP_SET * set, unsigned index);
extern int popSetNode(HEAP_SET * set , S_NODE * node , unsigned entry_index);

extern void increaseKey(HEAP_SET * set, unsigned entry_index, S_NODE*  node);
extern void decreaseKey(HEAP_SET * set, unsigned entry_index, S_NODE*  node);
extern void merge ( HEAP_SET * set , int * sizeList);

extern void insertNode ( HEAP_SET * set, S_NODE * root, int treeSize); //only for tests

/* misc handling */
extern void updateMin( HEAP_SET * set);
extern void heapDump( HEAP_SET * heap);
#endif
#include "fibo.h"
#include "skew.h"
#include <stdio.h>
#include <stdlib.h>



/* entry allocation*/

L_ENTRY * initEntry(int key){
    /*
    */
    L_ENTRY* ret= (L_ENTRY* )malloc(sizeof(L_ENTRY));

    if(!ret){
        fprintf(stderr, "error in initEntry unable to allocate memory for the heap entry\n");
        return NULL;
    }

    ret->nbElem=0; 
    ret->skHeap=initNode(key);

    return ret;
}//not tested ; prolly ok

void freeEntry(L_ENTRY* entry){
    /*
    warning frees the heap contained int the entry
    */

    if(!entry) return;

    if(entry->skHeap) freeSkewHeap(entry->skHeap);
    free(entry);
}//not tested ; prolly ok

/* heap set init / alloc*/

HEAP_SET* initSet(unsigned size){
    /*
    */
    HEAP_SET * ret= (HEAP_SET*)malloc(sizeof(HEAP_SET));
    if(!ret ){
        fprintf(stderr, "error: in initSet(%u) unable to allocate memory for the heapset\n",size);
        return NULL;
    }
    ret->minIndex=NULL;
    ret->nbelem=0;
    ret->entrylist= (L_ENTRY**) calloc(size* sizeof(L_ENTRY*), sizeof(L_ENTRY*));

    if(!ret->entrylist){
        fprintf(stderr, "error: in initSet(%u) unable to allocate memory for the heapset's list\n",size);
        free(ret);
        return NULL;
    }
    return ret;
}//not tested; prolly ok


void freeSet(HEAP_SET * set){
    /*
    do I free every tree ???
    */
}

void reallocSet(HEAP_SET * set){
    /*
    */
}

void insertSet(HEAP_SET * set, int key){
    /*
    */
    
    
}

void removeSet(HEAP_SET * set){
    /*
    */
}



void mergeElems(HEAP_SET * set){

}

/*fibo heap manipulation function */

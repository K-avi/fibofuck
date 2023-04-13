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

/////////////////

/* heap set init / alloc*/

HEAP_SET* initSet(unsigned size){
    /*
    */
    HEAP_SET * ret= (HEAP_SET*)malloc(sizeof(HEAP_SET));
    if(!ret ){
        fprintf(stderr, "error: in initSet(%u) unable to allocate memory for the heapset\n",size);
        return NULL;
    }
    ret->minIndex=0;
    ret->nbelem=0;
    ret->size=0;
    ret->nbRoot=0;
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
    checks for nullptr
    completely purges the heaps 
    */
    if(!set) return;

    for (unsigned i=0; i<set->size ; i++){
        if(set->entrylist[i]){
            freeEntry(set->entrylist[i]);
        }
    }
    free(set->entrylist); 
    free(set);
}//not tested; prolly ok


void reallocSet(HEAP_SET * set, unsigned size){
    /*
    checks for nullptr
    throws error if realloc fails
    */
    if(!set) return;
    if(!set->entrylist) return; //?????

    set->entrylist= realloc(set->entrylist, size * sizeof(L_ENTRY* ));

    if(!set->entrylist){
        fprintf(stderr, "error placeholder message\n");
        return;
    }else{
        set->size+=size;
        return;
    }

}//not tested


/*fibo heap manipulation function */


/* heap primitives */
void insertSet(HEAP_SET * set, int key){
    /*
    checks for nullptr and allocation
    handles reallocation!
    */

   if(!set) return;

   if(set->size==set->nbRoot){
        
        reallocSet(set, _set_realloc_default);
        if(!set->entrylist){
            fprintf(stderr, "error in insertSet(%p , %d) realloc failed\n", (void*)set,key);
            return;
        }
   }

   L_ENTRY * newEntry = initEntry(key);
  
   if(!newEntry){
        fprintf(stderr, "error: in insertSet(%p, %d) couldn't allocate memory for new entry\n", (void*) set, key);
        return;
   }

   for(unsigned i=0; i<set->size; i++){
        if(! set->entrylist[i]){
            set->entrylist[i]=newEntry;       
            set->nbelem++;
            set->nbRoot++;
        }
   }
  
}//not tested; CHECK IF ITS GOOD ; potential edge cases insertion 
// shouldn't need the loop in realloc case

void removeSet(HEAP_SET * set, unsigned index){
    /*
    frees the entry at a given index; 
    DOESNT FREE TREE OF THE ENTRY ONLY USE AFTER MERGE!!!
    */
    if(!set) return;
    if(!set->entrylist) return;
    if(set->size<=index) return;

    free(set->entrylist[index]);
    set->entrylist[index]=NULL;
    set->nbRoot--;

}//not tested; prolly ok ? document usage properly 


void merge ( HEAP_SET * set){
    /*
    hell.
    */

    if(!set) return;
    if(!set->entrylist) return;

}//not done 

#include "fibo.h"
#include "skew.h"
#include <limits.h>
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

L_ENTRY* mkEntryNode( S_NODE * node ,int size){
    /*
    NOT DONE 
    */
    
    if(!node){
        return NULL;
    }

    L_ENTRY* ret= (L_ENTRY* )malloc(sizeof(L_ENTRY));

    if(!ret){
        fprintf(stderr, "error in mkEntryNode unable to allocate memory for the heap entry\n");
        return NULL;
    }

    ret->skHeap= node;
    ret->nbElem=size; 

    return ret;
}//not done

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
void insertKey(HEAP_SET * set, int key){
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

void insertNode ( HEAP_SET * set, S_NODE * root, int treeSize){
    /*
    complexity of this is weird; checking for empty node and realloc makes it 
    O(nb_roots²)
    */
    if(! set && root) return;
    
    if(set->size==set->nbRoot){  
        reallocSet(set, _set_realloc_default);
        if(!set->entrylist){
            fprintf(stderr, "error in insertSet(%p , %p) realloc failed\n", (void*)set,(void*)root);
            return;
        }
   }
   for(unsigned i=0; i<set->size; i++){
        if(! set->entrylist[i]){
            L_ENTRY * newEntry = mkEntryNode(root, treeSize);
            if(!newEntry){
                fprintf(stderr, "failed to initialise memory in insertNode(%p , %p)\n", (void*)set, (void*) root);
                return;
            }
            set->entrylist[i]=newEntry;       
            set->nbelem++;
            set->nbRoot++;
        }
   }
}

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


void updateMin( HEAP_SET * set){
    if(!set) return;
    if(!set->entrylist) return;
    if(set->nbelem==0){
        set->minIndex=-1; 
        return;
    }
    int min=INT_MAX , minindex=-1;

    for(unsigned i=0; i<set->size; i++){
        if(set->entrylist[i]){
            if(set->entrylist[i]->skHeap->key<min) {
                min=set->entrylist[i]->skHeap->key;
                minindex= i;
            }
        }
    }

    if(minindex!=-1)set->minIndex= minindex;

    else fprintf(stderr , "warning in updateMin(%p) : empty set\n", set);
    
}


int popSetNode(HEAP_SET * set , S_NODE * node , unsigned entry_index){
    /*
    assumes that the node to pop is actually in the entry of the set 

    checks for nullptr. 
    The pop is in O(1) cuz it's similar to the Fibonnaci Heap pop. 

    what happens is that the node passed is freed and it's children (if they exist) become new trees in 
    the heap set 

    the function return the key stored at the node if succesfull and zero on error 
    */

    if(!set )return 0;
    if(entry_index> set->size) return 0;
    if(set->nbelem==0) return 0;

    L_ENTRY* entry = set->entrylist[entry_index];

    if(!(node && entry)) return 0;


    set->nbelem--; //decrease nbelem before actually deleting it to make call to update min acurate

    int ret= node->key;
    if(!node->parent){ //case where node is the root of the entry 
  
        //this if sucks ass
        if(node->lchild && node->rchild){ //both not null
            
            node->lchild->parent=node->rchild->parent=NULL;
            int sizeL, sizeR; 

            heapSize(&sizeL, node->lchild);
            heapSize(&sizeR, node->rchild);

            entry->nbElem= sizeL; //replaces tree in entry by left child
            entry->skHeap= node->lchild;

            insertNode(set, node->rchild, sizeR); //inserts rchild in the heap
            

        }else if(node->lchild){  //only lchild
            node->lchild->parent=NULL;

            entry->nbElem--;  //bc if no right child only root is popped etc
            entry->skHeap= node->lchild; 
        }else if(node->rchild){ //only rchild
            
            node->rchild->parent=NULL;

            entry->nbElem--;  //bc if no right child only root is popped etc
            entry->skHeap= node->lchild; 
        }else{ //both are null
        //frees entry and set stuff to null
            freeEntry(entry);
            set->entrylist[entry_index]=NULL;
        }

        if(entry_index==set->minIndex){ //updates min in set if necessary
            updateMin(set);
        }   

    }else{ //node passed isn't the root of a tree
        
        if(node->parent->lchild==node){ //unsets it's parent
            node->parent->lchild = NULL;
        }else{
            node->parent->rchild=NULL;
        }
        
        if(node->lchild){
            node->lchild->parent=NULL; 

            int sizeL;

            heapSize(&sizeL, node->lchild);
            insertNode(set, node->lchild, sizeL);
        }
        if(node->rchild){
            node->rchild->parent=NULL; 

            int sizeR;

            heapSize(&sizeR, node->lchild);
            insertNode(set, node->rchild, sizeR);
        }
    }

    free(node);
    return ret;

}//awful ; hellish ; atrocious ; horrible; deletion in O(1) my ass fibo trees are bullshit and I suck
//not tested; prolly wrong

void increaseKey(HEAP_SET * set, int entry_index, S_NODE*  node){

}

void decreaseKey(HEAP_SET * set, int entry_index, S_NODE*  node){
    
}

void merge ( HEAP_SET * set){
    /*
    hell.
    */

    if(!set) return;
    if(!set->entrylist) return;

}//not done 

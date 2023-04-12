#include "skew.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
//boy oh boy

//pain ; suffering even 

/*
    -> function to generate the skew heaps; 
    -> function to put em in the doubly linked list (this part is ez )
    -> proper manipulation of fib heap (here comes the pain)
*/

/* SKEW HEAP */

/* Skew heap allocation functions */

S_NODE * initNode(int key){
    /*
    initialises a tree node and returns it
    */
    S_NODE* ret = (S_NODE*) malloc(sizeof(S_NODE));
    if(!ret){
        fprintf(stderr,"error : allocation of heap failed\n");
        return NULL;
    }
    ret->key= key;
    ret->lchild=ret->rchild=ret->parent=NULL;

    return ret;
}//not tested ; pretty sure it works though

void freeSkewHeap(S_NODE * heap){
    /*
    frees a tree starting from the node given as argument
    */
    if(!heap) return; 

    else{
        
        freeSkewHeap(heap->lchild); 
        freeSkewHeap(heap->rchild); 
        free(heap);
    }
}//not tested


/* skew heap manipulation function */

void swapKey( S_NODE * node1, S_NODE* node2){
    if(!(node1 && node2)){
        return;
    }else{
        int tmp = node1->key;
        node1->key= node2->key;
        node2->key= tmp;
    }
}//not tested; prolly ok though 
//maybe useless


S_NODE * mergeHeaps( S_NODE * SkewHeap1, S_NODE * SkewHeap2){
    /*
    I should definitely explain the behavior of this weirdo 
    */
    if( ! ( SkewHeap1 || SkewHeap2 )) return NULL; //both are NULL

    else if(!SkewHeap1){ //trivial case : only SH2

        return SkewHeap2;
    }else if(!SkewHeap2){//trivial case :only sh1

        return SkewHeap1;
    }
        
    if(SkewHeap1->key> SkewHeap2->key){
        swapKey(SkewHeap1, SkewHeap2);
    }
    printf("sk1 k %d\n sk2 k %d\n", SkewHeap1->key, SkewHeap2->key);
    S_NODE * tmp = SkewHeap1->rchild;
      
    SkewHeap1->rchild= SkewHeap1->lchild;
    printf("call merge else if\n");

    SkewHeap1->lchild= mergeHeaps(SkewHeap2, tmp);
    SkewHeap1->lchild->parent=SkewHeap1;
    return SkewHeap1;
    
}//ot tested 
//prolly an issue with the parent though

S_NODE* insertHeap(S_NODE* skHeap, int value){
    /*
    doesn't check for null bc skHeap can be empty and the new node becomes the only node in the heap
    */

    S_NODE* newNode= initNode(value); 
    if(!newNode){
        fprintf(stderr, "failed to allocate memory for a new node in the heap\n");
        return skHeap;
    }
    return mergeHeaps(skHeap, newNode);

}//not tested

void decrNode( S_NODE * heapNode ){
    /*
    decrement the node passed as argument and swaps it w it's parent while it's lesser than it
    */
    if(!heapNode) return;

    heapNode->key--;

    while(heapNode->parent){ //swap w parent while parent is gt than u

        if(heapNode->parent->key < heapNode->key){
            
            int tmpKey = heapNode->key; 
           
            heapNode->key = heapNode->parent->key;
            heapNode->parent->key= tmpKey;
        }else{
            break;
        }
        heapNode=heapNode->parent;
    }
}//not tested 

int popRoot (S_NODE * skHeap){
    /*
    returns 0 if nullptr passed
    */
   if(!skHeap) return 0;

   S_NODE * skL =  skHeap->lchild, *skR= skHeap ->rchild;

    int ret = skHeap->key; 
    S_NODE * tmp = skHeap; 

    skHeap = mergeHeaps(skL, skR);

    free(tmp);

    return ret; 
}//not tested; 

int popNode (S_NODE * heapNode){
    /* 
    frees node passed; merges it's children ; 
    and then merges the result with it's parent

    returns 0 if nullptr passed
    */
    if(! heapNode) return 0; 

    //S_NODE * parent= heapNode->parent;

    S_NODE * newBranch= mergeHeaps(heapNode->lchild, heapNode->rchild);
    if(newBranch) newBranch->parent= NULL;
    
    int ret = heapNode->key;

    free(heapNode); 
    heapNode= newBranch;

  //  heapNode->parent= parent; 
    return ret; 

}//incorrect; do not use ; not good at all 

void minHeapify ( S_NODE *  heapNode){

}//not done

void incrNode( S_NODE * heapNode){

}//not done

void printInOrderHeap( S_NODE * heapNode) {

    if(!heapNode){
        //printf(" (null) ");
        return;
    }
    printInOrderHeap(heapNode->lchild);
    printf(" %d id :%p  par: %p l: %p  r: %p\n", heapNode->key, heapNode, heapNode->parent, heapNode->lchild, heapNode->rchild );
    printInOrderHeap(heapNode->rchild);
    
}
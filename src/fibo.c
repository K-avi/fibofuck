#include "fibo.h"

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
}//not tested; prolly ok though lol

void swapNodes ( S_NODE ** node1 , S_NODE ** node2){
        /*
        swaps the node ptr so be careful with this
        */
        if(! (node1 && node2)) return;
        S_NODE * tmp = *node1;

        *node1= *node2;
        *node2= tmp;
}

S_NODE * mergeHeaps( S_NODE * SkewHeap1, S_NODE * SkewHeap2){
    /*
    I should definitely explain the behavior of this weirdo 
    */
    if( ! ( SkewHeap1 || SkewHeap2 )) return NULL; //both are NULL

    else if(!SkewHeap1){ //trivial case : only SH2

        return SkewHeap2;
    }else if(!SkewHeap2){//trivial case :only sh1

        return SkewHeap1;
    }else{ //both are non null

        if(SkewHeap1->key > SkewHeap2->key) swapNodes(&SkewHeap1, &SkewHeap2);

        return NULL;
    }



}//not done lol

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

void popRoot (S_NODE * skewHeap){

}

void popNode (S_NODE * heapNode){
    
}

void minHeapify ( S_NODE *  heapNode){

}

void incrNode( S_NODE * heapNode){

}

/* DOUBLY LINKED LIST  */


/* FIBO HEAP */

/* fibo heap allocation functions */



/*fibo heap manipulation function */

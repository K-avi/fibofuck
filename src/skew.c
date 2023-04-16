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
}//tested; ok

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
}//tested; ok


/* skew heap manipulation function */

void swapKey( S_NODE * node1, S_NODE* node2){
    if(!(node1 && node2)){
        return;
    }else{
        int tmp = node1->key;
        node1->key= node2->key;
        node2->key= tmp;
    }
}//tested; ok 


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
   
    S_NODE * tmp = SkewHeap1->rchild;
      
    SkewHeap1->rchild= SkewHeap1->lchild;
   

    SkewHeap1->lchild= mergeHeaps(SkewHeap2, tmp);
    
    if(SkewHeap1->rchild) SkewHeap1->rchild->parent=SkewHeap1;
    if(SkewHeap1->lchild) SkewHeap1->lchild->parent=SkewHeap1;

    return SkewHeap1;
    
}//tested; ok
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

}//tested; ok

void decrNode( S_NODE * heapNode ){
    /*
    decrement the node passed as argument and swaps it w it's parent while it's lesser than it
    */
    if(!heapNode) return;

    heapNode->key--;

    while(heapNode->parent){ //swap w parent while parent is gt than u

        if(heapNode->parent->key > heapNode->key){
            
            int tmpKey = heapNode->key; 
           
            heapNode->key = heapNode->parent->key;
            heapNode->parent->key= tmpKey;
        }else{
            break;
        }
        heapNode=heapNode->parent;
    }
}//tested ; seems ok

int popRoot (S_NODE ** skHeapPTR){
    /*
    returns 0 if nullptr passed
    */
   if(!skHeapPTR) return 0;
   S_NODE * skHeap = *skHeapPTR;

   if(!skHeap) return 0;
   S_NODE * skL =  skHeap->lchild, *skR= skHeap ->rchild;

    int ret = skHeap->key; 
    S_NODE * tmp = skHeap; 

    *skHeapPTR = mergeHeaps(skL, skR);

    (*skHeapPTR)->parent=NULL;
    free(tmp);

    return ret; 
}//tested ;seems ok


int popNode (S_NODE ** heapNodePTR){
    /* 
    frees node passed; merges it's children ; 
    and then merges the result with it's parent
    
    Assumses that the tree is correctly structued 
    
    ie : node->parent->lchild == node || node -> parent ->rchild ==node
    
    returns 0 if nullptr passed ; should prolly print smtg in stderr
    */
    if(!heapNodePTR) return 0;
    int ret=0;
    S_NODE * heapNode = *heapNodePTR;

    if(! heapNode ) return 0; 

    if(!heapNode->parent){ //Case where node given is root
        return popRoot(heapNodePTR);
    }else if(!(heapNode->lchild || heapNode->rchild)){ //case where node passed is a leaf
            if(heapNode->parent->lchild==heapNode){
                heapNode->parent->lchild=NULL;
            }else{
                heapNode->parent->rchild=NULL;
            }
            ret=heapNode->key;
            free(heapNode);

    }else{  

        if(heapNode->parent->lchild==heapNode){
                heapNode->parent->lchild=mergeHeaps(heapNode->lchild, heapNode->rchild);
                heapNode->lchild->parent=heapNode->parent;
        }else{
                heapNode->parent->rchild=mergeHeaps(heapNode->lchild, heapNode->rchild);
                heapNode->rchild->parent=heapNode->parent;
        }
        ret=heapNode->key;
        free(heapNode);

    }
    return ret;
}//tested; seems ok 

void minHeapify ( S_NODE *  heapNode){
    /*
    checks for nullptr 
    given a node heapifies the subtree starting from this root 
    
    */
    if(!heapNode) return;
    
    int min= heapNode->key;
    S_NODE * minNode= heapNode;
    if(heapNode->lchild){
        if(heapNode->lchild->key< min){
            min= heapNode->lchild->key; 
            minNode= heapNode->lchild;
        }
    }

    if(heapNode->rchild){
        if(heapNode->rchild->key< min){
            min= heapNode->rchild->key; 
            minNode= heapNode->rchild;
        }
    }

    if(min!=heapNode->key){
        swapKey(heapNode, minNode);
        minHeapify(minNode);
    }
    
}//tested seems ok 

void incrNode( S_NODE * heapNode){
    /*
    increment a given node by one and heapifies it
    checks for nullptr
    */

    if(!heapNode) return;

    heapNode->key++ ;

    minHeapify(heapNode);

}//tested seems ok





void printInOrderHeap( S_NODE * heapNode) {
    if(!heapNode){
        //printf(" (null) ");
        return;
    }
    printInOrderHeap(heapNode->lchild);
    printf(" %d id :%p  par: %p l: %p  r: %p\n",  heapNode->key, (void*)heapNode, (void*)heapNode->parent,(void*) heapNode->lchild, (void*)heapNode->rchild );
    printInOrderHeap(heapNode->rchild); 
}

void heapSize (int * size , S_NODE * root){
    /*
    tail recursive implem of size of tree primitive
    */
    if(!root){
        return;
    }
    if(size)(*size)++;
    heapSize( size, root->lchild); 
    heapSize(size, root->rchild);
}
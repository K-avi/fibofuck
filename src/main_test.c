#include "skew.h"

#include <stdlib.h>
#include <stdio.h>


int main(){


    S_NODE * heap1= initNode(5);

    heap1=insertHeap(heap1, 2);

    S_NODE * heap3= initNode(0);
    heap3=insertHeap(heap3, -1); 

    heap3=insertHeap(heap3, 10);

    heap1=insertHeap(heap1, 0); 

    S_NODE * heap4= initNode(1);
 
     heap4=insertHeap(heap4, 4);

    S_NODE * heap5 =  initNode( 3);  ;   
       heap5= insertHeap(heap5, -6);
       heap5= insertHeap(heap5, 12);  

    printInOrderHeap(heap1);
  //  printf("in main %d %d %d\n", heap1->key, heap1->lchild->key, heap1->rchild->key);
   
   heap1=mergeHeaps(heap1, heap3);
    heap4=mergeHeaps(heap4, heap5);
   heap1=mergeHeaps(heap1, heap4);

    S_NODE* heap2= initNode(-10);

    heap2=insertHeap(heap2, -5);
    heap2=insertHeap(heap2, -4);
   heap2= insertHeap(heap2, -3);
     heap2= insertHeap(heap2, -2);

  heap1= mergeHeaps(heap1, heap2);
     

printInOrderHeap(heap1);
  //  printf("in main %d %d %d\n", heap1->key, heap1->lchild->key, heap1->rchild->key);
    freeSkewHeap(heap1);
    return 0;
}
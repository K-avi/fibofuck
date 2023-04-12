#include "skew.h"

#include <stdlib.h>
#include <stdio.h>


int main(){


    S_NODE * heap1= initNode(5);

   insertHeap(heap1, 2);
  insertHeap (heap1 , 3);
   printf("after 3 insert %d %d %d\n", heap1->key, heap1->lchild->key, heap1->rchild->key);
  printInOrderHeap(heap1);

    S_NODE * heap3= initNode(0);
   insertHeap(heap3, -1); 

    insertHeap(heap3, 10);

 

    S_NODE * heap4= initNode(1);
 
     insertHeap(heap4, 4);
      insertHeap(heap4, 20);

    S_NODE * heap5 =  initNode( 3);  ;   
       insertHeap(heap5, -6);
        insertHeap(heap5, 12);  

   
   
   mergeHeaps(heap1, heap3);
   mergeHeaps(heap4, heap5);
   mergeHeaps(heap1, heap4);

    S_NODE* heap2= initNode(-10);

   insertHeap(heap2, -5);
   insertHeap(heap2, -4);


   

    S_NODE* heap6 = initNode(13); 
    insertHeap(heap6, 8); 
    insertHeap(heap6, 11); 
    

    mergeHeaps(heap2, heap6);
    mergeHeaps(heap1, heap2);
        
   printf("heap after every insert ffs)");
   printInOrderHeap(heap1);

    printf("heap1 after pop: \n");



  int a = popRoot(&heap1); 

  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  decrNode(heap1->lchild->lchild);
  

  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);
  incrNode(heap1);

  printf("a is %d\n", a);

        printInOrderHeap(heap1);

    freeSkewHeap(heap1);
    return 0;
}
#include "skew.h"
#include "fibo.h"

#include <stdlib.h>
#include <stdio.h>


int main(){

/*
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


  
  popNode(&(heap1->lchild));
printf("heap after pop of lchild");
 printInOrderHeap(heap1);


    freeSkewHeap(heap1);*/

  HEAP_SET * set = initSet(5);
 /*insertKey(set, 2);
  insertKey(set, 2);
  insertKey(set, 2);
  insertKey(set, 2);
  insertKey(set, 2);
  insertKey(set, 2);
  insertKey(set, 2);*/

 // S_NODE * n= initNode(5);

 // insertHeap(n, 6);

 // insertNode(set, n, 2);

  //removeSet( set, 0);

 // popSetNode(set, n, 0);
 // decrNode(set->entrylist[0]->skHeap);
  //printf("%d\n", set->entrylist[0]->skHeap->key);

 // updateMin(set);

  insertKey(set, -5);

 // heapDump(set);

  insertKey(set, 2); 
  

  

 insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);

insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);
insertKey(set , 3);

insertKey(set , 12);

/*

int * sizelist = malloc(11* sizeof(int));
  for(int i=0 ; i<11; i++){
    sizelist[i]=-1;
  }

 if(sizelist) sizelist[0]=10;*/

  mergeWrapper(set);
  heapDump(set);
  //if(sizelist) free(sizelist);

  insertKey(set, 1);
   insertKey(set, 1);
    insertKey(set, 1);

     insertKey(set, 1);
      insertKey(set, 1);
       insertKey(set, 1);

        insertKey(set, 1);
         insertKey(set, 1);
   insertKey(set, 1);
    insertKey(set, 1);
     insertKey(set, 1);
     
  mergeWrapper(set);
  heapDump(set);

  freeSet(set);
  return 0;
}
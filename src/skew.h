#ifndef SKEW_H 
#define SKEW_H

typedef struct _node{ //node inside a tree 
   int key; 
   struct _node * parent; 
   struct _node * lchild; 
   struct _node * rchild; 
}S_NODE;


/* heap alloc functions */

extern S_NODE * initNode(int key);
extern void freeSkewHeap(S_NODE * heap);

/* heap manipulation */
extern void swapKey( S_NODE * node1, S_NODE* node2);

extern S_NODE * mergeHeaps( S_NODE * SkewHeap1, S_NODE * SkewHeap2);
extern S_NODE* insertHeap(S_NODE* skHeap, int value);
extern int popRoot (S_NODE ** skHeap);
extern int popNode (S_NODE ** heapNode);


extern void decrNode( S_NODE * heapNode );
extern void incrNode( S_NODE * heapNode );


/* misc functions */

extern void printInOrderHeap( S_NODE * heapNode);
extern void heapSize (int * size , S_NODE * root);

#endif
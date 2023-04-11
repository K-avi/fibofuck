#ifndef HEAP_H
#define HEAP_H

typedef struct _node{ //node inside a tree 
   int key; 
   struct _node * parent; 
   struct _node * lchild; 
   struct _node * rchild; 
}S_NODE;


typedef struct root_e{ //wrapper list for roots of the tree
   S_NODE * root_ptr;

   struct _root_e * prev; 
   struct _root_e * next;
}S_ROOT_ENTRY;

typedef struct{ //head and tail of the list 
   S_ROOT_ENTRY * head; 
   S_ROOT_ENTRY * tail;
} S_ROOT_LIST;

typedef struct fib_heap{ //heap structure 
 
   S_ROOT_LIST * roots_heap;
   S_NODE * min; 
   unsigned nb_trees;
   unsigned nb_entries;

}S_FIB_HEAP;



#endif
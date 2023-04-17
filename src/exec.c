#include "exec.h"
#include "ast.h"
#include "environment.h"
#include "globals.h"
#include "fibo.h"
#include "parser.tab.h"
#include "skew.h"
#include "stack.h"

#include <sys/select.h>
#include <sys/types.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

int exec( S_ENVIRONMENT * environment, S_STACK * stack , program* progr , unsigned char * printcheck){
  /*
  will prolly be similar to heapfuck/exec.c
  */

  printf("reached exec\n");
  printprgm(progr);
  printf("%u\n", progr->head->tok);
 
  if(!( environment && stack && progr)){
    return -1;
  }

  HEAP_SET * set= environment->heap_set;

  if(!set ) return -2;

  instruction * curr= progr->head;
  printf("curr %p %p\n", curr, curr->next);
  
  unsigned short stack_ptr = 0;

  S_NODE * curnode = environment->curnode;
  int curTree = environment->curTree;

  char safe_getchar[256]; //used in read function to pass stuff safely
  while (curr) {
  printf("reached while curr %p\n", (void*) curr);
    unsigned  tok= curr->tok;
    printf("tok is %u\n", tok);
   
    switch (tok) { 
      case INT_RTREE : 
            if(curTree==-1) break;
            for (int i=curTree+1; i< (int) set->size ; i++ ){

                if(set->entrylist[i]){
                  curTree=i; 
                  curnode = set->entrylist[i]->skHeap;
                  break;
                }
            }
      break; 
      case INT_LTREE :
            if(curTree==-1) break;
            for (int i=curTree; i> 0; i-- ){
                
                if(set->entrylist[i]){
                  curTree=i; 
                  curnode = set->entrylist[i]->skHeap;
                  break;
                }
            }
      break;

      case INT_LCHILD : if(curnode) {if(curnode->lchild) curnode=curnode->lchild ;} break;
      case INT_RCHILD : if(curnode) { if(curnode->rchild) curnode=curnode->rchild ; } break;
      case INT_PARENT : if(curnode) { if(curnode->parent) curnode=curnode->parent ;} break;

      case INT_PLUS : if(curnode && (curTree !=-1)) increaseKey(set,  curTree, curnode);  break;
      case INT_MIN :  if(curnode && (curTree !=-1)) decreaseKey(set,  curTree, curnode); break;

      case INT_LBRACKET : 

            if(!curnode) break; //handles empty set this way

            if (curnode->key == 0) {
              
                curr = curr->other;
            } else {
                if (stack_ptr >= STACK_SIZE) {
                    return -1; //stack overflow
                }
                stack->stack[stack_ptr++] = curr;
            }
      break;

      case INT_RBRACKET : 
       
          curr = stack->stack[--stack_ptr];
      break;

      case INT_POP :  //prolly wrong

          if(curnode && (curTree!=-1)){
            if(set->nbelem ==1){ //only one element in the heap
                popSetNode(set, curnode, curTree);
                curTree=-1; 
                curnode=NULL;
            }else{ //at least 2 elements

                S_NODE * tmpnode; 
                if(curnode->parent){ //not the root 
                   tmpnode=curnode->parent;

                   popSetNode(set, curnode,  curTree); 
                   curnode= tmpnode;

                }else{ //root
                  
                  if(curnode->lchild || curnode->rchild){ 
                  //at least a child so a new root will be set in the entry
                      popSetNode(set, curnode, curTree);
                      curnode=set->entrylist[curTree]->skHeap;
                  }else{ //no children so will have to set node afterwards
                      popSetNode(set, curnode, curTree);
                      curTree=-1; 
                      curnode=NULL;

                      for(unsigned i=0; i<set->size ; i++){//finds another tree
                          if(set->entrylist[i]){
                            curTree=i; 
                            curnode=set->entrylist[i]->skHeap;
                            break;
                          }
                      }
                  }
                }
            }
          }

      break;
      case INT_RMTREE : 
          if(curTree!=-1){
            set->nbRoot--; 
            set->nbelem-=set->entrylist[curTree]->nbElem;
            freeEntry(set->entrylist[curTree]);

            set->entrylist[curTree]=NULL;
            curnode=NULL; 
            curTree=-1;

            if(set->nbRoot){
              for(unsigned i=0; i<set->size ; i++){//finds another tree
                  if(set->entrylist[i]){
                      curTree=i; 
                      curnode=set->entrylist[i]->skHeap;
                      break;
                  }
              }
            }
          }
      break;

      case INT_CREATE : 
          insertKey(set, 0);
          if(!curnode){
              for(unsigned i=0; i<set->size; i++){
                if(set->entrylist[i]){
                  curTree= i; 
                  curnode= set->entrylist[i]->skHeap;
                  break;
                }
              }
          }
      break;
      case INT_READ :
            memset(safe_getchar, 0, 256);
            if(fgets(safe_getchar, 256, stdin)){
                insertKey(set, safe_getchar[0]);
                if(!curnode){
                    for(unsigned i=0; i<set->size; i++){
                      if(set->entrylist[i]){
                        curTree= i; 
                        curnode= set->entrylist[i]->skHeap;
                        break;
                      }
                    }
                }
            }else{
              fprintf(stderr, "error in exec: failed to read from stdin");
            }
      
      break;
      case INT_MERGE :
            mergeWrapper(set);
            if(! set->entrylist[curTree]){
                for(unsigned i=0; i<set->size; i++){
                      if(set->entrylist[i]){
                        curTree= i; 
                        curnode= set->entrylist[i]->skHeap;
                        break;
                      }
                }
            }
            
      break;

      case INT_PRINT :
          if(curnode) printf("%c", curnode->key);
          if(printcheck) *printcheck=1;
      break;
      case INT_DPRINT :  
        if(curnode) printf("%d", curnode->key); 
        if(printcheck) *printcheck=1;
      break;
      case INT_HEAPD : 
        heapDump(set); 
        if(printcheck) *printcheck=1;
      break;
      
      default: break;
    }
    printf("reached curr = curr next\n");
    curr=curr->next;
  }

  environment->curnode= curnode; 
  environment->curTree = curTree;
 

  return 0;

}//not finished; implement handling of empty heap 
//implement deletion /insertion operations 
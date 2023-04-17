#include "environment.h"
#include "fibo.h"
#include <stdio.h>
#include <stdlib.h>

S_ENVIRONMENT * initEnv(unsigned size){
    /*
    returns null if malloc error; 
    inits an environment containing a heap of size size
    */
    S_ENVIRONMENT * ret= (S_ENVIRONMENT*) malloc(sizeof(S_ENVIRONMENT));
    if(!ret){
        fprintf(stderr, "error in initEnv(%u) couldn't allocate memory for environment\n", size);
        return NULL;
    }


    ret->heap_set=initSet(size);
    if(!ret->heap_set){
        fprintf(stderr, "error in initEnv(%u) couldn't allocate memory for set in environment\n", size);
        free(ret);
        return NULL;
    }
    ret->curnode=NULL;
    ret->curTree=-1;
    
    return ret;
}//tested ; ok


void freeEnv(S_ENVIRONMENT * env){
    /*
    checks for nullptr
    */

    if(!env) return;

    if(env->heap_set){
        freeSet(env->heap_set);
    }

    free(env);
    return;
}//  tested ;  ok


void envDump( S_ENVIRONMENT * env){
    /*
    calls heapdump and gives info on the tree pointer and node pointer
    */

    if(!env){
         printf("NULL passed in envDump()\n");
         return;
    }
    
    if(env->curnode) printf("\nnode ptr in env set to node of id %p , containing key %d , parent is %p\n",
    (void*) env->curnode, env->curnode->key ,(void*) env->curnode->parent);

    else printf("node ptr is NULL\n");

    if(env->curTree!=-1) printf("tree pointer is set to %d\n", env->curTree);
    else printf("tree pointer set to default\n");

    heapDump(env->heap_set);
    
}//tested ok 
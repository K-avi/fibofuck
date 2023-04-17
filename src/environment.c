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
}//not tested ; prolly ok


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
}// not tested ; prolly ok
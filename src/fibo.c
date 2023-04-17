#include "fibo.h"
#include "skew.h"

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



/* entry allocation*/

L_ENTRY * initEntry(int key){
    /*
    */
    L_ENTRY* ret= (L_ENTRY* )malloc(sizeof(L_ENTRY));

    if(!ret){
        fprintf(stderr, "error in initEntry unable to allocate memory for the heap entry\n");
        return NULL;
    }

    ret->nbElem=1; 
    ret->skHeap=initNode(key);

    return ret;
}//tested ; ok

L_ENTRY* mkEntryNode( S_NODE * node ,int size){
    /*
    handles nullptr and malloc error
    */
    
    if(!node){
        return NULL;
    }

    L_ENTRY* ret= (L_ENTRY* )malloc(sizeof(L_ENTRY));

    if(!ret){
        fprintf(stderr, "error in mkEntryNode unable to allocate memory for the heap entry\n");
        return NULL;
    }

    ret->skHeap= node;
    ret->nbElem=size; 

    return ret;
}//tested; ok

void freeEntry(L_ENTRY* entry){
    /*
    warning frees the heap contained int the entry
    */

    if(!entry) return;

    if(entry->skHeap) freeSkewHeap(entry->skHeap);
    free(entry);
}// tested ;  ok

/////////////////

/* heap set init / alloc*/

HEAP_SET* initSet(unsigned size){
    /*
    */
    HEAP_SET * ret= (HEAP_SET*)malloc(sizeof(HEAP_SET));
    if(!ret ){
        fprintf(stderr, "error: in initSet(%u) unable to allocate memory for the heapset\n",size);
        return NULL;
    }
    ret->minIndex=-1;
    ret->nbelem=0;
    ret->size=0;
    ret->nbRoot=0;
    ret->entrylist= (L_ENTRY**) calloc(size* sizeof(L_ENTRY*), sizeof(L_ENTRY*));

    if(!ret->entrylist){
        fprintf(stderr, "error: in initSet(%u) unable to allocate memory for the heapset's list\n",size);
        free(ret);
        return NULL;
    }

    for(unsigned i=0; i<size; i++){
        ret->entrylist[i]=NULL;
    }
    return ret;
}// tested; ok


void freeSet(HEAP_SET * set){
    /*
    checks for nullptr
    completely purges the heaps 
    */
    if(!set) return;

    for (unsigned i=0; i<set->size ; i++){
        if(set->entrylist[i]){
            freeEntry(set->entrylist[i]);
        }
    }
    free(set->entrylist); 
    free(set);
}//tested; ok prolly ok


void reallocSet(HEAP_SET * set, unsigned size){
    /*
    checks for nullptr
    throws error if realloc fails
    */
    if(!set) return;
    if(!set->entrylist) return; //?????

    set->entrylist= (L_ENTRY**) realloc(set->entrylist, (set->size+size)*sizeof(L_ENTRY* ));


    for(unsigned i= set->size; i<set->size+size; i++){
        set->entrylist[i]=NULL;
    }
    if(!set->entrylist){
        fprintf(stderr, "error placeholder message\n");
        return;
    }else{
      //  printf("reached realloc ok ; size = %u", size);
        set->size+=size;
        return;
    }

}//tested; ok


/*fibo heap manipulation function */


/* heap primitives */


void updateMin( HEAP_SET * set){
    if(!set) return;
    if(!set->entrylist) return;
    if(set->nbelem==0){
        set->minIndex=-1; 
        return;
    }
    int min=INT_MAX , minindex=-1;

    for(unsigned i=0; i<set->size; i++){
        if(set->entrylist[i]){
            if(set->entrylist[i]->skHeap->key<min) {
                min=set->entrylist[i]->skHeap->key;
                minindex= i;
            }
        }
    }

    if(minindex!=-1)set->minIndex= minindex;

    else fprintf(stderr , "warning in updateMin(%p) : empty set\n",(void*) set);
    
}//tested; ok


static inline int * reallocsizeList(int * sizeList , unsigned realloc_size){
    /*
    reallocs the sizeList array of the merge function by adding realloc_size entries to it and initializing 
    them to -1.
    */
    if(!sizeList )return NULL;
    int NbMaxSizeList= sizeList[0];
    if(NbMaxSizeList<=0) return NULL;

    int * errorLpointer= sizeList;
    //printf("nbmaxsizelist is %d", NbMaxSizeList);
    sizeList= (int* ) realloc(sizeList, (NbMaxSizeList+ realloc_size)* sizeof(int));
    if(!sizeList){
        
        sizeList=NULL;

        free(errorLpointer);
        fprintf(stderr, "error in reallocsizeList(%p , %u ) failed to realloc sizeList", (void*) errorLpointer, realloc_size);
        return NULL;   
    }
    printf("realloc size %u , szl[0] %d\n", realloc_size, sizeList[0]);
    for(int i =sizeList[0]; i< ((int)sizeList[0]+(int)realloc_size) ; i++){
        printf("in realloc i= %d realloc size = %u", i, realloc_size);
        sizeList[i]= -1;
    }
   
    sizeList[0]+= (int)realloc_size;

    return  sizeList;
}
//not tested ; possibly wrong 



void merge ( HEAP_SET * set , int ** sizeListPtr){
    /*
    the merge function will merge trees containing the same number of nodes. 
    It will be called until the size of every tree is different 

    sizeList is an array to keep track of the sizes of different trees in the set. 

    at the index sizeList[i]=j  j is the index of an entry set->entrylist[j] containing a tree 
    of size i 

    sizeList[1]=j means that there is a tree of size 1 in set->entrylist[j] if no reference to an entry is 
    stored at an index sizeList[i] the value is set to -1

    the size of sizeList is stored at index 0; 
    sizeList[0] contains the number of elements in sizeList 

    merge will call itself recursively so sizeList needs to be allocated / de allocated after calling the function
    */
    if(! (set && sizeListPtr)) return;
    int * sizeList = *sizeListPtr;
    if(!( sizeList)) return;
    if(!set->entrylist) return;
    int * errorLpointer = sizeList; //used to dump error in failed realloc

    unsigned char mergeCheck =0; //used to check if a merge occured and call merge recursively if so
    

    for(unsigned i=0 ; i<set->size; i++){
        if( set->entrylist[i]){
            if(set->entrylist[i]->nbElem > (unsigned) sizeList[0]){ //check for realloc
          
                sizeList=reallocsizeList(sizeList, set->entrylist[i]->nbElem);
                if(!sizeList) {
                    fprintf(stderr, "error in merge(%p , %p ) failed to realloc sizeList", (void*)set, (void*) errorLpointer);
                    return;
                }
            }
           // printf("at i=%u sizeList[j]=%d j=%u", i, sizeList[set->entrylist[i]->nbElem], set->entrylist[i]->nbElem);
            if(( sizeList[set->entrylist[i]->nbElem] !=-1 )&& (  sizeList[set->entrylist[i]->nbElem]!= (int)i) ){ //merge case
                /*
                gotta: 
                ->merge trees in the 2 entries; 
                -> set index of sizeList to -1 
                -> set index of newsize in sizelist to current index 
                */
           
                int heapIndex= sizeList[set->entrylist[i]->nbElem]; //retrieves index
                
                sizeList[set->entrylist[heapIndex]->nbElem]=-1; //sets the index back to default

                set->entrylist[i]->skHeap= mergeHeaps(set->entrylist[i]->skHeap,  set->entrylist[heapIndex]->skHeap);
                set->entrylist[i]->nbElem+=set->entrylist[heapIndex]->nbElem;

                removeSet(set, heapIndex); //unsets the entry
                set->entrylist[heapIndex]=NULL;

                if( (unsigned)sizeList[0]< set->entrylist[i]->nbElem){ //realloc if needed
        
                   sizeList= reallocsizeList(sizeList, set->entrylist[i]->nbElem);
                    if(!sizeList){
                        fprintf(stderr, "error in merge(%p , %p ) failed to realloc sizeList", (void*)set, (void*) errorLpointer);
                        return;
                    }
                }
                sizeList[set->entrylist[i]->nbElem]= i; //sets index for tree of new size

                mergeCheck=1; 
            }else{ //set for merge
               // printf("at i=%u, reached non merge condition\n", i);
                if( (unsigned) sizeList[0]< set->entrylist[i]->nbElem){ //realloc if needed
                    sizeList=reallocsizeList(sizeList, set->entrylist[i]->nbElem);

                    if(!sizeList){
                        fprintf(stderr, "error in merge(%p , %p ) failed to realloc sizeList", (void*)set, (void*) errorLpointer);
                        return;
                    }
                }
                sizeList[set->entrylist[i]->nbElem]=i;
            }
        }
    }
    *sizeListPtr = sizeList;
    if(mergeCheck){
        merge(set, sizeListPtr);
    }
   // updateMin(set); 
}//tested seems ok 

void mergeWrapper( HEAP_SET * set){
    /*
    wrapper for merge function; handles the dynamic array and stuff
    */
    if(!set) return;
    int * sizeArr=(int*) malloc(65*sizeof(int));
    if(!sizeArr){
        fprintf(stderr, "error in mergeWrapper(%p) unable to allocate memory for sizeArr", (void*)set);
        return;
    }
    sizeArr[0]=64;
    
    for(unsigned i=1; i<65;i++){
        sizeArr[i]=-1;
    }

    int **sizeArrPtr =(int**) malloc(sizeof(int*));
    *sizeArrPtr= sizeArr;
    merge(set,sizeArrPtr );

    
    free(*sizeArrPtr); 
    free(sizeArrPtr);
}//tested ok

void insertKey(HEAP_SET * set, int key){
    /*
    checks for nullptr and allocation
    handles reallocation!
    */

   if(!set) return;

   if(set->size==set->nbRoot){
        
        reallocSet(set, _set_realloc_default);
        if(!set->entrylist){
            fprintf(stderr, "error in insertSet(%p , %d) realloc failed\n", (void*)set,key);
            return;
        }
   }

   L_ENTRY * newEntry = initEntry(key);
  
   if(!newEntry){
        fprintf(stderr, "error: in insertSet(%p, %d) couldn't allocate memory for new entry\n", (void*) set, key);
        return;
   }

   for(unsigned i=0; i<set->size; i++){
        if(! set->entrylist[i]){

            if(set->minIndex!=-1){
                if(key < set->entrylist[set->minIndex]->skHeap->key){
                    set->minIndex=i;
                }
            }
            set->entrylist[i]=newEntry;       
            set->nbelem++;
            set->nbRoot++;
            break;
        }
   }

   mergeWrapper(set);
  
}//tested ; ok
// shouldn't need the loop in realloc case

void insertNode ( HEAP_SET * set, S_NODE * root, int treeSize){
    /*
    complexity of this is weird; checking for empty node and realloc makes it 
    O(nb_roots²)
    */
    if(! set && root) return;
    
    if(set->size==set->nbRoot){  
        reallocSet(set, _set_realloc_default);
        if(!set->entrylist){
            fprintf(stderr, "error in insertSet(%p , %p) realloc failed\n", (void*)set,(void*)root);
            return;
        }
   }
   for(unsigned i=0; i<set->size; i++){
        if(! set->entrylist[i]){
            L_ENTRY * newEntry = mkEntryNode(root, treeSize);
            if(!newEntry){
                fprintf(stderr, "failed to initialise memory in insertNode(%p , %p)\n", (void*)set, (void*) root);
                return;
            }
            if(set->minIndex!=-1){
                if(newEntry->skHeap->key < set->entrylist[set->minIndex]->skHeap->key){
                    set->minIndex=i;
                }
            }
            set->entrylist[i]=newEntry;       
            set->nbelem+=treeSize;
            set->nbRoot++;
            break;
        }
   }

   mergeWrapper(set);
}// tested ; ok

void removeSet(HEAP_SET * set, unsigned index){
    /*
    frees the entry at a given index; 
    DOESNT FREE TREE OF THE ENTRY ONLY USE AFTER MERGE!!!
    */
    if(!set) return;
    if(!set->entrylist) return;
    if(set->size<=index) return;

    free(set->entrylist[index]);
    set->entrylist[index]=NULL;
    set->nbRoot--;


    mergeWrapper(set);
    updateMin(set);

}//tested ; ok


static void updateNbElem (HEAP_SET * set){
    if(!set) return;
    if(!set->entrylist) return;
    set->nbelem=0;
    for(unsigned i=0 ; i<set->size; i++){
        if(set->entrylist[i]){
            set->nbelem+=set->entrylist[i]->nbElem;
        }
    }
}


int popSetNode(HEAP_SET * set , S_NODE * node , unsigned entry_index){
    /*
    assumes that the node to pop is actually in the entry of the set 

    checks for nullptr. 
    The pop is in O(1) cuz it's similar to the Fibonnaci Heap pop. 

    what happens is that the node passed is freed and it's children (if they exist) become new trees in 
    the heap set 

    the function return the key stored at the node if succesfull and zero on error 
    */

    if(!set )return 0;
    if(entry_index> set->size) return 0;
    if(set->nbelem==0) return 0;

    L_ENTRY* entry = set->entrylist[entry_index];

    if(!(node && entry)) return 0;

    set->nbelem=set->nbelem-1; //decrease nbelem before actually deleting it to make call to update min acurate

    int ret= node->key;
    if(!node->parent){ //case where node is the root of the entry 
  
        //this if sucks ass
        if(node->lchild && node->rchild){ //both not null
            
            node->lchild->parent=node->rchild->parent=NULL;
            int sizeL=0, sizeR=0; 

            heapSize(&sizeL, node->lchild);
            heapSize(&sizeR, node->rchild);

            entry->nbElem= sizeL; //replaces tree in entry by left child
            entry->skHeap= node->lchild;

            insertNode(set, node->rchild, sizeR); //inserts rchild in the heap
          

        }else if(node->lchild){  //only lchild
            node->lchild->parent=NULL;

            entry->nbElem--;  //bc if no right child only root is popped etc
            entry->skHeap= node->lchild; 
        
        }else if(node->rchild){ //only rchild
            
            node->rchild->parent=NULL;
            entry->skHeap= node->lchild; 
           
        }else{ //both are null
        //frees entry and set stuff to null
            removeSet(set, entry_index);
            set->entrylist[entry_index]=NULL;
        }

        if((int)entry_index==set->minIndex){ //updates min in set if necessary
            updateMin(set);
        }   

    }else{ //node passed isn't the root of a tree
        
        if(node->parent->lchild==node){ //unsets it's parent
            node->parent->lchild = NULL;
        }else{
            node->parent->rchild=NULL;
        }
        if(node->lchild || node ->rchild){
            if(node->lchild){
                node->lchild->parent=NULL; 

                int sizeL=0;;

                heapSize(&sizeL, node->lchild);
                insertNode(set, node->lchild, sizeL);
                set->entrylist[entry_index]->nbElem-=sizeL;
               
            }
            if(node->rchild){
                node->rchild->parent=NULL; 

                int sizeR=0;

                heapSize(&sizeR, node->lchild);
                insertNode(set, node->rchild, sizeR);
                set->entrylist[entry_index]->nbElem-=sizeR;
                set->entrylist[entry_index]->nbElem--;
                
            }
            set->entrylist[entry_index]->nbElem--;
            
        }else{
            set->entrylist[entry_index]->nbElem--;
            
        }
        
    }

    free(node);
    mergeWrapper(set);
    updateNbElem(set);

    return ret;

}//awful ; hellish ; atrocious ; horrible; deletion in O(1) my ass fibo trees are bullshit and I suck
//tested; seems ok

void increaseKey(HEAP_SET * set, unsigned entry_index, S_NODE*  node){
    /*
    calls update min to ensure that min is not obsolete ;
    assumes that node is stored in the tree at entry index
    */

    if(!set && node) return;
    if(entry_index> set->size) return;
    if(!set->entrylist) return;

    incrNode(node);
    mergeWrapper(set);
    updateMin(set);

}// tested; ok

void decreaseKey(HEAP_SET * set, unsigned entry_index, S_NODE*  node){
    /*
    assumes that node is stored at the entry of index entry_index; 
    checks for new min
    */
    if(!set && node) return;
    if(entry_index> set->size) return;
    if(!set->entrylist) return;

    decrNode(node);

    if(set->entrylist[entry_index]->skHeap->key< set->entrylist[set->minIndex]->skHeap->key){
    //sets min if new min
        set->minIndex= entry_index;
    }
    mergeWrapper(set);
    updateMin(set);
}//tested; ok


void heapDump( HEAP_SET * heap){
    /*
    prints a lotta stuff about the heap
    */

    if(!heap ) return;

    printf("heap of size %u containing %u roots and %u elements\n", heap->size ,heap->nbRoot, heap->nbelem);
    printf("min index stored at %d\n", heap->minIndex);


    if(!heap->entrylist){
        printf("entry list of the heap is null\n");
        return;
    }
    for(unsigned i=0; i<heap->size; i++){
        if(!heap->entrylist[i]){
            printf("entry %u is NULL\n", i);
        }else{
            printf("entry %u contains %u elements\n", i,heap->entrylist[i]->nbElem);
            printInOrderHeap(heap->entrylist[i]->skHeap);
            printf("\n");
        }
    }
    printf("\n");
}//tested; ok 


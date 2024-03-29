#ifndef AST_H 
#define AST_H

#include "parser.tab.h"
#include <limits.h>


typedef unsigned int token;
struct program ;

typedef struct instruction{ 
    token tok ;
    struct instruction * next; 
    struct instruction * prev;
    struct instruction * other;

}instruction;

typedef struct program{

    instruction * head; 
    instruction * tail;

}program;



extern char token_to_char(int token);


extern instruction * mkinstruction( token tok);
extern program* initProg();

extern void insertHead( program * prog,  instruction * newH);

extern void insertTail( program * prog, instruction * newT);

extern void free_prog (program * prog);

extern void printprgm( program* prgm);

extern void progMerge (program * prog, instruction * list);

extern void mergeInstruction( instruction * list1, instruction * list2);

extern void free_instruct( instruction * list);

enum {  INT_LTREE=0 , INT_RTREE, INT_LCHILD , INT_RCHILD, INT_PARENT , INT_PLUS, INT_MINUS, 
 INT_LBRACKET, INT_RBRACKET, INT_READ, INT_CREATE ,INT_RAND , INT_RMTREE,  INT_POP, INT_HEAPD,  INT_PRINT, INT_DPRINT};


#endif
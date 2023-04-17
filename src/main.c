#include "environment.h"
#include "fibo.h"
#include "stack.h"
#include "globals.h"
#include "exec.h"
#include "ast.h"
#include "cmdline_interp.h"

#include "parser.tab.h"
#include "lex.yy.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>

extern program  * prog;


void sigint_handler( int sig){
    if(!progempty) {
        free_prog(prog);
    }
 
    if(stack) free_stack(stack);
    if(environment) freeEnv(environment);
    if(*sizeArrPtr)free(*sizeArrPtr);
    if(sizeArrPtr) free(sizeArrPtr); 
    yylex_destroy();
    printf("\n");
    exit (SIGINT);

    return;
}

int main(int argc, char ** argv){  

    signal(SIGINT, *sigint_handler );

    unsigned char cmdline_mode=1, file_mode=0;

    unsigned char helpset=0;

    char* filename = NULL;
    int c;

    printf("fibofuck Copyright (C) 2023  Ivan MULOT-RADOJCIC\nThis program comes with ABSOLUTELY NO WARRANTY;\nfor details see the GPLv3 documentation.\nThis is free software, and you are welcome to redistribute it under certain conditions\n\n");

    while ((c = getopt(argc, argv, "hcf:")) != -1) {
        
        switch (c) {
      
        case 'h':
            helpset=1;;
            break;
        
        case 'f':
            filename = optarg;
            cmdline_mode=0;
            file_mode=1;
            break;
        case 'c':
            
            cmdline_mode=1;
            file_mode=0;
            break;
      
        case '?':
            if (optopt == 'f')
            fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
            fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
            fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
       
            exit(-2);
        default:
            abort();
        }
    }

    if(helpset){
        printf("fibofuck is a brainfuck like esolang; the options available are:\n-f to read a file\n-c to use the command line interactive interpret\nmore informations on the fibofuck language can be found in the README.txt and docu/docu.html files.\n"); 
        exit(0);
    }
    
    /*initialising environment and stack ; prog is initialised by parser.tab.c*/
   
    stack= init_stack(STACK_SIZE);
    environment= initEnv(_set_size_default);

    sizeArrPtr= (int**) malloc(sizeof(int*));
    if(!sizeArrPtr){
        fprintf(stderr, "error in main ; failed to allocate memory for sizeArrPtr\n");
        
        free(sizeArrPtr);
        free_stack(stack);
        freeEnv(environment);
        exit(-4);
    }
    *sizeArrPtr= (int*) malloc(3*sizeof(int));
    if(!*sizeArrPtr){
        fprintf(stderr, "error in main ; failed to allocate memory for sizeArrPtr\n");
        
        free(sizeArrPtr);
        free_stack(stack);
        freeEnv(environment);

        exit(-5);
    }
    (*sizeArrPtr)[0]=2;
    
    for(unsigned i=1; i<3;i++){
        (*sizeArrPtr)[i]=-1;
    }

    if (cmdline_mode) {

         interactive_interp( environment, stack);
        
         /*freeing everything after exec*/
     
         free_stack(stack);
         freeEnv(environment);
         free_prog(prog);
         free(*sizeArrPtr);
         free(sizeArrPtr); 
         
         return 0;
         
    }else if(file_mode){

        yyin = fopen(filename, "r");
        if (!yyin) {
            perror("Could not open file");
            exit(-1);
        }
        yyparse();
        progempty=0;
        fclose(yyin);

        exec(environment, stack, prog, NULL);

        /*freeing everything after exec*/
      
        free_stack(stack);
        free_prog(prog);
        freeEnv(environment);
        free(*sizeArrPtr);
        free(sizeArrPtr); 
        
        progempty=1;

        yylex_destroy();
    }
    printf("reached endof main\n");
    return 0;
}
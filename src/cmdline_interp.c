#include "cmdline_interp.h"
#include "ast.h"
#include "environment.h"
#include "fibo.h"
#include "stack.h"
#include "globals.h"
#include "exec.h"

#include "parser.tab.h"
#include "lex.yy.h"

#include <stdio.h>
#include <string.h>

//shouldn't have to change too much 

extern program * prog;

void interactive_interp(S_ENVIRONMENT * environment, S_STACK * stack ){
    /*
    */
    char line[256];

    fflush(stdin); 
    fflush(stdout);

    char lprint=1;

    unsigned char printcheck=0;
    unsigned char syntax_err=0;

    printf("welcome to the fibofuck interactive interpreter!\nto exit simply type quit\n>>> ");
    while( fgets(line, 256, stdin)){


         fflush(stdin); 
         fflush(stdout);

         char * tmp= line; 

         while((*tmp==' '|| *tmp=='\t' || *tmp=='\n')) ++tmp;
         if((*tmp)=='\0' && lprint) {
            printf(">>> ");
            continue;
         }else if ((*tmp)=='\0'){
            lprint=1; 
            continue;
         }
         
         if(!lprint) lprint=1;
       
         if(!strncmp(line, "quit", 4)){
            break;
         }

        yy_scan_string(line);

        progempty=0;
        syntax_err= yyparse(); 

         if(!syntax_err) {
   
            exec(environment, stack, prog, &printcheck);
            
            free_prog(prog);
            prog=NULL;
         }

         progempty=1;    
         yylex_destroy();

        if(printcheck){
         printf("\n>>> ");
         printcheck=0;
        }else if(syntax_err){
         printf("\n>>> ");
         printcheck=0;
        }else{
         printf(">>>");
         lprint=0;
         
        }

        
   }
   printf("bye!\n"); 
  
}
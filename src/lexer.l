%option header-file="lex.yy.h"
%option noinput nounput noyywrap

%{
  #include "parser.tab.h"
  #define TOKEN(t) yylval.token = (t)
%}

%%

[ \t\n]+    { ; }

">"         { return TOKEN(RTREE); }
"<"         { return TOKEN(LTREE); }

"^"         { return TOKEN(PARENT); }
"/"         { return TOKEN(LCHILD); }
"\\"         { return TOKEN(RCHILD); }

"+"         { return TOKEN(PLUS); }
"-"         { return TOKEN(MINUS); }

"["         { return TOKEN(LBRACKET); }
"]"         { return TOKEN(RBRACKET); }

"!"         { return TOKEN(POP); }
"*"         { return TOKEN(RMTREE);}

"%"         {return TOKEN(CREATE);}
","         { return TOKEN(READ); }
"?"         { return TOKEN(RAND); }

":"         { return TOKEN(DPRINT);}
"."         { return TOKEN(PRINT); }
"#"         { return TOKEN(HEAP_DUMP);}

.           { ; }

%%
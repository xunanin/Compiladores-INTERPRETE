%{
#include "definicions.h"
#include <string.h>
#include "erros.h"
int linhas = 0;
%}

BRANCO  [ \t]+
ALFABETO  [A-Za-z]
DIXITO  [0-9]
FIN_LEX [\.;:]
IDENTIFICADOR  ({ALFABETO}|_)({ALFABETO}|{DIXITO}|_)*
ENTEIRO [+-]?{DIXITO}(_?|{DIXITO}+)*

DECIMAL {DIXITO}*\.{DIXITO}+
FLOTANTE   [+-]?({DECIMAL}|{ENTEIRO})(([eE][+-]?)?{DIXITO}+)?
BINARIO 0b[01]+
COMENTARIO_LINHA  \/\/[^\n]*
SUFIXO_CADEAS ([cwd])?
CADEA_COMILLAS_DOBRES \"(\\.|[^"\\])*\"
BINARIO_MAL 0b[2-9][0-9]*
%%
"\n"  ++linhas;
{BRANCO}  /*obviado*/
{ENTEIRO} return NUM_ENTEIRO;

{FLOTANTE} return NUM_FLOTANTE;
{IDENTIFICADOR}  %{
      switch(yytext[0]){
        case 'i':
          if((strcmp(yytext, "import"))==0){
            return IMPORT;
          }else if(strcmp(yytext, "int") == 0){
            return INT;
          }
        break;
        case 'e':
          if((strcmp(yytext, "enforce"))==0){
            return ENFORCE;
          }
        break;
        case 'd':
          if((strcmp(yytext, "double"))==0){
            return DOUBLE;
          }
        break;
        case 'f':
          if((strcmp(yytext, "float"))==0){
            return FLOAT;
          }else if((strcmp(yytext, "float"))==0){
            return FOREACH;
          }
        break;
        case 'v':
          if((strcmp(yytext, "void"))==0){
            return VOID;
          }
        break;
        case 'w':
          if((strcmp(yytext, "while"))==0){
            return WHILE;
          }else if((strcmp(yytext, "writefln"))==0){
            return WRITEFLN;
          }
        break;
        case 'r':
          if((strcmp(yytext, "return"))==0){
            return RETURN;
          }
        break;
        case 's':
          if((strcmp(yytext, "sum"))==0){
            return SUM;
          }
        break;
      }
      return ID;
%}

{BINARIO_MAL} num_malformado(BIN_MAL,yytext,linhas);
{BINARIO} return NUM_BINARIO;
. {
  switch(yytext[0]){
    case '+':
      return SUMA;
    break;
    case '-':
    return RESTA;
    break;
    case '*':
      return MULTIPLICACION;
    break;
    case '/':
      return DIVISION;
    break;
    case '>':
      return MAIOR;
    break;
    case '<':
      return MENOR;
    break;
    default:
      return yytext[0];
    break;
  }
}
{COMENTARIO_LINHA}  /**/
{CADEA_COMILLAS_DOBRES} return STRING;
"/*"  {
            int c;
            while((c = input()) != 0){
            if(c=='\n'){
              ++linhas;
            }else if(c == '*'){
              if((c=input()) == '/'){
                break;
              }else{
                unput(c);
              }
            }
          }
        }

"/+"    {
            int c;
            int num_aninhados=1;
            while((c=input()) != 0){
              if(c == '\n'){
                ++linhas;
              }else if(c == '+'){
                if((c=input()) == '/'){
                  --num_aninhados;
                  if(num_aninhados==0){
                    break;
                  }
                }else{
                  unput(c);
                }
              }else if(c == '/'){
                if((c=input()) == '+'){
                  ++num_aninhados;
                }else{
                  unput(c);
                }
              }
            }
  }
">="  return MAIOR_IGUAL;
"<="  return MENOR_IGUAL;
"!="  return NON_IGUAL;
"=="  return IGUAL;
<<EOF>> {
    yyterminate();
}

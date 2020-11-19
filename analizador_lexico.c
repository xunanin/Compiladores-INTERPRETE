#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "definicions.h"
#include "taboa_simbolos.h"
#include <unistd.h>


//Varibles e función creada por flex para a lectura e análise do ficheiro pasado
extern int yylex();
extern FILE* yyin;
extern char* yytext;

//Estrutura que almacena o lexema co seu identificador
typedef struct l{
  char* literal;
  int id;
}struct_lexema;

typedef struct_lexema* ref_lex;//referencia a struct_lexema para creación de tipo opaco

//Función para a reserva de memoria do string onde se almacena o lexema
void crea_lex(ref_lex* lexema){
  if(*lexema != NULL)
    (*lexema)->literal = (char*)malloc(BLOQUE*sizeof(char));
  else
    printf("Non se puido reservar memoria\n");
}

//Función que libera a memoria reservada para o lexema
void borra_lex(ref_lex* lexema){
  if(*lexema != NULL)
    free((*lexema)->literal);
  else
    printf("Non se puido reservar memoria\n");
}

//Apertura do ficheiro para a análise léxica
void iniciaFich(char* nome){
  yyin = fopen(nome, "r");
}

//Función principal do analizador léxico
void indica_comp_lexica(ref_nodo* taboa, ref_lex* lexema){
  //Chamamos á función de análise léxica de lex.yy.c
  int id = yylex();
  //Copiamos lexema obtido
  strcpy((*lexema)->literal, yytext);
  //Se o lexema é unha palabra reservada ou un identificador miramos se se atopa na táboa de símbolos
  if(id>=ID && id <=NOT_EQUAL)
    (*lexema)->id = busca(taboa, yytext, id);
  else
    (*lexema)->id = id;
}

//Función que devolve o lexema dunha compoñente léxica
char* devolve_lexema(ref_lex c_lexica){
  return c_lexica->literal;
}
//Función que devolve o ID dunha compoñente léxica
int devolveID(ref_lex c_lexica){
  return c_lexica->id;
}
//Función que imprime ambos campos da compoñente léxica.
void imprime_lex(ref_lex c_lex){
  printf("< \"%s\": %d >\n", c_lex->literal, c_lex->id);
}

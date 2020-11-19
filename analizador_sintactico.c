#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "analizador_lexico.h"
#include "taboa_simbolos.h"

#include "definicions.h"

#define NUM_SIMBOLOS 11


int main(int argc, char** argv){
  ref_lex lexema=NULL;//array de lexemas
  ref_nodo taboa = NULL;//táboa de símbolos
  //Arrays de palabras reservadas da linguaxe e  valores
  char* simbolos[NUM_SIMBOLOS] = {"import", "enforce", "double", "int", "float", "void", "while", "foreach", "return", "sum", "writefln"};
  int valores[NUM_SIMBOLOS] = {IMPORT, ENFORCE, DOUBLE, INT, FLOAT, VOID, WHILE, FOREACH, RETURN, SUM,  WRITEFLN};
  int i, erro;


  //Insertamos os símbolos na táboa
  for(i=0;i<NUM_SIMBOLOS;i++){
    erro = inserta_nodo(&taboa, simbolos[i], valores[i]);
    if(erro != 0){
      printf("Erro ao crear a táboa de símbolos\n");
      return -1;
    }
  }
  //Imprimimos o contido da táboa de símbolos antes de iniciar a análise léxica
  printf("\n---------------------------- TÁBOA DE SÍMBOLOS ANTES DE EXECUTAR O ANALIZADOR LÉXICO ----------------------------\n\n");
  preorder(taboa);
  printf("\n-----------------------------------------------------------------------------------------------------------------\n\n");
  //Abrimos o ficheiro que se vai analizar.
  iniciaFich("regression.d");
  //reservamos memoria para a variable que conten o lexema
  lexema = (ref_lex)malloc(sizeof(ref_lex));
  crea_lex(&lexema);

  //Comezamos a análise do ficheiro
  indica_comp_lexica(&taboa, &lexema);
  while((devolveID(lexema))!=0){
      imprime_lex(lexema);//Para cada compoñente léxica imprimimos o contido e o identificador
      indica_comp_lexica(&taboa, &lexema);
  }
  //Imprimimos o contido da táboa de símbolos despois da análise
  printf("\n---------------------------- TÁBOA DE SÍMBOLOS DESPOIS DE EXECUTAR O ANALIZADOR LÉXICO ----------------------------\n\n");
  preorder(taboa);
  printf("\n-----------------------------------------------------------------------------------------------------------------\n");
  //Borramos o contido da táboa e liberamos a memoria da variable onde se almacenan os lexemas
  borrar_taboa(&taboa);
  borra_lex(&lexema);
  free(lexema);
  return 0;
}

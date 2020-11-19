#include <stdlib.h>
#include <stdio.h>
#include "definicions.h"


void num_malformado(int tipo_num, char* lexema, int linha){
  switch(tipo_num){
    case INT_MAL:
      printf("------------------------------------------------------------------------------------------------------------\n-->O enteiro %s da liña %d está mal formado. Contén caracter non aceptado.<--\n------------------------------------------------------------------------------------------------------------\n", lexema, linha);
      return;
    break;
    case FLOAT_MAL:
      printf("------------------------------------------------------------------------------------------------------------\n-->O flotante %s da liña %d está mal formado. Contén caracter non aceptado.<--\n------------------------------------------------------------------------------------------------------------\n", lexema, linha);
      return;
    break;
    case BIN_MAL:
      printf("------------------------------------------------------------------------------------------------------------\n-->O número binario %s da liña %d está mal formado. Contén caracter non aceptado.<--\n------------------------------------------------------------------------------------------------------------\n", lexema, linha);
      return;
    break;
  }
}

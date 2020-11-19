#include <stdlib.h>
#include <stdio.h>

typedef union dep{
  void* funcion;
  float valor;
} contidos;

typedef struct var{
  union dep contido;
  int codigo;
}nodo;

int main(int argc, char** argv){
  if(argc < 2){
    return -1;
  }
  int valor;
  nodo n;
  if((valor = atoi(argv[1]))==1){//creamos con punteiro a función
      printf("%p\n", &main);
      n.contido.funcion = &main;
      n.codigo = 1;
      printf("%p\n", n.contido.funcion);
  }else if(valor == 2){//creamos con real
    printf("%f\n", 23.5);
    n.contido.valor = 23.5;
    n.codigo = 3;
    printf("%f\n", n.contido.valor);
  }else{//erro
      return -1;
  }
}

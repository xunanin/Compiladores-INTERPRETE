#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "definicions.h"

//Estrutura dun nodo da táboa de símbolos
typedef struct n{
  char* lexema;
  int id;
  short int tipo;
  union d{
    void* func;
    float valor;
  } contido;
  struct n* esquerda;
  struct n* dereita;
  int peso;
}nodo_avl;

typedef nodo_avl* ref_nodo;
//Función para o cálculo do máximo entre dous valorese
int max(int a,int b){
  return (a > b)?a : b;
}
//Cálculo do peso dun nodo
int val_peso(ref_nodo nodo){
  if(nodo!=NULL){
    return nodo->peso;
  }
}

//Función que devolve o factor de equilibrio dun nodo dado
int equilibrio(ref_nodo n){
  if(n==NULL)
    return 0;
  return val_peso(n->esquerda)-val_peso(n->dereita);
}

////////////////////////////
int crea_nodo_funcion(ref_nodo* n, char* lex , int id, void* funcion){
  *nodo = (ref_nodo)malloc(sizeof(nodo_avl));

}
///////////////////////////

//Función para a creación dun nodo dados un lexema e o código dese lexema
int crea_nodo(ref_nodo* nodo, char* lex, int identificador){
  //Reservamos memoria para o nodo
  *nodo=(ref_nodo)malloc(sizeof(nodo_avl));
  //Comprobamos se se reservou correctamente a memoria
  if(*nodo==NULL){
    printf("Non se puido realizar a reserva de memoria para o nodo.\n");
    return 10;
  }
  //Reservamos memoria para o lexema do nodo
  (*nodo)->lexema=(char*)malloc(sizeof(lex));
  if((*nodo)->lexema==NULL){
    printf("Non se puido realizar a reserva de memoria para o lexema.\n");
    return 11;
  }
  //Copiamos o contido do lexema pasado no nodo
  strcpy((*nodo)->lexema, lex);
  //Completamos o resto de campos
  (*nodo)->id=identificador;
  (*nodo)->dereita=NULL;
  (*nodo)->esquerda=NULL;
  (*nodo)->peso=1;
  return 0;
}
//Función que imprime un nodo
void imprime_nodo(ref_nodo nodo){
  printf("%s: %d\n", nodo->lexema, nodo->id);
}

void destrue_nodo_beta(ref_nodo* nodo){
  free((*nodo)->lexema);
  free(*nodo);
  *nodo=NULL;
}

//Función que devolve o valor máis a esquerda dunha árbore
ref_nodo menor_valor(ref_nodo nodo){
  ref_nodo actual = nodo;devolve o lexema dunha compoñente léxica
  while(actual->esquerda != NULL)
    actual = actual->esquerda;
  return actual;
}

//Función que realiza unha inserción e a rotación á dereita desde un determinado nodo para equilibrar a árbore
int rotacion_dereita(ref_nodo* raiz){
  //Intercambio dos nodos
  ref_nodo x = (*raiz)->esquerda;
  ref_nodo z = x->dereita;
  ref_nodo aux = *raiz;
  x->dereita = aux;
  aux->esquerda = z;
  //Recalculamos os pesos
  aux->peso=max(val_peso(aux->esquerda), val_peso(aux->dereita))+1;
  x->peso=max(val_peso(x->esquerda), val_peso(x->dereita))+1;
  //Actualizamos o valor do nodo pasado
  *raiz=x;
  return 0;
}

//Función que realiza unha inserción e unha rotación cara a esquerda desde un determinado nodo
int rotacion_esquerda(ref_nodo* raiz){
  ref_nodo x = (*raiz)->dereita;
  ref_nodo z = x->esquerda;
  ref_nodo aux = *raiz;
  x->esquerda = aux;
  aux->dereita = z;
  x->peso=max(val_peso(x->esquerda), val_peso(x->dereita))+1;
  aux->peso=max(val_peso(aux->esquerda), val_peso(aux->dereita))+1;
  *raiz=x;
  return 0;
}

//Función para a inserción dun nodo na táboa de símbolos pasada a raíz.
int inserta_nodo(ref_nodo *nodo, char* lex, int codigo){
  //Se o nodo raíz non existe crearase dado o código e devolverase un código de que se completou sen problema
  if(nodo!=NULL&&(*nodo)==NULL){
    crea_nodo(nodo, lex, codigo);
    return 0;
  }
  //Se non é o nodo raíz miramos onde se debe insertar
  int compara=strcmp((*nodo)->lexema, lex);
  int _equilibrio, comp_d, comp_e;
  if(compara>0){//Se a clave é menor insertámolo como fillo esquerdo do nodo raíz
    inserta_nodo(&((*nodo)->esquerda), lex, codigo);
  }
  else if(compara<0){//En caso de ser maior insertarase como fillo dereito
    inserta_nodo(&((*nodo)->dereita), lex, codigo);
  }
  else//En caso de que estea insertado devolvemos 0
    return 0;
  //Recalculamos pesos
  (*nodo)->peso=1+max(val_peso((*nodo)->dereita), val_peso((*nodo)->esquerda));
  //Calculamos factor de equilibrio do nodo raíz.
  _equilibrio=equilibrio(*nodo);

  //Miramos onde se debe colocar o novo nodo
  if((*nodo)!=NULL&&(*nodo)->esquerda!=NULL)
    comp_e=strcmp(lex, (*nodo)->esquerda->lexema);//Comparamos o novo nodo co nodo á esquerda da raíz
  if((*nodo)->dereita!=NULL)
    comp_d=strcmp(lex, (*nodo)->dereita->lexema);//Comparamos o novo nodo co nodo á dereita da raíz

  //Se o equilibrio é maior que 1 e o nodo a insertar é menor que o elemento da esquerda do nodo facemos unha rotación cara a dereita
  if(_equilibrio > 1 && comp_e < 0){
    rotacion_dereita(nodo);
    return 0;
  }
  //Se o equilibrio é menor que -1 e o nodo a insertar é maior que o elemento da dereita do nodo facemos unha rotación cara a esquerda
  if(_equilibrio < -1 && comp_d > 0){
    rotacion_esquerda(nodo);
    return 0;
  }
  //Se o equilibrio é maior que 1 e o nodo a insertar é maior que o elemento da dereita do nodo facemos unha rotación cara a esquerda e outra cara a dereita
  if(_equilibrio > 1 && comp_e > 0){
    rotacion_esquerda(&((*nodo)->esquerda));
    rotacion_dereita(nodo);
    return 0;
  }
  //Se o equilibrio é menor que -1 e o nodo a insertar é menor que o elemento da dereita do nodo facemos unha rotación cara a dereita e outra cara a esquerda
  if(_equilibrio < -1 && comp_d < 0){
    rotacion_dereita(&((*nodo)->dereita));
    rotacion_esquerda(nodo);
    return 0;
  }
  return 0;
}
//Función para o borrado dun nodo dado o lexema
int borra_nodo(ref_nodo* nodo, char* lex){
  //Comprobamos que o nodo non estea baleiro
  if(*nodo==NULL)
    return 0;
  //Comparamos o lexema da raíz co elemento pasado
  int compara = strcmp((*nodo)->lexema, lex);

  if(compara > 0){//Se é menor que a raíz borramos o elemento da esquerda
    borra_nodo(&((*nodo)->esquerda), lex);
  }else if(compara < 0){//Se é maior que a raíz borramos o elemento da dereita
    borra_nodo(&((*nodo)->dereita), lex);
  }else{//En caso de ser o elemento
    //Comprobamos se é un nodo folla
    if(((*nodo)->esquerda == NULL) || ((*nodo)->dereita == NULL)){
      ref_nodo aux = (*nodo)->esquerda ? (*nodo)->esquerda: (*nodo)->dereita;
      if(aux == NULL){
        //Se é nodo folla eliminámolo
        aux = (*nodo);
        (*nodo) = NULL;
      }else//En caso contrario almacenamos o valor do nodo na raíz
        **nodo=*aux;
      free(aux);//Liberamos nodo
    }else{
      /*
        Se os dous nodos fillos están ocupados
        Colocamos na posición do nodo raíz o
        menor elemento situado á dereita deste
      */
      ref_nodo aux = menor_valor((*nodo)->dereita);
      (*nodo)->lexema = aux->lexema;
      borra_nodo(&((*nodo)->dereita), aux->lexema);//Borramos nodo
    }
  }
  // if(*nodo == NULL){
  //   return 0;
  // }

  //Recalculamos peso e factor de equilibrio da árbore resultante
  (*nodo)->peso = 1 + max(val_peso((*nodo)->esquerda), val_peso((*nodo)->dereita));
  int _equilibrio = equilibrio(*nodo);

  //Miramos as posibles rotacións do mesmo xeito que nas insercións
  if(_equilibrio > 1 && equilibrio((*nodo)->esquerda) >= 0){
    rotacion_dereita(nodo);
    return 0;
  }
  if(_equilibrio > 1 && equilibrio((*nodo)->esquerda) < 0){
    rotacion_esquerda(&((*nodo)->esquerda));
    rotacion_dereita(nodo);
    return 0;
  }
  if(_equilibrio < -1 && equilibrio((*nodo)->esquerda) <= 0){
    rotacion_esquerda(nodo);
    return 0;
  }
  if(_equilibrio < -1 && equilibrio((*nodo)->esquerda) > 0){
    rotacion_dereita(&((*nodo)->dereita));
    rotacion_esquerda(nodo);
    return 0;
  }
  return 0;
}

//Función que percorre a árbore e imprime todos os nodos
void preorder(ref_nodo n){
  if(n!=NULL){
    // if(strcmp(n->lexema,lex)==0)
    //   return n;
    printf("%s:%d\n", n->lexema, n->id);//Primeiro imprime o elemento raíz
    preorder(n->esquerda);//Despois vai imprimindo todos os elementos da árbore esquerda
    preorder(n->dereita);//Despois vai imprimindo todos os elementos da árbore dereita
  }
}

//Función que busca se un nodo se atopa na árbore. En caso contrario insértao.
int busca(ref_nodo* nodo, char* lex, int id){
  ref_nodo actual = *nodo;
  int compara, codigo;
  codigo=id;
  while(actual!=NULL){
    compara=strcmp(lex, actual->lexema);
    if(compara<0){//se o contido do nodo actual é maior que o lexema buscamos polo lado esquerdo
      // printf("%s é maior que a clave %s\n", actual->lexema, lex);
      return busca((ref_nodo*)(&(*nodo)->esquerda), lex, id);
    }else if(compara>0){
      // printf("%s é menor que a clave %s\n", actual->lexema, lex);
      return busca((ref_nodo*)(&(*nodo)->dereita), lex, id);
    }
    if(compara == 0){
      *nodo = actual;

      return actual->id;
    }
  }
  if(codigo==0){
    codigo = ID;
  }
  //Se o nodo non está no lexema insertámolo
  inserta_nodo(nodo, lex, codigo);
  return codigo;
}


void borrar_taboa(ref_nodo*  raiz){
  //Eliminamos lado esquerdo
  while((*raiz)->esquerda != NULL){
    ref_nodo aux = menor_valor((*raiz)->esquerda);//Obtemos o elemento máis á esquerda desde o fillo esquerdo da raíz
    if(aux->dereita == NULL){
      //Se non ten fillo dereito seguimos baixando polos fillos esquerdos
      borra_nodo(&(*raiz)->esquerda, aux->lexema);
    }else{
      //Se ten fillo dereito eliminamos primeiro os da dereita e despois os da esquerda
      borra_nodo(&(*raiz)->esquerda, (aux->dereita)->lexema);
      borra_nodo(&(*raiz)->esquerda, aux->lexema);
    }
  }
  //Eliminamos rama dereita da raíz
  while((*raiz)->dereita != NULL){
    ref_nodo aux = menor_valor((*raiz)->dereita);//Obtemos o elemento máis á esquerda desde o fillo dereito da raíz
    if(aux->dereita == NULL){
      //Se non ten fillo dereito seguimos baixando polos fillos esquerdos
      borra_nodo(&(*raiz)->dereita, aux->lexema);
    }else{
      //Se ten fillo dereito eliminamos primeiro os da dereita e despois os da esquerda
      borra_nodo(&(*raiz)->dereita, (aux->dereita)->lexema);
      borra_nodo(&(*raiz)->dereita, aux->lexema);
    }
  }
  //Eliminamos nodo raíz
  borra_nodo(raiz, (*raiz)->lexema);
}

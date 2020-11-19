typedef void* ref_nodo;

int inserta_nodo(ref_nodo *nodo, char* lex, int codigo);
int borra_nodo(ref_nodo* nodo, char* lex);
void preorder(ref_nodo n);
int busca(ref_nodo* nodo, char* lex, int id);
void borrar_taboa(ref_nodo*  raiz);

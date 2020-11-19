#include "taboa_simbolos.h"

typedef void* ref_lex;
void crea_lex(ref_lex* lexema);
void iniciaFich(char* nome);
void indica_comp_lexica(ref_nodo* taboa, ref_lex* lexema);
void imprime_lex(ref_lex lex);
char* devolve_lexema(ref_lex c_lexica);
int devolveID(ref_lex c_lexica);
void borra_lex(ref_lex* lexema);

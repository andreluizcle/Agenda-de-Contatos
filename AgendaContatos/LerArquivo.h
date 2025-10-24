#ifndef LERARQUIVO_H
#define LERARQUIVO_H

//
#include <EstruturaContato.h>

//
#define NOME_ARQUIVO "Contatos.txt"

//
void Executar(void (*Comando)(FILE*), const char* modo);

//
void Consultar(void (*Comando)(FILE*, Contato**), const char* modo, Contato** dados);

#endif
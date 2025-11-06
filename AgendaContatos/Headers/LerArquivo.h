#ifndef LERARQUIVO_H
#define LERARQUIVO_H

//
#include "EstruturaContato.h"

//
#define NOME_ARQUIVO "Contatos.bin"

//
void Executar(void (*Comando)(FILE*, Contato), const char* modo, Contato dados);
int Consultar(int (*Comando)(FILE*, Contato**), const char* modo, Contato** dados);

#endif
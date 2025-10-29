// Declaração de Header de Arquivo
#ifndef CONSULTARCONTATO_H
#define CONSULTARCONTATO_H

// Incluir Struct de Contato
#include "EstruturaContato.h"

// Headers dos Métodos do Arquivo
void ListarContatos(FILE* arquivo, Contato** dados);
void ListarContatosArquivo(Contato** dados);

#endif
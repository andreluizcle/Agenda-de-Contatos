// Declaração de Header de Arquivo
#ifndef CONSULTARCONTATO_H
#define CONSULTARCONTATO_H

// Incluir Struct de Contato
#include "EstruturaContato.h"

// Headers dos Métodos do Arquivo
int ListarContatos(FILE* arquivo, Contato** dados);
int ListarContatosArquivo(Contato** dados);
int UltimoCodigoContato();
extern int totalContatos;

#endif
// Declaração de Header de Arquivo
#ifndef CONSULTARCONTATO_H
#define CONSULTARCONTATO_H

// Incluir Struct de Contato
#include "EstruturaContato.h"

// Headers dos Métodos do Arquivo
int ListarContatos(FILE* arquivo, Contato** dados);
int ListarContatosArquivo(Contato** dados);
int ListarContatosFiltradoArquivo(Contato ** listaContatos, const char* filtro);

int ConsultarUltimoContato(FILE* arquivo, Contato** dados);
int ConsultarUltimoContatoArquivo(Contato** dados);

int ConsultarContatoSelecionado(FILE* arquivo, Contato** dados);
int ConsultarContatoSelecionadoArquivo(Contato** dados);

void OrdenarConsulta(Contato** listaContatos, int quantidadeContatos);
char* upperCase(const char* texto);

#endif
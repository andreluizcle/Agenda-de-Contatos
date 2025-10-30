#ifndef CADASTRARCONTATO_H
#define CADASTRARCONTATO_H

// Inclusão de arquivos externos
#include "../EstruturaContato.h"
#include "../LerArquivo.h" // -> Ele é incluído pois tem o nome do arquivo definido

//Headers dos métodos para cadastro
void CadastrarContato(FILE* arquivo, Contato novoContato);
void CadastrarContatoArquivo(Contato novoContato);

#endif
#ifndef CADASTRARCONTATO_H
#define CADASTRARCONTATO_H

// Inclusão da estrutura de contato
#include <../EstruturaContato.h>
#include <../LerArquivo.h>

//Headers do(s) método(s) para cadastro
void CadastrarContato(FILE *arquivo, Contato **contatosSalvos, Contato novoContato);
void CadastrarContato(Contato novoContato);

#endif
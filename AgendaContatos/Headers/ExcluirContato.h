#ifndef EXCLUIRCONTATO_H
#define EXCLUIRCONTATO_H

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "EstruturaContato.h"
#include "LerArquivo.h"
#include "CadastrarContato.h"
#include "ConsultarContato.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ExcluirContato(FILE* arquivo, Contato contatoexc);
void ExcluirContaatoArquivo(Contato contatoexc);

#endif
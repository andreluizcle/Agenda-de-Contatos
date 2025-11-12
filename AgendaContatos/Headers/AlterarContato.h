#ifndef ALTERARCONTATO_H
#define ALTERARCONTATO_H

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EstruturaContato.h"
#include "LerArquivo.h"
#include "CadastrarContato.h"
#include "ConsultarContato.h"

void AlterarContato(FILE* arquivo, Contato contatoalt);

#endif
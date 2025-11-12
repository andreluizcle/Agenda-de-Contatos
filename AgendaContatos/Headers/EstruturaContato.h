#ifndef ESTRUTURACONTATO_H
#define ESTRUTURACONTATO_H
#define tamanhoPadrao 50

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[tamanhoPadrao];
    char telefone[tamanhoPadrao];
    char email[tamanhoPadrao];
    char endereco[tamanhoPadrao];
    int ativo;
} Contato;

#endif
#ifndef ESTRUTURACONTATO_H
#define ESTRUTURACONTATO_H
#define tamanhoPadrao 50
#define tamanhoTelefone 12

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[tamanhoPadrao];
    char telefone[tamanhoTelefone];
    char email[tamanhoPadrao];
    char endereco[tamanhoPadrao];
    int ativo;
} Contato;

#endif
// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/CadastrarContato.h"

// Método de cadastro do contato no arquivo
void CadastrarContato(FILE* arquivo, Contato novoContato){
    Contato contato;
    int cadastrado = 0;
    // long é usado para trabalhar com valores em bytes (ponteiro de um arquivo, por exemplo)
    long posicaoAtual = 0;

    while(fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &contato.codigo, contato.nome, contato.telefone, contato.email, contato.endereco, &contato.ativo) != EOF){
        if(!(contato.ativo) && !(cadastrado)){
            // Move o ponteiro (em bytes) para o começo da linha em que ativo == 0
            fseek(arquivo, posicaoAtual, SEEK_SET);
            
            fprintf(arquivo, "%d|%s|%s|%s|%s|%d\n", novoContato.codigo, novoContato.nome, novoContato.telefone, novoContato.email, novoContato.endereco, novoContato.ativo);
            cadastrado = 1;
            break;
        }
        // Recebe a posição atual do ponteiro - vem depois do fprintf para que o ponteiro sempre esteja no começo da linha
        posicaoAtual = ftell(arquivo);
    }

    // Se não houver nenhum contato que foi excluído, não entrará na primeira condicional
    // necessitando, então, dessa
    if(!cadastrado)
        fprintf(arquivo, "%d|%s|%s|%s|%s|%d\n", novoContato.codigo, novoContato.nome, novoContato.telefone, novoContato.email, novoContato.endereco, novoContato.ativo);
}

// Método de cadastro a ser acessado pela interface
void CadastrarContatoArquivo(Contato novoContato){
    // Definição de valor base para o campo de controle de existência de contato
    novoContato.ativo = 1;

    // Preenchendo todas as strings até o tamanho máximo para que todos os contatos ocupem o mesmo espaço na memória
    while(strlen(novoContato.nome)<(tamanhoPadrao-1)){
        strcat(novoContato.nome, " ");
    }
    while(strlen(novoContato.telefone)<(tamanhoPadrao-1)){
        strcat(novoContato.telefone, " ");
    }
    while(strlen(novoContato.email)<(tamanhoPadrao-1)){
        strcat(novoContato.email, " ");
    }
    while(strlen(novoContato.endereco)<(tamanhoPadrao-1)){
        strcat(novoContato.endereco, " ");
    }

    // Acessar o método de cadastro
    void (*Comando)(FILE*, Contato) = CadastrarContato;
    Executar(Comando, "r+", novoContato);
}
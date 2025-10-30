// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "EstruturaContato.h"
#include "LerArquivo.h"
#include "CadastrarContato.h"

// Método de cadastro do contato no arquivo
/* 
    A ideia do método era encontrar a posição alfabética em que o novo contato
    deveria ser inserido e inserí-lo, porém isso tornou-se inviável por ser
    possível apenas com a criação de um arquivo temporário e um processo exten-
    so demais para ser descrito aqui.
    Portanto a função é implementada com a sobrescrita de um contato excluído
    ou com o registro normal (no fim do .txt) ;]
*/
void CadastrarContato(FILE* arquivo, Contato novoContato){
    Contato contato;
    int cadastrado = 0;

    while(fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", &contato.codigo, contato.nome, contato.telefone, contato.email, contato.endereco, &contato.ativo) != EOF){
        if(!(contato.ativo && cadastrado)){
            fprintf(arquivo, "%d|%s|%s|%s|%s|%d\n", novoContato.codigo, novoContato.nome, novoContato.telefone, novoContato.email, novoContato.endereco, novoContato.ativo);
            cadastrado = 1;
            break;
        }
    }

    if(!cadastrado)
        fprintf(arquivo, "%d|%s|%s|%s|%s|%d\n", novoContato.codigo, novoContato.nome, novoContato.telefone, novoContato.email, novoContato.endereco, novoContato.ativo);
}

// Método de cadastro a ser acessado pela interface
void CadastrarContatoArquivo(Contato novoContato){
    // Definição de valor base para o campo de controle de existência de contato
    novoContato.ativo = 1;

    // Acessar o método de cadastro
    void (*Comando)(FILE*, Contato) = CadastrarContato;
    Executar(Comando, "r+", novoContato);
}
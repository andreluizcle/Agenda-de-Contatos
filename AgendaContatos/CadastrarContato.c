// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/CadastrarContato.h"
#include "Headers/ConsultarContato.h"

// Método de cadastro do contato no arquivo
void CadastrarContato(FILE* arquivo, Contato novoContato){
    Contato contato;
    int cadastrado = 0;

    // Cadastrando o novo contato
    while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        if(!(contato.ativo) && !(cadastrado)){
            // Move o ponteiro (em bytes) para o começo da linha em que ativo == 0 p/ sobrescrita
            fseek(arquivo, -(long)sizeof(Contato), SEEK_CUR);
            
            fwrite(&novoContato, sizeof(Contato), 1, arquivo);
            cadastrado = 1;
            break;
        }
    }

    // Se não houver nenhum contato que foi excluído, não entrará na primeira condicional
    // necessitando, então, dessa
    if(!cadastrado){
        fseek(arquivo, 0, SEEK_END);
        fwrite(&novoContato, sizeof(Contato), 1, arquivo);
    }
}

// Método de cadastro a ser acessado pela interface
void CadastrarContatoArquivo(Contato novoContato){
    // Definição de valor base para o campo de controle de existência de contato
    novoContato.ativo = 1;

    // Definição do código do novo contato
    Contato* ultimoContato = (Contato*)malloc(sizeof(Contato));
    ConsultarUltimoContatoArquivo(&ultimoContato);
    novoContato.codigo = ultimoContato.codigo + 1;
    free(ultimoContato);

    // Acessar o método de cadastro
    void (*Comando)(FILE*, Contato) = CadastrarContato;
    Executar(Comando, "rb+", novoContato);
}
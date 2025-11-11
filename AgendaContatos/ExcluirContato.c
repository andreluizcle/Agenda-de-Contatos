// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/CadastrarContato.h"
#include "Headers/ConsultarContato.h"

void ExcluirContato(FILE* arquivo, Contato contatoexc) {
    Contato contato;

    // Excluindo o contato do arquivo
    fseek(arquivo, 0, SEEK_SET); // Retorna ao início do arquivo
    while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        if(contato.codigo == contatoexc.codigo) {
            contatoexc.codigo = 0;
            contatoexc.ativo = 0;
            contatoexc.nome[0] = '\0';
            contatoexc.telefone[0] = '\0';
            contatoexc.email[0] = '\0';
            contatoexc.endereco[0] = '\0';
            // Move o ponteiro (em bytes) para o começo da linha em que id == contatoexc.id p/ sobrescrita
            fseek(arquivo, -(long)sizeof(Contato), SEEK_CUR);
            fwrite(&contatoexc, sizeof(Contato), 1, arquivo);
            break;
        }
    }
}

void ExcluirContaatoArquivo(Contato contatoexc) {
    Executar(ExcluirContato, "r+b", contatoexc);

}
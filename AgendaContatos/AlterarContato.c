#include "Headers/AlterarContato.h"

void AlterarContato(FILE* arquivo, Contato contatoalt){
    Contato contato;

    // Alterando o contato no arquivo
    while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        if(contato.codigo == contatoalt.codigo) {
            // Move o ponteiro (em bytes) para o começo da linha em que id == contatoalt.id p/ sobrescrita
            fseek(arquivo, -(long)sizeof(Contato), SEEK_CUR);

            fwrite(&contatoalt, sizeof(Contato), 1, arquivo);
            break;
        }
    }
}

// Método de cadastro a ser acessado pela interface
void AlterarContatoArquivo(Contato contatoAlterar){
    // Definição de valor base para o campo de controle de existência de contato
    contatoAlterar.ativo = 1;

    // Acessar o método de cadastro
    void (*Comando)(FILE*, Contato) = AlterarContato;
    Executar(Comando, "rb+", contatoAlterar);
}
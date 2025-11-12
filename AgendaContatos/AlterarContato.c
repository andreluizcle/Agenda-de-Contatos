#include "Headers/AlterarContato.h"

void AlterarContato(FILE* arquivo, Contato contatoalt){
    Contato contato;

    // Alterando o contato no arquivo
    fseek(arquivo, 0, SEEK_SET); // Retorna ao início do arquivo
      while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        if(contato.codigo == contatoalt.codigo) {
            contato.codigo = contatoalt.codigo;
            contato.ativo = contatoalt.ativo;
            contato.nome[0] = contatoalt.nome[0];
            contato.telefone[0] = contatoalt.telefone[0];
            contato.email[0] = contatoalt.email[0];
            contato.endereco[0] = contatoalt.endereco[0];
            // Move o ponteiro (em bytes) para o começo da linha em que id == contatoalt.id p/ sobrescrita
            fseek(arquivo, -(long)sizeof(Contato), SEEK_CUR);
            fwrite(&contato, sizeof(Contato), 1, arquivo);
            break;
        }
    }
}
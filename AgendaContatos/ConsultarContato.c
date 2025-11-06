// Incluir Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluir Arquivos Externos
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/ConsultarContato.h"

// Métodos de Consulta de Contatos
int ListarContatos(FILE* arquivo, Contato** dados) {
    // Ler Cada Bloco do Arquivo
    int indice = 0;
    Contato contatoLido;
    
    while (fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
        // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
        *dados = (Contato*)realloc(*dados, (indice+1)*sizeof(Contato));
        
        // Guardar os Dados do Ponteiro no Vetor
        (*dados)[indice].codigo = contatoLido.codigo;
        strcpy((*dados)[indice].nome, contatoLido.nome);
        strcpy((*dados)[indice].telefone, contatoLido.telefone);
        strcpy((*dados)[indice].email, contatoLido.email);
        strcpy((*dados)[indice].endereco, contatoLido.endereco);
        (*dados)[indice].ativo = contatoLido.ativo;
        
        // Mudar Índice para Próxima Leitura
        indice++;
    }
    
    // Retornar Quantidade de Contatos
    return indice;
}

int ListarContatosArquivo(Contato** dados) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ListarContatos;
    int quantidadeContatos = Consultar(Comando, "rb", dados);

    // Retornar Quantidade de Contatos
    return quantidadeContatos;
}

int ConsultarUltimoContato(FILE* arquivo, Contato** dados) {
    // Ler Cada Bloco do Arquivo
    int ultimoCodigo = 0;
    Contato contatoLido;

    while(fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
        // Guardar os Dados Somente do Último Contato
        if(contatoLido.ativo && contatoLido.codigo > ultimoCodigo) {
            (*dados)[0].codigo = contatoLido.codigo;
            strcpy((*dados)[0].nome, contatoLido.nome);
            strcpy((*dados)[0].telefone, contatoLido.telefone);
            strcpy((*dados)[0].email, contatoLido.email);
            strcpy((*dados)[0].endereco, contatoLido.endereco);
            (*dados)[0].ativo = contatoLido.ativo;
        }
    }

    // Retornar Quantidade de Contatos
    return 1;
}

int ConsultarUltimoContatoArquivo(Contato** dados) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ConsultarUltimoContato;
    int ultimoCodigo = Consultar(Comando, "rb", dados);

    // Retornar Quantidade de Contatos
    return ultimoCodigo;
}
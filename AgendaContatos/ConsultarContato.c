// Incluir Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluir Arquivos Externos
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/ConsultarContato.h"

// Métodos de Consulta de Contatos
int ListarContatos(FILE* arquivo, Contato** listaContatos) {
    // Ler Cada Bloco do Arquivo
    int indice = 0;
    Contato contatoLido;
    
    while (fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
        if (contatoLido.ativo) {
            // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
            *listaContatos = (Contato*)realloc(*listaContatos, (indice+1)*sizeof(Contato));
            
            // Guardar os Dados do Contato Ativo no Vetor
            (*listaContatos)[indice].codigo = contatoLido.codigo;
            strcpy((*listaContatos)[indice].nome, contatoLido.nome);
            strcpy((*listaContatos)[indice].telefone, contatoLido.telefone);
            strcpy((*listaContatos)[indice].email, contatoLido.email);
            strcpy((*listaContatos)[indice].endereco, contatoLido.endereco);
            (*listaContatos)[indice].ativo = contatoLido.ativo;
            
            // Mudar Índice para Próxima Leitura
            indice++;
        }
    }
    
    // Retornar Quantidade de Contatos
    return indice;
}

int ListarContatosArquivo(Contato** listaContatos) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ListarContatos;
    int quantidadeContatos = Consultar(Comando, "rb", listaContatos);

    // Retornar Quantidade de Contatos
    return quantidadeContatos;
}

int ConsultarUltimoContato(FILE* arquivo, Contato** contato) {
    // Ler Cada Bloco do Arquivo
    int ultimoCodigo = 0;
    Contato contatoLido;

    while(fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
        // Guardar os Dados Somente do Último Contato
        if(contatoLido.ativo && contatoLido.codigo > ultimoCodigo) {
            (*contato)->codigo = contatoLido.codigo;
            strcpy((*contato)->nome, contatoLido.nome);
            strcpy((*contato)->telefone, contatoLido.telefone);
            strcpy((*contato)->email, contatoLido.email);
            strcpy((*contato)->endereco, contatoLido.endereco);
            (*contato)->ativo = contatoLido.ativo;
        }
    }

    // Retornar Quantidade de Contatos
    return 1;
}

int ConsultarUltimoContatoArquivo(Contato** contato) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ConsultarUltimoContato;
    int ultimoCodigo = Consultar(Comando, "rb", contato);

    // Retornar Quantidade de Contatos
    return ultimoCodigo;
}

// int ConsultarContatoSelecionado(FILE* arquivo, Contato** contato) {
//     // Ler Cada Bloco do Arquivo
//     int codigoContato = (*contato)[0].codigo;
//     Contato contatoLido;

//     while(fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
//         // Guardar os Dados Somente do Contato Escolhido
//         if(contatoLido.ativo && contatoLido.codigo > ultimoCodigo) {
//             (*contato)->codigo = contatoLido.codigo;
//             strcpy((*contato)->nome, contatoLido.nome);
//             strcpy((*contato)->telefone, contatoLido.telefone);
//             strcpy((*contato)->email, contatoLido.email);
//             strcpy((*contato)->endereco, contatoLido.endereco);
//             (*contato)->ativo = contatoLido.ativo;
//         }
//     }

//     // Retornar Quantidade de Contatos
//     return 1;
// }

// int ConsultarContatoSelecionadoArquivo(Contato** contato) {
//     // Rodar o Comando no Arquivo
//     int (*Comando)(FILE*, Contato**) = ConsultarContatoSelecionado;
//     int ultimoCodigo = Consultar(Comando, "rb", contato);

//     // Retornar Quantidade de Contatos
//     return ultimoCodigo;
// }
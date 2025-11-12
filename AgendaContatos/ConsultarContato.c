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

    OrdenarConsulta(listaContatos, indice);

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

int ListarContatosFiltradoArquivo(Contato** listaContatos, const char* filtro) {
    // Listar todos os contatos cadastrados (e ativos)
    int indice = 0;
    Contato* contatos = (Contato*)malloc(sizeof(Contato));
    int quantidadeContatos = ListarContatosArquivo(&contatos);

    // Percorrer por cada contato e verificar cada letra
    for (int i = 0; i < quantidadeContatos; i++) {
        int filtrado = 1;
        for (int j = 0; j < strlen(filtro); j++) {
            int diferenca = contatos[i].nome[j] - filtro[j];

            if (!(diferenca == 0 || (contatos[i].nome[j] < 95 && diferenca == -32) ||
            (contatos[i].nome[j] > 95 && diferenca == 32))) {
                filtrado = 0;
                break;
            }
        }

        // Após verificação, adicionar o contato a nova lista
        if (filtrado == 1) {
            // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
            *listaContatos = (Contato*)realloc(*listaContatos, (indice+1)*sizeof(Contato));
            
            // Guardar os Dados do Contato Filtrado no Vetor
            (*listaContatos)[indice].codigo = contatos[i].codigo;
            strcpy((*listaContatos)[indice].nome, contatos[i].nome);
            strcpy((*listaContatos)[indice].telefone, contatos[i].telefone);
            strcpy((*listaContatos)[indice].email, contatos[i].email);
            strcpy((*listaContatos)[indice].endereco, contatos[i].endereco);
            (*listaContatos)[indice].ativo = contatos[i].ativo;
            
            // Mudar Índice para Próxima Leitura
            indice++;
        }
    }

    OrdenarConsulta(listaContatos, indice);

    // Retornar Quantidade de Contatos
    return indice;
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
    int quantidadeContatos = Consultar(Comando, "rb", contato);

    // Retornar Quantidade de Contatos
    return quantidadeContatos;
}

int ConsultarContatoSelecionado(FILE* arquivo, Contato** contato) {
    // Ler Cada Bloco do Arquivo
    int codigoContato = (*contato)[0].codigo;
    Contato contatoLido;

    while(fread(&contatoLido, sizeof(Contato), 1, arquivo) > 0) {
        // Guardar os Dados Somente do Contato Escolhido
        if(contatoLido.ativo && contatoLido.codigo == codigoContato) {
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

int ConsultarContatoSelecionadoArquivo(Contato** contato) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ConsultarContatoSelecionado;
    int quantidadeContatos = Consultar(Comando, "rb", contato);

    // Retornar Quantidade de Contatos
    return quantidadeContatos;
}

// Método para ordenar a lista originada em uma consulta ao registro de contatos
// Recebe um ponteiro de ponteiro pois será usado dentro de métodos
// que manipulam tal tipo
void OrdenarConsulta(Contato** listaContatos, int quantidadeContatos){
    for(int i=0; i<quantidadeContatos-1; i++){
        for(int j=i+1; j<quantidadeContatos; j++){
            // Comparação para ordenação alfabética
            if(strcmp((*listaContatos)[j].nome, (*listaContatos)[i].nome) < 0){

                //Troca de posição entre contatos
                Contato contatoAuxiliar = (*listaContatos)[i];
                (*listaContatos)[i] = (*listaContatos)[j];
                (*listaContatos)[j] = contatoAuxiliar;
            }
        }
    }
}
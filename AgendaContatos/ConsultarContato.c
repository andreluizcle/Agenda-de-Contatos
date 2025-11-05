// Incluir Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluir Arquivos Externos
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/ConsultarContato.h"
int totalContatos = 0;
/*void ListarContatos(FILE* arquivo, Contato** dados) {
    // Ler o Arquivo e Guardar os Dados
    int indice = -1;
    do {
        // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
        indice++;
        int len = strlen((*dados)[indice].endereco); 
        (*dados)[indice].endereco[len - 2] = '\0'; 
        *dados = (Contato*)realloc(*dados, (indice+1)*sizeof(Contato));
    }
    while (fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", &(*dados)[indice].codigo, 
        (*dados)[indice].nome, (*dados)[indice].telefone, (*dados)[indice].email, 
        (*dados)[indice].endereco) != EOF);
}*/
void ListarContatos(FILE *arquivo, Contato **dados) {
    int indice = -1;
    totalContatos = 0; // zera antes de começar a contagem
    do {
        indice++;

        // Aumentar o tamanho do vetor de contatos
        *dados = (Contato *)realloc(*dados, (indice + 1) * sizeof(Contato));

        // Ler um contato do arquivo
        if (fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                   &(*dados)[indice].codigo,
                   (*dados)[indice].nome,
                   (*dados)[indice].telefone,
                   (*dados)[indice].email,
                   (*dados)[indice].endereco) == EOF) {
            break;
        }

        int len = strlen((*dados)[indice].endereco);
        if (len >= 2) {
            (*dados)[indice].endereco[len - 2] = '\0';
        }
        totalContatos++;
    } while (!feof(arquivo));
}

// Método para Listar Contatos no Arquivo
void ListarContatosArquivo(Contato** dados) {
    // Rodar o Comando no Arquivo
    void (*Comando)(FILE*, Contato**) = ListarContatos;
    Consultar(Comando, "r", dados);
}

// Método para verificar o maior código de contato já informado e retornar ele +1 (p/ o novo contato)
int UltimoCodigoContato(){
    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Ocorreu um erro ao abrir o arquivo!");
        return;
    }

    int ultimoCodigo = 0;
    Contato contato;

    while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        ultimoCodigo = contato.codigo > ultimoCodigo ? contato.codigo : ultimoCodigo;
    }

    fclose(arquivo);

    return ++ultimoCodigo;
}
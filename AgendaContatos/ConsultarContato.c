// Incluir Bibliotecas
#include <stdio.h>
#include <stdlib.h>

// Incluir Arquivos Externos
#include "EstruturaContato.h"
#include "ConsultarContato.h"
#include "LerArquivo.h"

// Comando para Listagem de Contatos
void ListarContatos(FILE* arquivo, Contato** dados) {
    // Ler o Arquivo e Guardar os Dados
    int indice = 0;
    while (fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", &(*dados)[indice].codigo, (*dados)[indice].nome, 
        (*dados)[indice].telefone, (*dados)[indice].email, (*dados)[indice].endereco) != EOF) {
            // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
            indice++;
            *dados = (Contato*)realloc(*dados, (indice+1)*sizeof(Contato));
        }
}

// Método para Listar Contatos no Arquivo
void ListarContatosArquivo(Contato** dados) {
    // Rodar o Comando no Arquivo
    void (*Comando)(FILE*, Contato**) = ListarContatos;
    Executar(Comando, "r", dados);
}
// Incluir Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Incluir Arquivos Externos
#include "Headers/EstruturaContato.h"
#include "Headers/LerArquivo.h"
#include "Headers/ConsultarContato.h"

// Método para Listar Contatos
int ListarContatos(FILE* arquivo, Contato** dados) {
    // Ler Cada Bloco do Arquivo
    int indice = 0, linhaLida = 0;
    Contato contatoLido;
    
    while ((linhaLida = fread(&contatoLido, sizeof(Contato), 1, arquivo)) > 0) {
        // Aumentar o Tamanho do Ponteiro para Guardar todos os Contatos
        *dados = (Contato*)realloc(*dados, (indice+1)*sizeof(Contato));
        
        // Guardar os Dados do Ponteiro no Vetor
        (*dados)[indice].codigo = contatoLido.codigo;
        strcpy((*dados)[indice].nome, contatoLido.nome);
        strcpy((*dados)[indice].telefone, contatoLido.telefone);
        strcpy((*dados)[indice].email, contatoLido.email);
        strcpy((*dados)[indice].endereco, contatoLido.endereco);
        (*dados)[indice].ativo = contatoLido.ativo;
        printf("%s\n", (*dados)[indice].nome);
        
        // Mudar Índice para Próxima Leitura
        indice++;
    }
    
    // Retornar Quantidade de Contatos
    return indice;
}

// Método para Listar Contatos no Arquivo
int ListarContatosArquivo(Contato** dados) {
    // Rodar o Comando no Arquivo
    int (*Comando)(FILE*, Contato**) = ListarContatos;
    int quantidadeContatos = Consultar(Comando, "r", dados);

    // Retornar Quantidade de Contatos
    return quantidadeContatos;
}

// Método para verificar o maior código de contato já informado e retornar ele +1 (p/ o novo contato)
int UltimoCodigoContato(){
    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");
    if (arquivo == NULL) {
        perror("Ocorreu um erro ao abrir o arquivo!");
        return 0;
    }

    int ultimoCodigo = 0;
    Contato contato;

    while(fread(&contato, sizeof(Contato), 1, arquivo) == 1){
        if(contato.ativo)
            ultimoCodigo = contato.codigo > ultimoCodigo ? contato.codigo : ultimoCodigo;
    }

    fclose(arquivo);

    return ++ultimoCodigo;
}
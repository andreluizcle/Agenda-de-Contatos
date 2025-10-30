// Inclusão de bibliotecas
#include <stdlib.h>
#include <stdio.h>

// Inclusão de arquivos externos (estruturas de funções, detalhes fundamentais etc)
#include "../EstruturaContato.h"
#include "../LerArquivo.h"
#include "CadastrarContato.h"

// Método de cadastro do contato no arquivo
/* 
    A ideia do método era encontrar a posição alfabética em que o novo contato
    deveria ser inserido. Porém, os métodos de inserção de dados em arquivo não
    criam um espaço extra, "empurrando" os bytes seguintes, quando se insere
    bytes no meio de um arquivo. Portanto faz-se necessário criar um arquivo
    temporário, efetuar a gravação de dados em ordem alfabética (incluindo o
    novo contato), excluir o arquivo original e renomear o novo arquivo ;)
*/
void CadastrarContato(FILE* arquivo, Contato novoContato){
    Contato contato;
    int inserido = 0;
    
    // Cria um arquivo temporário
    FILE *arquivoTemporario = fopen("temporario.txt", "w");
    
    // Retorna o poteiro pro começo do arquivo
    rewind(arquivo);

    // Escrita do arquivo temporário em ordem alfabética (incluindo o novo contato)
    while(fscanf(arquivo, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", &contato.codigo, contato.nome, 
        contato.telefone, contato.email, contato.endereco) != EOF){
            if(!inserido && strcmp(contato.nome, novoContato.nome)<=0){
                fprintf(temporario, "%d|%s|%s|%s|%s\n", novoContato.codigo, novoContato.nome,
                novoContato.telefone, novoContato.email, novoContato.endereco);
                inserido = 1;
            }
            
            fprintf(temporario, "%d|%s|%s|%s|%s\n", contato.codigo, contato.nome,
                contato.telefone, contato.email, contato.endereco);
    }
    
    if(!inserido){
        fprintf(temporario, "%d|%s|%s|%s|%s\n", novoContato.codigo, novoContato.nome,
                novoContato.telefone, novoContato.email, novoContato.endereco);
    }
    
    // TO DO: excluir o arquivo original e renomear o temporário
}

// Método de cadastro a ser acessado pela interface pública
void CadastrarContatoArquivo(Contato novoContato){
    // Acessar o método de cadastro
    void (*Comando)(FILE *referenciaArquivo, Contato contatoParaCadastro) = CadastrarContato;
    Executar(Comando, "r+", novoContato);
}
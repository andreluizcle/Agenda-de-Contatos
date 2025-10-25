#include <stdio.h>
#include <EstruturaContato.h>
#include <LerArquivo.h>

//
void Executar(void (*Comando)(FILE*, Contato**), const char* modo, Contato** dados)
{
    // Verificar se o Arquivo Existe
    FILE* arquivo = fopen(NOME_ARQUIVO, modo);
    if (arquivo == NULL) {
        perror("Ocorreu um erro ao abrir o arquivo!");
        return;
    }
    
    // Executar o Comando no Arquivo
    Comando(arquivo, dados);
    
    // Fechar Arquivo após Execução
    fclose(arquivo);
    return;
}
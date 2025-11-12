#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>

#include "Headers/EstruturaContato.h"
#include "Headers/ConsultarContato.h"
#include "Headers/CadastrarContato.h"
#include "Headers/AlterarContato.h"
#include "Headers/ExcluirContato.h"

// Lista global para os contatos
GtkWidget *list_box;

static void pesquisaClicada(GtkButton *button, gpointer user_data);
void SalvarResultados(GtkButton *button, gpointer user_data);
static void CriarContatoPopUp(GtkButton *button, gpointer user_data);
static void AtualizarContatoPopUp(GtkButton *button, gpointer user_data,char codigo[5], char nome[50], char telefone[50], char email[50], char endereco[50]);
static void Alterar(GtkButton *button, gpointer user_data);
static GtkWidget* criarLinhaContato(char codigo[5], char nome[50], char telefone[50], char email[50], char endereco[50]);
static void atualizarPesquisa(const char *query);
static void iniciarJanela(GtkApplication *app);
static void Excluir(GtkButton *button, gpointer user_data);

// Callback do botão de pesquisa
static void pesquisaClicada(GtkButton *button, gpointer user_data) {
    GtkEntry *entrada = GTK_ENTRY(user_data);
    const char *texto = gtk_entry_get_text(entrada);
    atualizarPesquisa(texto);
}

//Fazar alteracao de contato
void SalvarResultados(GtkButton *button, gpointer user_data) {
    GtkWidget **entrada = (GtkWidget **) user_data;

    //get_text retorna ponteiro para dentro do proprio Widget
    const char *nome = gtk_entry_get_text(GTK_ENTRY(entrada[0]));
    const char *telefone = gtk_entry_get_text(GTK_ENTRY(entrada[1]));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entrada[2]));
    const char *endereco = gtk_entry_get_text(GTK_ENTRY(entrada[3]));
    const char *codigo = gtk_entry_get_text(GTK_ENTRY(entrada[4]));

    Contato novoContato;
    strcpy(novoContato.nome, g_strdup(nome));
    strcpy(novoContato.telefone, g_strdup(telefone));
    strcpy(novoContato.email, g_strdup(email));
    strcpy(novoContato.endereco, g_strdup(endereco));
    novoContato.codigo = atoi(codigo);
    AlterarContatoArquivo(novoContato);

    GtkWidget *janelaAtual = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(janelaAtual);
    atualizarPesquisa("");
}

//Interface criar contato
static void CriarContatoPopUp(GtkButton *button, gpointer user_data) {
    GtkWidget *janelaAnterior = GTK_WIDGET(user_data);
    GtkWidget *CaixaDialogo,*grid;
    GtkWidget *inputNome, *inputTelefone, *labelNome, *labelTelefone, *labelEmail, *inputEmail, *labelEndereco, *inputEndereco, *botaoEnviar;

    CaixaDialogo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(CaixaDialogo), "Adicionar Contato");
    gtk_window_set_transient_for(GTK_WINDOW(CaixaDialogo), GTK_WINDOW(janelaAnterior));
    gtk_window_set_modal(GTK_WINDOW(CaixaDialogo), TRUE); //Bloquear Interação com a janela anterior
    gtk_window_set_default_size(GTK_WINDOW(CaixaDialogo), 250, 200);
    gtk_window_set_resizable(GTK_WINDOW(CaixaDialogo), FALSE);
    gtk_window_set_icon_from_file(GTK_WINDOW(CaixaDialogo), "icons/icon2.png", NULL);

    //Criar Caixa Vertical da tela
    GtkWidget *verticalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(verticalBox), 10);
    gtk_container_add(GTK_CONTAINER(CaixaDialogo), verticalBox);

    //Cada Item da vertical e uma caixa horizontal
    GtkWidget *horizontalBoxNome = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxNome), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxNome);

    GtkWidget *horizontalBoxTelefone = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxTelefone), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxTelefone);

    GtkWidget *horizontalBoxEmail = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxEmail), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxEmail);
    
    GtkWidget *horizontalBoxEndereco = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxEndereco), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxEndereco);

    labelNome = gtk_label_new("Nome:    ");
    labelTelefone = gtk_label_new("Telefone:");
    labelEmail = gtk_label_new("Email:   ");
    labelEndereco = gtk_label_new("Endereço:");
    inputNome = gtk_entry_new();
    inputTelefone = gtk_entry_new();
    inputEmail = gtk_entry_new();
    inputEndereco = gtk_entry_new();
    botaoEnviar = gtk_button_new_with_label("Enviar");

    //Alinhamentos
    gtk_widget_set_halign(labelNome, GTK_ALIGN_START);
    gtk_widget_set_halign(labelTelefone, GTK_ALIGN_START);
    gtk_widget_set_halign(labelEmail, GTK_ALIGN_START);
    gtk_widget_set_halign(labelEndereco, GTK_ALIGN_START);

    //Adicionar cada item nas caixas
    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), labelNome, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), inputNome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), labelTelefone, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), inputTelefone, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEmail), labelEmail, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEmail), inputEmail, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEndereco), labelEndereco, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEndereco), inputEndereco, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(verticalBox), botaoEnviar, TRUE, FALSE, 0);

    //Criar Dinamicamente com GTK para utilizar na SalvarResultados
    GtkWidget **entradas = g_new(GtkWidget *, 4); //criar array dinamico 4
    entradas[0] = inputNome;
    entradas[1] = inputTelefone;
    entradas[2] = inputEmail;
    entradas[3] = inputEndereco;

    g_signal_connect(botaoEnviar, "clicked", G_CALLBACK(SalvarResultados), entradas);
    gtk_widget_show_all(CaixaDialogo);
}

//Callback botao Alterar
static void Alterar(GtkButton *button, gpointer user_data){
    GtkWidget **entrada = (GtkWidget **) user_data;

    const char *nome = gtk_label_get_text(GTK_LABEL(entrada[0]));
    const char *telefone = gtk_label_get_text(GTK_LABEL(entrada[1]));
    const char *email = gtk_label_get_text(GTK_LABEL(entrada[2]));
    const char *endereco = gtk_label_get_text(GTK_LABEL(entrada[3]));
    const char *codigo = gtk_label_get_text(GTK_LABEL(entrada[4]));

    AtualizarContatoPopUp(NULL, NULL, g_strdup(codigo), g_strdup(nome), g_strdup(telefone), g_strdup(email), g_strdup(endereco));
}

//Interface Atualizar Contato
static void AtualizarContatoPopUp(GtkButton *button, gpointer user_data, char codigo[5], char nome[50], char telefone[50], char email[50], char endereco[50]){
    GtkWidget *janelaAnterior = GTK_WIDGET(user_data);
    GtkWidget *CaixaDialogo,*grid;
    GtkWidget *inputNome, *inputTelefone, *labelNome, *labelTelefone, *labelEmail, *inputEmail, *labelEndereco, *inputEndereco, *botaoEnviar, *cod;
    cod = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(cod), codigo);

    CaixaDialogo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(CaixaDialogo), "Atualizar Contato");
    gtk_window_set_transient_for(GTK_WINDOW(CaixaDialogo), GTK_WINDOW(janelaAnterior));
    gtk_window_set_modal(GTK_WINDOW(CaixaDialogo), TRUE); //Bloquear Interação com a janela anterior
    gtk_window_set_default_size(GTK_WINDOW(CaixaDialogo), 250, 200);
    gtk_window_set_resizable(GTK_WINDOW(CaixaDialogo), FALSE);
    gtk_window_set_icon_from_file(GTK_WINDOW(CaixaDialogo), "icons/icon2.png", NULL);

    //Caixa vertical da tela
    GtkWidget *verticalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(verticalBox), 10);
    gtk_container_add(GTK_CONTAINER(CaixaDialogo), verticalBox);

    //Cada item do vertical e um horizontal
    GtkWidget *horizontalBoxNome = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxNome), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxNome);

    GtkWidget *horizontalBoxTelefone = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxTelefone), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxTelefone);

    GtkWidget *horizontalBoxEmail = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxEmail), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxEmail);
    
    GtkWidget *horizontalBoxEndereco = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxEndereco), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxEndereco);

    labelNome = gtk_label_new("Nome:    ");
    labelTelefone = gtk_label_new("Telefone:");
    labelEmail = gtk_label_new("Email:   ");
    labelEndereco = gtk_label_new("Endereço:");
    inputNome = gtk_entry_new();
    inputTelefone = gtk_entry_new();
    inputEmail = gtk_entry_new();
    inputEndereco = gtk_entry_new();
    botaoEnviar = gtk_button_new_with_label("Enviar");

    //Colocar valores anteriores no input
    gtk_entry_set_text(GTK_ENTRY(inputNome), nome);
    gtk_entry_set_text(GTK_ENTRY(inputTelefone), telefone);
    gtk_entry_set_text(GTK_ENTRY(inputEmail), email);
    gtk_entry_set_text(GTK_ENTRY(inputEndereco), endereco);

    //alinhamento
    gtk_widget_set_halign(labelNome, GTK_ALIGN_START);
    gtk_widget_set_halign(labelTelefone, GTK_ALIGN_START);
    gtk_widget_set_halign(labelEmail, GTK_ALIGN_START);
    gtk_widget_set_halign(labelEndereco, GTK_ALIGN_START);

    //colocar itens na caixa
    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), labelNome, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), inputNome, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), labelTelefone, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), inputTelefone, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEmail), labelEmail, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEmail), inputEmail, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEndereco), labelEndereco, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxEndereco), inputEndereco, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(verticalBox), botaoEnviar, TRUE, FALSE, 0);

    //Criar Dinamicamente com GTK para utilizar na SalvarResultados
    GtkWidget **entradas = g_new(GtkWidget *, 5);
    entradas[0] = inputNome;
    entradas[1] = inputTelefone;
    entradas[2] = inputEmail;
    entradas[3] = inputEndereco;
    entradas[4] = cod;

    g_signal_connect(botaoEnviar, "clicked", G_CALLBACK(SalvarResultados), entradas);
    gtk_widget_show_all(CaixaDialogo);
}

//Excluir Contato
static void Excluir(GtkButton *button, gpointer user_data){
    Contato contato;
    contato.codigo = GPOINTER_TO_INT(user_data);
    ExcluirContaatoArquivo(contato);
    atualizarPesquisa("");
}

// Cria uma linha com o nome de um contato
static GtkWidget* criarLinhaContato(char codigo[5], char nome[50], char telefone[50], char email[50], char endereco[50]){
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
  GtkWidget *cod = gtk_label_new(codigo);
  GtkWidget *labelNome = gtk_label_new(nome);
  GtkWidget *labelTelefone = gtk_label_new(telefone);
  GtkWidget *labelEmail = gtk_label_new(email);
  GtkWidget *labelEndereco = gtk_label_new(endereco);
  GtkWidget *botaoAlterar = gtk_button_new_with_label("Alterar");
  GtkWidget *botaoExcluir = gtk_button_new_with_label("Excluir");
  GtkWidget **informacoes = g_new(GtkWidget*, 5); // aloca vetor de 5 ponteiros

  informacoes[4] = cod;
  informacoes[0] = labelNome;
  informacoes[1] = labelTelefone;
  informacoes[2] = labelEmail;
  informacoes[3] = labelEndereco;

  gtk_widget_set_halign(labelNome, GTK_ALIGN_CENTER);
  //Expand, Fill, Margin Expand->Crese se houver espaço, se estiver orientado vertical cresce vertical, Fill->Ocupa todo espaço que recebeu ou nao ocupa mas reserva
  gtk_box_pack_start(GTK_BOX(box), labelNome, TRUE, TRUE, 6); //Resize
  gtk_widget_set_size_request(labelNome, 200, -1); //Tamanho na tela

  gtk_widget_set_halign(labelTelefone, GTK_ALIGN_CENTER); //Alinhamento
  gtk_widget_set_size_request(labelTelefone, 200, -1); //Resize
  gtk_box_pack_start(GTK_BOX(box), labelTelefone, TRUE, TRUE, 6); //Tamanho na tela

  gtk_widget_set_halign(labelEmail, GTK_ALIGN_CENTER); //Alinhamento
  gtk_widget_set_size_request(labelEmail, 200, -1); //Resize
  gtk_box_pack_start(GTK_BOX(box), labelEmail, TRUE, TRUE, 6); //Tamanho na tela

  gtk_widget_set_halign(labelEndereco, GTK_ALIGN_CENTER); //Alinhamento
  gtk_widget_set_size_request(labelEndereco, 200, -1); //Resize
  gtk_box_pack_start(GTK_BOX(box), labelEndereco, TRUE, TRUE, 6); //Tamanho na tela

  g_signal_connect(botaoAlterar, "clicked", G_CALLBACK(Alterar), informacoes);
  // dar tamanho mínimo ao botão para garantir visibilidade
  gtk_widget_set_size_request(botaoAlterar, 80, -1); //Tamanho na tela
  gtk_widget_set_halign(botaoAlterar, GTK_ALIGN_END); //Alinhamento
  gtk_box_pack_start(GTK_BOX(box), botaoAlterar, TRUE, TRUE, 6); //Resize
  

  gtk_widget_set_halign(botaoExcluir, GTK_ALIGN_END); //Alinhamento
  g_signal_connect(botaoExcluir, "clicked", G_CALLBACK(Excluir), GINT_TO_POINTER(codigo));
  // dar tamanho mínimo ao botão para garantir visibilidade
  gtk_widget_set_size_request(botaoExcluir, 80, -1); //Tamanho na tela
  gtk_box_pack_start(GTK_BOX(box), botaoExcluir, TRUE, TRUE, 6); //Resize
  
  return box;
}

// Atualiza os resultados da pesquisa
static void atualizarPesquisa(const char *query) {
    GList *children, *iter;
    char cod[5];
    // Remove o conteúdo atual da lista
    children = gtk_container_get_children(GTK_CONTAINER(list_box));
    //Iter->next (Proximo No do Grafo)
    for (iter = children; iter != NULL; iter = iter->next)
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

    // Listar todos os contatos cadastrados (e ativos)
    Contato* dados = (Contato*)malloc(sizeof(Contato));
    int quantidadeContatos = 0;
    
    //query vazia = listar tudo
    if (strlen(query) == 0)
        quantidadeContatos = ListarContatosArquivo(&dados);
    else
        quantidadeContatos = ListarContatosFiltradoArquivo(&dados, query);

    for (int i = 0; i < quantidadeContatos; i++) {
        snprintf(cod, sizeof(cod), "%d", dados[i].codigo);
        GtkWidget *linha = criarLinhaContato(cod, dados[i].nome, dados[i].telefone, dados[i].email, dados[i].endereco);
        //-1 -> Final da lista (Parametro de posição)
        gtk_list_box_insert(GTK_LIST_BOX(list_box), linha, -1);
    }

    // Limpar memória da lista de contatos
    free(dados);
    gtk_widget_show_all(list_box);
}

// Cria e inicializa a janela principal
static void iniciarJanela(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Agenda de Contatos");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "icons/icon1.png", NULL);

    GtkWidget *verticalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(verticalBox), 10);
    gtk_container_add(GTK_CONTAINER(window), verticalBox);

    // Título
    GtkWidget *titulo = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(titulo), "<span font='20'><b>Agenda de Contatos</b></span>");
    gtk_widget_set_halign(titulo, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(verticalBox), titulo, FALSE, FALSE, 0);

    // Campo de entrada
    GtkWidget *input = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input), "Digite o nome ou telefone para pesquisar...");
    gtk_box_pack_start(GTK_BOX(verticalBox), input, FALSE, FALSE, 0);

    // Botão de pesquisa
    GtkWidget *botaoPesquisa = gtk_button_new_with_label("Pesquisar");
    gtk_box_pack_start(GTK_BOX(verticalBox), botaoPesquisa, FALSE, FALSE, 0);
    g_signal_connect(botaoPesquisa, "clicked", G_CALLBACK(pesquisaClicada), input);

    // Botão CriarContato
    GtkWidget *botaoCriarContato = gtk_button_new_with_label("Criar Contato");
    gtk_box_pack_start(GTK_BOX(verticalBox), botaoCriarContato, FALSE, FALSE, 0);
    g_signal_connect(botaoCriarContato, "clicked", G_CALLBACK(CriarContatoPopUp), NULL);

    // Área de lista rolável
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(verticalBox), scroll, TRUE, TRUE, 0);

    list_box = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(scroll), list_box);

    atualizarPesquisa("");  // Mostra todos inicialmente

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("br.com.andre.agendacontatos", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(iniciarJanela), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
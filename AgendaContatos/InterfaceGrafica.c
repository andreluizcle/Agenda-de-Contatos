#include <gtk/gtk.h>
#include <string.h>

#include "EstruturaContato.h"
#include "ConsultarContato.h"

// Lista global para os contatos
GtkWidget *list_box;

// Cria uma linha com o nome de um contato
static GtkWidget* criarLinhaContato(int codigo, char nome[50], char telefone[50], char email[50], char endereco[50]) {
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
  GtkWidget *labelNome = gtk_label_new(nome);
  GtkWidget *labelTelefone = gtk_label_new(telefone);
  GtkWidget *labelEmail = gtk_label_new(email);
  GtkWidget *labelEndereco = gtk_label_new(endereco);
  
  gtk_widget_set_halign(labelNome, GTK_ALIGN_START);
  //Expand, Fill, Margin Expand->Crese se houver espaço, se estiver orientado vertical cresce vertical, Fill->Ocupa todo espaço que recebeu ou nao ocupa mas reserva
  gtk_box_pack_start(GTK_BOX(box), labelNome, TRUE, TRUE, 0);

  gtk_widget_set_halign(labelTelefone, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(box), labelTelefone, TRUE, TRUE, 0);

  gtk_widget_set_halign(labelEmail, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(box), labelEmail, TRUE, TRUE, 0);

  gtk_widget_set_halign(labelEndereco, GTK_ALIGN_START);
  gtk_box_pack_start(GTK_BOX(box), labelEndereco, TRUE, TRUE, 0);

  return box;
}

// Atualiza os resultados da pesquisa
static void atualizarPesquisa(const char *query) {
    GList *children, *iter;

    // Remove o conteúdo atual da lista
    children = gtk_container_get_children(GTK_CONTAINER(list_box));
    //Iter->next (Proximo No do Grafo)
    for (iter = children; iter != NULL; iter = iter->next)
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

    // Simulação de resultados -> Chamar metodo que faz a busca aqui
    Contato* dados = (Contato*)malloc(sizeof(Contato));
    ListarContatosArquivo(&dados);
    // const char *Contatos[] = {"Contato 1", "Contato 2", "Contato 3", "Contato 4", NULL};
    // const char *Telefones[] = {"(11) 1111-1111", "(22) 1111-1111","(33) 1111-1111","(44) 1111-1111", NULL};

    for (int i = 0; dados[i].codigo != NULL; i++) {
        if (strstr(dados[i].nome, query) != NULL || strlen(query) == 0) {
            GtkWidget *linha = criarLinhaContato(dados[i].codigo, dados[i].nome, 
                dados[i].telefone, dados[i].email, dados[i].endereco);
            //-1 -> Final da lista (Parametro de posição)
            gtk_list_box_insert(GTK_LIST_BOX(list_box), linha, -1);
        }
    }

    gtk_widget_show_all(list_box);
}

// Callback do botão de pesquisa
static void pesquisaClicada(GtkButton *button, gpointer user_data) {
    GtkEntry *entrada = GTK_ENTRY(user_data);
    const char *texto = gtk_entry_get_text(entrada);
    atualizarPesquisa(texto);
}

void SalvarResultados(GtkButton *button, gpointer user_data) {
    GtkWidget **entrada = (GtkWidget **) user_data;

    //get_text retorna ponteiro para dentro do proprio Widget
    const char *nome = gtk_entry_get_text(GTK_ENTRY(entrada[0]));
    const char *telefone = gtk_entry_get_text(GTK_ENTRY(entrada[1]));

    char *dados[2];
    dados[0] = g_strdup(nome); //Copia 
    dados[1] = g_strdup(telefone);

    //Método para salvar dados aqui
    printf("Nome: %s\n", dados[0]);
    printf("Telefone: %s\n", dados[1]);

    g_free(dados[0]);
    g_free(dados[1]);
    g_free(entrada);

    GtkWidget *janelaAtual = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(janelaAtual);
    atualizarPesquisa("");
}

static void CriarContatoPopUp(GtkButton *button, gpointer user_data) {
    GtkWidget *janelaAnterior = GTK_WIDGET(user_data);
    GtkWidget *CaixaDialogo,*grid;
    GtkWidget *inputNome, *inputTelefone, *labelNome, *labelTelefone, *botaoEnviar;

    CaixaDialogo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(CaixaDialogo), "Adicionar Contato");
    gtk_window_set_transient_for(GTK_WINDOW(CaixaDialogo), GTK_WINDOW(janelaAnterior));
    gtk_window_set_modal(GTK_WINDOW(CaixaDialogo), TRUE); //Bloquear Interação com a janela anterior
    gtk_window_set_default_size(GTK_WINDOW(CaixaDialogo), 250, 150);
    gtk_window_set_resizable(GTK_WINDOW(CaixaDialogo), FALSE);
    gtk_window_set_icon_from_file(GTK_WINDOW(CaixaDialogo), "icons/icon2.png", NULL);

    GtkWidget *verticalBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(verticalBox), 10);
    gtk_container_add(GTK_CONTAINER(CaixaDialogo), verticalBox);

    GtkWidget *horizontalBoxNome = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxNome), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxNome);

    GtkWidget *horizontalBoxTelefone = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(horizontalBoxTelefone), 10);
    gtk_container_add(GTK_CONTAINER(verticalBox), horizontalBoxTelefone);

    labelNome = gtk_label_new("Nome:    ");
    labelTelefone = gtk_label_new("Telefone:");
    inputNome = gtk_entry_new();
    inputTelefone = gtk_entry_new();
    botaoEnviar = gtk_button_new_with_label("Enviar");

    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), labelNome, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxNome), inputNome, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), labelTelefone, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(horizontalBoxTelefone), inputTelefone, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(verticalBox), botaoEnviar, TRUE, FALSE, 0);

    //Criar Dinamicamente com GTK para utilizar na SalvarResultados
    GtkWidget **entradas = g_new(GtkWidget *, 2);
    entradas[0] = inputNome;
    entradas[1] = inputTelefone;

    g_signal_connect(botaoEnviar, "clicked", G_CALLBACK(SalvarResultados), entradas);
    gtk_widget_show_all(CaixaDialogo);
}

// Cria e inicializa a janela principal
static void iniciarJanela(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Agenda de Contatos");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
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

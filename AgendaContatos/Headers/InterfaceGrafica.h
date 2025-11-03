// Declaração de Header de Arquivo
#ifndef INTERFACEGRAFICA_H
#define INTERFACEGRAFICA_H

// Incluir Struct de Contato
#include "EstruturaContato.h"
#include <gtk/gtk.h>

static void pesquisaClicada(GtkButton *button, gpointer user_data);
void SalvarResultados(GtkButton *button, gpointer user_data);
static void CriarContatoPopUp(GtkButton *button, gpointer user_data);
static void AtualizarContatoPopUp(GtkButton *button, gpointer user_data, char nome[50], char telefone[50], char email[50], char endereco[50]);
static void Alterar(GtkButton *button, gpointer user_data);
static GtkWidget* criarLinhaContato(int codigo, char nome[50], char telefone[50], char email[50], char endereco[50]);
static void atualizarPesquisa(const char *query);
static void iniciarJanela(GtkApplication *app);
static void Excluir(GtkButton *button, gpointer user_data);

#endif
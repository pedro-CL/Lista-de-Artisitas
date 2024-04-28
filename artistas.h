#ifndef ARTISTAS_H
#define ARTISTAS_H

#define MAX 1000

typedef struct Artista Artista;

typedef struct ListaArtistas ListaArtistas;

void iniciarArtista(ListaArtistas *lista);
void listarArtista(ListaArtistas *lista);
void inserirArtista(ListaArtistas *lista,  Artista *artista);
void adicionarArtista(ListaArtistas *lista,  Artista *artista);
void editarArtista(ListaArtistas *lista, int posicao,  Artista *novoArtista);
int buscaBinaria(ListaArtistas *lista, char *nome);
int buscaSequencial(ListaArtistas *lista, char *album);
void removerArtista(ListaArtistas *lista, char *nome);
int compararArtistas( void *a,  void *b);
int menu(void);

#endif


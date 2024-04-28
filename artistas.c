#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "artistas.h"

#define MAX 1000

typedef struct Artista{
    char nome[MAX];
    char genero[MAX];
    char local[MAX];
    char albuns[MAX];
}Artista;

typedef struct ListaArtistas{
    Artista *artistas;
    int numArtistas;
}ListaArtistas;

void iniciarArtista(ListaArtistas *lista){
    lista->numArtistas = 0;
    lista->artistas = NULL;   
}

void listarArtista(ListaArtistas *lista){   
    sleep(2);
    for (int i = 0; i < lista->numArtistas; i++){
        printf("\n=========================================\n");
        printf("Nome: %s\n", lista->artistas[i].nome);
        printf("Genero Musical: %s\n", lista->artistas[i].genero);
        printf("Local de Nascimento: %s\n", lista->artistas[i].local);
        printf("Albuns:\n%s\n", lista->artistas[i].albuns);
        printf("=========================================\n");
        sleep(1);
    }
    sleep(1);
}

void inserirArtista(ListaArtistas *lista,  Artista *artista){
    FILE *arquivo = fopen("artistas.txt", "a");

    if (arquivo == NULL){
        printf("\n                      ********************************");
        printf("\n                      **** Erro ao abrir o arquivo ***");
        printf("\n                      ********************************\n\n");
        sleep(3);
        system("cls");
        exit(1);
    }

    fprintf(arquivo, "%s\n%s\n%s\n", artista->nome, artista->genero, artista->local);

    char albuns[MAX];
    printf("\nQuantos albuns deseja adicionar: ");
    int numAlbuns;
    scanf("%d", &numAlbuns);
    for (int j = 0; j < numAlbuns; j++){
        printf("    Album %d: ", j + 1);
        fgets(albuns, MAX, stdin);
        albuns[strcspn(albuns, "\n")] = '\0';
        fprintf(arquivo, "%s\n", albuns);
    }

    fprintf(arquivo, "==========\n");

    fclose(arquivo);

    lista->numArtistas++;
    lista->artistas = (Artista *)realloc(lista->artistas, lista->numArtistas * sizeof(Artista));

    lista->artistas[lista->numArtistas - 1] = *artista;
}

void adicionarArtista(ListaArtistas *lista,  Artista *artista){
    lista->numArtistas++;

    lista->artistas = (Artista *)realloc(lista->artistas, lista->numArtistas * sizeof(Artista));

    if(lista->artistas == NULL){
        printf("*** Erro ao adicionar artista ***\n");
        exit(1);
    }
    lista->artistas[lista->numArtistas - 1] = *artista;
}

void editarArtista(ListaArtistas *lista, int posicao,  Artista *novoArtista){
    if (posicao < 0 || posicao >= lista->numArtistas){
        printf("\n                      ********************************");
        printf("\n                      ******* Posicao invalida *******");
        printf("\n                      ********************************\n\n");
        sleep(3);
        system("cls");
        exit(1);
    }

    strcpy(lista->artistas[posicao].nome, novoArtista->nome);
    strcpy(lista->artistas[posicao].genero, novoArtista->genero);
    strcpy(lista->artistas[posicao].local, novoArtista->local);

    FILE *arquivo = fopen("artistas.txt", "w");
    if (arquivo == NULL){
        printf("\n*** Erro ao abrir arquivo para edicao de artista. ***\n");
        exit(1);
    }

    for (int i = 0; i < lista->numArtistas; i++){
        fprintf(arquivo, "\n%s\n",lista->artistas[i].nome);
            fprintf(arquivo, "%s\n", lista->artistas[i].genero);
            fprintf(arquivo, "%s\n",lista->artistas[i].local);
            fprintf(arquivo, "%s\n",lista->artistas[i].albuns);
            fprintf(arquivo, "==========");
    }
    fclose(arquivo);
}


int buscaBinaria(ListaArtistas *lista, char *nome){
    int esquerda = 0;
    int direita = lista->numArtistas - 1;

    while (esquerda <= direita){
        int meio = esquerda + (direita - esquerda) / 2;
        int cmp = strcmp(lista->artistas[meio].nome, nome);

        if (cmp == 0){
            return meio;
        }
        else if (cmp < 0){
            esquerda = meio + 1;
        }
        else{
            direita = meio - 1;
        }
    }

    return -1;
}

int buscaSequencial(ListaArtistas *lista, char *album){
    for (int i = 0; i < lista->numArtistas; i++){
        if (strstr(lista->artistas[i].albuns, album) != NULL){
            return i;
        }
    }
    return -1;
}

void removerArtista(ListaArtistas *lista, char *nome){
    int posicao = buscaBinaria(lista, nome);

    if (posicao == -1){
        printf("\n                      ********************************");
        printf("\n                      **** Artista nao encontrado ****");
        printf("\n                      ********************************\n\n");
        sleep(3);
        system("cls");
        exit(1);
    }

    FILE *arquivo = fopen("artistas.txt", "w");
    if (arquivo == NULL){
        printf("*** Erro ao abrir arquivo para remocao de artista. ***\n");
        exit(1);
    }

    for (int i = 0; i < lista->numArtistas; i++){
        if (i != posicao){
            fprintf(arquivo, "\n%s\n",lista->artistas[i].nome);
            fprintf(arquivo, "%s\n", lista->artistas[i].genero);
            fprintf(arquivo, "%s\n",lista->artistas[i].local);
            fprintf(arquivo, "%s\n",lista->artistas[i].albuns);
            fprintf(arquivo, "==========");
        }
    }

    fclose(arquivo);

    for (int i = posicao; i < lista->numArtistas - 1; i++){
        lista->artistas[i] = lista->artistas[i + 1];
    }

    lista->numArtistas--;
    lista->artistas = (Artista *)realloc(lista->artistas, lista->numArtistas * sizeof(Artista));
    if (lista->numArtistas == 0){
        free(lista->artistas);
        lista->artistas = NULL;
    }
    system("cls");
    printf("\nMENSAGEM: Artista \"%s\" removido com sucesso!\n", nome);
}

int compararArtistas( void *a,  void *b){
    const Artista *artistaA = (const Artista *)a;
    const Artista *artistaB = (const Artista *)b;
    return strcmp(artistaA->nome, artistaB->nome);
}

int menu(void){
    ListaArtistas lista;
    iniciarArtista(&lista);

    FILE *arquivo = fopen("artistas.txt", "r");

    if (arquivo == NULL){
        printf("\n  *********************************\n");
        printf("\n  **** Erro ao abrir o arquivo ****\n");
        printf("\n  *********************************\n");
        exit(1);
    }

    char linhaTexto[100];
    Artista artista;
    int contador = 0;

    while (fgets(linhaTexto, 100, arquivo)){
        linhaTexto[strcspn(linhaTexto, "\n")] = '\0';

        if (strcmp(linhaTexto, "==========") == 0){
            if (contador >= 4){
                adicionarArtista(&lista, &artista);
            }
            contador = 0;
        }
        else{
            switch (contador){
                case 0:
                    strcpy(artista.nome, linhaTexto);
                    break;
                case 1:
                    strcpy(artista.genero, linhaTexto);
                    break;
                case 2:
                    strcpy(artista.local, linhaTexto);
                    break;
                case 3:
                    strcpy(artista.albuns, linhaTexto);
                    break;
                default:
                    strcat(artista.albuns, "\n");
                    strcat(artista.albuns, linhaTexto);
                    break;
            }
            contador++;
        }
    }
    fclose(arquivo);

    printf("\nAnalisando a Lista, por favor aguarde");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    system("cls");

    printf("---------------------- Lista dos Artistas ----------------------\n");

    qsort(lista.artistas, lista.numArtistas, sizeof(Artista), compararArtistas);

    listarArtista(&lista);
    printf("----------------------------------------------------------------\n");
    printf("\nPreparando o menu, por favor aguarde");

    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");
    system("cls");

    int opcao;
    int posicao;
    char novoNome[50];
    char novoGenero[50];
    char novoLocal[100];
    char buscarnome[50];
    char busrcarAlbum[100];
    int resultadoBusca;
    

    do{
        system("cls");
        printf("\n        ========================= Menu =========================\n");
        printf("          1. Insercao ordenada (por nome) de novos artistas\n");
        printf("          2. Remocao de um artista\n");
        printf("          3. Edicao de um artista\n");
        printf("          4. Busca binaria por um artista\n");
        printf("          5. Busca sequencial por um album.\n");
        printf("          6. Sair\n");
        printf("        ========================================================\n\n");
        sleep(1);
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                system("cls");
                printf("\n\nNome do artista: ");
                fflush(stdin);
                fgets(artista.nome, sizeof(artista.nome), stdin);
                artista.nome[strcspn(artista.nome, "\n")] = '\0';

                printf("Genero musical: ");
                fgets(artista.genero, sizeof(artista.genero), stdin);
                artista.genero[strcspn(artista.genero, "\n")] = '\0';

                printf("Local de nascimento: ");
                fgets(artista.local, sizeof(artista.local), stdin);
                artista.local[strcspn(artista.local, "\n")] = '\0';

                inserirArtista(&lista, &artista);

                printf("\n\nAdicionando artista %s, por favor aguarde", artista.nome);
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");

                system("cls");
                printf("\nArtista adicionado com sucesso!\n");
                break;
            case 2:
                system("cls");
                printf("\n\nNome do artista que deseja remover: ");
                fflush(stdin);
                fgets(buscarnome, sizeof(buscarnome), stdin);
                buscarnome[strcspn(buscarnome, "\n")] = '\0';

                removerArtista(&lista, buscarnome);
                break;
            case 3:
                system("cls");
                printf("\n\nNome do artista que deseja ser editado: ");
                fflush(stdin);
                fgets(buscarnome, sizeof(buscarnome), stdin);
                buscarnome[strcspn(buscarnome, "\n")] = '\0';

                posicao = buscaBinaria(&lista, buscarnome);

                if(posicao != -1){
                    system("cls");
                    printf("----- Artista: %s ----- \n", buscarnome);

                    printf("\n    Novo nome: ");
                    fgets(novoNome, sizeof(novoNome), stdin);
                    novoNome[strcspn(novoNome, "\n")] = '\0';

                    printf("    genero musical: ");
                    fgets(novoGenero, sizeof(novoGenero), stdin);
                    novoGenero[strcspn(novoGenero, "\n")] = '\0';

                    printf("    local de nascimento: ");
                    fgets(novoLocal, sizeof(novoLocal), stdin);
                    novoLocal[strcspn(novoLocal, "\n")] = '\0';
                    
                    printf("----------------------- \n");

                    strcpy(artista.nome, novoNome);
                    strcpy(artista.genero, novoGenero);
                    strcpy(artista.local, novoLocal);

                    editarArtista(&lista, posicao, &artista);

                    printf("\nEditando artista %s, por favor aguarde", buscarnome);
                    sleep(1);
                    printf(".");
                    sleep(1);
                    printf(".");
                    sleep(1);
                    printf(".");
                    sleep(1);
                    printf(".");
                    sleep(1);
                    printf(".");

                    system("cls");
                    printf("\nMENSAGEM: Artista editado com sucesso!\n");
                    sleep(2);
                    system("cls");
                }
                else{
                    printf("\n                      ********************************");
                    printf("\n                      **** Artista nao encontrado ****");
                    printf("\n                      ********************************\n\n");
                    sleep(2);
                    system("cls");
                }
                break;
            case 4:
                system("cls");
                printf("\n\nQual nome do artista que deseja encontrar: ");
                fflush(stdin);
                fgets(buscarnome, sizeof(buscarnome), stdin);
                buscarnome[strcspn(buscarnome, "\n")] = '\0';

                posicao = buscaBinaria(&lista, buscarnome);

                if(posicao != -1){   
                    system("cls");
                    printf("\n---- Artista encontrado ----\n\n");
                    printf("Nome: %s\n", lista.artistas[posicao].nome);
                    printf("Genero Musical: %s\n", lista.artistas[posicao].genero);
                    printf("Local de Nascimento: %s\n", lista.artistas[posicao].local);
                    printf("Albuns:\n%s\n", lista.artistas[posicao].albuns);
                    printf("\n----------------------------\n\n");
                    sleep(3);
                }
                else{
                    printf("\n                      ********************************");
                    printf("\n                      **** Artista nao encontrado ****");
                    printf("\n                      ********************************\n\n");
                    sleep(3);
                    system("cls");
                }
                break;

            case 5:
                system("cls");
                printf("\n\nQual nome do album que deseja encontrar: ");
                fflush(stdin);
                fgets(busrcarAlbum, sizeof(busrcarAlbum), stdin);
                busrcarAlbum[strcspn(busrcarAlbum, "\n")] = '\0';

                resultadoBusca = buscaSequencial(&lista, busrcarAlbum);

                if(resultadoBusca != -1){   
                    system("cls");
                    printf("\n---- Album encontrado ----\n");
                    printf("Nome: %s\n", lista.artistas[resultadoBusca].nome);
                    printf("Albuns:\n%s\n", lista.artistas[resultadoBusca].albuns);
                    printf("\n--------------------------\n");
                    sleep(2);
                }
                else{
                    printf("\n                      ********************************");
                    printf("\n                      ***** Album nao encontrado *****");
                    printf("\n                      ********************************\n\n");
                    sleep(3);
                    system("cls");
                }
                break;
            case 6:
                system("cls");
                printf("\nSaindo");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                sleep(1);
                printf(".");
                system("cls");
                break;
            default:
                printf("\n**** Opcao invalida.Tente novamente ***\n");
                sleep(1);
                break;
        }
    } while (opcao != 6);
}

int main(){
    menu();
    return 0;
}

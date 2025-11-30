#include "lista_encadeada.h"
#include "ec_rgb_colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h> 

void delay_ms(unsigned int ms);

/* Estruturas internas */
struct No
{
    struct Estudante estudante;
    struct No *proximo;
    struct No *anterior; // ponteiro para o no anterior (lista dupla)
};

struct ListaEnc
{
    struct No *cabeca;       
    struct No *final;        // guardo o ultimo para inserir rapido no fim
    unsigned int quantidade; 
};

//  Cabeçalhos (protótipos) de todas as funções privadas 
static struct Estudante le_criaEstudante(void);
static struct Estudante le_LeEstudante(void);
static void le_ImprimeEstudante(struct Estudante e);
static struct Estudante le_GetEstudante(int i);
static int le_ListaNaoInicializada(struct ListaEnc *lista);
int le_InsereListaInicio2(struct ListaEnc *lista, struct Estudante e);
int le_InsereListaFim2(struct ListaEnc *lista, struct Estudante e);
int le_InsereListaOrdenada2(struct ListaEnc *lista, struct Estudante e);
// Declarei aqui para nao dar erro no main se esquecer de por no .h
void le_EnderecosNos(struct ListaEnc *lista); 

// Funções Públicas
struct ListaEnc *le_CriaLista(void);
void le_DestroiLista(struct ListaEnc **lista);
void le_InsereTestes(struct ListaEnc *lista);
int le_ListaVazia(struct ListaEnc *lista);
int le_ListaCheia(struct ListaEnc *lista);
int le_TamanhoLista(struct ListaEnc *lista, int imprime);
int le_RemoveTodos(struct ListaEnc *lista, int exige_confirmacao);
int le_InsereListaInicio(struct ListaEnc *lista);
int le_InsereListaFim(struct ListaEnc *lista);
int le_InsereListaOrdenada(struct ListaEnc *lista);
void le_EstudantesArquivo(struct ListaEnc *lista);
void le_ImprimeLista(struct ListaEnc *lista);
struct Estudante le_BuscaChave(struct ListaEnc *lista, char *chave);
struct Estudante le_RemoveChave(struct ListaEnc *lista, char *chave);
// Funcao nova para buscar e imprimir para tras
void le_BuscaImprimeRetroativo(struct ListaEnc *lista, char *chave, int n);


/* IMPLEMENTAÇÃO */

static struct Estudante le_criaEstudante()
{
    struct Estudante e = {0, 0, ""};
    return e;
}

static struct Estudante le_LeEstudante()
{
    struct Estudante e = le_criaEstudante();

    printf("ID: ");
    scanf("%d", &e.ID);
    getchar();
    if (e.ID == 0) return e;
    
    printf("Nota: ");
    scanf("%f", &e.nota);
    
    printf("Nome: ");
    getchar(); 
    scanf("%[^\n]", e.nome);

    return e;
}

static void le_ImprimeEstudante(struct Estudante e)
{
    printf("ID: %d\tNota: %4.2f\tNome: %s\n", e.ID, e.nota, e.nome);
}

static struct Estudante le_GetEstudante(int i)
{
    // dados fixos apenas para teste
    struct Estudante e;
    if (i == 0) { e.ID = 10; e.nota = 9.0; strcpy(e.nome, "Alan Turing"); }
    else if (i == 1) { e.ID = 20; e.nota = 9.7; strcpy(e.nome, "Ada Lovelace"); }
    else if (i == 2) { e.ID = 30; e.nota = 9.9; strcpy(e.nome, "Grace Hopper"); }
    else { e = le_criaEstudante(); }
    return e;
}

void le_InsereTestes(struct ListaEnc *lista)
{
    struct Estudante e;
    printf("Inserindo estudantes de Teste...\n");
    for (int i = 0; i < 3; i++)
    {
        e = le_GetEstudante(i);
        le_InsereListaFim2(lista, e); // uso a insercao no fim
    }
}

struct ListaEnc *le_CriaLista()
{
    // aloca a lista e inicializa tudo como null
    struct ListaEnc *lista = (struct ListaEnc *)malloc(sizeof(struct ListaEnc));
    if (lista == NULL)
    {
        printf("Erro: sem memoria para criar a lista\n");
        return NULL;
    }
    lista->cabeca = NULL;
    lista->final = NULL; // importante zerar o final tambem
    lista->quantidade = 0;
    return lista;
}

static int le_ListaNaoInicializada(struct ListaEnc *lista)
{
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 1;
    }
    return 0;
}

int le_TamanhoLista(struct ListaEnc *lista, int imprime)
{
    if (le_ListaNaoInicializada(lista)) return -1;
    if (imprime)
    {
        printf("Quantidade de elementos: %u\n", lista->quantidade);
    }
    return (int)lista->quantidade;
}

int le_ListaVazia(struct ListaEnc *lista)
{
    if (lista == NULL) return 1;
    if (lista->quantidade == 0)
    {
        printf("Lista vazia\n");
        return 1;
    }
    return 0;
}

int le_ListaCheia(struct ListaEnc *lista)
{
    (void)lista;
    return 0; 
}

// Insercao no inicio adaptada para lista dupla
int le_InsereListaInicio2(struct ListaEnc *lista, struct Estudante e)
{
    if (lista == NULL) return 0;
    
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL) return 0;
    
    novo->estudante = e;
    novo->proximo = lista->cabeca;
    novo->anterior = NULL; // nao tem ninguem antes do primeiro

    if (lista->cabeca != NULL)
    {
        lista->cabeca->anterior = novo; // o antigo primeiro aponta pra tras (novo)
    }
    else
    {
        // se a lista tava vazia, o novo tambem eh o ultimo
        lista->final = novo;
    }
    
    lista->cabeca = novo;
    lista->quantidade++;
    return 1;
}

int le_InsereListaInicio(struct ListaEnc *lista)
{
    struct Estudante e = le_LeEstudante();
    if (e.ID == 0) return 0;
    return le_InsereListaInicio2(lista, e);
}

// Insercao no fim rapida (usando o ponteiro final)
int le_InsereListaFim2(struct ListaEnc *lista, struct Estudante e)
{
    if (lista == NULL) return 0;

    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL) return 0;

    novo->estudante = e;
    novo->proximo = NULL; // vai ser o ultimo, entao proximo eh null
    
    if (lista->cabeca == NULL)
    {
        // lista vazia, insere igual no inicio
        novo->anterior = NULL;
        lista->cabeca = novo;
        lista->final = novo;
    }
    else
    {
        // insere direto no fim sem percorrer a lista toda
        novo->anterior = lista->final;
        lista->final->proximo = novo;
        lista->final = novo; // atualiza o ponteiro final
    }

    lista->quantidade++;
    return 1;
}

int le_InsereListaFim(struct ListaEnc *lista)
{
    struct Estudante e = le_LeEstudante();
    if (e.ID == 0) return 0;
    return le_InsereListaFim2(lista, e);
}

// Insercao ordenada na lista dupla
int le_InsereListaOrdenada2(struct ListaEnc *lista, struct Estudante e)
{
    if (lista == NULL) return 0;

    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL) return 0;
    novo->estudante = e;

    // se for inserir no comeco (ou lista vazia)
    if (lista->cabeca == NULL || e.ID < lista->cabeca->estudante.ID)
    {
        novo->proximo = lista->cabeca;
        novo->anterior = NULL;
        
        if (lista->cabeca != NULL)
            lista->cabeca->anterior = novo;
        else
            lista->final = novo; // se era vazia, atualiza o final

        lista->cabeca = novo;
    }
    else
    {
        // procura a posicao correta
        struct No *atual = lista->cabeca;
        while (atual->proximo != NULL && atual->proximo->estudante.ID < e.ID)
        {
            atual = atual->proximo;
        }
        
        // insere entre atual e atual->proximo
        novo->proximo = atual->proximo;
        novo->anterior = atual;
        
        if (atual->proximo != NULL)
        {
            atual->proximo->anterior = novo;
        }
        else
        {
            // se inseriu depois do ultimo, o novo vira o final
            lista->final = novo;
        }
        
        atual->proximo = novo;
    }

    lista->quantidade++;
    return 1;
}

int le_InsereListaOrdenada(struct ListaEnc *lista)
{
    struct Estudante e = le_LeEstudante();
    if (e.ID == 0) return 0;
    return le_InsereListaOrdenada2(lista, e);
}

int le_RemoveTodos(struct ListaEnc *lista, int exige_confirmacao)
{
    if (le_ListaNaoInicializada(lista)) return 0;
    
    if (lista->quantidade == 0) return 1;

    if (exige_confirmacao)
    {
        printf("Apagar tudo? (s/n): ");
        char c;
        scanf(" %c", &c);
        if (c != 's' && c != 'S') return 0;
    }

    // percorre liberando a memoria
    struct No *atual = lista->cabeca;
    while (atual != NULL)
    {
        struct No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    lista->cabeca = NULL;
    lista->final = NULL; // nao esquecer de limpar o final
    lista->quantidade = 0;
    return 1;
}

void le_DestroiLista(struct ListaEnc **lista)
{
    if (lista == NULL || *lista == NULL) return;
    le_RemoveTodos(*lista, 0);
    free(*lista);
    *lista = NULL;
}

void le_ImprimeLista(struct ListaEnc *lista)
{
    if (le_ListaNaoInicializada(lista)) return;
    struct No *atual = lista->cabeca;
    
    printf("\n--- Lista de Estudantes ---\n");
    while(atual != NULL)
    {
        le_ImprimeEstudante(atual->estudante);
        atual = atual->proximo;
    }    
    printf("--- Fim ---\n\n");
}

struct Estudante le_BuscaChave(struct ListaEnc *lista, char *chave)
{
    struct Estudante vazio = le_criaEstudante();
    if (le_ListaNaoInicializada(lista) || chave == NULL) return vazio;

    struct No *atual = lista->cabeca;
    while (atual != NULL)
    {
        // converto ID pra string pra comparar tambem
        char bufferID[20];
        sprintf(bufferID, "%d", atual->estudante.ID);
        
        if (strstr(atual->estudante.nome, chave) != NULL || strcmp(bufferID, chave) == 0)
        {
            return atual->estudante;
        }
        atual = atual->proximo;
    }
    return vazio;
}

// Funcao pedida no Item 3.1
void le_BuscaImprimeRetroativo(struct ListaEnc *lista, char *chave, int n)
{
    if (le_ListaNaoInicializada(lista) || chave == NULL) return;

    struct No *atual = lista->cabeca;
    int achou = 0;

    // 1. procuro o estudante
    while (atual != NULL)
    {
        char bufferID[20];
        sprintf(bufferID, "%d", atual->estudante.ID);

        if (strstr(atual->estudante.nome, chave) != NULL || strcmp(bufferID, chave) == 0)
        {
            achou = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!achou)
    {
        printf("Estudante nao encontrado.\n");
        return;
    }

    printf("\n>>> Estudante:\n");
    le_ImprimeEstudante(atual->estudante);

    // 2. volto n posicoes imprimindo
    printf("\n<<< %d Anteriores:\n", n);
    for (int i = 0; i < n; i++)
    {
        // verifica se chegou no comeco da lista
        if (atual->anterior == NULL)
        {
            printf("(Chegou no inicio da lista)\n");
            break;
        }
        atual = atual->anterior;
        le_ImprimeEstudante(atual->estudante);
    }
    printf("\n");
}

struct Estudante le_RemoveChave(struct ListaEnc *lista, char *chave)
{
    struct Estudante vazio = le_criaEstudante();
    if (le_ListaNaoInicializada(lista) || chave == NULL) return vazio;

    struct No *atual = lista->cabeca;

    while (atual != NULL)
    {
        char bufferID[20];
        sprintf(bufferID, "%d", atual->estudante.ID);

        if (strstr(atual->estudante.nome, chave) != NULL || strcmp(bufferID, chave) == 0)
        {
            struct Estudante ret = atual->estudante;

            // Arruma os ponteiros para remover o 'atual'
            if (atual->anterior != NULL)
            {
                atual->anterior->proximo = atual->proximo;
            }
            else
            {
                // se for o primeiro
                lista->cabeca = atual->proximo;
            }

            if (atual->proximo != NULL)
            {
                atual->proximo->anterior = atual->anterior;
            }
            else
            {
                // se for o ultimo, atualizo o ponteiro final
                lista->final = atual->anterior;
            }

            free(atual);
            if (lista->quantidade > 0) lista->quantidade--;
            
            printf("Removido com sucesso.\n");
            return ret;
        }
        atual = atual->proximo;
    }
    return vazio;
}

// Modificado para o Item 2: pergunta onde inserir
void le_EstudantesArquivo(struct ListaEnc *lista)
{
    if (le_ListaNaoInicializada(lista)) return;

    FILE *f = fopen("notas.csv", "r");
    if (f == NULL)
    {
        printf("Arquivo 'notas.csv' nao encontrado.\n");
        return;
    }

    int op = 0;
    printf("\nCarregar arquivo:\n1-Inicio\n2-Fim\n3-Ordenado\nOpcao: ");
    scanf("%d", &op);

    struct Estudante e;
    int contador = 0;
    
    // le o arquivo linha por linha
    while (fscanf(f, "%d;%[^;];%f\n", &e.ID, e.nome, &e.nota) == 3)
    {
        if (op == 1) le_InsereListaInicio2(lista, e);
        else if (op == 2) le_InsereListaFim2(lista, e);
        else le_InsereListaOrdenada2(lista, e);
        contador++;
    }

    printf("%d estudantes carregados.\n", contador);
    fclose(f);
}

void le_EnderecosNos(struct ListaEnc *lista)
{
    if (le_ListaNaoInicializada(lista)) return;
    struct No *atual = lista->cabeca;
    printf("DEBUG: Enderecos (Ant <- Atual -> Prox)\n");
    while (atual != NULL)
    {
        printf("[%d] %p <- %p -> %p\n", atual->estudante.ID, 
               (void*)atual->anterior, (void*)atual, (void*)atual->proximo);
        atual = atual->proximo;
    }
    // Mostra onde o ponteiro final esta apontando
    printf("Final da lista: %p\n", (void*)lista->final);
}

void delay_ms(unsigned int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
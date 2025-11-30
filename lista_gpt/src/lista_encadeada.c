#include "lista_encadeada.h"
#include "ec_rgb_colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>  // nanosleep

void delay_ms(unsigned int ms);

/* Estruturas internas */
struct No
{
    struct Estudante estudante;
    struct No *proximo;
    struct No *anterior
};

struct ListaEnc
{
    struct No *cabeca;       // ponteiro para o primeiro nó da lista
    struct No *final;
    unsigned int quantidade; // quantidade de elementos
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
void le_EnderecosNos(struct ListaEnc *lista);

// EM PRODUÇÃO le_EnderecosNos DEVE ser privada
// colocá-la no .c

// Funções do header(Publicas)
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

// Implementação das funções 

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
    printf("%d\t", e.ID);
    printf("%4.2f\t", e.nota);
    printf("%s\n", e.nome);
    delay_ms(1000);
}

static struct Estudante le_GetEstudante(int i)
{
    struct Estudante e;

    if (i == 0)
    {
        e.ID = -1;
        e.nota = 9.0;
        strcpy(e.nome, "John von Neumann");
    }
    if (i == 1)
    {
        e.ID = -2;
        e.nota = 9.7;
        strcpy(e.nome, "Edgar Frank Codd");
    }
    if (i == 2)
    {
        e.ID = -3;
        e.nota = 9.9;
        strcpy(e.nome, "Donald Ervin Knuth");
    }

    if (i > 2)
    {
        e.ID = 0;
        e.nota = 0;
        strcpy(e.nome, "");
    }

    return e;
}

void le_InsereTestes(struct ListaEnc *lista)
{
    struct Estudante e;

    printf("Inserindo estudantes de Teste...\n");

    for (int i = 0; i < 3; i++)
    {
        e = le_GetEstudante(i);
        le_InsereListaInicio2(lista, e);
    }
}

struct ListaEnc *le_CriaLista()
{
    // aloca dinamicamente a lista, utilizando ponteiros
    // inicializa a lista
    // retorna a lista

    struct ListaEnc *lista = (struct ListaEnc *)malloc(sizeof(struct ListaEnc));
    if (lista == NULL)
    {
        printf("Erro: nao foi possivel alocar memoria para a lista\n");
        return NULL;
    }
    lista->cabeca = NULL;
    lista->quantidade = 0;
    return lista;
}

static int le_ListaNaoInicializada(struct ListaEnc *lista)
{
    // se lista não estiver inicializada, mensagem em amarelo
    // retornar 0 ou 1 dependendo do caso 
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 1;
    }
    return 0;
}

int le_TamanhoLista(struct ListaEnc *lista, int imprime)
{
    // retorna a quantidade de elementos da lista
    // opção para imprimir ou ão quantidade de elementos da lista
    // caso a tratar: lista não inicializada
    
    if (le_ListaNaoInicializada(lista)) return -1;
    if (imprime)
    {
        printf("Quantidade de elementos: %u\n", lista->quantidade);
    }
    return (int)lista->quantidade;
}


int le_ListaVazia(struct ListaEnc *lista)
{
    // SE lista vazia, imprimir mensagem em amarelo
    // retorna 1 ou 0, dependendo se a lista está ou não vazia
    // caso a tratar: lista não inicializada

    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 1;
    }
    if (lista->quantidade == 0)
    {
        printf("Lista vazia\n");
        return 1;
    }
    return 0;
}

int le_ListaCheia(struct ListaEnc *lista)
{
    // para lista encadeada dinamica, nunca cheia (a nao ser por falta de memoria)
    (void)lista;
    return 0;
}

int le_InsereListaInicio2(struct ListaEnc *lista, struct Estudante e)
{
    // alocar no, e validar se conseguiu
    // armazenar dados do estudante
    // caso a tratar: lista não inicializada
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 0;
    }
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL)
    {
        printf("Erro: falha na alocacao de no\n");
        return 0;
    }
    novo->estudante = e;
    novo->proximo = lista->cabeca;
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


int le_InsereListaFim2(struct ListaEnc *lista, struct Estudante e)
{
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 0;
    }
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL)
    {
        printf("Erro: falha na alocacao de no\n");
        return 0;
    }
    novo->estudante = e;
    novo->proximo = NULL;

    if (lista->cabeca == NULL)
    {
        lista->cabeca = novo;
    }
    else
    {
        struct No *atual = lista->cabeca;
        while (atual->proximo != NULL) atual = atual->proximo;
        atual->proximo = novo;
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

int le_InsereListaOrdenada2(struct ListaEnc *lista, struct Estudante e)
{
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 0;
    }

    struct No *novo = (struct No *)malloc(sizeof(struct No));
    if (novo == NULL)
    {
        printf("Erro: falha na alocacao de no\n");
        return 0;
    }
    novo->estudante = e;
    novo->proximo = NULL;

    if (lista->cabeca == NULL || e.ID < lista->cabeca->estudante.ID)
    {
        novo->proximo = lista->cabeca;
        lista->cabeca = novo;
        lista->quantidade++;
        return 1;
    }

    struct No *atual = lista->cabeca;
    while (atual->proximo != NULL && atual->proximo->estudante.ID < e.ID)
    {
        atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
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
    if (lista == NULL)
    {
        printf("Aviso: lista nao inicializada\n");
        return 0;
    }
    if (lista->cabeca == NULL)
    {
        printf("Lista ja esta vazia\n");
        return 1;
    }
    if (exige_confirmacao)
    {
        printf("Confirmar remocao de todos os elementos? (s/n): ");
        int c = getchar();
        while (getchar() != '\n'); // limpar buffer
        if (c != 's' && c != 'S')
        {
            printf("Operacao cancelada\n");
            return 0;
        }
    }

    struct No *atual = lista->cabeca;
    while (atual != NULL)
    {
        struct No *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    lista->cabeca = NULL;
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

void le_EnderecosNos(struct ListaEnc *lista)
{
    if (le_ListaNaoInicializada(lista)) return;
    if (lista->cabeca == NULL)
    {
        printf("Lista vazia\n");
        return;
    }
    struct No *atual = lista->cabeca;
    while (atual != NULL)
    {
        printf("No %p -> proximo %p\n", (void*)atual, (void*)atual->proximo);
        atual = atual->proximo;
    }
}


void le_ImprimeLista(struct ListaEnc *lista)
{
    // imprime todos os elementos da lista
    // caso a tratar: lista não inicializada
    
    if (le_ListaNaoInicializada(lista)) return;

    struct No *atual = lista->cabeca;

    while(atual != NULL)
    {
        le_ImprimeEstudante(atual->estudante);
        atual = atual->proximo;
    }    

}

//static void le_ImprimeEstudante(struct Estudante e);

struct Estudante le_BuscaChave(struct ListaEnc *lista, char *chave)
{
    struct Estudante vazio = le_criaEstudante();
    if (le_ListaNaoInicializada(lista)) return vazio;
    if (chave == NULL) return vazio;

    struct No *atual = lista->cabeca;
    while (atual != NULL)
    {
        if (strstr(atual->estudante.nome, chave) != NULL)
        {
            return atual->estudante;
        }
        atual = atual->proximo;
    }
    return vazio;
}

struct Estudante le_RemoveChave(struct ListaEnc *lista, char *chave)
{
    struct Estudante vazio = le_criaEstudante();
    if (le_ListaNaoInicializada(lista)) return vazio;
    if (chave == NULL) return vazio;

    struct No *atual = lista->cabeca;
    struct No *ant = NULL;

    while (atual != NULL)
    {
        if (strstr(atual->estudante.nome, chave) != NULL)
        {
            // remover atual
            if (ant == NULL)
            {
                lista->cabeca = atual->proximo;
            }
            else
            {
                ant->proximo = atual->proximo;
            }
            struct Estudante ret = atual->estudante;
            free(atual);
            if (lista->quantidade > 0) lista->quantidade--;
            return ret;
        }
        ant = atual;
        atual = atual->proximo;
    }
    return vazio;
}

void le_EstudantesArquivo(struct ListaEnc *lista)
{
    if (le_ListaNaoInicializada(lista)) return;

    FILE *f = fopen("estudantes.txt", "r");
    if (f == NULL)
    {
        printf("Arquivo 'estudantes.txt' nao encontrado\n");
        return;2
    }

    struct Estudante e;
    // assume formato: ID<espaço>nota<espaço>nome até fim da linha
    while (fscanf(f, "%d %f %99[^\n]\n", &e.ID, &e.nota, e.nome) == 3)
    {
        le_InsereListaFim2(lista, e);
    }

    fclose(f);
}


void delay_ms(unsigned int ms) {
    struct timespec ts;
    
    // Converte milissegundos em segundos e nanossegundos
    ts.tv_sec = ms / 1000;  // Parte inteira em segundos
    ts.tv_nsec = (ms % 1000) * 1000000;  // O resto em nanossegundos (1 milissegundo = 1.000.000 nanossegundos)

    // Faz a pausa de acordo com os valores calculados
    nanosleep(&ts, NULL);
}

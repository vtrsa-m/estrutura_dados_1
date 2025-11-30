#include "lista_encadeada.h"
#include "ec_rgb_colors.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>  // nanosleep

void delay_ms(unsigned int ms);

struct No
{
    struct Estudante estudante;
    struct No *proximo;
};

struct ListaEnc
{
    struct No *cabeca;       // ponteiro para o primeiro nó da lista
    unsigned int quantidade; // quantidade de elementos
};

static struct Estudante le_GetEstudante(int i);
static struct Estudante le_criaEstudante();
static struct Estudante le_LeEstudante();
static void le_ImprimeEstudante(struct Estudante e);

struct ListaEnc *le_CriaLista();
int le_InsereListaInicio(struct ListaEnc *lista);
int le_InsereListaInicio2(struct ListaEnc *lista, struct Estudante e);
int le_InsereListaFim2(struct ListaEnc *lista, struct Estudante e);
int le_InsereListaOrdenada2(struct ListaEnc *lista, struct Estudante e);
void le_ImprimeLista(struct ListaEnc *lista);
void le_EstudantesArquivo(struct ListaEnc *lista);


//IMPLEMENTAÇÃO
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



}

static int le_ListaNaoInicializada(struct ListaEnc *lista)
{
    // se lista não estiver inicializada, mensagem em amarelo
    // retornar 0 ou 1 dependendo do caso 
    if(lista == NULL){
        ec_imprimirCor("0", "y");
    }
    else ec_imprimirCor("1", "y");

}

int le_TamanhoLista(struct ListaEnc *lista, int imprime)
{
    // retorna a quantidade de elementos da lista
    // opção para imprimir ou ão quantidade de elementos da lista
    // caso a tratar: lista não inicializada
    

}


int le_ListaVazia(struct ListaEnc *lista)
{
    // SE lista vazia, imprimir mensagem em amarelo
    // retorna 1 ou 0, dependendo se a lista está ou não vazia
    // caso a tratar: lista não inicializada

}

int le_ListaCheia(struct ListaEnc *lista)
{
}

int le_InsereListaInicio2(struct ListaEnc *lista, struct Estudante e)
{
    // alocar no, e validar se conseguiu
    // armazenar dados do estudante
    // caso a tratar: lista não inicializada
    
}


int le_InsereListaInicio(struct ListaEnc *lista)
{

}


int le_InsereListaFim2(struct ListaEnc *lista, struct Estudante e)
{

}

int le_InsereListaFim(struct ListaEnc *lista)
{
}

int le_InsereListaOrdenada2(struct ListaEnc *lista, struct Estudante e)
{
}

int le_InsereListaOrdenada(struct ListaEnc *lista)
{
}


int le_RemoveTodos(struct ListaEnc *lista, int exige_confirmacao)
{
}

void le_DestroiLista(struct ListaEnc **lista)
{
}

void le_EnderecosNos(struct ListaEnc *lista)
{
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
    
}

struct Estudante le_RemoveChave(struct ListaEnc *lista, char *chave)
{

}

void le_EstudantesArquivo(struct ListaEnc *lista)
{
}


void delay_ms(unsigned int ms) {
    struct timespec ts;
    
    // Converte milissegundos em segundos e nanossegundos
    ts.tv_sec = ms / 1000;  // Parte inteira em segundos
    ts.tv_nsec = (ms % 1000) * 1000000;  // O resto em nanossegundos (1 milissegundo = 1.000.000 nanossegundos)

    // Faz a pausa de acordo com os valores calculados
    nanosleep(&ts, NULL);
}

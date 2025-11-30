#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

/*
As principais operações sobre uma lista são: Referente à lista:
    criação;
    destruição;
    verificação do tamanho;
    verificação se está vazia, 
        ou cheia;

    listagem dos elementos;

    Referente aos elementos da lista;
        Inserção;
        Busca;
        Remoção;
*/

struct Estudante 
{
    int ID;
    float nota;
    char nome[30];
};
	
struct No;
struct ListaEnc;

struct ListaEnc * le_CriaLista();
void le_DestroiLista(struct ListaEnc **);

void le_InsereTestes(struct ListaEnc *);
int le_ListaVazia(struct ListaEnc *);
int le_ListaCheia(struct ListaEnc *);
int le_TamanhoLista(struct ListaEnc *, int imprime);
int le_RemoveTodos(struct ListaEnc *lista, int exige_confirmacao);

int le_InsereListaInicio(struct ListaEnc *lista);
int le_InsereListaFim(struct ListaEnc *lista);
int le_InsereListaOrdenada(struct ListaEnc *lista);
void le_EstudantesArquivo(struct ListaEnc *lista);
void le_ImprimeLista(struct ListaEnc *lista);

struct Estudante le_BuscaChave(struct ListaEnc *lista, char *chave);
struct Estudante le_RemoveChave(struct ListaEnc *lista, char *chave);

// EM PRODUÇÃO le_EnderecosNos DEVE ser privada
// colocá-la no .c
void le_EnderecosNos(struct ListaEnc *lista);

#endif


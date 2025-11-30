#include "lista_ini.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void lista_EnderecosNo(struct No *no, int num);
void lista_ImprimeNos(struct No **cabeca);

void  lista_TresNosEstaticos()
{

    struct Estudante estudante2, estudante3;
    estudante2.ID = 1;
    estudante2.nota = 9.7;
    strcpy(estudante2.nome, "Edgar Frank Codd");

    estudante3.ID = 2;
    estudante3.nota = 9.9;
    strcpy(estudante3.nome, "Donald Ervin Knuth");

    struct No no1, no2, no3;

    struct No **cabeca = malloc(sizeof(struct No*));
    *cabeca = &no1;

    no1.proximo = &no2;
    no2.proximo = &no3;
    no3.proximo = NULL;

    printf("\n\nEndereços de todos os nós: \n");

    lista_EnderecosNo(&no1, 1);
    lista_EnderecosNo(&no2, 2);
    lista_EnderecosNo(&no3, 3);
    
    //Inserindo os dados nos nós da lista

    no1.estudante.ID = 3;
    no1.estudante.nota = 9.0;
    strcpy(no1.estudante.nome, "John von Neumann");

    no2.estudante = estudante2;
    no3.estudante = estudante3;

    lista_ImprimeNos(cabeca);
    free(cabeca);
    cabeca = NULL;
}
 

void lista_EnderecosNo(struct No *no, int num)
{
    printf("no%d:\t ender: %p\t próximo: %p\n", num, (void*) no, (void *) no->proximo);
}

void lista_ImprimeNos(struct No **cabeca)
{
    if (cabeca == NULL) 
    {
        printf("Lista não inicializada!\n");
        return;
    }
    struct No *atual = *cabeca;
    if (atual == NULL)
    {
        printf("Lista não inicializada!\n");
        return;
    }
    printf("\n\nID\tNOTA\tNOME\n");
    while (atual != NULL)
    {
        printf("%d\t", atual->estudante.ID);
        printf("%.2f\t", atual->estudante.nota);
        printf("%s\n", atual->estudante.nome);
        
        atual = atual->proximo;
    }

}



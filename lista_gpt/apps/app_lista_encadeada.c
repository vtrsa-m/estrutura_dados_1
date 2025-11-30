#include "lista_encadeada.h"
#include "ec_rgb_colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
void executa(int opcao, struct ListaEnc **lista);

int main(void)
{
    struct ListaEnc *lista = le_CriaLista();

    le_InsereTestes(lista);
    le_ImprimeLista(lista);

    int opcao;
    do
    {
        opcao = menu();
        executa(opcao, &lista);
    } while (opcao > 0);

    le_DestroiLista(&lista);

    return 0;
}

int menu()
{
    int opcao;

    ec_imprimirCor("\n\nMenu de opcoes\n", "E");
    ec_imprimirCor("============================================================\n", "E");
    printf("0   - Sair\n");
    printf("1   - Imprimir lista completa\n");
    printf("2   - Ver enderecos de memoria (Debug)\n");
    printf("3   - Inserir no Inicio\n");
    printf("4   - Inserir no Fim (Rapido)\n");
    printf("5   - Inserir Ordenado por ID\n");
    printf("6   - Buscar estudante\n");
    printf("7   - Remover estudante\n");
    printf("8   - Carregar do arquivo (escolher modo)\n");
    printf("9   - Apagar lista toda\n");
    printf("10  - Busca Retroativa (Item 3.1)\n"); // Opcao nova
    printf("100 - Destruir lista e liberar memoria\n");
    ec_imprimirCor("============================================================\n", "E");

    ec_imprimirCor("Digite a opcao: ", "E");
    scanf("%d", &opcao);
    return opcao;
}

void executa(int opcao, struct ListaEnc **lista )
{
    char chave[40];
    struct Estudante e;
    int n = 0;

    switch (opcao)
    {
        case 1: 
            le_ImprimeLista(*lista); 
            break;

        case 2:
            // mostra os ponteiros anterior/proximo
            le_EnderecosNos(*lista); 
            break;

        case 3:
            // insere no comeco
            le_InsereListaInicio(*lista); 
            break;

        case 4:
            // insere no final usando o ponteiro 'final'
            le_InsereListaFim(*lista); 
            break;

        case 5:
            le_InsereListaOrdenada(*lista); 
            break;            

        case 6: 
        case 7: 
            do
            {
                printf("Digite o nome ou ID (0 para sair): ");
                getchar(); 
                scanf("%[^\n]", chave);
                
                if (strcmp(chave, "0") == 0) break;

                if (opcao == 6)
                    e = le_BuscaChave(*lista, chave);
                else 
                    e = le_RemoveChave(*lista, chave);

                if (e.ID != 0)
                {
                    if (opcao == 6)
                        printf("Achei o estudante: \n");
                    else 
                        printf("Estudante removido: \n");

                    printf("ID: %d\tNota: %.2f\tNome: %s\n", e.ID, e.nota, e.nome);
                }
                else 
                {
                    printf("Nao encontrei ninguem com esse nome/ID.\n");
                }
                
            } while (strcmp(chave, "0") != 0);
            break;

        case 8:
            le_EstudantesArquivo(*lista); 
            break;
            
        case 9:
            le_RemoveTodos(*lista, 1);
            break;

        case 10: 
            // Novo item 3.1: busca e imprime os anteriores
            printf("Buscar quem (Nome ou ID): ");
            getchar(); 
            scanf("%[^\n]", chave);
            
            printf("Mostrar quantos anteriores? ");
            scanf("%d", &n);
            
            le_BuscaImprimeRetroativo(*lista, chave, n);
            break;

        case 99:
            ec_imprimirTodasAsCores(50);
            break;

        case 100:
            le_DestroiLista(lista);
            break;
        
        default:
            if(opcao != 0) printf("Opcao nao existe!\n");
            break;
    }
}
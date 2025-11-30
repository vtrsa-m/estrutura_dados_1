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
    } while (opcao >0);

    le_DestroiLista(&lista);

    return 0;
}

int menu()
{

    int opcao;

    ec_imprimirCor("\n\nMenu de opções a executar\n", "E");
    ec_imprimirCor("============================================================\n", "E");
    printf("0   - Finalizar programa!\n");
    printf("1   - Imprimir todos os elementos da lista\n");
    printf("2   - Imprimir os endereços de todos elementos da lista\n");
    printf("3   - Inserir elemento(s) no início da lista\n");
    printf("4   - Inserir elemento(s) no final da lista\n");
    printf("5   - Inserir elemento(s) ordenados pelo ID\n");
    printf("6   - Buscar elemento(s) da lista\n");
    printf("7   - Remover elemento(s) da lista\n");
    printf("8   - Importar dados arquivo notas.csv\n");
    printf("9   - Remover todos os elementos da lista\n");
    printf("99  - AUX: ec_imprimirTodasAsCores\n");
    printf("100 - Destruir a lista\n");
    ec_imprimirCor("============================================================\n", "E");

    ec_imprimirCor("Informe a opção a executar: ", "E");
    scanf("%d", &opcao);
    return opcao;
}

void executa(int opcao, struct ListaEnc **lista )
{
    char chave[40];
    struct Estudante e;

    switch (opcao)
    {
        case 1: 
            le_ImprimeLista(*lista); break;
        case 2:
            le_EnderecosNos(*lista); break;
        case 3:
            le_InsereListaInicio(*lista); break;
        case 4:
            le_InsereListaFim(*lista); break;
        case 5:
            le_InsereListaOrdenada(*lista); break;            
        case 6: case 7: // dois casos tratados juntos
            do
            {
                printf("Informe a chave de busca (0 para finalizar): ");
                getchar();
                scanf("%[^\n]", chave);
                if (opcao == 6)
                    e = le_BuscaChave(*lista, chave);
                else e = le_RemoveChave(*lista, chave);

                if (e.ID != 0)
                {
                    if (opcao == 6)
                        printf("Dados do estudante retornado: \n");
                    else printf("Dados do estudante excluído: \n");

                    printf("%d\t", e.ID);
                    printf("%.2f\t", e.nota);
                    printf("%s\n", e.nome);
                }
                
            } while (strcmp(chave, "0")!= 0);

            break;

        case 8:
            le_EstudantesArquivo(*lista); 
            break;
        case 9:
            le_RemoveTodos(*lista, 1);
            break;

        case 99:
            ec_imprimirTodasAsCores(50);break;
        case 100:
            le_DestroiLista(lista);


    }

}
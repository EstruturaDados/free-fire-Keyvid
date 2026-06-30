#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

struct Item {
    char nome [30];
    char tipo [20];
    int quantidade;

};

int main() {
    struct Item inventario[10];
    int opcao;
    int total_itens = 0;

    // Menu principal com opções:
    do{
        printf("=== MOCHILA FREE FIRE ===\n");
        printf("(1) Adicionar Item\n");
        printf("(2) Remover Item\n");
        printf("(3) Listar Item\n");
        printf("(4) Buscar Item\n");
        printf("(0) Sair\n");
        printf("Escolha uma opção:");
        scanf("%d", &opcao);
        
        // 1. Adicionar um item
        // A estrutura switch trata cada opção chamando a função correspondente.
        switch(opcao) {
            case 1:
            printf("\n=== LOOTEAR ITEM ===\n");

            if (total_itens < 10) {
                printf("Nome do item(ex.:Kit Medico, AK47, Colete...): ");
                scanf(" %[^\n]", inventario[total_itens].nome);

                printf("Tipo do item:(ex.: arma, municao, cura): ");
                scanf(" %[^\n]", inventario[total_itens].tipo);

                printf("Quantidade: ");
                scanf("%d", &inventario[total_itens].quantidade);

                total_itens++;

                printf("Item guardado com sucesso!\n");
            } else {
                printf("A mochila está cheia! Você precisa dropar algo.\n");
            }
            break;

        // 2. Remover um item
        case 2: 
            printf("\n=== DROPAR ITEM ===\n");

            if (total_itens == 0) {
                printf("A mochila está varia!\n");
            } else {

                char nome_busca[30];
                printf("Qual o nome do item que deseja dropar? ");
                scanf(" %[^\n]", nome_busca);

                int encontrado = 0;

                for (int i = 0; i < total_itens; i++) {
                    if (strcmp(inventario[i].nome, nome_busca) == 0) {
                        encontrado = 1;

                        for (int j = i; j < total_itens - 1; j++) {
                            inventario[j] = inventario[j + 1];
                        }
                        total_itens--;

                        printf("-> '%s' dropado com sucesso!\n", nome_busca);
                        break;
                    }
                }

                if (encontrado == 0) {
                    printf("-> Erro: Item '%s' não encontrado na mochila.\n", nome_busca);
                }
            }
            break;

        // 3. Listar todos os itens
        // Exibe uma tabela formatada com todos os componentes presentes na mochila.
        case 3: 
            printf("\n=== IVENTARIO ===\n");

            if(total_itens == 0) {
                printf("A mochila está vazia!");
            } else {
                printf("%-5s | %-20s | %-15s | %s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
                printf("=============================================================\n");
                for (int i = 0; i < total_itens; i++) {
                    printf("[%d]  | %-20s | %-15s | %d\n", 
                        i,
                        inventario[i].nome,
                        inventario[i].tipo,
                        inventario[i].quantidade);

                }
                printf("=============================================================\n");
                printf("Total de itens: %d/10\n", total_itens);
            }
            break;

         // 4. Ordenar os itens por critério (nome, tipo, prioridade)
        case 4:
            printf("\n=== BUSCAR ITEM ===\n");
            if (total_itens == 0) {
                printf("A mochila está vazia! Nâo há itens disponíveis.\n");
            } else {
                char nome_busca[30];
                printf("Digite o nome do item que procura: ");
                scanf(" %[^\n]", nome_busca);

                int encontrado = 0;

                for (int i = 0; i < total_itens; i++) {
                    if (strcmp(inventario[i].nome, nome_busca) == 0) {
                        printf("\n -> ITEM ENCONTRADO:\n");

                        printf("%-5s | %-20s | %-15s | %s\n", "ID", "NOME", "TIPO", "QUANTIDADE");
                        printf("==================================================================\n");
                        printf("[%d]  | %-20s | %-15s | %d\n", 
                        i,
                        inventario[i].nome,
                        inventario[i].tipo,
                        inventario[i].quantidade);

                    encontrado = 1;
                    break; 

                    }
                }

                if (encontrado == 0 ) {
                    printf("\n-> Erro: O item '%s' não está na mochila.\n", nome_busca);
                }
            }
            break;

        case 0: 
            printf("\nFechando mochila...\n");
            break;
        
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.



// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

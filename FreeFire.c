#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

struct Item {
    char nome [30];
    char tipo [20];
    int quantidade;
    int prioridade;

};

int main() {
    struct Item inventario[10];
    int opcao;
    int total_itens = 0;
    int ordenado_por_nome = 0;

    // Menu principal com opções:
    do{
        printf("\n==============================================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("==============================================================\n");
        printf("Itens na Mochila: %d/10\n", total_itens);
        
        printf("Status da Ordenacao por Nome: %s\n\n", ordenado_por_nome == 1 ? "ORDENADO" : "NAO ORDENADO");
        
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("--------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        // 1. Adicionar um item
        // A estrutura switch trata cada opção chamando a função correspondente.
        switch(opcao) {
            case 1:
                printf("\n--- Coletando Novo Componente ---\n");
                
                if (total_itens < 10) {
                    printf("Nome: ");
                    scanf(" %[^\n]", inventario[total_itens].nome);
                    
                    printf("Tipo (Estrutural, Eletronico, Energia): ");
                    scanf(" %[^\n]", inventario[total_itens].tipo);
                    
                    printf("Quantidade: ");
                    scanf("%d", &inventario[total_itens].quantidade);
                    
                    // A nova variavel da struct
                    printf("Prioridade de Montagem (1-5): ");
                    scanf("%d", &inventario[total_itens].prioridade);
                    
                    printf("\nComponente '%s' adicionado!\n", inventario[total_itens].nome);
                    
                    total_itens++;
                    ordenado_por_nome = 0;
                    
                } else {
                    printf("A mochila esta cheia! Descarte algum componente primeiro.\n");
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
            printf("\n--- INVENTARIO ATUAL (%d/10) ---\n", total_itens);
            
            if (total_itens == 0) {
                printf("Mochila vazia.\n");
            } else {
                printf("--------------------------------------------------------------\n");
                // %-20s = 20 espaços alinhados à esquerda
                printf("%-20s | %-15s | %-10s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
                printf("--------------------------------------------------------------\n");
                
                for (int i = 0; i < total_itens; i++) {
                    printf("%-20s | %-15s | %-10d | %d\n", 
                            inventario[i].nome, 
                            inventario[i].tipo, 
                            inventario[i].quantidade,
                            inventario[i].prioridade);
                }
                printf("--------------------------------------------------------------\n");
            }
            break;

         // 4. Ordenar os itens por critério (nome, tipo, prioridade)
        case 4: {
                printf("\n--- Organizar Mochila ---\n");
                
                if (total_itens < 2) {
                    printf("Voce precisa de pelo menos 2 componentes para ordenar.\n");
                } else {
                    int sub_opcao;
                    printf("1. Bubble Sort (Ordenar por Nome)\n");
                    printf("2. Insertion Sort (Ordenar por Tipo)\n");
                    printf("3. Selection Sort (Ordenar por Prioridade)\n");
                    printf("Escolha a estrategia de ordenacao: ");
                    scanf("%d", &sub_opcao);
                    
                    // Inicia o relogio e o contador de comparacoes
                    clock_t inicio = clock();
                    int comparacoes = 0;
                    
                    switch(sub_opcao) {
                        case 1: // Bubble Sort (Por Nome)
                            for (int i = 0; i < total_itens - 1; i++) {
                                for (int j = 0; j < total_itens - i - 1; j++) {
                                    comparacoes++;
                                    if (strcmp(inventario[j].nome, inventario[j+1].nome) > 0) {
                                        struct Item temp = inventario[j];
                                        inventario[j] = inventario[j+1];
                                        inventario[j+1] = temp;
                                    }
                                }
                            }
                            ordenado_por_nome = 1; // Habilita a Busca Binaria!
                            printf("\n-> Ordenacao por Nome concluida!\n");
                            break;
                            
                        case 2: // Insertion Sort (Por Tipo)
                            for (int i = 1; i < total_itens; i++) {
                                struct Item carta_atual = inventario[i];
                                int j = i - 1;
                                
                                comparacoes++;
                                while (j >= 0 && strcmp(inventario[j].tipo, carta_atual.tipo) > 0) {
                                    inventario[j + 1] = inventario[j];
                                    j = j - 1;
                                    comparacoes++; 
                                }
                                inventario[j + 1] = carta_atual;
                            }
                            ordenado_por_nome = 0; // Quebrou a ordem por nome
                            printf("\n-> Ordenacao por Tipo concluida!\n");
                            break;
                            
                        case 3: // Selection Sort (Por Prioridade)
                            for (int i = 0; i < total_itens - 1; i++) {
                                int indice_menor = i;
                                for (int j = i + 1; j < total_itens; j++) {
                                    comparacoes++;
                                    if (inventario[j].prioridade > inventario[indice_menor].prioridade) {
                                        indice_menor = j;
                                    }
                                }
                                if (indice_menor != i) {
                                    struct Item temp = inventario[i];
                                    inventario[i] = inventario[indice_menor];
                                    inventario[indice_menor] = temp;
                                }
                            }
                            ordenado_por_nome = 0; // Quebrou a ordem por nome
                            printf("\n-> Ordenacao por Prioridade concluida!\n");
                            break;
                            
                        default:
                            printf("\nEstrategia invalida! Operacao cancelada.\n");
                            break;
                    }
                    
                    // Se o usuario escolheu uma opcao valida de 1 a 3, imprime o desempenho
                    if (sub_opcao >= 1 && sub_opcao <= 3) {
                        clock_t fim = clock();
                        double tempo_gasto = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
                        printf("Comparacoes realizadas: %d\n", comparacoes);
                        printf("Tempo de execucao: %f ms\n", tempo_gasto);
                    }
                }
                break;
            }

        case 5:
            if (ordenado_por_nome == 0) {
                printf("Erro: Ordene por NOME Primeiro!\n");
            }

            char chave[20];
            printf("Digite o nome do componente para ativar a torre: ");
            scanf(" %[^\n]", chave);

            int inicio_busca = 0;
            int fim_busca = total_itens - 1;
            int meio;
            int encontrou = 0;
            int comp_busca = 0;

            clock_t inicio_tempo_busca = clock();

            while (inicio_busca <= fim_busca) {
                comp_busca++;
                meio = inicio_busca + (fim_busca - inicio_busca) / 2;
                
                int resultado_strcmp = strcmp(inventario[meio].nome, chave);
                
                if (resultado_strcmp == 0) {
                    encontrou = 1;
                    break; // Achou exatamente no meio!
                } 
                else if (resultado_strcmp < 0) {
                    // A chave esta na metade da direita
                    inicio_busca = meio + 1;
                } 
                else {
                    // A chave esta na metade da esquerda
                    fim_busca = meio - 1;
                }
            }

            clock_t fim_tempo_busca = clock();
            double tempo_busca_ms = ((double)(fim_tempo_busca - inicio_tempo_busca) / CLOCKS_PER_SEC) * 1000.0;

            if (encontrou) {
                printf("\nCOMPONENTE CHAVE LOCALIZADO NO INDICE [%d]!\n", meio);
                printf("Torre de Fuga Pronta para Ativacao!\n");
            } else {
                printf("\nComponente nao encontrado na ilha.\n");
            }
            printf("Comparacoes feitas na busca: %d\n", comp_busca);
            printf("Tempo de busca: %f ms\n", tempo_busca_ms);



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

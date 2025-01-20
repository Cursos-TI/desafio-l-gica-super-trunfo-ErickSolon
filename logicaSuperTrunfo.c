#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_ESTADOS 8
#define CIDADES_POR_ESTADO 4
#define TOTAL_CIDADES (NUM_ESTADOS * CIDADES_POR_ESTADO)

// função para calcular a densidade populacional
float calcularDensidadePopulacional(unsigned int populacao, float area) {
    // evitará ter area menor ou igual a 0 para não dar problema de divisão por zero. 
    if (area >= 0) {
        return populacao / area;
    } else {
        return 0;
    }
}

// função para calcular PIB per capita
float calcularPibPerCapita(float pib, unsigned int populacao) {
    // evitará ter população menor ou igual a 0 para não dar problema de divisão por zero. 
    if (populacao >= 0) {
        return pib / populacao;
    } else {
        return 0;
    }
}
 
// aqui nesta função calcula o super poder de cada carta escolhida, 
// como a densidade populacional deve ser considerada de forma inversa (quanto menor, melhor), 
// podemos subtrair a densidade para que a densidade de fato "diminua" o valor do Super Poder.
float calcularSuperPoder(unsigned int populacao, float area, float pib, unsigned int pontosTuristicos) {
    float densidadePopulacional = calcularDensidadePopulacional(populacao, area);
    float pibPerCapita = calcularPibPerCapita(pib, populacao);

    return ((1.0f / densidadePopulacional + pibPerCapita + pontosTuristicos + populacao + area + pib);
}

// função que retorna o índice de uma cidade no array "codigo".
int obterIndiceCidade(char *codigoCidade, char codigo[TOTAL_CIDADES][4]) {
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        if (strcmp(codigoCidade, codigo[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// aqui ele compara as cartas
void compararCartas(int escolhaComparacao, char *codigoCidade1, char *codigoCidade2, unsigned int populacao[], float area[], float pib[], unsigned int pontosTuristicos[], char codigo[TOTAL_CIDADES][4]) {
    int cidade1 = -1, cidade2 = -1;
    
    for (int i = 0; i < TOTAL_CIDADES; i++) {
        if (strcmp(codigo[i], codigoCidade1) == 0) {
            cidade1 = i;
        }
        if (strcmp(codigo[i], codigoCidade2) == 0) {
            cidade2 = i;
        }
    }

    if (cidade1 == -1 || cidade2 == -1) {
        printf("Código da cidade não encontrado.\n");
        return;
    }

    float densidadePopulacional1 = calcularDensidadePopulacional(populacao[cidade1], area[cidade1]);
    float densidadePopulacional2 = calcularDensidadePopulacional(populacao[cidade2], area[cidade2]);
    unsigned int populacao1 = populacao[cidade1];
    unsigned int populacao2 = populacao[cidade2];
    float area1 = area[cidade1];
    float area2 = area[cidade2];
    float pib1 = pib[cidade1];
    float pib2 = pib[cidade2];
    unsigned int pontosTuristicos1 = pontosTuristicos[cidade1];
    unsigned int pontosTuristicos2 = pontosTuristicos[cidade2];
    float superPoder1 = calcularSuperPoder(populacao[cidade1], area[cidade1], pib[cidade1], pontosTuristicos[cidade1]);
    float superPoder2 = calcularSuperPoder(populacao[cidade2], area[cidade2], pib[cidade2], pontosTuristicos[cidade2]);

    printf("Comparando Cidade %s e Cidade %s:\n", codigoCidade1, codigoCidade2);

    switch (escolhaComparacao) {
        case 1:
            if (pontosTuristicos1 > pontosTuristicos2) {
                printf("Cidade %s vence nos Pontos Túristicos com valor %d\n", codigoCidade1, pontosTuristicos1);
            } else if (pib2 > pib1) {
                printf("Cidade %s vence nos Pontos Túristicos com valor %d\n", codigoCidade2, pontosTuristicos2);
            } else {
                printf("Empate nos Pontos Túristicos com valor %d\n", pib1);
            }

            break;

        case 2:
            if (pib1 > pib2) {
                printf("Cidade %s vence no PIB com valor %.2f\n", codigoCidade1, pib1);
            } else if (pib2 > pib1) {
                printf("Cidade %s vence no PIB com valor %.2f\n", codigoCidade2, pib2);
            } else {
                printf("Empate na Área com valor %.2f\n", pib1);
            }
            break;
        
        case 3:
            if (densidadePopulacional1 < densidadePopulacional2) {
                printf("Cidade %s vence na Densidade Populacional com valor %.2f\n", codigoCidade1, densidadePopulacional1);
            } else if (densidadePopulacional2 < densidadePopulacional1) {
                printf("Cidade %s vence na Densidade Populacional com valor %.2f\n", codigoCidade2, densidadePopulacional2);
            } else {
                printf("Empate na Densidade Populacional com valor %.2f\n", densidadePopulacional1);
            }
            break;

        case 4:
            if (populacao1 > populacao2) {
                printf("Cidade %s vence na População com valor %d\n", codigoCidade1, populacao1);
            } else if (populacao2 > populacao1) {
                printf("Cidade %s vence na População com valor %d\n", codigoCidade2, populacao2);
            } else {
                printf("Empate na População com valor %d\n", populacao1);
            }
            break;

        case 5:
            if (area1 > area2) {
                printf("Cidade %s vence na Área com valor %.2f\n", codigoCidade1, area1);
            } else if (area2 < area1) {
                printf("Cidade %s vence na Área com valor %.2f\n", codigoCidade2, area2);
            } else {
                printf("Empate na Área com valor %.2f\n", area1);
            }
            break;
        
        case 6:
            

            if (superPoder1 > superPoder2) {
                printf("Cidade %s vence com Super Poder: %.2f\n", codigoCidade1, superPoder1);
            } else if (superPoder2 > superPoder1) {
                printf("Cidade %s vence com Super Poder: %.2f\n", codigoCidade2, superPoder2);
            } else {
                printf("Empate no Super Poder: %.2f\n", superPoder1);
            }
            break;

        default:
            printf("Escolha não reconhecida tente novamente...");
            break;
    }
}

// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.

int main() {
    // Definição das variáveis para armazenar as propriedades das cidades
    // Você pode utilizar o código do primeiro desafio
    char codigoCidade[TOTAL_CIDADES][4];
    char nome[TOTAL_CIDADES][100]; 
    unsigned int populacao[TOTAL_CIDADES];
    float area[TOTAL_CIDADES]; 
    float pib[TOTAL_CIDADES]; 
    unsigned int pontosTuristicos[TOTAL_CIDADES];
    int indice = 0;
    double pibPerCapita;
    double densidadePopulacional;
    char digitarCodigoCidade1[4], digitarCodigoCidade2[4];
    int escolhaTipoJogo;
    
    // Cadastro das Cartas:
    // Implemente a lógica para solicitar ao usuário que insira os dados das cidades
    // utilizando a função scanf para capturar as entradas.
    // utilize o código do primeiro desafio

    // Exemplo:
    // printf("Digite o código da cidade: ");
    // scanf("%s", codigo);
    // 
    // (Repita para cada propriedade)

    // Comparação de Cartas:
    // Desenvolva a lógica de comparação entre duas cartas.
    // Utilize estruturas de decisão como if, if-else para comparar atributos como população, área, PIB, etc.

    // Exemplo:
    // if (populacaoA > populacaoB) {
    //     printf("Cidade 1 tem maior população.\n");
    // } else {
    //     printf("Cidade 2 tem maior população.\n");
    // }

    // Exibição dos Resultados:
    // Após realizar as comparações, exiba os resultados para o usuário.
    // Certifique-se de que o sistema mostre claramente qual carta venceu e com base em qual atributo.

    // Exemplo:
    // printf("A cidade vencedora é: %s\n", cidadeVencedora);

     // tela inicial do jogo onde o jogador escolherá 1 ou 2 como opções que estão descritas.
    printf("<><><><><> Super Trunfo (Países) <><><><><>\n");
    printf("1 ... Inserção de cidades manualmente.\n");
    printf("2 ... Inserção de cidades automaticamente.\n");
    printf("Escolha >>> ");
    scanf("%d", &escolhaTipoJogo);

    if (escolhaTipoJogo == "") {
        printf("escolha novamente... fechando jogo...");
        exit(0);
    } else {
        switch (escolhaTipoJogo) {
            case 1: {
                for (char estado = 'A'; estado <= 'H'; estado++) {
                    for (int cidade = 1; cidade <= 4; cidade++) {
                        sprintf(codigoCidade[indice], "%c%02d", estado, cidade);
                        printf("\n=== Cadastro da Cidade %s ===\n", codigoCidade[indice]);
                        printf("Digite o nome da cidade: ");
                        getchar();
                        fgets(nome[indice], sizeof(nome[indice]), stdin); 
                        nome[indice][strcspn(nome[indice], "\n")] = '\0';
                        printf("Digite a população da cidade: ");
                        scanf("%u", &populacao[indice]);
                        printf("Digite a área da cidade (em km²): ");
                        scanf("%f", &area[indice]); 
                        printf("Digite o PIB da cidade (em bilhões): ");
                        scanf("%f", &pib[indice]);
                        printf("Digite o número de pontos turísticos da cidade: ");
                        scanf("%u", &pontosTuristicos[indice]);
                            
                        indice++;
                    }
                }

                break;
            }

            case 2: {
                for (char estado = 'A'; estado <= 'H'; estado++) {
                    for (int cidade = 1; cidade <= 4; cidade++) {                        
                        sprintf(codigoCidade[indice], "%c%02d", estado, cidade);
                        printf("\n=== Cidade Cadastrada %s ===\n", codigoCidade[indice]);
                        sprintf(nome[indice], "Cidade %d", indice + 1);
                        populacao[indice] = 100000 + indice * 1000;
                        area[indice] = 200 + indice * 10;
                        pib[indice] = 50 + indice * 5;
                        pontosTuristicos[indice] = indice % 10;

                        indice++;
                    }
                }

                break;
            }

            default: {
                printf("Item não compreendido, fechado jogo! tente novamente...");
                exit(0);
                break;
            }
        }
    }
    
    // aqui ele apenas mostra as cartas baseado na escolha das opções na tela inicial, e printa cada carta dos arrays
    printf("\n=== Cartas das cidades ===\n");

    for (int i = 0; i < TOTAL_CIDADES; i++) {
        densidadePopulacional = calcularDensidadePopulacional(populacao[i], area[i]);
        pibPerCapita = calcularPibPerCapita(pib[i], populacao[i]);

        printf("\n=== Código da cidade %s ===\n", codigoCidade[i]);
        printf("Nome da cidade: %s\n", nome[i]);
        printf("População da cidade: %u\n", populacao[i]);
        printf("Área da cidade: %.2f km²\n", area[i]);
        printf("PIB da cidade: %.2f bilhões\n", pib[i]);
        printf("Número de pontos turísticos: %u\n", pontosTuristicos[i]);
        printf("Densidade populacional: %.2f hab/km²\n", densidadePopulacional);
        printf("PIB per capita: %.2f bilhões/habitante\n", pibPerCapita);
    }

    printf("\n=== Fim das Cartas ===\n");

    // aqui é onde é feita a comparação de cada carta
    do {
        int escolhaComparacaoLoop;

        printf("\n\nDigite o código de duas cidades para que sejam comparadas! Exemplo: A01 e A02\n");
        printf("Digite \"-1\" em qualquer input de código de cidade para parar de comparar as cartas e sair do programa!\n");
        printf("Cidade 1: ");
        scanf("%s", &digitarCodigoCidade1);
        printf("Cidade 2: ");
        scanf("%s", &digitarCodigoCidade2);

        if (strcmp(digitarCodigoCidade1, "-1") == 0 || strcmp(digitarCodigoCidade2, "-1") == 0) {
            break;
        }
        
        printf("Escolha qual item a comparação deve ser feita: ");
        printf("1 ... pontos turísticos\n");
        printf("2 ... PIB\n");
        printf("3 ... densidade populacional\n");
        printf("4 ... população\n");
        printf("5 ... área\n");
        printf("6 ... super poder\n");
        printf("Escolha >>> ");
        scanf("%d", &escolhaComparacaoLoop);

        compararCartas(escolhaComparacaoLoop, digitarCodigoCidade1, digitarCodigoCidade2, populacao, area, pib, pontosTuristicos, codigoCidade);
    } while (1);

    return 0;
}

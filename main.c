#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// #include <stdio.h>
// #include <string.h>

#define MAX 100 // Máximo tamanho da matriz e da palavra.

// Estrutura para armazenar as posições e direções das palavras encontradas.
typedef struct
{
    int x, y;         // Posição inicial da palavra (linha, coluna).
    char direcao[20]; // Direção da palavra encontrada.
} PosicaoDirecao;

// Função para converter letras de uma palavra para maiúsculas.
void destacarPalavra(char *palavra)
{
    while (*palavra)
    {
        *palavra = toupper((unsigned char)*palavra);
        palavra++;
    }
}

// Funções de busca vão aqui.

// Direções: {linha, coluna}
int direcoes[8][2] = {
    {-1, 0},  // Cima
    {1, 0},   // Baixo
    {0, -1},  // Esquerda
    {0, 1},   // Direita
    {-1, -1}, // Diagonal superior esquerda
    {-1, 1},  // Diagonal superior direita
    {1, -1},  // Diagonal inferior esquerda
    {1, 1}    // Diagonal inferior direita
};

// Verifica se uma palavra pode ser formada a partir de (x, y) em uma direção específica.
bool buscarDirecao(char matriz[][MAX], int x, int y, char *palavra, int direcao, int linhas, int colunas)
{
    int len = strlen(palavra);
    int dx = direcoes[direcao][0], dy = direcoes[direcao][1];

    for (int i = 0; i < len; i++)
    {
        int nx = x + i * dx, ny = y + i * dy;

        // Verifica se estamos fora do diagrama ou se a letra não corresponde.
        if (nx < 0 || ny < 0 || nx >= linhas || ny >= colunas || matriz[nx][ny] != palavra[i])
        {
            return false;
        }
    }

    // A palavra corresponde, destacá-la e retornar verdadeiro.
    for (int i = 0; i < len; i++)
    {
        int nx = x + i * dx, ny = y + i * dy;
        matriz[nx][ny] = toupper(matriz[nx][ny]); // Destacando palavra
    }
    return true;
}

void buscarPalavras(char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], int qtd_palavras, PosicaoDirecao posicoes[])
{
    for (int p = 0; p < qtd_palavras; p++)
    {
        char *palavra = palavras[p];
        bool encontrou = false;

        for (int x = 0; x < linhas && !encontrou; x++)
        {
            for (int y = 0; y < colunas && !encontrou; y++)
            {
                for (int direcao = 0; direcao < 8 && !encontrou; direcao++)
                {
                    if (buscarDirecao(matriz, x, y, palavra, direcao, linhas, colunas))
                    {
                        posicoes[p].x = x;
                        posicoes[p].y = y;
                        // Armazenando a direção encontrada
                        switch (direcao)
                        {
                        case 0:
                            strcpy(posicoes[p].direcao, "cima");
                            break;
                        case 1:
                            strcpy(posicoes[p].direcao, "baixo");
                            break;
                        case 2:
                            strcpy(posicoes[p].direcao, "esquerda");
                            break;
                        case 3:
                            strcpy(posicoes[p].direcao, "direita");
                            break;
                        case 4:
                            strcpy(posicoes[p].direcao, "diagonal superior esquerda");
                            break;
                        case 5:
                            strcpy(posicoes[p].direcao, "diagonal superior direita");
                            break;
                        case 6:
                            strcpy(posicoes[p].direcao, "diagonal inferior esquerda");
                            break;
                        case 7:
                            strcpy(posicoes[p].direcao, "diagonal inferior direita");
                            break;
                        }
                        encontrou = true;
                    }
                }
            }
        }

        if (!encontrou)
        {
            // Se a palavra não foi encontrada, registra-se isso de alguma maneira.
            posicoes[p].x = -1; // Indica posição inválida/não encontrada.
        }
    }
}

// Função para ler os dados de entrada.
void lerDados(char *nomeArquivo, char matriz[][MAX], int *linhas, int *colunas, char palavras[][MAX], int *qtd_palavras)
{
    FILE *arquivo = fopen(nomeArquivo, "r"); // Abre o arquivo para leitura.
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    // Lê o número de linhas e colunas do diagrama.
    fscanf(arquivo, "%d %d\n", linhas, colunas);

    // Lê o diagrama.
    for (int i = 0; i < *linhas; i++)
    {
        fscanf(arquivo, "%s\n", matriz[i]);
    }

    // Lê as palavras até o final do arquivo.
    *qtd_palavras = 0; // Inicializa o contador de palavras.
    while (fscanf(arquivo, "%s\n", palavras[*qtd_palavras]) != EOF)
    {
        (*qtd_palavras)++;
    }

    fclose(arquivo); // Fecha o arquivo.
}

// Função para escrever o arquivo de saída.
void escreverSaida(char *nomeArquivo, char matriz[][MAX], int linhas, int colunas, char palavras[][MAX], PosicaoDirecao posicoes[], int qtd_palavras)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo %s para escrita.\n", nomeArquivo);
        return;
    }

    // Escrevendo o diagrama modificado.
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            fputc(matriz[i][j], arquivo);
        }
        fputs("\n", arquivo);
    }

    fputs("\n", arquivo); // Espaço entre o diagrama e a lista de palavras.

    // Escrevendo a lista de palavras encontradas com posições e direções.
    for (int i = 0; i < qtd_palavras; i++)
    {
        if (posicoes[i].x != -1)
        { // Verificando se a palavra foi encontrada.
            fprintf(arquivo, "%s – (%d,%d):%s\n", palavras[i], posicoes[i].x, posicoes[i].y, posicoes[i].direcao);
        }
        else
        {
            fprintf(arquivo, "%s – não encontrada\n", palavras[i]);
        }
    }

    fclose(arquivo);
    printf("Arquivo de saída '%s' gerado com sucesso.\n", nomeArquivo);
}

int main()
{
    char matriz[MAX][MAX], palavras[MAX][MAX];
    int linhas, colunas, qtd_palavras;
    PosicaoDirecao posicoes[MAX];

    lerDados("entrada.txt", matriz, &linhas, &colunas, palavras, &qtd_palavras);
    buscarPalavras(matriz, linhas, colunas, palavras, qtd_palavras, posicoes);
    escreverSaida("saida.txt", matriz, linhas, colunas, palavras, posicoes, qtd_palavras);

    return 0;
}

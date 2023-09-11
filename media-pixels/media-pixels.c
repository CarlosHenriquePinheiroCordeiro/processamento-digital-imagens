#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    converteMediaEscalaCinza();
    converteMediaSaidaP3();
}

void converteMediaEscalaCinza() {
    oImg        = fopen("Fig1.ppm", "r");
    oNovaImagem = fopen("imagemCinzaConvertida.pgm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n255\n");
    char  sCor[10000]  = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 100, oImg);
    }
    short iQuantidade = 0;
    short iPixels     = 0;
    while (fgets(sCor, 10000, oImg)) {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL) {
            if (strcmp(sSplit, "\n") != 0) {
                iPixels = iPixels + atoi(sSplit);
                iQuantidade++;
                if (iQuantidade % 3 == 0) {
                    iPixels = round(iPixels/3);
                    fprintf(oNovaImagem, "%d\n", iPixels);
                    iQuantidade = 0;
                    iPixels     = 0;
                }
            }
            sSplit = strtok(NULL, " ");
        }
    }
    fclose(oNovaImagem);
    fclose(oImg);
}

void converteMediaSaidaP3() {
    oImg        = fopen("Fig4.ppm", "r");
    oNovaImagem = fopen("imagemMediaRgbP3.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    char  sCor[10000]  = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    short iQuantidade = 0;
    short iPixels     = 0;
    while (fgets(sCor, 10000, oImg)) {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL) {
            if (strcmp(sSplit, "\n") != 0) {
                iPixels = iPixels + atoi(sSplit);
                iQuantidade++;
                if (iQuantidade % 3 == 0) {
                    iPixels = round(iPixels/3);
                    fprintf(oNovaImagem, "%d %d %d\n", iPixels, iPixels, iPixels);
                    iQuantidade = 0;
                    iPixels     = 0;
                }
            }
            sSplit = strtok(NULL, " ");
        }
    }
    fclose(oNovaImagem);
    fclose(oImg);
}
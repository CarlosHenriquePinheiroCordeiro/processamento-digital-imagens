#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *oImg;
FILE *oNovaImagem;

int main() {
    realcaCinza();
    realcaRgb();
    return 0;
}

void realcaCinza() {
    //Realçando imagem em escala de cinza
    oImg = fopen("EntradaEscalaCinza.pgm", "r");
    int iMax = 0;
    int iMin = 255;
    char  sCor[10]  = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    while (fgets(sCor, 10, oImg)) {
        if (atoi(sCor) < iMin) {
            iMin = atoi(sCor);
        }
        if (atoi(sCor) > iMax) {
            iMax = atoi(sCor);
        }
    }
    fclose(oImg);
    oImg = fopen("EntradaEscalaCinza.pgm", "r");
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    oNovaImagem = fopen("imagemCinzaRealcada.pgm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n255\n");
    while (fgets(sCor, 10, oImg)) {
        fprintf(oNovaImagem, "%d\n", realcaPixel(atoi(sCor), iMax, iMin));
    }
    fclose(oNovaImagem);
    fclose(oImg);
}

void realcaRgb() {
    //Realçando imagem em escala de cinza
    oImg = fopen("EntradaRGB.ppm", "r");
    int iMaxR = 0;
    int iMinR = 255;
    int iMaxG = 0;
    int iMinG = 255;
    int iMaxB = 0;
    int iMinB = 255;
    char sCor[10000] = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    short iCor = 0;
    while (fgets(sCor, 10000, oImg)) {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL) {
            if (strcmp(sSplit, "\n") != 0) {
                iCor++;
                if (iCor == 1) {
                    if (atoi(sSplit) > iMaxR) {
                        iMaxR = atoi(sSplit);
                    }
                    if (atoi(sSplit) < iMinR) {
                        iMinR = atoi(sSplit);
                    }
                }
                if (iCor == 2) {
                    if (atoi(sSplit) > iMaxG) {
                        iMaxG = atoi(sSplit);
                    }
                    if (atoi(sSplit) < iMinG) {
                        iMinG = atoi(sSplit);
                    }
                }
                if (iCor == 3) {
                    if (atoi(sSplit) > iMaxB) {
                        iMaxB = atoi(sSplit);
                    }
                    if (atoi(sSplit) < iMinB) {
                        iMinB = atoi(sSplit);
                    }
                    iCor = 0;
                }
            }
            sSplit = strtok(NULL, " ");
        }
    }
    fclose(oImg);
    oImg = fopen("EntradaRGB.ppm", "r");
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    oNovaImagem = fopen("imagemRgbRealcada.ppm", "w");
    fprintf(oNovaImagem, "P3\n800 800\n255\n");
    iCor = 0;
    while (fgets(sCor, 10000, oImg)) {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL) {
            if (strcmp(sSplit, "\n") != 0) {
                iCor++;
                if (iCor == 1) {
                    fprintf(oNovaImagem, "%d ", realcaPixel(atoi(sSplit), iMaxR, iMinR));
                }
                if (iCor == 2) {
                    fprintf(oNovaImagem, "%d ", realcaPixel(atoi(sSplit), iMaxG, iMinG));
                }
                if (iCor == 3) {
                    fprintf(oNovaImagem, "%d \n", realcaPixel(atoi(sSplit), iMaxB, iMinB));
                    iCor = 0;
                }
            }
            sSplit = strtok(NULL, " ");
        }
    }
    
    fclose(oNovaImagem);
    fclose(oImg);
}

int realcaPixel(int iPixel, int iMax, int iMin) {
    int a = 255/(iMax-iMin);
    int b = (-1*a)*iMin;
    return (a*iPixel)+b;
}
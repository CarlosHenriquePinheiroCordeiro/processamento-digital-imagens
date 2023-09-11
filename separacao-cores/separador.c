#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    short iXImagem = 481;
    short iYImagem = 321;
    short aPixels[481][321][3];
    oImg = fopen("Fig4.ppm", "r");
    short iX = 0;
    short iY = 0;
    char  sCor[200] = "";
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 200, oImg);
    }
    while (fgets(sCor, 200, oImg)) {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL) {
            if (strcmp(sSplit, "\n") != 0) {
                if (iY > 0 && iY % iYImagem == 0) {
                    iY = 0;
                    iX++;
                }
                aPixels[iX][iY][0] = atoi(sSplit);
                sSplit = strtok(NULL, " ");
                aPixels[iX][iY][1] = atoi(sSplit);
                sSplit = strtok(NULL, " ");
                aPixels[iX][iY][2] = atoi(sSplit);
                iY++;
            }
            sSplit = strtok(NULL, " ");
        }
    }
    fclose(oImg);

    oNovaImagem = fopen("imagem1.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n", aPixels[i][j][0], 0, 0);
        }
    }
    fclose(oNovaImagem);

    oNovaImagem = fopen("imagem2.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n", 0, aPixels[i][j][1], 0);
        }
    }
    fclose(oNovaImagem);

    oNovaImagem = fopen("imagem3.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n", 0, 0, aPixels[i][j][2]);
        }
    }
    fclose(oNovaImagem);

    oNovaImagem = fopen("imagem4.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n",  aPixels[i][j][0], 255, 255);
        }
    }
    fclose(oNovaImagem);

    oNovaImagem = fopen("imagem5.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n", 255, aPixels[i][j][1], 255);
        }
    }
    fclose(oNovaImagem);

    oNovaImagem = fopen("imagem6.ppm", "w");
    fprintf(oNovaImagem, "P3\n481 321\n255\n");
    for (short i = 0; i < iXImagem; i++) {
        for (short j = 0; j < iYImagem; j++) {
            fprintf(oNovaImagem, "%d %d %d\n", 255, 255, aPixels[i][j][2]);
        }
    }
    fclose(oNovaImagem);
    
}
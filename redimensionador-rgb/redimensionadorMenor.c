#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     */
    short iTamanhoSelecionado = 1;
    short iXImagem = 800;
    short iYImagem = 800;
    short aPixels[iXImagem][iYImagem][3];
    oImg = fopen("Entrada_RGB.ppm", "r");
    short iX = 0;
    short iY = 0;
    char  sCor[200] = "";
    printf("\nMontando matriz de pixels...");
    for (short i = 0; i < 3; i++) {
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

    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     */
    short aTamanhosX[2] = {80, 480};
    short aTamanhosY[2] = {80, 320};
    short iTamanhoX = aTamanhosX[iTamanhoSelecionado];
    short iTamanhoY = aTamanhosY[iTamanhoSelecionado];

    printf("\nRedimensionando colunas...");
    oNovaImagem = fopen("redimenRgbMenor.ppm", "w");
    short iQuantidadeMedia = iYImagem / iTamanhoY;
    short iRed    = 0;
    short iGreen  = 0;
    short iBlue   = 0;
    for (iX = 0; iX < iYImagem; iX++) { //Escrevendo imagem com colunas redimensionadas
        for (iY = 0; iY < iXImagem; iY++) {
            iRed   += aPixels[iX][iY][0];
            iGreen += aPixels[iX][iY][1];
            iBlue  += aPixels[iX][iY][2];
            if ((iY+1) % iQuantidadeMedia == 0) {
                fprintf(oNovaImagem, "%d %d %d\n", iRed/iQuantidadeMedia, iGreen/iQuantidadeMedia, iBlue/iQuantidadeMedia);
                iRed    = 0;
                iGreen  = 0;
                iBlue   = 0;
            }
        }
    }
    fclose(oNovaImagem);
    oNovaImagem = fopen("redimenRgbMenor.ppm", "r");
    int aNovos[iXImagem*iTamanhoY][3];
    int iIndice = 0;
    iX = 0;
    iY = 0;
    while (fgets(sCor, 200, oNovaImagem)) {//Salvando imagem com colunas redimensionadas em um array para posteriormente redimensionar as linhas
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
    fclose(oNovaImagem);
    for (iY = 0; iY < iYImagem; iY++) {
        for (iX = 0; iX < iXImagem; iX++) {
            iRed   += aPixels[iX][iY][0];
            iGreen += aPixels[iX][iY][1];
            iBlue  += aPixels[iX][iY][2];
            if ((iX+1) % iQuantidadeMedia == 0) {
                iRed   = iRed/iQuantidadeMedia;
                iGreen = iGreen/iQuantidadeMedia;
                iBlue  = iBlue/iQuantidadeMedia;
                aPixels[(((iX+1))/iQuantidadeMedia)-1][iY][0] = iRed;
                aPixels[(((iX+1))/iQuantidadeMedia)-1][iY][1] = iGreen;
                aPixels[(((iX+1))/iQuantidadeMedia)-1][iY][2] = iBlue;
                iRed    = 0;
                iGreen  = 0;
                iBlue   = 0;
            }
        }
    }
    printf("\nMontando nova imagem...");
    oNovaImagem = fopen("redimenRgbMenor.ppm", "w");
    fprintf(oNovaImagem, "P3\n");
    /**
     * (0) 10x Menor
     * (1) Padrão 480x320
     */
    char aTamanhosResolucao[10][10] = {"80 80","480 320"};
    fprintf(oNovaImagem, aTamanhosResolucao[iTamanhoSelecionado]);
    fprintf(oNovaImagem, "\n255\n");
    int iContador = 0;
    iX = 0;
    iY = 0;
    while (iContador < iTamanhoX*iTamanhoY) {
        for (iY = 0; iY < iTamanhoY; iY++) {
            iContador++;
            fprintf(oNovaImagem, "%d\n%d\n%d\n", aPixels[iX][iY][0], aPixels[iX][iY][1], aPixels[iX][iY][2]);
        }
        iX++;
    }
    fclose(oNovaImagem);
    fclose(oImg);
}
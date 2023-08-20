#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oNovaImagem;
FILE *oNovaImagem;

void main() {
    /**
     * (0) Padrão 720p (HD)
     * (1) Padrão 1080p Full HD 
     * (2) Padrão 4k
     * (3) Padrão 8k
     */
    short iTamanhoSelecionado = 0;
    short iXImagem = 800;
    short iYImagem = 800;
    short aPixels[iXImagem][iYImagem][3];
    oImg = fopen("Entrada_RGB.ppm", "r");
    short iX = 0;
    short iY = 0;
    char  sCor[200] = "";
    short iTeste = 0;
    printf("\nMontando matriz de pixels...");
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

    /**
     * (0) Padrão 720p (HD)
     * (1) Padrão 1080p Full HD 
     * (2) Padrão 4k
     * (3) Padrão 8k
     */
    short aTamanhosX[4] = {720, 1080, 2160, 4320};
    short aTamanhosY[4] = {1280, 1920, 3840, 7680};
    short iTamanhoX = aTamanhosX[iTamanhoSelecionado];
    short iTamanhoY = aTamanhosY[iTamanhoSelecionado];

    printf("\nRedimensionando imagem...");
    oNovaImagem = fopen("redimenRgbMaior.ppm", "w");
    
    fprintf(oNovaImagem, "P3\n");
    /**
     * (0) Padrão 720p (HD)
     * (1) Padrão 1080p Full HD 
     * (2) Padrão 4k
     * (3) Padrão 8k
     */
    char aTamanhosResolucao[10][10] = {"1280 720","1920 1080","3840 2160","7680 4320"};
    fprintf(oNovaImagem, aTamanhosResolucao[iTamanhoSelecionado]);
    fprintf(oNovaImagem, "\n255\n");

    short iRed     = 0;
    short iGreen   = 0;
    short iBlue    = 0;
    int iFaltantes = iTamanhoX;
    if (iTamanhoX < iXImagem) { //Diminuir linhas
        iFaltantes = iXImagem - iTamanhoX;
    }
    for (iX = 0; iX < iXImagem; iX++) {
        short iCores  = 0;
        for (iY = 0; iY < iYImagem; iY++) {
            if (aPixels[iX][iY][0] != iRed || aPixels[iX][iY][1] != iGreen || aPixels[iX][iY][2] != iBlue) {
                iCores++;
                iRed    = aPixels[iX][iY][0];
                iGreen  = aPixels[iX][iY][1];
                iBlue   = aPixels[iX][iY][2];
            }
        }
        short iPixels = round((iTamanhoY-iYImagem)/iCores);
        int iContador = 0;
        iRed          = 0;
        iGreen        = 0;
        iBlue         = 0;
        short iVezes  = 1;
        if (iTamanhoX > iXImagem) { //Aumentar as linhas
            if (iX % 2 != 0 && iFaltantes > 0) {
                iVezes = round(iTamanhoX/iXImagem)+1;
            }
            if (iFaltantes < 1) {
                break;
            }
        }
        else { //Diminuir as linhas
            if (iFaltantes > 0 && iX % 5 == 0) {
                iVezes = 0;
                iFaltantes--;
            }
        }
        for (short i = 0; i < iVezes; i++) {
            for (iY = 0; iY < iYImagem; iY++) {
                if (aPixels[iX][iY][0] != iRed || aPixels[iX][iY][1] != iGreen || aPixels[iX][iY][2] != iBlue) {
                    iRed    = aPixels[iX][iY][0];
                    iGreen  = aPixels[iX][iY][1];
                    iBlue   = aPixels[iX][iY][2];
                    for (int p = 0; p < iPixels; p++) {
                        fprintf(oNovaImagem, "%d\n%d\n%d\n", iRed, iGreen, iBlue);
                        iContador += 3;
                    }
                }
                fprintf(oNovaImagem, "%d\n%d\n%d\n", iRed, iGreen, iBlue);
                iContador += 3;
            }
            while (iContador < iTamanhoY*3) {
                fprintf(oNovaImagem, "%d\n%d\n%d\n", iRed, iGreen, iBlue);
                iContador += 3;
            }
            iContador = 0;
        }
        if (iTamanhoX > iXImagem) { //Aumentar as linhas
            iFaltantes -= iVezes;
        }
    }
    fclose(oNovaImagem);
}
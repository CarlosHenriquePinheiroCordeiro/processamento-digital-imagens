#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
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
    for (short i = 0; i < 3; i++) //Ignorando valores de cabeçalho, resolução e tonalidade
    {
        fgets(sCor, 200, oImg);
    }
    while (fgets(sCor, 200, oImg))
    {
        char *sSplit = strtok(sCor, " ");
        while (sSplit != NULL)
        {
            if (strcmp(sSplit, "\n") != 0) 
            {
                if (iY > 0 && iY % iYImagem == 0)
                {
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

    printf("\nRedimensionando colunas...");
    oNovaImagem = fopen("redimenY.ppm", "w");
    short iRed    = 0;
    short iGreen  = 0;
    short iBlue   = 0;
    for (iX = 0; iX < iXImagem; iX++)
    {
        short iPixels = 0;
        short iIndice = 0;
        for (iY = 0; iY < iYImagem; iY++)
        {
            if (aPixels[iX][iY][0] != iRed || aPixels[iX][iY][1] != iGreen || aPixels[iX][iY][2] != iBlue)
            {
                iPixels = (iTamanhoY*iPixels)/iYImagem;
                for (short p = 0; p < iPixels; p++)
                {
                    iIndice++;
                    fprintf(oNovaImagem, "%d %d %d ", iRed, iGreen, iBlue);
                }
                iRed    = aPixels[iX][iY][0];
                iGreen  = aPixels[iX][iY][1];
                iBlue   = aPixels[iX][iY][2];
                iPixels = 0;
                continue;
            }
            iPixels++;
        }
        for (iIndice; iIndice < iYImagem; iIndice++)
        {
            fprintf(oNovaImagem, "%d %d %d ", iRed, iGreen, iBlue);
        }
        fprintf(oNovaImagem, "\n");
    }
    fclose(oNovaImagem);

    oImg = fopen("Entrada_RGB.ppm", "r");
    oNovaImagem = fopen("redimenY.ppm", "r");
    printf("\nRedimensionando linhas...");
    if (iTamanhoX > iXImagem) //Aumentar linhas
    {
        int   iLimite = iYImagem*3;
        int   iIndice = 0;
        short iLinhas = floor(iTamanhoX/iXImagem);
        short aPixelsLinha[iLimite];
        while (fgets(sCor, 200, oImg))
        {
            if (iIndice == iLimite)
            {
                break;
            }
            char *sSplit = strtok(sCor, " ");
            while (sSplit != NULL)
            {
                if (strcmp(sSplit, "\n") != 0) 
                {
                    if (iY > 0 && iY % iYImagem == 0)
                    {
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
    }
    else//Diminuir linhas
    {

    }
    // fclose(oNovaImagem);
    fclose(oImg);
}
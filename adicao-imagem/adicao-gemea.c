#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *oImg;
FILE *oImg2;
FILE *oNovaImagem;

void main() {
    oImg           = fopen("Entrada_EscalaCinza.pgm", "r");
    oImg2          = fopen("Entrada_EscalaCinza2.pgm", "r");
    oNovaImagem    = fopen("imagemGemeaAdicionada.pbm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n255\n");
    char sCor[10]  = "";
    char sCor2[10] = "";
    int iCor       = 0;
    int iCor2      = 0;
    for (short i = 0; i < 3; i++) {
        fgets(sCor , 10, oImg);
        fgets(sCor2, 10, oImg2);
    }
    while (fgets(sCor, 10, oImg))
    {
        iCor  = atoi(sCor);
        fgets(sCor2, 10, oImg2);
        iCor2 = atoi(sCor2);
        if (iCor != iCor2) {
            iCor = iCor2;
        }
        fprintf(oNovaImagem, "%d\n", iCor);
    }
    fclose(oImg);
    fclose(oImg2);
    fclose(oNovaImagem);
}
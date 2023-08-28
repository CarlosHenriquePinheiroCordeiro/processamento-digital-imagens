#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *oImg;
FILE *oNovaImagem;

void main() {
    oImg        = fopen("Entrada_EscalaCinza.pgm", "r");
    oNovaImagem = fopen("imagemTonalidadeDiminuida.pgm", "w");
    fprintf(oNovaImagem, "P2\n800 800\n31\n");
    char  sCor[10]  = "";
    printf("\nContando pixels...");
    for (short i = 0; i < 3; i++) { //Ignorando valores de cabeçalho, resolução e tonalidade
        fgets(sCor, 10, oImg);
    }
    while (fgets(sCor, 10, oImg))
    {
        fprintf(oNovaImagem, "%d\n", diminuiTonalidadePixel(atoi(sCor)));
    }
    fclose(oNovaImagem);
    fclose(oImg);
}

int diminuiTonalidadePixel(int iPixel) {
    return round((iPixel*31)/255);
}
#include <stdio.h>
#include <stdlib.h>

int caracter = 219;

int main(void) {
    int A[5][29];
    int B[2][2];
    int C1[4][1], C2[1][4];
    int D1[3][2], D2[2][3], D3[3][2], D4[2][3];
    int E1[3][2], E2[3][2], E3[2][3], E4[2][3];
    int F1[3][5], F2[3][5], F3[3][5], F4[3][5], F5[3][5],
            F6[3][5], F7[3][5], F8[3][5];
    int i, j;
    int a, b, c1, c2, d1, d2, d3, d4, e1, e2, e3, e4, f1, f2,
            f3, f4, f5, f6, f7, f8;

    printf("                        BIENVENIDO A\n\n");

    A[0][0] = printf("%c%c", caracter, caracter);
    A[0][1] = printf("%c%c", caracter, caracter);
    A[0][2] = printf("%c%c", caracter, caracter);
    A[0][3] = printf("%c%c", caracter, caracter);
    A[0][4] = printf("%c%c", caracter, caracter);
    A[0][5] = printf("''");
    A[0][6] = printf("%c%c", caracter, caracter);
    A[0][7] = printf("%c%c", caracter, caracter);
    A[0][8] = printf("%c%c", caracter, caracter);
    A[0][9] = printf("''");
    A[0][10] = printf("%c%c", caracter, caracter);
    A[0][11] = printf("%c%c", caracter, caracter);
    A[0][12] = printf("%c%c", caracter, caracter);
    A[0][13] = printf("%c%c", caracter, caracter);
    A[0][14] = printf("%c%c", caracter, caracter);
    A[0][15] = printf("''");
    A[0][16] = printf("%c%c", caracter, caracter);
    A[0][17] = printf("%c%c", caracter, caracter);
    A[0][18] = printf("%c%c", caracter, caracter);
    A[0][19] = printf("%c%c", caracter, caracter);
    A[0][20] = printf("''");
    A[0][21] = printf("%c%c", caracter, caracter);
    A[0][22] = printf("%c%c", caracter, caracter);
    A[0][23] = printf("%c%c", caracter, caracter);
    A[0][24] = printf("''");
    A[0][25] = printf("%c%c", caracter, caracter);
    A[0][26] = printf("%c%c", caracter, caracter);
    A[0][27] = printf("%c%c", caracter, caracter);
    A[0][28] = printf("%c%c\n", caracter, caracter);
    A[1][0] = printf("''");
    A[1][1] = printf("''");
    A[1][2] = printf("%c%c", caracter, caracter);
    A[1][3] = printf("''");
    A[1][4] = printf("''");
    A[1][5] = printf("''");
    A[1][6] = printf("%c%c", caracter, caracter);
    A[1][7] = printf("''");
    A[1][8] = printf("''");
    A[1][9] = printf("''");
    A[1][10] = printf("''");
    A[1][11] = printf("''");
    A[1][12] = printf("%c%c", caracter, caracter);
    A[1][13] = printf("''");
    A[1][14] = printf("''");
    A[1][15] = printf("''");
    A[1][16] = printf("%c%c", caracter, caracter);
    A[1][17] = printf("''");
    A[1][18] = printf("''");
    A[1][19] = printf("%c%c", caracter, caracter);
    A[1][20] = printf("''");
    A[1][21] = printf("''");
    A[1][22] = printf("%c%c", caracter, caracter);
    A[1][23] = printf("''");
    A[1][24] = printf("''");
    A[1][25] = printf("%c%c", caracter, caracter);
    A[1][26] = printf("''");
    A[1][27] = printf("''");
    A[1][28] = printf("''\n");
    A[2][0] = printf("''");
    A[2][1] = printf("''");
    A[2][2] = printf("%c%c", caracter, caracter);
    A[2][3] = printf("''");
    A[2][4] = printf("''");
    A[2][5] = printf("''");
    A[2][6] = printf("%c%c", caracter, caracter);
    A[2][7] = printf("%c%c", caracter, caracter);
    A[2][8] = printf("''");
    A[2][9] = printf("''");
    A[2][10] = printf("''");
    A[2][11] = printf("''");
    A[2][12] = printf("%c%c", caracter, caracter);
    A[2][13] = printf("''");
    A[2][14] = printf("''");
    A[2][15] = printf("''");
    A[2][16] = printf("%c%c", caracter, caracter);
    A[2][17] = printf("%c%c", caracter, caracter);
    A[2][18] = printf("%c%c", caracter, caracter);
    A[2][19] = printf("''");
    A[2][20] = printf("''");
    A[2][21] = printf("''");
    A[2][22] = printf("%c%c", caracter, caracter);
    A[2][23] = printf("''");
    A[2][24] = printf("''");
    A[2][25] = printf("%c%c", caracter, caracter);
    A[2][26] = printf("%c%c", caracter, caracter);
    A[2][27] = printf("%c%c", caracter, caracter);
    A[2][28] = printf("%c%c\n", caracter, caracter);
    A[3][0] = printf("''");
    A[3][1] = printf("''");
    A[3][2] = printf("%c%c", caracter, caracter);
    A[3][3] = printf("''");
    A[3][4] = printf("''");
    A[3][5] = printf("''");
    A[3][6] = printf("%c%c", caracter, caracter);
    A[3][7] = printf("''");
    A[3][8] = printf("''");
    A[3][9] = printf("''");
    A[3][10] = printf("''");
    A[3][11] = printf("''");
    A[3][12] = printf("%c%c", caracter, caracter);
    A[3][13] = printf("''");
    A[3][14] = printf("''");
    A[3][15] = printf("''");
    A[3][16] = printf("%c%c", caracter, caracter);
    A[3][17] = printf("''");
    A[3][18] = printf("''");
    A[3][19] = printf("%c%c", caracter, caracter);
    A[3][20] = printf("''");
    A[3][21] = printf("''");
    A[3][22] = printf("%c%c", caracter, caracter);
    A[3][23] = printf("''");
    A[3][24] = printf("''");
    A[3][25] = printf("''");
    A[3][26] = printf("''");
    A[3][27] = printf("''");
    A[3][28] = printf("%c%c\n", caracter, caracter);
    A[4][0] = printf("''");
    A[4][1] = printf("''");
    A[4][2] = printf("%c%c", caracter, caracter);
    A[4][3] = printf("''");
    A[4][4] = printf("''");
    A[4][5] = printf("''");
    A[4][6] = printf("%c%c", caracter, caracter);
    A[4][7] = printf("%c%c", caracter, caracter);
    A[4][8] = printf("%c%c", caracter, caracter);
    A[4][9] = printf("''");
    A[4][10] = printf("''");
    A[4][11] = printf("''");
    A[4][12] = printf("%c%c", caracter, caracter);
    A[4][13] = printf("''");
    A[4][14] = printf("''");
    A[4][15] = printf("''");
    A[4][16] = printf("%c%c", caracter, caracter);
    A[4][17] = printf("''");
    A[4][18] = printf("''");
    A[4][19] = printf("%c%c", caracter, caracter);
    A[4][20] = printf("''");
    A[4][21] = printf("%c%c", caracter, caracter);
    A[4][22] = printf("%c%c", caracter, caracter);
    A[4][23] = printf("%c%c", caracter, caracter);
    A[4][24] = printf("''");
    A[4][25] = printf("%c%c", caracter, caracter);
    A[4][26] = printf("%c%c", caracter, caracter);
    A[4][27] = printf("%c%c", caracter, caracter);
    A[4][28] = printf("%c%c", caracter, caracter);

    printf("\n\n                     ☭ Компании СССР ☭");
    printf("\n\n\n\n");

    printf("                 ____________________________\n");
    printf("                |                            |\n");
    printf("                |  Prisione ↲ para comenzar  |\n");
    printf("                |____________________________|\n");
    printf("                |                            |\n");
    printf("                |         Puntuacion:        |\n");
    printf("                |____________________________|\n");
    printf("                |                            |\n");
    printf("                |      Tiempo de Juego:      |\n");
    printf("                |____________________________|\n\n\n");

    scanf("");

    printf("              ____________________________________\n\n");

    b = B[0][0] = printf("%c%c", caracter, caracter),
    B[0][1] = printf("%c%c\n\n", caracter, caracter),
    B[1][0] = printf("%c%c", caracter, caracter),
    B[1][1] = printf("%c%c\n\n", caracter, caracter);

    c1 = C1[0][0] = printf("%c%c", caracter, caracter),
    C1[1][0] = printf("%c%c", caracter, caracter),
    C1[2][0] = printf("%c%c", caracter, caracter),
    C1[3][0] = printf("%c%c\n\n", caracter, caracter);

    c2 = C2[0][0] = printf("%c%c\n\n", caracter, caracter),
    C2[0][1] = printf("%c%c\n\n", caracter, caracter),
    C2[0][2] = printf("%c%c\n\n", caracter, caracter),
    C2[0][3] = printf("%c%c\n\n", caracter, caracter);

    d1 = D1[0][0] = printf("''"),
    D1[0][1] = printf("%c%c", caracter, caracter),
    D1[1][0] = printf("''\n"),
    D1[1][1] = printf("%c%c", caracter, caracter),
    D1[2][0] = printf("%c%c", caracter, caracter),
    D1[2][1] = printf("%c%c\n\n", caracter, caracter);

    d2 = D2[0][0] = printf("%c%c", caracter, caracter),
    D2[0][1] = printf("''\n"),
    D2[0][2] = printf("%c%c", caracter, caracter),
    D2[1][0] = printf("%c%c\n\n", caracter, caracter),
    D2[1][1] = printf("%c%c", caracter, caracter),
    D2[1][2] = printf("''\n\n");

    d3 = D3[0][0] = printf("%c%c", caracter, caracter),
    D3[0][1] = printf("%c%c", caracter, caracter),
    D3[1][0] = printf("%c%c\n\n", caracter, caracter),
    D3[1][1] = printf("''"),
    D3[2][0] = printf("%c%c", caracter, caracter),
    D3[2][1] = printf("''\n\n");

    d4 = D4[0][0] = printf("''"),
    D4[0][1] = printf("%c%c\n\n", caracter, caracter),
    D4[0][2] = printf("%c%c", caracter, caracter),
    D4[1][0] = printf("%c%c\n\n", caracter, caracter),
    D4[1][1] = printf("''");
    D4[1][2] = printf("%c%c\n\n", caracter, caracter);

    e1 = E1[0][0] = printf("''"),
    E1[0][1] = printf("%c%c", caracter, caracter),
    E1[0][2] = printf("%c%c\n\n", caracter, caracter),
    E1[1][0] = printf("%c%c", caracter, caracter),
    E1[1][1] = printf("%c%c", caracter, caracter),
    E1[1][2] = printf("''\n\n");

    e2 = E2[0][0] = printf("%c%c", caracter, caracter),
    E2[0][1] = printf("%c%c", caracter, caracter),
    E2[0][2] = printf("''\n"),
    E2[1][0] = printf("''"),
    E2[1][1] = printf("%c%c", caracter, caracter),
    E2[1][2] = printf("%c%c\n\n", caracter, caracter);

    e3 = E3[0][0] = printf("''"),
    E3[0][1] = printf("%c%c\n\n", caracter, caracter),
    E3[1][0] = printf("%c%c", caracter, caracter),
    E3[1][1] = printf("%c%c\n\n", caracter, caracter),
    E3[2][0] = printf("%c%c", caracter, caracter),
    E3[2][1] = printf("''\n\n");

    e4 = E4[0][0] = printf("%c%c", caracter, caracter),
    E4[0][1] = printf("''\n"),
    E4[0][2] = printf("%c%c", caracter, caracter),
    E4[1][0] = printf("%c%c\n\n", caracter, caracter),
    E4[1][1] = printf("''"),
    E4[1][2] = printf("%c%c\n\n", caracter, caracter);
    return 0;
}
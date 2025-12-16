#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <pthread.h>
#include "FramePrinter.h"
//
// Created by isald on 11/18/2023.
//


char sigFig=0;
int semaforo = 0;
int coordsFigur[3] = {0,0, 0}; //The third element refers to the rotation.
int juegoContinua=1;
int puntuacion=0;
int lineasEliminadas = 0;
unsigned int timer = 750;

void reiniciar(char gridMatrix[24][10][2]) {
    for(int i=0; i<24; i++) {
        for(int j=0; j<10; j++) {
            gridMatrix[i][j][0] = 0;
            gridMatrix[i][j][1] = 0;
        }
    }
    sigFig=0;
    semaforo = 0;
    coordsFigur[0] = 0;
    coordsFigur[1] = 0;
    coordsFigur[2] = 0;
    juegoContinua=1;
    puntuacion=0;
    timer = 750;
}

typedef struct gridMatrixPlusMutex {
    //char (*gridM)[24][10][2];
    char gridMatrix[24][10][2];
    pthread_mutex_t *mutex;
} gridPlusMutex;

void puntos(char gridMatrix[24][10][2]) {
    int punts = 0;
    for(int q=0; q<4; q++) { //Comprobacion.
        for(int i = 24; i>=4; --i) {
            int linea=0;
            for(int j = 0; j<10; j++) {
                if(gridMatrix[i][j][0] != 0 && gridMatrix[i][j][0] != 'A') {
                    linea++;
                }
            }
            if(linea == 10) {
                for(int o = i; o>4; o--) {
                    for (int j = 0; j < 10; j++) {
                        gridMatrix[o][j][0] = gridMatrix[o-1][j][0];
                    }
                }
                punts += 100;
                lineasEliminadas++;
                timer-=50;
            }
        }
    }

    if(punts != 0) {
        punts = (punts/100) * punts;
    }
    puntuacion += punts + 1;
}

void generarSiguienteFigura() { //Generates a new random figure and saves it in sigFig.
    srand(time(NULL));
    int randNum = rand()%7;
    switch (randNum) {
        case 1:
            sigFig = 'I';
            break;
        case 2:
            sigFig = 'L';
            break;
        case 3:
            sigFig = 'J';
            break;
        case 4:
            sigFig = 'Z';
            break;
        case 5:
            sigFig = 'S';
            break;
        case 6:
            sigFig = 'T';
            break;
        default: //AKA: case 7:
            sigFig = 'O';
    }
    //sigFig = 'T';
}

void siguienteFigura(char gridMatrix[24][10][2]) {
    //No block should be active now.
    for(int i = 0; i<24; i++) {
        for(int j =0; j<10; j++) {
            gridMatrix[i][j][1] = 0;
        }
    }

    coordsFigur[0] = 0;
    coordsFigur[1] = 5;
    coordsFigur[2] = 1;
    switch (sigFig) {
        case 'I':
            for(int i = 0; i<4; i++) {
                gridMatrix[i][coordsFigur[1]][0] = sigFig;
                gridMatrix[i][coordsFigur[1]][1] = 'A';
            }
            break;
        case 'L':
            for(int i = 0; i<3; i++) {
                gridMatrix[i][coordsFigur[1]][0] = sigFig;
                gridMatrix[i][coordsFigur[1]][1] = 'A';
            }
            gridMatrix[2][coordsFigur[1]+1][0] = sigFig;
            gridMatrix[2][coordsFigur[1]+1][1] = 'A';
            coordsFigur[1] = 4;
            break;
        case 'J':
            for(int i = 0; i<3; i++) {
                gridMatrix[i][coordsFigur[1]+1][0] = sigFig;
                gridMatrix[i][coordsFigur[1]+1][1] = 'A';
            }
            gridMatrix[2][coordsFigur[1]][0] = sigFig;
            gridMatrix[2][coordsFigur[1]][1] = 'A';
            break;
        case 'Z':
            for(int i = 0; i<2; i++) {
                for(int j=0; j<2; j++) {
                    if(i==1) j++;
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = sigFig;
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 'A';
                    if(i==1) j--;
                }
            }
            break;
        case 'S':
            for(int i = 0; i<2; i++) {
                for(int j=0; j<2; j++) {
                    if(i==0) j++;
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = sigFig;
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 'A';
                    if(i==0) j--;
                }
            }
            break;
        case 'T':
            gridMatrix[coordsFigur[0]][coordsFigur[1]+1][0] = sigFig;
            gridMatrix[coordsFigur[0]][coordsFigur[1]+1][1] = 'A';
            for(int i = 0; i<3; i++) {
                gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][0] = sigFig;
                gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][1] = 'A';
            }
            break;
        case 'O':
            for(int i = 0; i<2; i++) {
                for(int j=0; j<2; j++) {
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = sigFig;
                    gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 'A';
                }
            }
            break;
    }
    generarSiguienteFigura(); //Because we already used the figure that's in sigFig we generate a new figure.
}

int comprobarJuego(char gridMatrix[24][10][2], char modo) {
    //Comprobar si las figuras pueden seguir bajando.
    switch(modo) {
        case 'B':
            for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 10; j++) {
                    if (gridMatrix[i][j][1] == 'A') {
                        if (i == 23 || !(gridMatrix[i + 1][j][0] == 0 ||
                                         (gridMatrix[i + 1][j][0] != 0 && gridMatrix[i + 1][j][1] == 'A'))) {
                            //gridMatrix[i+1][j][1] = 0;
                            return 0; //Means there is a stop so the piece should stop falling.
                        }
                    }
                }
            }
            break;
        case 'D':
            for (int i = 0; i < 24; i++) {
                for (int j = 0; j < 10; j++) {
                    if (gridMatrix[i][j][1] == 'A') {
                        if (!(gridMatrix[i][j + 1][0] == 0 ||
                              (gridMatrix[i][j + 1][0] != 0 && gridMatrix[i][j + 1][1] == 'A')) || j == 9) {
                            //gridMatrix[i][j+1][1] = 0;
                            return 0; //Means there is a stop so the piece should stop moving to the right.
                        }
                    }
                }
            }
            break;
        case 'A':
            for (int i = 0; i < 24; i++) {
                for (int j = 10; j >= 0; --j) {
                    if (gridMatrix[i][j][1] == 'A') {
                        if (!(gridMatrix[i][j - 1][0] == 0 ||
                              (gridMatrix[i][j - 1][0] != 0 && gridMatrix[i][j - 1][1] == 'A')) || j == 0) {
                            //gridMatrix[i][j+1][1] = 0;
                            return 0; //Means there is a stop so the piece should stop moving to the right.
                        }
                    }
                }
            }
            break;
        case 'O': //We do nothing ;)
            break;
        case 'I':
            if (coordsFigur[2] == 1) {
                if (coordsFigur[1] > 6) {
                    return 0; //Means you can't put horizontal the figura.
                }
                for (int i = 0; i < 4; i++) {
                    if (gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] != 0 &&
                        gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] != 'A') {
                        return 0; //Means you can't rotate the figure.
                    }
                }
            } else {
                if (coordsFigur[0] > 20) {
                    return 0; //Means you can't put straight the figure.
                }
                for (int i = 0; i < 4; i++) {
                    if (gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate the figure.
                    }
                }
            }
            break;
        case 'S': {//Llaves usadas para poder declarar temp.
            if ((coordsFigur[2] == 2 && coordsFigur[1] > 7) || (coordsFigur[1] == 1 && coordsFigur[0] > 21)) {
                return 0; //Means you can't rotate the figure.
            }
            int temp = 0;
            if (coordsFigur[2] == 1) {
                for (int i = 0; i < 2; i++, temp++) {
                    if(gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                }
            } else {
                for (int i = 0; i < 2; i++, temp++) {
                    if(gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                }
            }
        }
            break;
        case 'Z': {//Llaves usadas para poder declarar temp.
            if ((coordsFigur[2] == 2 && coordsFigur[1] > 7) || (coordsFigur[1] == 1 && coordsFigur[0] > 21)) {
                return 0; //Means you can't rotate the figure.
            }
            int temp = 0;
            if (coordsFigur[2] == 1) {
                for (int i = 0; i < 2; i++, temp++) {
                    if(gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                }
            } else {
                for (int i = 0; i < 2; i++, temp++) {
                    if( gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                }
            }
        }
            break;
        case 'J':
            if((coordsFigur[2] == 1 || coordsFigur[2] == 3) && coordsFigur[1] > 7) {
                return 0; //Means you can't rotate the figure.
            } else if ((coordsFigur[2] == 2 || coordsFigur[2] == 4) && coordsFigur[0] > 21) {
                return 0; //Means you can't rotate the figure.
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0]][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 2:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0]][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 3:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 2][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 2][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 4:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 2][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + 2][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
            }
            break;
        case 'L':
            if((coordsFigur[2] == 1 || coordsFigur[2] == 3) && coordsFigur[1] > 7) {
                return 0; //Means you can't rotate the figure.
            } else if ((coordsFigur[2] == 2 || coordsFigur[2] == 4) && coordsFigur[0] > 21) {
                return 0; //Means you can't rotate the figure.
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 2:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0]][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 3:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0]][coordsFigur[1] + 2][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + 2][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 4:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1]!= 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 2][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + 2][coordsFigur[1] + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
            }
            break;
        case 'T':
            if((coordsFigur[2] == 2 || coordsFigur[2] == 4) && coordsFigur[1] > 7) {
                return 0; //Means you can't rotate the figure.
            } else if ((coordsFigur[2] == 1 || coordsFigur[2] == 3) && coordsFigur[0] > 21) {
                return 0; //Means you can't rotate the figure.
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 2:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 3:
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0] + i][coordsFigur[1] + 1][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1]][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1]][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    break;
                case 4:
                    if( gridMatrix[coordsFigur[0]][coordsFigur[1] + 1][0] != 0 && gridMatrix[coordsFigur[0]][coordsFigur[1] + 1][1] != 'A') {
                        return 0; //Can't rotate.
                    }
                    for (int i = 0; i < 3; i++) {
                        if( gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][0] != 0 && gridMatrix[coordsFigur[0] + 1][coordsFigur[1] + i][1] != 'A') {
                            return 0; //Can't rotate.
                        }
                    }
                    break;
            }
            break;
    }
    /*if( paste != 0 && paste != 'A') {
        return 0; //Can't rotate.
    }*/
    return 1;
}

void *bajarFiguras(void *gridPMatrix) {
    gridPlusMutex *gpm = (gridPlusMutex*)gridPMatrix; //gpm will be a pointer that it's pointing in the same direction as gridPMatrix.

    /*color(36,33);
    for(int o=0; o<24; o++) {
        for(int p = 0; p<10; p++) {
            if(((*gpm).gridMatrix[o][p][0]) == 0) {
                printf("0    ");
            } else {
                printf("%c   ", (*gpm).gridMatrix[o][p][0]);
            }
        }
        printf("\n ");
    }*/

    while(pthread_mutex_trylock(gpm->mutex) != 0) {Sleep(2);}

    //printf("LOCKED");
    switch (comprobarJuego(gpm->gridMatrix, 'B')) {
        case 0:
            //printf("Entra");
            if(coordsFigur[0] < 4) {
                printf("ALTOO JA");
                juegoContinua = 0; //Means the game is over.
            }
            generarSiguienteFigura();
            siguienteFigura(gpm->gridMatrix);
            puntos(gpm->gridMatrix);
            break;

        case 1:
            for(int i=22; i>=0; i--) {
                for(int j=9; j>=0; j--) {
                    if(gpm->gridMatrix[i][j][1] == 'A') {
                        gpm->gridMatrix[i+1][j][0] = gpm->gridMatrix[i][j][0];
                        gpm->gridMatrix[i+1][j][1] = 'A';

                        gpm->gridMatrix[i][j][0] = 0;
                        gpm->gridMatrix[i][j][1] = 0;
                    }
                }
            }
            coordsFigur[0]++; //Updating the row the figure is in.
            //return 1;
    }
    pthread_mutex_unlock((*gpm).mutex);
    fflush(stdin);
    return NULL;
}

void moverFigura(void* gridPMutex, char movimiento) {
    gridPlusMutex *gpm = (gridPlusMutex*) gridPMutex;

    while(pthread_mutex_trylock(gpm->mutex) != 0) {Sleep(2);}

    for(int i=0; i<24; i++) {
        for(int j=0; j<10; j++) {
            if(gpm->gridMatrix[i][j][1] == 'A')
            {
                char mov = movimiento;
                if(mov == 'I') {
                    mov = 'A'; //Means it's going to the left.
                }
                if(!comprobarJuego(gpm->gridMatrix, mov)) {
                    pthread_mutex_unlock((*gpm).mutex);
                    return;
                }
            }
        }
    }

    if(movimiento == 'I') {
        coordsFigur[1]--; //We update the coords of the figure.
    } else {
        coordsFigur[1]++; //We update the coords of the figure.
    }

    for(int i=0; i<24;i++) {
        if (movimiento == 'I') {
            for (int j = 0; j < 10; j++) {
                if (gpm->gridMatrix[i][j][1] == 'A') {
                    gpm->gridMatrix[i][j - 1][0] = gpm->gridMatrix[i][j][0];
                    gpm->gridMatrix[i][j - 1][1] = 'A';

                    gpm->gridMatrix[i][j][0] = 0;
                    gpm->gridMatrix[i][j][1] = 0;
                }
            }
        } else {
            for (int j = 9; j >= 0; j--) {
                if (gpm->gridMatrix[i][j][1] == 'A') {
                    gpm->gridMatrix[i][j + 1][0] = gpm->gridMatrix[i][j][0];
                    gpm->gridMatrix[i][j + 1][1] = 'A';

                    gpm->gridMatrix[i][j][0] = 0;
                    gpm->gridMatrix[i][j][1] = 0;
                }
            }
        }
    }
    pthread_mutex_unlock((*gpm).mutex);
}

void rotar(void *gridPMutex) {
    gridPlusMutex *gpm = (gridPlusMutex*) gridPMutex;

    while(pthread_mutex_trylock(gpm->mutex) != 0) {Sleep(2);}

    if(!comprobarJuego(gpm->gridMatrix, sigFig)) {
        pthread_mutex_unlock(gpm->mutex);
        return;
    }
    switch(sigFig) {
        case 'O': //We do nothing ;)
            break;
        case 'I':
            if (coordsFigur[2] == 1) {
                for (int i = 0; i < 4; i++) {
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] = 0;
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1] = 0;
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] = 'A';
                }
                coordsFigur[2] = 2;
            } else {
                for (int i = 0; i < 4; i++) {
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i][0] = 0;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i][1] = 0;
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1]][1] = 'A';
                }
                coordsFigur[2] = 1;
            }
            break;

        case 'S': {//Llaves usadas para poder declarar temp.
            int temp = 0;
            if (coordsFigur[2] == 1) {
                for (int i = 0; i < 2; i++, temp++) {
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][0] = 0;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][1] = 0;
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][1] = 'A';
                }
                coordsFigur[2] = 2;
            } else {
                for (int i = 0; i < 2; i++, temp++) {
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1] + i + 1][1] = 'A';
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][0] = 0;
                    gpm->gridMatrix[coordsFigur[0] + i + temp][coordsFigur[1] + i][1] = 0;
                }
                coordsFigur[2] = 1;
            }
        }
            break;
        case 'Z': {//Llaves usadas para poder declarar temp.
            int temp = 0;
            if (coordsFigur[2] == 1) {
                for (int i = 0; i < 2; i++, temp++) {
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][1] = 'A';
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][0] = 0;
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][1] = 0;
                }
                coordsFigur[2] = 2;
            } else {
                for (int i = 0; i < 2; i++, temp++) {
                    //Clearing 'old' position.
                    gpm->gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][0] = 0;
                    gpm->gridMatrix[coordsFigur[0] + i + 1][coordsFigur[1]][1] = 0;
                    //Setting New Position.
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0] + i][coordsFigur[1] + i + temp][1] = 'A';
                }
                coordsFigur[2] = 1;
            }
        }
            break;
        case 'J':
            //Erasing the piece.
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if(gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] == 'A') {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = 0;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 0;
                    }
                }
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]][1] = 'A';
                    coordsFigur[2] = 2;
                    break;
                case 2:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+1][1] = 'A';
                    coordsFigur[2] = 3;
                    break;
                case 3:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+2][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+2][1] = 'A';
                    coordsFigur[2] = 4;
                    break;
                case 4:
                    for(int i = 0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+2][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+2][coordsFigur[1]][1] = 'A';
                    coordsFigur[2] = 1;
                    break;
            }
            break;
        case 'L':
            //Erasing the piece.
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if(gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] == 'A') {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = 0;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 0;
                    }
                }
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]][1] = 'A';
                    coordsFigur[2] = 2;
                    break;
                case 2:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]][1] = 'A';
                    coordsFigur[2] = 3;
                    break;
                case 3:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+2][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+2][1] = 'A';
                    coordsFigur[2] = 4;
                    break;
                case 4:
                    for(int i = 0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+2][coordsFigur[1]+1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+2][coordsFigur[1]+1][1] = 'A';
                    coordsFigur[2] = 1;
                    break;
            }
            break;
        case 'T':
            //Erasing the piece.
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if(gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] == 'A') {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][0] = 0;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+j][1] = 0;
                    }
                }
            }
            switch (coordsFigur[2]) {
                case 1:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+1][1] = 'A';
                    coordsFigur[2] = 2;
                    break;
                case 2:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+i][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+1][1] = 'A';
                    coordsFigur[2] = 3;
                    break;
                case 3:
                    for (int i=0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+i][coordsFigur[1]+1][1] = 'A';
                    }
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]][1] = 'A';
                    coordsFigur[2] = 4;
                    break;
                case 4:
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+1][0] = sigFig;
                    gpm->gridMatrix[coordsFigur[0]][coordsFigur[1]+1][1] = 'A';
                    for(int i = 0; i<3; i++) {
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][0] = sigFig;
                        gpm->gridMatrix[coordsFigur[0]+1][coordsFigur[1]+i][1] = 'A';
                    }
                    coordsFigur[2] = 1;
                    break;
            }
            break;
    }
    pthread_mutex_unlock(gpm->mutex);
    return;
}

void *movimiento(void* gridPMutex) {
    gridPlusMutex *gpm = (gridPlusMutex*) gridPMutex;

    char caracter = 0;

    caracter = getch();
    switch(caracter) {
        case '\033':
            printf("\nESCAPE!!!ESCAPE!!!");
            caracter = getch();
            if(caracter == '[') {
                switch(getch()) {
                    case 'C':
                    case 'c':
                        moverFigura(gpm, 'D'); //Mueve la pieza a la derecha.
                        break;
                    case 'D':
                    case 'd':
                        moverFigura(gpm, 'I'); //Mueve la pieza a la izquierda.
                        break;
                }
            }
            break;
        case 'W':
        case 'w':
            rotar(gpm);
            break;
        case 'A':
        case 'a':
            moverFigura(gpm, 'I'); //Mueve la pieza a la izquierda.
            break;
        case 'S':
        case 's':
            bajarFiguras(gridPMutex);
            break;
        case 'D':
        case 'd':
            moverFigura(gpm, 'D'); //Mueve la pieza a la derecha.
            break;
        default:
    }
    semaforo = 0;
    return NULL;
    fflush(stdin);
}
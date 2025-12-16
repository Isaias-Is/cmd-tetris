//
// Created by isald on 11/18/2023.
//

#ifndef GAMECONTROLS_H
#define GAMECONTROLS_H

#include <pthread.h>

extern char sigFig; //Store what's the next figure to be shown.
extern int coordsFigur[3]; //Stores the current coordinates(int the matrix) of the active figure.
extern int semaforo;
extern int juegoContinua;
extern int puntuacion;
extern int lineasEliminadas;
extern unsigned int timer;

extern void reiniciar(char gridMatrix[24][10][2]);
extern void siguienteFigura(char gridMatrix[24][10][2]); //Generates randow
extern void *movimiento(void *gridPMutex); //Checks if the tetrimino should move based on the input of the user.
extern void rotarFigura(void *gridPMutex);
extern void moverFigura(void *gridPMutex, char movimiento);
extern void *bajarFiguras(void *gridPMatrix); //Advances the active figure to the next position.
extern int comprobarJuego(char gridMatrix[24][10][2], char modo);
void puntos(char gridMatrix[24][10][2]);
void generarSiguienteFigura(); //Randomly generates the next figure and stores it in 'sigFig'.

typedef struct gridPlusMutex {
    char gridMatrix[24][10][2];
    pthread_mutex_t *mutex;
} gridPlusMutex;

#endif //GAMECONTROLS_H

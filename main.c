#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <pthread.h>
#include "FramePrinter.h"
#include "GameControls.h"

pthread_mutex_t mutex; //Declaring a mutex.
gridPlusMutex gpm = {0};

int main() {
    int scale = 2;
    //Starting coordinates for the refreshDisplay function.
    refreshCoords[0] = 2;
    refreshCoords[1] = 19;

    pthread_mutex_init(&mutex, NULL); //Defining a mutex with deffault attrs.
    gpm.mutex = &mutex; //

    //Going to use threads to make the game really functional.
    pthread_t bajarFigID, movimientoID;

    int op;
    do {
        op = imprimirMenu();
        if(op == -1) {
            return -1;
        }
        fflush(stdin); //Cleaning the stdin buffer before starting the real game.
        reiniciar(gpm.gridMatrix); //Preparamos to-do para el juego.
        printScreen(scale); //Printing the game area.

        //<Initializing GameControls> (Necessary, if not the game doesn't work properlu.)
        generarSiguienteFigura(); //Needs to be called once at the beginning.
        siguienteFigura(gpm.gridMatrix); //We pass the matrix that's being used to show the game.
        for(int it=0; it<3; it++) { //Keeps running while the user doesn't lose.
            pthread_create(&bajarFigID, NULL, bajarFiguras, (void *) &gpm); //Creating the thread.
            pthread_join(bajarFigID, NULL); //Waiting for the thread bajarFig to finish.
        }
        //>/<Initializing GameControls>

        while(juegoContinua && timer > 1) { //Keeps running while the user doesn't lose.
            pthread_create(&bajarFigID, NULL, bajarFiguras, (void*) &gpm); //Creating the thread.
            moveTo(0,0);
            static int n=1;
            //printf("ITER: %d\nCoords[%d][%d]\nPuntuacion: %d", n, coordsFigur[0], coordsFigur[1], puntuacion);
            printf("\n\n\nPUNTUACION: %d", puntuacion);
            pthread_join(bajarFigID, NULL); //Waiting for the thread bajarFig to finish.
            n++;
            if(semaforo == 0) { //If the thread doesn't exist already.
                fflush(stdin);
                pthread_create(&movimientoID, NULL, movimiento, (void*) &gpm); //Creating the thread.
                semaforo = 1;
            }

            refreshPlayField(gpm.gridMatrix, scale/*, coords*/);
            Sleep(timer);
        }
        mayorPuntuacion = mayorPuntuacion < puntuacion ?  puntuacion:mayorPuntuacion; //NUEVA MEJOR PUNTUACION?
    } while(op != -1);

    //Closing everything?
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);

    system("cls");
    //Resetting everyting to normal.
    color(0,0); //Returning it's black and white color to the terminal.
    printf("\033[?25h"); //Making the cursor visible again.
    return 0;
}



#include "FramePrinter.h"
#include "GameControls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

int refreshCoords[2] = {2,19}; //Defining the coordinates where refreshField will start refreshing the playfield.
int mayorPuntuacion = 0;
//Sets the console to print characters in a color.
/**/ void color(int colorFG, int colorBG) {
    switch(colorFG) {
        case 30: //Black.
            printf("\033[30m");
            break;
        case 31: //Red.
            printf("\033[31m");
            break;
        case 32: //Green.
            printf("\033[32m");
            break;
        case 33: //Yellow.
            printf("\033[33m");
            break;
        case 34: //Blue.
            printf("\033[34m");
            break;
        case 35: //Magenta.
            printf("\033[35m");
            break;
        case 36: //Cyan.
            printf("\033[36m");
            break;
        case 37: //White.
            printf("\033[37m");
            break;
        case 90: //Bright Black.
            printf("\033[90m");
            break;
        case 91: //Bright Red.
            printf("\033[91m");
            break;
        case 92: //Bright Green.
            printf("\033[92m");
            break;
        case 93: //Bright Yellow.
            printf("\033[93m");
            break;
        case 94: //Bright Blue.
            printf("\033[94m");
            break;
        case 95: //Bright Magenta.
            printf("\033[95m");
            break;
        case 96: //Bright Cyan.
            printf("\033[96m");
            break;
        case 97: //Bright White.
            printf("\033[97m");
            break;
        case 0:
            printf("\033[0m"); //Returning to default color.
            break;
    }
    switch(colorBG) {
        case 40: //Black.
            printf("\033[40m");
            break;
        case 41: //Red.
            printf("\033[41m");
            break;
        case 42: //Green.
            printf("\033[42m");
            break;
        case 43: //Yellow.
            printf("\033[43m");
            break;
        case 44: //Blue.
            printf("\033[44m");
            break;
        case 45: //Magenta.
            printf("\033[45m");
            break;
        case 46: //Cyan.
            printf("\033[46m");
            break;
        case 47: //White.
            printf("\033[47m");
            break;
        case 100: //Bright Black.
            printf("\033[100m");
            break;
        case 101: //Bright Red.
            printf("\033[101m");
            break;
        case 102: //Bright Green.
            printf("\033[102m");
            break;
        case 103: //Bright Yellow.
            printf("\033[103m");
            break;
        case 104: //Bright Blue.
            printf("\033[104m");
            break;
        case 105: //Bright Magenta.
            printf("\033[105m");
            break;
        case 106: //Bright Cyan.
            printf("\033[106m");
            break;
        case 107: //Bright White.
            printf("\033[107m");
            break;
        case 0:
            printf("\033[0m"); //Returning to default color.
            break;
    }
    return;
}

/*
Name            FG  BG
----------------------
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107
*/

//Produces a piip sound.
/**/ void piip(void) {
    printf("\a");
}

/**/ void tabs(int scale) { //Prints tabs.
    for(int i=0; i<scale; i++) {
        printf("\t");
    }
}

/**/ int printScreen(int scale) {
    int currentRow = 1; //The first row is 1.
    system("cls");
    // <Printing the Play Field>
    tabs(2); color(96,104);
    for (int i = 0; i < 20*scale+4; i++) {
        printf("%c", 219);
    }
    printf("\n");
    for(int i=0; i<20*scale+1; i++) {
        tabs(2);
        printf("%c", 219);
        printf("%c", 219);
        for (int j = 0; j < 20 * scale; j++) {
            color(30,40);
            printf("%c", 219);
            //color(0,0);
        }
        color(96,104);
        printf("%c", 219);
        printf("%c", 219);
        printf("\r");
        //Moving to the next row.
        currentRow++;
        moveTo(currentRow, 1);
    }
    tabs(2);
    for (int i = 0; i < 20*scale+4; i++) {
        printf("%c", 219);
    }
    // </Printing the Play Field>


    // <Printing the right part of the game screen>

    // </Printing the right part of the game screen>

    color(0,0);
    return 0;
}

/**/ void moveTo(int row, int col) { //Move the cursor to the specified locarion.
    printf("\033[%d;%dH", row, col);
}

/*void refreshPlayField(char gridMatrix[24][10][2], int scale, int refreshCoords[2]) {
    moveTo(refreshCoords[0], refreshCoords[1]); //Moves to the upper left part of the playfield.
    color(33, 40);

    for (int i = 0; i<20; i++) {
        for(int iSc = 0; iSc < scale; iSc++) {
            moveTo(refreshCoords[0]+i*scale+iSc, refreshCoords[1]); //Moves the cursor to update accordingly the screen.
            for (int j = 0; j < 10; j++) {
                if(gridMatrix[i+4][j][0] != 0) {
                    switch (gridMatrix[i+4][j][0]) {
                        case 'I':
                            color(94, 40); //Blue bright color.
                            break;
                        case 'L':
                            color(91, 40); //Should be orange, however I'm putting red bright color.
                            break;
                        case 'J':
                            color(34, 40); //Blue color.
                            break;
                        case 'Z':
                            color(31, 40); //Red color.
                            break;
                        case 'S':
                            color(32, 40); //Green color.
                            break;
                        case 'T':
                            color(35, 40); //Should be purple, putting magenta color.
                            break;
                        case 'O':
                            color(33, 40); //Yellow color.
                            break;
                    }
                    for(int iSC=0; iSC<scale*2; iSC++) {
                        printf("%c", 219);
                    }
                } else {
                    for(int iSC=0; iSC<scale*2; iSC++) {
                        printf(" ");
                    }
                }
            }
        }
    }
    printf("\033[?25l");
}*/

/**/ void moveCursor(int dir) {
    switch(dir) {
        case 1:
            printf("\033[A"); //UP
            break;
        case 2:
            printf("\033[B"); //DOWN
            break;
        case 3:
            printf("\033[C"); //RIGHT
            break;
        case 4:
            printf("\033[D"); //LEFT
            break;
        default:
            //Nothing happens :).
            break;
    }
}

//This is another version of refreshPlayField to be run as a thread.
void *refreshPlayField(void *gridPM, int scale /*int refreshCoords[2]*/) {
    gridPlusMutex *gpm = (gridPlusMutex*)gridPM;
    while(pthread_mutex_trylock(gpm->mutex) != 0) {Sleep(5);}

    moveTo(refreshCoords[0], refreshCoords[1]); //Moves to the upper left part of the playfield.
    color(33, 40);

    for (int i = 0; i<20; i++) {
        for(int iSc = 0; iSc < scale; iSc++) {
            moveTo(refreshCoords[0]+i*scale+iSc, refreshCoords[1]); //Moves the cursor to update accordingly the screen.
            for (int j = 0; j < 10; j++) {
                if(gpm->gridMatrix[i+4][j][0] != 0) {
                    switch (gpm->gridMatrix[i+4][j][0]) {
                        case 'I':
                            color(94, 40); //Blue bright color.
                            break;
                        case 'L':
                            color(91, 40); //Should be orange, however I'm putting red bright color.
                            break;
                        case 'J':
                            color(34, 40); //Blue color.
                            break;
                        case 'Z':
                            color(31, 40); //Red color.
                            break;
                        case 'S':
                            color(32, 40); //Green color.
                            break;
                        case 'T':
                            color(35, 40); //Should be purple, putting magenta color.
                            break;
                        case 'O':
                            color(33, 40); //Yellow color.
                            break;
                    }
                    for(int iSC=0; iSC<scale*2; iSC++) {
                        printf("%c", 219);
                    }
                } else {
                    for(int iSC=0; iSC<scale*2; iSC++) {
                        printf(" ");
                    }
                }
            }
        }
    }
    printf("\033[?25l");
    pthread_mutex_unlock(gpm->mutex);
    return NULL;
}

int imprimirMenu() {
    system("cls");
    color(93, 96); //NegroBrillante?!-Negro

    //printf("                        BIENVENIDO A\n");
    printf("    _____ _                     _   _        _____ \n"
           "   | __  |_|___ ___ _ _ ___ ___|_|_| |___   |  _  |\n"
           "   | __ -| | -_|   | | | -_|   | | . | . |  |     |\n"
           "   |_____|_|___|_|_|\\_/|___|_|_|_|___|___|  |__|__|\n"
           "                                                   \n");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c\n", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("\n''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c\n", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c\n", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("''");
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("''");
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);
    printf("%c%c", 219, 219);

    printf("\n\n                  Компании СССР");
    
    color(33,40); //Amarillo-Negro.
    printf("\n                ____________________________\n");
    printf("               |                            |\n");
    printf("               | ");color(32,40); //Verde-Negro.
    printf(" Presione <%c para comenzar", 188); color(33,40); //Amarillo-Negro.
    printf(" |\n               |____________________________|\n");
    printf("               |                            |\n");
    printf("               |      ");color(91,40); //RojoBrillante-Negro
    printf("MAYOR PUNTUACION"); color(33,40); //Amarillo-Negro.
    printf("      |\n                |             ");color(94,107); //AzulBrillante-BlancoBrillante.
    printf("%d", mayorPuntuacion); color(33,40); //Amarillo-Negro.
    printf("            |\n               |                            |\n");
    printf("               |____________________________|\n");
    printf("               |                            |\n");
    printf("               |      "); color(91,40); //RojoBrillante-Negro
    printf("Lineas Eliminadas"); color(33,40); //Amarillo-Negro.
    printf("     |\n                |             "); color(94,107); //AzulBrillante-BlancoBrillante.
    printf("%d", lineasEliminadas); color(33,40); //Amarillo-Negro.
    printf("            |\n               |                            |\n");
    printf("               |____________________________|\n\n\n");
    color(0,0);
    printf("Para Salir Presione Teclee 'Salir': ");

    char op[6];
    gets(op);
    fflush(stdin);

    printf("              ____________________________________\n\n");
    if(strcmp("Salir", op) == 0) {
        return -1;
    }
    return 1;
}
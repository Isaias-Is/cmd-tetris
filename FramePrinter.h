//
// Created by Isaias on 10/17/2023.
//

#ifndef FRAMEPRINTER_H
#define FRAMEPRINTER_H

//Fundamental
extern void color(int FG, int BG); //To print colored outputs to the terminal, 1: Foreground Color. 2: Background Color.
extern void tabs(int scale); //Prints tabs.
extern int printScreen(int); //Prints the basic game screen.
//extern void refreshPlayField(char gridMatrix[24][10][2], int scale, int coords[2]); //Refreshes the play field.
extern void *refreshPlayField(void *gridPM, int scale/*, int coords[2]*/); //Refreshes the play field.
extern void moveTo(int row, int col); //Moves to the determined position.

extern void moveCursor(int dir); //You specify through a number the direction of movement of the cursor.

extern int refreshCoords[2];

//Optional.
extern void piip(void); //Produces a piip sound.
extern int imprimirMenu();

extern int mayorPuntuacion;

#endif //FRAMEPRINTER_H

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
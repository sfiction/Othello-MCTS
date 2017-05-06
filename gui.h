#ifndef __OTHELLO_GUI
#define __OTHELLO_GUI
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>

int f[9][9];
int flag  = 1;

void Circle(GLfloat rx, GLfloat ry, GLfloat r);

void display(void);

void mouseClick(int btn, int state, int x, int y);

void mouseMove(int x, int y);

#endif
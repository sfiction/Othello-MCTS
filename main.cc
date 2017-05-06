#include "Othello.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
using namespace std;
using namespace Othello;
volatile int f[9][9];
volatile int flag  = 0;
volatile int GUI_x,GUI_y;
void speedTestOfRandomPlayer(){
	RandomPlayer a, b;

	const int n = 1e4;
	int cnt = 0;
	for (int iter = 0; iter < n; ++iter){
		Round round(a, b);
		do{
			round.nextStep();
		}while (!round.isEnd());
		cnt += round.getResult();
	}
	fprintf(stderr, "%d\n", cnt);
}

void randomVsHuman(){
	RandomPlayer a;
	HumanPlayer b;
	Round round(a, b);
	do{
		round.nextStep();
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MCTSTest(){
	RandomPlayer a;
	MCTSPlayer b;

    printf("debug 3\n");

	Round round(b, a);
	do{
		round.nextStep();
		printf("%s\n", round.getBoard().to_string().c_str());
        fflush(stdout);
    }while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void GUITest(){
    GUIPlayer a;
    MCTSPlayer b;
    Round round(a,b);
    do{
        round.nextStep();
        printf("%s\n", round.getBoard().to_string().c_str());
        fflush(stdout);
    }while(!round.isEnd());
    printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}

void MCTSSingleStepTest(){
	MCTSPlayer a;
	ChessBoard board(0x001E0E46426040E1, 0xFE61F1B9BD9FBF1E);
	printf("%s\n", board.to_string().c_str());
	a.nextStep(board, BLACK);
}

void MCTSVsHuman(){
	MCTSPlayer a;
	HumanPlayer b;
	Round round(a, b);
	do{
		round.nextStep();
	}while (!round.isEnd());
	printf("%d %d\n", round.getBoard().countBlack(), round.getBoard().countWhite());
}
void Circle(GLfloat rx, GLfloat ry, GLfloat r) {
        int vertexNum = 36;
        GLfloat rotateAngle = 360.0 / vertexNum * 2 * 3.1415926 / 360;
        GLfloat x[100], y[100];
        x[1] = rx, y[1] = ry + r;
        for (int i = 2; i <= vertexNum; i++) {
            x[i] = (x[1] - rx)*cos(rotateAngle*(i - 1)) - (y[1] - ry)*sin(rotateAngle*(i - 1)) + rx;
            y[i] = (x[1] - rx)*sin(rotateAngle*(i - 1)) + (y[1] - ry)*cos(rotateAngle*(i - 1)) + ry;
        }
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(rx, ry, 0);
        for (int i = 1; i <= vertexNum; i++) {
            glVertex3f(x[i], y[i], 0);
        }
        glVertex3f(x[1], y[1], 0);
        glEnd();
    }

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.31, 0.31, 0.31);
    /*draw the board background*/
    glBegin(GL_QUADS);
    glVertex3f(-0.9, 0.9, 0.0);
    glVertex3f(0.9, 0.9, 0.0);
    glVertex3f(0.9, -0.9, 0.0);
    glVertex3f(-0.9, -0.9, 0.0);
    glEnd();
    //draw line
    glColor3f(1, 1, 1);
    glLineWidth(10);
    for (int i = 0; i < 9; i++) {
        glBegin(GL_LINES);
        glVertex3f(-0.9, 0.9 - 0.225*i, 0);
        glVertex3f(0.9, 0.9 - 0.225*i, 0);
        glEnd();
    }
    for (int i = 0; i < 9; i++) {
        glBegin(GL_LINES);
        glVertex3f(-0.9 + 0.225*i, 0.9, 0);
        glVertex3f(-0.9 + 0.225*i, -0.9, 0);
        glEnd();
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (f[i][j] == 1) {
                glColor3f(0, 0, 0);
                Circle(-0.9 + 0.1125 + 0.225*i, 0.9 - 0.1125 - 0.225*j, 0.1);
            }
            else if (f[i][j] == 2) {
                glColor3f(1, 1, 1);
                Circle(-0.9 + 0.1125 + 0.225*i, 0.9 - 0.1125 - 0.225*j, 0.1);
            }
        }
    }
    glutSwapBuffers();
}

void mouseClick(int btn, int state, int x, int y)
{
    printf("Click one time.\n");
    fflush(stdout);
    if (flag && btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //flag = 1;
        glColor3f(1.0, 0.0, 0.0);
        GLfloat rx = (x / 400.0) * 0.9;
        GLfloat ry = (y / 400.0) * 0.9;
        int tx, ty;
        tx = int(rx / 0.225);
        ty = int(ry / 0.225);
        printf("Here , x: %d y: %d\n", tx, ty);
        fflush(stdout);
        GUI_x = tx,GUI_y = ty;
        flag = 0;
        printf("in mouse click flag : %d\n",flag);
        fflush(stdout);
    }
}
void mouseMove(int x, int y) {
    
}

int main(){
//	srand(time(NULL));
//	speedTestOfRandomPlayer();
//	randomVsHuman();
	
//	MCTSSingleStepTest();
//	MCTSVsHuman();
	
    //cout << "debug 1" << endl;

    f[3][3] = 2;
    f[3][4] = 1;
    f[4][3] = 1;
    f[4][4] = 2;

    HANDLE h;

    //cout << "test" << endl;

    printf("debug 1\n");
    fflush(stdout);

    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GUITest,NULL,1,0); //创建子线程
    ResumeThread(h);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Simple GLUT App");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMove);


    printf("debug 2\n");
    fflush(stdout);
    //MCTSTest();
    glutMainLoop();


    

	return 0;
}

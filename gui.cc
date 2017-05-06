/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h> 
#endif

#include <GL/glut.h>


GLenum doubleBuffer;
GLint thing1, thing2;


static void Init(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearAccum(0.0, 0.0, 0.0, 0.0);

    thing1 = glGenLists(1);
    glNewList(thing1, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    glRectf(-1.0, -1.0, 1.0, 0.0);
    glEndList();

    thing2 = glGenLists(1);
    glNewList(thing2, GL_COMPILE);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(0.0, -1.0, 1.0, 1.0);
    glEndList();

    

}

static void Reshape(int width, int height)
{

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void Key(unsigned char key, int x, int y)
{

    switch (key) {
      case '1':
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glutPostRedisplay();
    break;
      case '2':
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glutPostRedisplay();
    break;
      case 27:
    exit(0);
    }
}

static void Draw(void)
{

    glPushMatrix();

    glScalef(0.8, 0.8, 1.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(thing1);
    glAccum(GL_LOAD, 0.5);

    glClear(GL_COLOR_BUFFER_BIT);
    glCallList(thing2);
    glAccum(GL_ACCUM, 0.5);

    glAccum(GL_RETURN, 1.0);

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex3f(-0.9, 0.9, 0.0);
    glVertex3f(0.9, 0.9, 0.0);
    glVertex3f(0.9, -0.9, 0.0);
    glVertex3f(-0.9, -0.9, 0.0);
    glEnd();

    glPopMatrix();

    if (doubleBuffer) {
    glutSwapBuffers();
    } else {
    glFlush();
    }
}

static void Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-sb") == 0) {
        doubleBuffer = GL_FALSE;
    } else if (strcmp(argv[i], "-db") == 0) {
        doubleBuffer = GL_TRUE;
    }
    }
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);
    Args(argc, argv);

    type = GLUT_RGB | GLUT_ACCUM;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);
    glutInitWindowSize(300, 300);
    glutCreateWindow("Accum Test");

    Init();

    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Key);
    glutDisplayFunc(Draw);
    glutMainLoop();
}*/
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>

int f[9][9];
int flag  = 1;

/*int __builtin_popcount(unsigned long long n) {
    int ret = 0;
    for (; n; n >>= 1)
        ret += n & 1;
    return ret;
}*/

//#include "Othello.h"
const GLfloat Pi = 3.1415926536f; 


// x0 = (x-rx0)*cos(a)-(y-ry9)*sin(a)+rx0;
// y0 = (x-rx0)*sin(a)+(y-ry0)*cos(a)+ry0;



/*void mouseMove(int x, int y)
{
    printf("On moving , x : %d , y : %d\n", x, y);
}*/

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
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
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
/*class OthelloDisplay {
    static int f[9][9];
    static int flag;
public:
    OthelloDisplay() {
        for (int i = 1; i < 9; i++) {
            for (int j = 1; j < 9; j++) {
                f[i][j] = 0;
            }
        }
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(10, 10);
        glutInitWindowSize(800, 800);
        glutCreateWindow("Simple GLUT App");
        glutDisplayFunc(display);
        glutIdleFunc(display);
        glutMouseFunc(mouseClick);
        glutMotionFunc(mouseMove);
        glutMainLoop();
    }
    static void Circle(GLfloat rx, GLfloat ry, GLfloat r) {
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
    
};

int OthelloDisplay::f[9][9] = { 0 };
int OthelloDisplay::flag = 0;*/
void mouseClick(int btn, int state, int x, int y)
{
    printf("Click one time.\n");
    if (flag && btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //flag = 1;
        glColor3f(1.0, 0.0, 0.0);
        GLfloat rx = (x / 400.0) * 0.9;
        GLfloat ry = (y / 400.0) * 0.9;
        int tx, ty;
        tx = int(rx / 0.225);
        ty = int(ry / 0.225);
        printf("Here , x: %d y: %d\n", tx, ty);
        f[tx][ty] = 1;
        //printf("%f %f\n",rx,ry);
        //Circle(rx, ry, 0.11);
    }
}
void mouseMove(int x, int y) {
    
}

/*int main (int argc,  char *argv[])
{
    //void mouseMove(int x,int y);
    //void mouseClick(int btn,int state,int x,int y);
    //OthelloDisplay o;
    
    return 0;
}*/
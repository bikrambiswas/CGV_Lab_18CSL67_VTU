#include<GL/glut.h>
//#include<iostream.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;
static int window;
static int menu_id=2;
static int submenu_id=1;
static int value = 0;

typedef struct 
{
GLfloat x, y, z;
}wcPt3D;

void bino(GLint n, GLint *C)
{
GLint k, j;
for (k = 0; k <= n; k++)
{
C[k] = 1;
for (j = n; j >= k + 1; j--)
C[k] *= j;
for (j = n - k; j >= 2; j--)
C[k] /= j;
}
}
void computebzPt(GLfloat u, wcPt3D *bzPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C)
{
GLint k, n = nCtrlPts - 1;
GLfloat bzBdFcn;
bzPt->x = bzPt->y = bzPt->z = 0.0;
for (k = 0; k< nCtrlPts; k++)
{
bzBdFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
bzPt->x += ctrlPts[k].x * bzBdFcn;
bzPt->y += ctrlPts[k].y * bzBdFcn;
bzPt->z += ctrlPts[k].z * bzBdFcn;
}
}
void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nbzCPts)
{
wcPt3D bzCPt;
GLfloat u;
GLint *C, k;
C = (int*) malloc (sizeof (sizeof(int)* nCtrlPts));
bino(nCtrlPts - 1, C);
glBegin(GL_LINE_STRIP);
for (k = 0; k <= nbzCPts; k++)
{
u = (GLfloat)k / (GLfloat)nbzCPts;
computebzPt(u, &bzCPt, nCtrlPts, ctrlPts, C);
glVertex2f(bzCPt.x, bzCPt.y);
}
glEnd();
free(C);
}
void displayFunc()
{
GLint nCtrlPts = 4, nbzCPts = 20;
static float theta = 0;
wcPt3D ctrlPts[4] = {
{ 20, 100, 0 },
{ 30, 110, 0 },
{ 50, 90, 0 },
{ 60, 100, 0 }
};
ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
ctrlPts[3].x -= 4 * sin((theta)* PI / 180.0);
ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
theta += 0.1;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 1.0, 1.0);
glPointSize(5);
glPushMatrix();
glLineWidth(5);
glColor3f(255 / 255, 153 / 255.0, 51 / 255.0); //Indian flag: Orange color code
for (int i = 0; i<8; i++)
{
glTranslatef(0, -0.8, 0);
bezier(ctrlPts, nCtrlPts, nbzCPts);
}
glColor3f(1, 1, 1); //Indian flag: white color code
for (int i = 0; i<8; i++)
{
glTranslatef(0, -0.8, 0);
bezier(ctrlPts, nCtrlPts, nbzCPts);
}
glColor3f(19 / 255.0, 136 / 255.0, 8 / 255.0); //Indian flag: green color code
for (int i = 0; i<8; i++)
{
glTranslatef(0, -0.8, 0);
bezier(ctrlPts, nCtrlPts, nbzCPts);
}
glPopMatrix();
glColor3f(0.7, 0.5, 0.3);
glLineWidth(5);
glBegin(GL_LINES);
glVertex2f(20, 100);
glVertex2f(20, 40);
glEnd();
glFlush();
glutPostRedisplay();
glutSwapBuffers();
}
void winReshapeFun(GLint newWidth, GLint newHeight)
{
glViewport(0, 0, newWidth, newHeight);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
glClear(GL_COLOR_BUFFER_BIT);
}
void display(void)
{

glClear(GL_COLOR_BUFFER_BIT);
if (value == 1)
{
return; 
//glutPostRedisplay();
}
else if (value == 2)
{
glPushMatrix();
glColor3d(1.0, 0.0, 1.0);
glutDisplayFunc(displayFunc);
glutWireSphere(0.5, 50, 50);
glPopMatrix();
glutPostRedisplay();

}

glFlush();
}
void menu(int num)
{
if (num == 0)
{
glutDestroyWindow(window);
exit(0);
}
else
{
value = num;
}
glutPostRedisplay();
}
void createMenu(void)
{
submenu_id = glutCreateMenu(menu);
glutAddMenuEntry("draw a flag", 2);
menu_id = glutCreateMenu(menu);
glutAddMenuEntry("Clear", 1);
glutAddSubMenu("Draw", submenu_id);
glutAddMenuEntry("Quit", 0);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void myinit()
{
glViewport(0, 0, 500, 500);
glClearColor(1.0, 1.0, 1.0, 1.0);
glColor3f(1.0, 0.0, 0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
glutInitWindowSize(500, 500);
glutInitWindowPosition(100, 100);
window = glutCreateWindow("Menusand Submenus- Programming Techniques");
createMenu();
glClearColor(0.0, 0.0, 0.0, 0.0);
glutDisplayFunc(display);
glutReshapeFunc(winReshapeFun);
myinit();
glutMainLoop();
}

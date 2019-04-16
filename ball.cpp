#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int animationPeriod = 100;
#define PI 3.14159265
#define VAL PI / 180.0

void axis(double length, bool flag)
{
  glPushMatrix();
  glBegin(GL_LINES);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, length);
  glEnd();
  if (flag)
  {
    glTranslated(0, 0, length - 0.2);
    glutWireCone(0.04, 0.2, 12, 9);
  }
  glPopMatrix();
}

void setup()
{
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glViewport(0, 0, 640, 480);

  // glClear(GL_COLOR_BUFFER_BIT);
}

double pageWidth = 4;
double pageHeight = 2;
double height = 2;
double alpha = 30;
double radius = 0.5;
double yball = 2 + 4 * sin(30 * VAL) + 0.5;
double zball = 0;
void drawScene()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80.0, 64.0 / 48.0, 0.1, 100);
  // glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4, 5, 1, 0, 4, 1, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1, 1, 0);

  glPushMatrix();
  axis(2, true);
  glRotated(90, 0, 1, 0);
  axis(2, false);
  glRotated(-90, 1, 0, 0);
  axis(2, false);
  glPopMatrix();

  // cout << sin(30 * VAL) << endl;

  glPushMatrix();
  glTranslated(0, 2 + 2 * sin(30 * VAL), 2 * cos(30 * VAL));
  glRotated(-(90 - alpha), 1, 0, 0);
  glScaled(pageHeight, pageWidth, 0.01);
  glutWireCube(1);
  glPopMatrix();

  glColor3d(0, 0, 1);

  glPushMatrix();

  glTranslated(0, yball, zball);
  // glTranslated(0, 2, 4 * cos(30 * VAL));

  glutWireSphere(0.5, 15, 15);

  glPopMatrix();

  glFlush();
}

void animate()
{

  zball += 0.1;

  usleep(animationPeriod * 1000);

  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(1400, 400);
  glutCreateWindow("window");
  glutDisplayFunc(drawScene);
  glutIdleFunc(animate);

  glutMainLoop();
}
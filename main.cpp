#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include "ball.h"
#include "page.h"
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

double height = 2;
double height2 = 2;
double alpha = 30;
double t = 0;
double v0 = 0;
int state = 1;
Page page(4, 2);
Ball ball(0, height + page.width * sin(alpha * VAL) + 0.5 + height2, 0, 0.5);
void drawScene()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80.0, 64.0 / 48.0, 0.1, 100);
  // gluPerspective()
  // glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(8, 9, 2, 0, 0, 0, 0.0, 1.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3d(1, 1, 0);

  glPushMatrix();
  axis(2, true);
  glRotated(90, 0, 1, 0);
  axis(2, false);
  glRotated(-90, 1, 0, 0);
  axis(2, false);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0, height + (page.width / 2) * sin(alpha * VAL), (page.width / 2) * cos(alpha * VAL));
  glRotated(-(90 - alpha), 1, 0, 0);
  glScaled(page.height, page.width, 0.01);
  glutWireCube(1);
  glPopMatrix();

  glColor3d(0, 0, 1);

  glPushMatrix();
  glTranslated(ball.x, ball.y, ball.z);
  glutWireSphere(ball.radius, 15, 15);
  glPopMatrix();

  glFlush();

  glutSwapBuffers();
}

void animate()
{
  t += 0.01;
  if (state == 1)
  {
    ball.y = -5 * t * t + (height + page.width * sin(alpha * VAL) + ball.radius + height2);

    if (ball.y <= height + page.width * sin(alpha * VAL) + ball.radius)
    {
      state = 2;
      v0 = 10 * t;
      cout << "t= " << t << "  v0= " << v0 << "  y= " << ball.y << endl;
    }
  }
  else if (state == 2)
  {
    // ball.y = -0.25 * t * t + v0 * t + (height + page.width * sin(alpha * VAL) + ball.radius)
  }

  usleep(1000);

  glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y)
{
  switch (key)
  {
  case ' ':
    t = 0;
    state = 1;
    break;

  default:
    break;
  }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(1400, 400);
  glutCreateWindow("window");
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(keyInput);
  glutIdleFunc(animate);

  glutMainLoop();
}
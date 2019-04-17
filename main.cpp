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
}

double height = 2;
double height2 = 2;
double alpha = 30;
double t = 0;
double v_0 = 0;
double z_0;
double xangle = 0;
int state = 1;
Page page(4, 2);
Ball ball(0, height + page.width * sin(alpha * VAL) + 0.5 + height2, 0, 0, 0, 0, 0.5);

double y_0 = height + page.width * sin(alpha * VAL) + ball.radius + height2;

void drawScene()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80.0, 64.0 / 48.0, 0.1, 100);
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
  // state = 4;
  glRotated(xangle, 1, 0, 0);
  glutWireSphere(ball.radius, 15, 15);
  glPopMatrix();

  glFlush();

  glutSwapBuffers();
}

void animate()
{
  if (state == 1)
  {
    double newY = -5 * t * t + y_0;
    ball.dy = newY - ball.y;
    ball.y += ball.dy;

    if (ball.y <= height + page.width * sin(alpha * VAL) + ball.radius)
    {
      state = 2;
      cout << "t= " << t << "  v= " << (10 * t) << "  v0= " << v_0 << "  y= " << ball.y << "  y0= " << y_0 << endl;
      v_0 = 10 * t;
      y_0 = ball.y;
      t = 0;
    }
  }
  else if (state == 2)
  {
    double newY = -5 * sin(alpha * VAL) * t * t + -v_0 * t + y_0;
    ball.dy = newY - ball.y;
    ball.y += ball.dy;

    ball.dz = (cos(alpha * VAL) / sin(alpha * VAL)) * fabs(ball.dy);
    ball.z += ball.dz;

    xangle += (ball.dz / ball.radius) * (180 / PI);

    if (ball.z >= page.width * cos(alpha * VAL))
    {
      state = 3;
      cout << "t= " << t << "  v= " << (10 * sin(alpha * VAL) * t + v_0) << "  v0= " << v_0 << "  y= " << ball.y << "  y0= " << y_0 << "  z= " << ball.z << endl;
      v_0 = 10 * sin(alpha * VAL) * t + v_0;
      y_0 = ball.y;
      z_0 = ball.z;
      t = 0;
    }
  }
  else if (state == 3)
  {
    double newZ = v_0 * cos(alpha * VAL) * t + z_0;
    ball.dz = newZ - ball.z;
    ball.z += ball.dz;

    xangle += (ball.dz / ball.radius) * (180 / PI);

    ball.y = -5 * t * t - v_0 * sin(alpha * VAL) * t + y_0;

    if (ball.y <= 0)
    {
      state = 4;
    }
  }

  t += 0.01;

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
    ball.z = 0;
    y_0 = height + page.width * sin(alpha * VAL) + ball.radius + height2;
    break;

  case 'x':
    xangle++;
    cout << xangle << endl;
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
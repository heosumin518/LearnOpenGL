#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define PI 3.1415
int num = 11;
float radius = 100.0;

void DrawPolygon(int n)
{
	float x, y;
	float delta;
	delta = 2 * PI / n;
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++) {
		x = 250.0 + radius * cos(delta * i);
		y = 250.0 + radius * sin(delta * i);
		glVertex2f(x, y);
	}
	glEnd();
}

void Display()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(0, 250);
	glVertex2i(500, 250);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(250, 0);
	glVertex2i(250, 500);
	glEnd();
	DrawPolygon(num);
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(400, 400);
	glutInitWindowSize(500, 500);
	glutCreateWindow("N-gonal Polygon ");
	glutDisplayFunc(Display);
	glutMainLoop();
}
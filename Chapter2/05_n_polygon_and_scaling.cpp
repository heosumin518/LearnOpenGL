#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define PI 3.1415926
#define Window_Width 500
#define Window_Height 500

int viewing_width = 500;
int viewing_height = 500;
int viewport_width = Window_Width;
int viewport_height = Window_Height;
int num = 10;
float radius = 30;

void init()
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-250, 250, -250, 250);
}

void MyReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

void Draw_Circle()
{
	float delta;
	glColor3f(1.0, 1.0, 0.0);
	delta = 2 * PI / num;
	glBegin(GL_POLYGON);

	for (int i = 0; i < num; i++)
		glVertex2f(radius * cos(delta * i), radius * sin(delta * i));

	glEnd();
}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);

	glVertex2f(-250.0, -250.0);
	glVertex2f(250.0, -250.0);
	glVertex2f(250.0, 250.0);
	glVertex2f(-250.0, 250.0);

	glEnd();

	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-250.0, 0.0);
	glVertex2f(250.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, -250.0);
	glVertex2f(0, 250.0);

	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2i(100, 100);
	glVertex2i(150, 100);
	glVertex2i(150, 150);
	glVertex2i(100, 150);

	glEnd();

	Draw_Circle();

	glFlush();
	glutSwapBuffers();
}

void MyKey(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'n': num += 1;
			break;
		case 'm': num -= 1;
			if (num < 3)
				num = 3;
			break;
		case 'a': radius += 1.0;
			break;
		case 's': radius -= 1.0;
			break;
		default: break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("N-Polygon & Scaling");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutMainLoop();
}

#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define PI 3.1415926

float radius = 50.0;
float twist;
int n = 1;

GLenum draw_type;
GLfloat vertex[3][2];

void triangle(GLfloat* a, GLfloat* b, GLfloat* c, int type)
{
	GLfloat v[2];
	double d;
	glBegin(GL_POLYGON);

	switch (type) {
		case (7): glEdgeFlag(GL_FALSE); break;
		default: glEdgeFlag(GL_TRUE);
	}

	d = sqrt(a[0] * a[0] + a[1] * a[1]);
	v[0] = cos(twist * d) * a[0] - sin(twist * d) * a[1];
	v[1] = sin(twist * d) * a[0] + cos(twist * d) * a[1];

	glVertex2fv(v);

	switch (type)
	{
		case (7): glEdgeFlag(GL_FALSE); break;
		default: glEdgeFlag(GL_TRUE);
	}

	d = sqrt(b[0] * b[0] + b[1] * b[1]);
	v[0] = cos(twist * d) * b[0] - sin(twist * d) * b[1];
	v[1] = sin(twist * d) * b[0] + cos(twist * d) * b[1];

	glVertex2fv(v);

	switch (type)
	{
		case (7): glEdgeFlag(GL_FALSE); break;
		default: glEdgeFlag(GL_TRUE);
	}

	d = sqrt(c[0] * c[0] + c[1] * c[1]);
	v[0] = cos(twist * d) * c[0] - sin(twist * d) * c[1];
	v[1] = sin(twist * d) * c[0] + cos(twist * d) * c[1];

	glVertex2fv(v);

	glEnd();
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m, int k)
{
	int j, flag[4];
	GLfloat v[3][2];

	if (m > 0)
	{
		for (j = 0; j < 2; j++)
		{
			v[0][j] = (a[j] + b[j]) / 2;
			v[1][j] = (b[j] + c[j]) / 2;
			v[2][j] = (c[j] + a[j]) / 2;
		}

		flag[0] = 3;
		flag[1] = 1;
		flag[2] = 2;
		flag[3] = 7;

		divide_triangle(a, v[0], v[2], m - 1, flag[0]);
		divide_triangle(v[0], b, v[1], m - 1, flag[1]);
		divide_triangle(v[2], v[1], c, m - 1, flag[2]);
	}
	else
		triangle(a, b, c, k);
}

void init()
{
	glClearColor(0.4, 0.4, 0.4, 0.0);
	draw_type = GL_LINES;

	for (int i = 0; i < 3; i++)
	{
		vertex[i][0] = radius * cos(PI / 2 + 2.0 * PI / 3 * i);
		vertex[i][1] = radius * sin(PI / 2 + 2.0 * PI / 3 * i);
	}
	glPolygonMode(GL_FRONT, GL_LINE);
	twist = PI / 100.0;
	twist = 0.0;
}

void MyReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	divide_triangle(vertex[0], vertex[1], vertex[2], n, 0);
	glFlush();
	glutSwapBuffers();
}

void SpecialKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT: n -= 1; break;
		case GLUT_KEY_RIGHT: n += 1; break;
		case GLUT_KEY_UP: twist += 0.001; break;
		case GLUT_KEY_DOWN: twist -= 0.001; break;
		default: break;
	}
}

void IdleFunction()
{
	RenderScene();
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Primitives");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(SpecialKey);
	glutIdleFunc(IdleFunction);
	glutMainLoop();
}
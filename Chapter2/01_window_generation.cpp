#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 400);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(200, 200);
	glVertex2i(400, 200);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(200.0, 200.0);
	glVertex2f(200.0, 400.0);
	glEnd();
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Window Generation");
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
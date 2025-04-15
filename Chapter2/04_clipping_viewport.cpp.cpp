#include <gl/glut.h>
#include <math.h>

#define PI 3.1415926
#define Vertex_No 36

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void DrawAxis()
{
	glColor3f(0.3f, 0.3f, 0.3f);
	glLineWidth(2.0);
	glBegin(GL_LINES);

	glVertex2f(-10.0, 0.0);
	glVertex2f(10.0, 0.0);
	glVertex2f(0.0, -10.0);
	glVertex2f(0.0, 10.0);

	glEnd();
}

void DrawSquare()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);

	glVertex2f(4.0, 4.0);
	glVertex2f(6.0, 4.0);
	glVertex2f(6.0, 6.0);
	glVertex2f(4.0, 6.0);

	glEnd();
}

void DrawCircle()
{
	int i;
	float delta_theta;
	delta_theta = 2 * PI / Vertex_No;
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);

	for (i = 0; i < Vertex_No; i++)
		glVertex2f(cos(delta_theta * i), sin(delta_theta * i));

	glEnd();
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawAxis();
	DrawSquare();
	DrawCircle();
	glFlush();
}

void reshape(int w, int h)
{
	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);	// 抗力 1) 2)
	//glViewport(0, 0, (GLsizei)w/2, (GLsizei)h/2);	// 抗力 3-1)
	glViewport((GLsizei)w / 2 / 2, (GLsizei)h / 2 / 2, (GLsizei)w / 2, (GLsizei)h / 2);	// 抗力 3-2)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);	// 抗力 1) 3)
	//gluOrtho2D(-5, 5, -10, 10);	// 抗力 2-1)
	//gluOrtho2D(-10, 10, -5, 5);	// 抗力 2-2)
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 200);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
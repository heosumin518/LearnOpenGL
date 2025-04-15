#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define WIDTH 400
#define HEIGHT 400
#define LEFT -50
#define BOTTOM -150

int gPoints[100][2];
int gNum = 0;

void MyReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// function call : Mouse1
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	// function call : Mouse2
	//gluOrtho2D (-WIDTH/4.0, -WIDTH/4.0+WIDTH, -HEIGHT/4.0, -HEIGHT/4.0+HEIGHT);
	// function call : Mouse3
	//gluOrtho2D (LEFT, LEFT + WIDTH, BOTTOM, BOTTOM+HEIGHT);
}

void DrawControlPoints(void)
{
	glPointSize(5.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	for (int k = 0; k < gNum; k++)
	{
		glVertex2f(gPoints[k][0], gPoints[k][1]);
	}
	glEnd();
}

void RenderScene()
{
	glClearColor(1.0, 1.0, 0.0, 0.0); // Set display-window color to Yellow
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw X-Axis
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);	// Red
	glVertex2i(WIDTH / 2, HEIGHT / 2);
	glVertex2i(WIDTH, HEIGHT / 2);

	// Draw Y-Axis
	glColor3f(0.0, 0.0, 1.0);	// Blue
	glVertex2f(WIDTH / 2, HEIGHT / 2);
	glVertex2f(WIDTH / 2, HEIGHT);
	glEnd();

	DrawControlPoints();

	glFlush();
}

void Mouse1(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gPoints[gNum][0] = x;
		gPoints[gNum][1] = HEIGHT - y;
		gNum++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gNum = 0;
	}
	glutPostRedisplay();
}

void Mouse2(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gPoints[gNum][0] = x - WIDTH / 4;
		gPoints[gNum][1] = -1.0 * HEIGHT / 2 + (HEIGHT - y);
		gNum++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gNum = 0;
	}

	glutPostRedisplay();
}

void Mouse3(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		gPoints[gNum][0] = LEFT + x;
		gPoints[gNum][1] = BOTTOM + (HEIGHT - y);
		gNum++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		gNum = 0;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Draw Points");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(Mouse1);
	//glutMouseFunc(Mouse2);
	//glutMouseFunc(Mouse3);

	glutMainLoop();
}
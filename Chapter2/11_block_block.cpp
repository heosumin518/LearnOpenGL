#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>

GLfloat winHeight = 500.0f;
GLfloat winWidth = 500.0f;
GLfloat xstep, ystep; // velocity of a moving ball;
GLfloat x1, y1; // Left-Low Position of Moving Ball
GLfloat x2, y2; // Left-Low Position of Fixed Block
GLfloat ball_size = 100.0;
GLsizei block_size = 40.0;

void init()
{
	x1 = 30.0f;
	y1 = 30.0f;
	xstep = 0.015f;
	ystep = 0.013f;
	x2 = winWidth / 2.0 - block_size;
	y2 = winHeight / 2.0 - block_size;
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	if (w <= h)
	{
		winHeight = 500.0f * h / w;
		winWidth = 500.0f;
	}
	else
	{
		winWidth = 500.0f * w / h;
		winHeight = 500.0f;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winWidth, 0, winHeight, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
}

void Collision_Check()
{
	GLfloat xcenter, ycenter;
	if (x1 <= 0 || x1 + 2.0 * ball_size >= winWidth)
		xstep = -xstep;
	if (y1 <= 0 || y1 + 2.0 * ball_size >= winHeight)
		ystep = -ystep;
	xcenter = x1 + ball_size;
	ycenter = y1 + ball_size;
	if ((xstep > 0) && (x2 - ball_size <= xcenter) &&
		(xcenter <= x2) && (ycenter >= xcenter - x2 + y2) &&
		(ycenter <= -1.0 * xcenter + x2 + y2 + 2.0 * block_size))
		xstep = -xstep;
	else if ((xstep < 0) && (x2 + 2.0 * block_size <= xcenter) &&
		(xcenter <= x2 + 2.0 * block_size + ball_size) &&
		(ycenter <= xcenter - x2 + y2) &&
		(ycenter >= -1.0 * xcenter + x2 + 2.0 * block_size + y2))
		xstep = -xstep;
	else if ((ystep > 0) && (y2 - ball_size <= ycenter) &&
		(ycenter <= y2) && (ycenter <= xcenter - x2 + y2) &&
		(ycenter <= -1.0 * xcenter + x2 + 2.0 * block_size + y2))
		ystep = -ystep;
	else if ((ystep < 0) && (y2 + 2.0 * block_size <= ycenter) &&
		(ycenter <= y2 + 2.0 * block_size + ball_size) &&
		(ycenter >= xcenter - x2 + y2) &&
		(ycenter >= -1.0 * xcenter + x2 + 2.0 * block_size + y2))
		ystep = -ystep;
	x1 += xstep;
	y1 += ystep;
}

void RenderScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	Collision_Check();

	// Moving Ball
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 2.0 * ball_size, y1);
	glVertex2f(x1 + 2.0 * ball_size, y1 + 2.0 * ball_size);
	glVertex2f(x1, y1 + 2.0 * ball_size);
	glEnd();

	// Fixed Block
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x2, y2);
	glVertex2f(x2 + 2.0 * block_size, y2);
	glVertex2f(x2 + 2.0 * block_size, y2 + 2.0 * block_size);
	glVertex2f(x2, y2 + 2.0 * block_size);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Block_Block Collision");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}
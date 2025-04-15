#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define PI 3.1415926

float standard_x = -100.0, standard_y = -100.0;
float width = 200.0, height = 200.0, Width = 500.0, Height = 500.0;
float radius = 10.0, radius2 = 20.0, delta_x = 0.0, delta_y = 1.0;
float start_delta = 0.0, start_theta = 0.0, xp = 0.0, yp = -50.0;
float cx = 0.0, cy = 0.0, point_size = 3.0, delta, distance;
int collide_count = 0, num = 5;

GLenum draw_type;

void MyReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y +
		height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Draw_Star(float x, float y, float radius, float start)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x + radius * cos(start + delta * 0), y + radius * sin(start + delta * 0));
	glVertex2f(x + radius * cos(start + delta * 2), y + radius * sin(start + delta * 2));
	glVertex2f(x + radius * cos(start + delta * 4), y + radius * sin(start + delta * 4));
	glVertex2f(x + radius * cos(start + delta * 1), y + radius * sin(start + delta * 1));
	glVertex2f(x + radius * cos(start + delta * 3), y + radius * sin(start + delta * 3));
	glEnd();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.4, 0.4, 0.4, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);

	start_delta += 0.02;

	if (xp + radius >= standard_x + width || xp - radius <= standard_x)
		delta_x *= (-1.0);

	if (yp + radius >= standard_y + height || yp - radius <= standard_y)
		delta_y *= (-1.0);

	distance = sqrt((xp - cx) * (xp - cx) + (yp - cy) * (yp - cy));

	if (distance < radius + radius2)
	{
		delta_x *= (-1.0);
		delta_y *= (-1.0);
		collide_count++;
	}

	xp += delta_x;
	yp += delta_y;
	delta = 2.0 * PI / num;

	if (collide_count % 2 == 0)
	{
		glColor3f(1.0, 0.0, 0.0);
		Draw_Star(cx, cy, radius2, start_delta);
	}

	glPointSize(point_size);
	glColor3f(1.0, 1.0, 0.0);
	Draw_Star(xp, yp, radius, -2.0 * start_delta);
	glFlush();
	glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xp = x / Width * width + standard_x;
		yp = (Height - y) / Height * height + standard_y;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Primitives");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(myMouse);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}
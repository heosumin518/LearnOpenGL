#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define PI 3.1415926

float standard_x = -100.0;
float standard_y = -100.0;
float width = 200.0, height = 200.0;
float point_size = 3.0;
float gotime = 0.0, radius = 50.0;
int num = 10;
float delta;
GLenum draw_type;

void MyReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);
}

void RenderScene()
{
	glClearColor(0.4, 0.4, 0.4, 0.0);
	gotime += 0.1;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);
	glBegin(GL_LINES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(standard_x, 0);
	glVertex2f(standard_x + width, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, standard_y);
	glVertex2f(0, standard_y + height);

	glEnd();

	glPushMatrix();
	glRotatef(gotime, 0.0, 0.0, 1.0);
	glPointSize(point_size);
	glColor3f(0.0, 1.0, 0.0);
	delta = 2.0 * PI / num;
	glBegin(draw_type);

	for (int i = 0; i < num; i++)
		glVertex2f(radius * cos(delta * i), radius * sin(delta * i));

	glEnd();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void MyKey(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a': radius += 1.0; break;
		case 's': radius -= 1.0; break;
		case 'o': point_size += 1.0; break;
		case 'p': point_size -= 1.0; break;
		case 'm': num += 1.0; break;
		case 'n': num -= 1.0;
			if (num < 3) num = 3;
			break;
		default: break;
	}
}

void SpecialKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT: standard_x -= 1.0; break;
		case GLUT_KEY_RIGHT: standard_x += 1.0; break;
		case GLUT_KEY_UP: standard_y += 1.0; break;
		case GLUT_KEY_DOWN: standard_y -= 1.0; break;
		case GLUT_KEY_F1: draw_type = GL_POINTS; break;
		case GLUT_KEY_F2: draw_type = GL_LINES; break;
		case GLUT_KEY_F3: draw_type = GL_TRIANGLES; break;
		case GLUT_KEY_F4: draw_type = GL_QUADS; break;
		case GLUT_KEY_F5: draw_type = GL_LINE_STRIP; break;
		case GLUT_KEY_F6: draw_type = GL_LINE_LOOP; break;
		case GLUT_KEY_F7: draw_type = GL_POLYGON; break;
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
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutSpecialFunc(SpecialKey);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}

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
int viewport_position_x = 0;
int viewport_position_y = 0;
int xstart = -250;
int ystart = -250;
int point[100][2];
int num = 0;
int polygon_num = 3;
float radius = 50.0;
float cX = 0.0, cY = 0.0;

void init()
{
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xstart, xstart + viewing_width, ystart, ystart + viewing_height);
	glShadeModel(GL_FLAT);
	//glShadeModel(GL_SMOOTH);
}

void MyReshape(int w, int h)
{
	glViewport(viewport_position_x, viewport_position_y, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xstart, xstart + viewing_width, ystart, ystart + viewing_height);
}

void Draw_Circle(float centerX, float centerY)
{
	float delta;
	glColor3f(1.0, 1.0, 0.0);
	delta = 2 * PI / polygon_num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < polygon_num; i++)
		glVertex2f(centerX + radius * cos(delta * i), centerY + radius * sin(delta * i));
	glEnd();
}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xstart, xstart + viewing_width, ystart, ystart + viewing_height);
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(xstart, ystart);
	glVertex2f(xstart + viewing_width, ystart);
	glVertex2f(xstart + viewing_width, ystart + viewing_height);
	glVertex2f(xstart, ystart + viewing_height);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(xstart, 0);
	glVertex2f(xstart + viewing_width, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0, ystart);
	glVertex2f(0, ystart + viewing_height);
	glEnd();
	glLineWidth(3.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(100, 100);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(150, 100);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(150, 150);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(100, 150);
	glEnd();
	Draw_Circle(cX, cY);
	glLineWidth(1.0);
	glPointSize(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	for (int i = 0; i < num; i++)
		glVertex2i(point[i][0], point[i][1]);

	glEnd();
	glFlush();
	glutSwapBuffers();
}

void MyMouse(int button, int state, int x, int y)
{
	int xx, yy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xx = x;
		yy = Window_Height - y;
		point[num][0] = xstart + viewing_width *
			(xx - viewport_position_x) / viewport_width;
		point[num][1] = ystart + viewing_height *
			(yy - viewport_position_y) / viewport_height;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		num = 0;
	}
	glutPostRedisplay();
}

void MyKey(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1': viewport_position_x = 0;
			viewport_position_y = 0;
			viewport_width = Window_Width / 2;
			viewport_height = Window_Height / 2;
			break;
		case '2': viewport_position_x = 0;
			viewport_position_y = Window_Height / 2;
			viewport_width = Window_Width / 2;
			viewport_height = Window_Height / 2;
			break;
		case '3': viewport_position_x = Window_Width / 2;
			viewport_position_y = 0;
			viewport_width = Window_Width / 2;
			viewport_height = Window_Height / 2;
			break;
		case '4': viewport_position_x = Window_Width / 2;
			viewport_position_y = Window_Height / 2;
			viewport_width = Window_Width / 2;
			viewport_height = Window_Height / 2;
			break;
		case '5': viewport_position_x = Window_Width / 4;
			viewport_position_y = Window_Height / 4;
			viewport_width = Window_Width / 2;
			viewport_height = Window_Height / 2;
			break;
		case '6': viewport_position_x = 0;
			viewport_position_y = 0;
			viewport_width = Window_Width;
			viewport_height = Window_Height;
			break;
		case 'n': polygon_num += 1;
			break;
		case 'm': polygon_num -= 1;
			if (polygon_num < 3)
				polygon_num = 3;
			break;
		default: break;
	}
	glViewport(viewport_position_x, viewport_position_y,
		viewport_width, viewport_height);
	glutPostRedisplay();
}

void MySpecial(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_LEFT: xstart += 1.0; break;
		case GLUT_KEY_RIGHT: xstart -= 1.0; break;
		case GLUT_KEY_UP: ystart -= 1.0; break;
		case GLUT_KEY_DOWN: ystart += 1.0; break;
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
	glutCreateWindow("Mouse&Viewport");
	init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKey);
	glutMouseFunc(MyMouse);
	glutSpecialFunc(MySpecial);
	glutMainLoop();
}
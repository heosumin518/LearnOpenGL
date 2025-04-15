#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.1415926
#define Vertex_No 100
#define Big 10
#define Small 2
#define Ball_radius 0.3
#define Divide 24

int arc_length;
float Cx, Cy, Dx, Dy;
float start_angle;
float end_angle;
float delta_theta;
float inter, outer;
float move_state;

struct Point2d
{
	float x;
	float y;
};

struct Point3d
{
	float x;
	float y;
	float z;
};

struct Color
{
	float r;
	float g;
	float b;
};

struct Block
{
	Point2d center;
	int collision;
	float radius;
	Color color;
};

Block* block;
int total;

void Init_Block()
{
	float d_theta, theta;
	block = new Block[total];
	d_theta = 2.0 * PI / Divide;

	for (int i = 0; i < total; i++)
	{
		theta = d_theta * i;
		if (i < Divide)
		{
			block[i].center.x = (Big - 0.5) * cos(theta);
			block[i].center.y = (Big - 0.5) * sin(theta);
		}
		else
		{
			block[i].center.x = (Big - 1.0) * cos(theta + d_theta / 2.0);
			block[i].center.y = (Big - 1.0) * sin(theta + d_theta / 2.0);
		}
		block[i].collision = 0;
		block[i].color.r = (float)(1.0 * (i % 3) / 2);
		block[i].color.g = (float)(1.0 * (Divide - i) / Divide);
		block[i].color.b = (float)(1.0 * (i % 10) / 9);
		block[i].radius = 0.5;
	}
}

void Check_Blocks()
{
	float dist, xfac, yfac;
	float delta_x, delta_y;

	for (int i = 0; i < total; i++)
	{
		delta_x = block[i].center.x - Cx;
		delta_y = block[i].center.y - Cy;
		dist = sqrt(delta_x * delta_x + delta_y * delta_y);
		if (block[i].collision == 0 && dist <= block[i].radius + Ball_radius) {
			block[i].collision += 1;
			Dx *= -0.8;
			Dy *= -0.8;
			break;
		}
	}
}

void init()
{
	Cx = 2.6;
	Cy = 3.0;
	Dx = 0.04;
	Dy = 0.08;
	move_state = 1.0;
	inter = Small + 0.1;
	outer = Small + 0.3;
	start_angle = 0.0;
	arc_length = 20;
	delta_theta = 2 * PI / Vertex_No;
	total = 2 * Divide;
	Init_Block();
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

void DrawBigCircle()
{
	int i;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0);
	glBegin(GL_POLYGON);

	for (i = 0; i < Vertex_No; i++)
	{
		glVertex2f(Big * cos(delta_theta * i), Big * sin(delta_theta * i));
	}

	glEnd();
}

void DrawSmallCircle()
{
	int i;
	glColor3f(0.0f, 0.0f, 1.0f);
	delta_theta = 2 * PI / Vertex_No;
	glPointSize(5.0);
	glBegin(GL_POLYGON);

	for (i = 0; i < Vertex_No; i++)
	{
		glVertex2f(Small * cos(delta_theta * i), Small * sin(delta_theta * i));
	}

	glEnd();
}

void Draw_Block()
{
	float x, y;
	for (int i = 0; i < total; i++)
	{
		if (block[i].collision == 0)
		{
			glColor3f(block[i].color.r, block[i].color.g, block[i].color.b);
			glBegin(GL_POLYGON);

			for (int j = 0; j < Vertex_No; j++)
			{
				x = block[i].center.x +
					block[i].radius * cos(delta_theta * j);
				y = block[i].center.y +
					block[i].radius * sin(delta_theta * j);
				glVertex2f(x, y);
			}
			glEnd();
		}
	}
}

void DrawArc()
{
	int i;
	glPointSize(5.0);
	glColor3f(1.0f, 0.0f, 0.0f);

	for (i = 0; i < arc_length; i++)
	{
		glBegin(GL_POLYGON);
		glVertex2f(inter * cos(start_angle + delta_theta * i),
			inter * sin(start_angle + delta_theta * i));
		glVertex2f(inter * cos(start_angle + delta_theta * (i + 1)),
			inter * sin(start_angle + delta_theta * (i + 1)));
		glVertex2f(outer * cos(start_angle + delta_theta * (i + 1)),
			outer * sin(start_angle + delta_theta * (i + 1)));
		glVertex2f(outer * cos(start_angle + delta_theta * i),
			outer * sin(start_angle + delta_theta * i));
		glEnd();
	}
}

void DrawCircle()
{
	int i;
	float A;
	float Nx, Ny;
	float NDx, NDy;
	float speed;
	float distance;
	float angle;
	float bar_center_x, bar_center_y;
	float check_orientation;
	float new_distance;
	int angle_zone;

	glColor3f(1.0f, 0.0f, 0.0f);
	end_angle = start_angle + delta_theta * arc_length;
	speed = sqrt(Dx * Dx + Dy * Dy);
	NDx = -Dx / speed;
	NDy = -Dy / speed;
	angle = atan2(Cy, Cx);

	while (angle < 0.0)
		angle += 2.0 * PI;

	bar_center_x = outer * cos((start_angle + end_angle) / 2.0);
	bar_center_y = outer * sin((start_angle + end_angle) / 2.0);
	check_orientation = bar_center_x * (Cx - bar_center_x) +
		bar_center_y * (Cy - bar_center_y);
	distance = sqrt(Cx * Cx + Cy * Cy);
	if (((start_angle <= angle) && (angle <= end_angle)) ||
		((start_angle <= angle + 2.0 * PI) && (angle + 2.0 * PI <= end_angle)))
		angle_zone = 1;
	else
		angle_zone = -1;
	if (angle_zone > 0)
	{
		if (move_state < 0.0 && check_orientation >= 0.0)
		{
			if (distance <= outer + Ball_radius)
			{
				Nx = Cx / distance;
				Ny = Cy / distance;
				A = NDx * Nx + NDy * Ny;
				Dx = 2.0 * A * Nx - NDx;
				Dy = 2.0 * A * Ny - NDy;
				Dx *= speed;
				Dy *= speed;
			}
		}
	}

	if (distance >= Big - Ball_radius)
	{
		Nx = -Cx / distance;
		Ny = -Cy / distance;
		A = NDx * Nx + NDy * Ny;
		Dx = 2.0 * A * Nx - NDx;
		Dy = 2.0 * A * Ny - NDy;
		Dx *= speed;
		Dy *= speed;
	}

	Check_Blocks();
	Cx += Dx;
	Cy += Dy;
	new_distance = sqrt(Cx * Cx + Cy * Cy);

	if (new_distance >= distance)
		move_state = 1.0;
	else
		move_state = -1.0;

	glPointSize(5.0);
	glBegin(GL_POLYGON);

	for (i = 0; i < Vertex_No; i++)
	{
		glVertex2f(Cx + Ball_radius * cos(delta_theta * i),
			Cy + Ball_radius * sin(delta_theta * i));
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	DrawAxis();
	DrawBigCircle();
	DrawSmallCircle();
	DrawArc();
	DrawCircle();
	Draw_Block();
	glFlush();
	glutSwapBuffers();
}

void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'b': start_angle += 0.1; break;
		case 'm': start_angle -= 0.1; break;
	}

	while (start_angle < 0.0)
		start_angle += 2.0 * PI;

	while (start_angle > 2.0 * PI)
		start_angle -= 2.0 * PI;

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Key);
	glutIdleFunc(display);
	glutMainLoop();
}
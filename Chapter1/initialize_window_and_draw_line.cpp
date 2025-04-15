#include <windows.h>
#include <gl/glut.h>

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.
	glColor3f(1.0, 0.0, 0.0); // Set line segment color to red.
	glBegin(GL_LINES);
	glVertex2i(180, 15); // Specify line-segment geometry.
	glVertex2i(10, 145);
	glEnd();
	glFlush(); // Process all OpenGL routines as quickly as possible.
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);   // GLUT 초기화
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);    // 윈도우 위치 설정
	glutInitWindowSize(400, 300);    // 윈도우 사이즈 설정
	glutCreateWindow("An Example OpenGL Program");
	init();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
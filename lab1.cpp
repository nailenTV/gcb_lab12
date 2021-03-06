#include "GL/glew.h"
#include "GL/freeglut.h"

#include <iostream>

int windowId;

GLdouble eye_x = 0.0f, eye_y = 0.0f, eye_z = 0.0f;
GLdouble lookAt_x = 0.0f, lookAt_y = 0.0f, lookAt_z = -1.0f;

GLfloat angle = 0.0f;

void keyboard(unsigned char key, int x, int y) {
	std::cout << "Key=" << key << std::endl;

	switch (key)
	{
	case 'g':
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 'a':
		eye_x += -0.1f;
		break;
	case 'd':
		eye_x += 0.1f;
		break;
	case 'w':
		eye_z += -0.1f;
		break;
	case 's':
		eye_z += 0.1f;
		break;
	default:
		break;
	}

	std::cout << "eye at (" << eye_x << ", " << eye_y << ", " << eye_z << ")" << std::endl;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	std::cout << "Button=" << button << " State=" << state
		<< " x=" << x << ", y=" << y << std::endl;

	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);

	if (button == GLUT_LEFT && state == GLUT_DOWN) {
		glClearColor(x / (float)window_width, y / (float)window_height, 1.0f, 1.0);
	}
}

void render() {
	std::cout << "Start Frame" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.1f);
	glVertex2f(-0.7f, -0.1f);
	glVertex2f(0.5f, 0.1f);
	glEnd();

	std::cout << "End Frame" << std::endl;

	glutSwapBuffers();
}

void reshapeFunc(int width, int height) {
	if (width == 0 || height == 0) return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, (GLdouble)width / (GLdouble)height, 0.5, 20.0);
	glViewport(0, 0, width, height);
}

void render3D() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(
		eye_x, eye_y, eye_z,
		eye_x + lookAt_x, eye_y + lookAt_y, eye_z + lookAt_z,
		0.0f, 1.0f, 0.0f
	);

	//glTranslatef(0.0f, 0.0f, -1.5f);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.5, 1.5, 32, 32);
	glPopMatrix();

	glutSwapBuffers();
}

void idle() {
	angle += 0.1f;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	std::cout << "Hello World" << std::endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(500, 400);

	windowId = glutCreateWindow("CG Termin 1");

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	glutDisplayFunc(render3D);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idle);
	//reshapeFunc(800, 600);

	glutMainLoop();
	return 0;
}

//glScalef(1.5f, 1.0f, 1.0f);
	//glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	//glTranslatef(1.0f, 0.0f, -0.5f);

	/*glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(1);*/

	/*GLfloat matR[][4] = {
		{0.707, 0.707, 0.0, 0.0},
		{-0.707, 0.707, 0.0, 0.0},
		{0.0, 0.0, 1.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	};

	glLoadIdentity();
	glLoadMatrixf(&matR[0][0]);
	glTranslatef(0.5f, 0.0f, -1.5f);*/
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <cstdio> 

void keyboard(unsigned char key, int x, int y)
{
	if(key == 27)
	{
		printf("ESC was pressed\n");
		exit(1);
	}
}

void mouse(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_UP)
				printf("x = %d, y = %d, LEFT BUTTON UP\n",x,y);
			break;
		case GLUT_RIGHT_BUTTON:	
			if(state == GLUT_UP)
				printf("x = %d, y = %d, RIGHT BUTTON UP\n",x,y);
			break;
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Offline Lab");
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(render);
	glutMainLoop();
}
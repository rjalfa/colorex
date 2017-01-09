#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glui.h>
#include <cstdio> 
#include <algorithm>
using namespace std;

void printHex();
int majorwindow;
GLUI_StaticText* colorcode;
float r=0,g=0,b=0;
char s[8] = "#000000";
void refreshColor()
{
  //printf("Refreshing color: R:%f, G:%f, B:%f\n",r,g,b);
  sprintf(s,"#%02X%02X%02X",(int)r,(int)g,(int)b);
  printf("Color Code: %s\n",s);
  glClearColor(r/255,g/255,b/255,1.0f);
  printHex();
  glutPostRedisplay ();
}


void keyboard(unsigned char key, int x, int y)
{
  printf("%d was pressed\n",key);
	switch(key)
  {
    case 'r':r = min(r+1,255.0f);refreshColor();break;
    case 'g':g = min(g+1,255.0f);refreshColor();break;
    case 'b':b = min(b+1,255.0f);refreshColor();break;
    case 'e':r = max(r-1,0.0f);refreshColor();break;
    case 'f':g = max(g-1,0.0f);refreshColor();break;
    case 'v':b = max(b-1,0.0f);refreshColor();break;
    case 27:exit(0);break; 
  }
}

void printHex()
{
  glColor3f(1.0f,1.0f,1.0f);
  glRasterPos2f(20,20);
  //glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)"Hello");
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'3');
  colorcode->set_text(s);
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

void callback_Button(int arg)
{
	printf("Button pressed with arg %d",arg);
}

void idle ()
{
	glutSetWindow (majorwindow);
	glutPostRedisplay ();
}

void render()
{

  glClearColor(r/255,g/255,b/255,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	majorwindow = glutCreateWindow("Color Mixer");
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(render);
  GLUI *subwindow1 = GLUI_Master.create_glui_subwindow(majorwindow, GLUI_SUBWINDOW_RIGHT);
  colorcode = subwindow1->add_statictext(s);
  //GLUI_Master.set_main_gfx_window(majorwindow);
	//GLUI_Master.set_glutIdleFunc (idle);
	glutMainLoop();
}
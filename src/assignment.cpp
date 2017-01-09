#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glui.h>
#include <cstdio> 
#include <algorithm>
using namespace std;

void printHex();
void fixHSV();
int majorwindow;
GLUI_StaticText* colorcode;
GLUI_StaticText* hsv_h;
GLUI_StaticText* hsv_s;
GLUI_StaticText* hsv_v;
GLUI_StaticText* rgb_r;
GLUI_StaticText* rgb_g;
GLUI_StaticText* rgb_b;
GLUI_Spinner* change_step;
float del = 5.0;
float r=0,g=0,b=0,h=0,s=0,v=0;

char st[8] = "#000000";
char temp[20] = "$";

void refreshColor()
{
	sprintf(st,"#%02X%02X%02X",(int)r,(int)g,(int)b);
	//printf("Color Code: %s\n",st);
	glClearColor(r/255,g/255,b/255,1.0f);
	fixHSV();
	printHex();
	glutSetWindow(majorwindow);
	glutPostRedisplay();
}

//Source: https://www.cs.rit.edu/~ncs/color/t_convert.html
void refreshColorHSV()
{
	int i;
	float f, p, q, t;
	if( s == 0 ) {
		// achromatic (grey)
		r = g = b = v;
		return;
	}
	h /= 60;		// sector 0 to 5
	i = (int)h;
	f = h - i;			// factorial part of h
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * ( 1 - s * ( 1 - f ) );
	switch(i)
	{
		case 0:
			r = v;g = t;b = p;break;
		case 1:
			r = q;g = v;b = p;break;
		case 2:
			r = p;g = v;b = t;break;
		case 3:
			r = p;g = q;b = v;break;
		case 4:
			r = t;g = p;b = v;break;
		default:
			r = v;g = p;b = q;break;
	}
	r = (int)(r*255.0);
	g = (int)(g*255.0);
	b = (int)(b*255.0);
	h*=60;
	//printf("HSV Convert: %.2f, %.2f %.2f\n",r,g,b);
	printHex();
	glutSetWindow(majorwindow);
	glutPostRedisplay();
}

//Source: https://www.cs.rit.edu/~ncs/color/t_convert.html
void fixHSV()
{
	if(r == 0.0f && g == 0.0f && b == 0.0f) {h=0;s=0;v=1.0;return;}
	else if(r == 255.0f && g == 255.0f && b == 255.0f) {h=0;s=0;v=0;return;}
	float m = min(r/255,min(g/255,b/255));
	float M = max(r/255,max(g/255, b/255));
	v = M;					// v
	float delta = M - m;
	if(M != 0)
		s = delta / M;		// s
	else {
		s = 0;
		h = -1;
		return;
	}
	if(r/255 == M)
		h = ( g/255.0 - b/255.0 ) / delta;		// between yellow & mag/255.0enta
	else if( g/255.0 == M )
		h = 2 + ( b/255.0 - r/255 ) / delta;	// between cyan & yellow
	else
		h = 4 + ( r/255 - g/255.0 ) / delta;	// between magenta & cyan
	h *= 60;				// degrees
	if( h < 0 )
		h += 360;
	h = max(h,0.0f);
	h = min(h,360.0f);
	s = max(s,0.0f);
	s = min(s,1.0f);
	v = max(v,0.0f);
	v = min(v,1.0f);
	if(h!=h) h = 0.0f;
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
  	{
		case 'r':r = min(r+del,255.0f);refreshColor();break;
		case 'g':g = min(g+del,255.0f);refreshColor();break;
		case 'b':b = min(b+del,255.0f);refreshColor();break;
		case 'e':r = max(r-del,0.0f);refreshColor();break;
		case 'f':g = max(g-del,0.0f);refreshColor();break;
		case 'v':b = max(b-del,0.0f);refreshColor();break;
		case 27:exit(0);break; 
  	}
}

void controlFunc(int arg)
{
	switch(arg)
	{
		case 1:r = min(r+del,255.0f);refreshColor();break;
    	case 2:g = min(g+del,255.0f);refreshColor();break;
    	case 3:b = min(b+del,255.0f);refreshColor();break;
    	case 4:r = max(r-del,0.0f);refreshColor();break;
    	case 5:g = max(g-del,0.0f);refreshColor();break;
    	case 6:b = max(b-del,0.0f);refreshColor();break;
    	case 7:r = min(r+del,255.0f);g = min(g+del,255.0f);b = min(b+del,255.0f);refreshColor();break;
    	case 8:r = max(r-del,0.0f);g = max(g-del,0.0f);b = max(b-del,0.0f);refreshColor();break; 
	}
}

void controlFuncHSV(int arg)
{
	switch(arg)
	{
		case 1:h = min(h+del,360.0f);break;
    	case 2:s = min(s+0.01f*del,1.0f);break;
    	case 3:v = min(v+0.01f*del,1.0f);break;
    	case 4:h = max(h-del,0.0f);break;
    	case 5:s = max(s-0.01f*del,0.0f);break;
    	case 6:v = max(v-0.01f*del,0.0f);break;
	}
	refreshColorHSV();
}

void printHex()
{
	glColor3f(1.0f,1.0f,1.0f);
	glutPostRedisplay();
	colorcode->set_text(st);
	sprintf(temp,"Red: %d",(int)r);
	rgb_r->set_text(temp);
	sprintf(temp,"Green: %d",(int)g);
	rgb_g->set_text(temp);
	sprintf(temp,"Blue: %d",(int)b);
	rgb_b->set_text(temp);
	sprintf(temp,"Hue: %.2f",h);
	hsv_h->set_text(temp);
	sprintf(temp,"Saturation: %.2f%%",s*100.0);
	hsv_s->set_text(temp);
	sprintf(temp,"Value: %.2f%%",v*100.0);
	hsv_v->set_text(temp);
}

void masterControl(int arg)
{
	switch(arg)
	{
		case 1:r=0;g=0;b=0;refreshColor();break;
		case 2:r=255;g=255;b=255;refreshColor();break;
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
  	glClearColor(r/255,g/255,b/255,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	majorwindow = glutCreateWindow("ColoReX | Color Mixer");
	glutDisplayFunc(render);
	
	//Add GLUI Elements
	GLUI *subwindow2 = GLUI_Master.create_glui_subwindow(majorwindow,GLUI_SUBWINDOW_BOTTOM);
	GLUI *subwindow1 = GLUI_Master.create_glui_subwindow(majorwindow, GLUI_SUBWINDOW_RIGHT);
	//GLUI_Master.set_glutIdleFunc(idle);
	GLUI_Master.set_glutKeyboardFunc(keyboard);
	GLUI_Master.set_glutMouseFunc(mouse);
	subwindow1->set_main_gfx_window(majorwindow);
	subwindow1->add_statictext("Press the following to mix:");
	subwindow1->add_statictext("r : Increase red");
	subwindow1->add_statictext("g : Increase green");
	subwindow1->add_statictext("b : Increase blue");
	subwindow1->add_statictext("e : Decrease red");
	subwindow1->add_statictext("f : Decrease green");
	subwindow1->add_statictext("v : Decrease blue");
	GLUI_Panel* color = subwindow1->add_panel("RGB Values");
	colorcode = subwindow1->add_statictext_to_panel(color,st);
	rgb_r = subwindow1->add_statictext_to_panel(color,"Red: 0");
	rgb_g = subwindow1->add_statictext_to_panel(color,"Green: 0");
	rgb_b = subwindow1->add_statictext_to_panel(color,"Blue: 0");
	GLUI_Panel* controls = subwindow1->add_panel("Controls");
	GLUI_Panel* rgbcontrol = subwindow1->add_panel_to_panel(controls,"");
	subwindow1->add_button_to_panel(rgbcontrol,"Red Up",1,controlFunc);
	subwindow1->add_button_to_panel(rgbcontrol,"Green Up",2,controlFunc);
	subwindow1->add_button_to_panel(rgbcontrol,"Blue Up",3,controlFunc);
	subwindow1->add_column_to_panel(rgbcontrol,true);
	subwindow1->add_button_to_panel(rgbcontrol,"Red Down",4,controlFunc);
	subwindow1->add_button_to_panel(rgbcontrol,"Green Down",5,controlFunc);
	subwindow1->add_button_to_panel(rgbcontrol,"Blue Down",6,controlFunc);
	GLUI_Panel* brightness = subwindow1->add_panel_to_panel(controls,"");
	subwindow1->add_button_to_panel(brightness,"Brighten",7,controlFunc);
	subwindow1->add_column_to_panel(brightness,true);
	subwindow1->add_button_to_panel(brightness,"Darken",8,controlFunc);

	GLUI_Panel* hsv_master = subwindow2->add_panel("HSV Manipulator");
	GLUI_Panel* controls_hsv = subwindow2->add_panel_to_panel(hsv_master,"Controls");
	subwindow1->add_button_to_panel(controls_hsv,"Hue Up",1,controlFuncHSV);
	subwindow1->add_button_to_panel(controls_hsv,"Saturation Up",2,controlFuncHSV);
	subwindow1->add_button_to_panel(controls_hsv,"Value Up",3,controlFuncHSV);
	subwindow1->add_column_to_panel(controls_hsv,false);
	subwindow1->add_button_to_panel(controls_hsv,"Hue Down",4,controlFuncHSV);
	subwindow1->add_button_to_panel(controls_hsv,"Saturation Down",5,controlFuncHSV);
	subwindow1->add_button_to_panel(controls_hsv,"Value Down",6,controlFuncHSV);
	subwindow1->add_column_to_panel(hsv_master,false);
	GLUI_Panel* display_hsv = subwindow2->add_panel_to_panel(hsv_master,"HSV Values");
	hsv_h = subwindow2->add_statictext_to_panel(display_hsv,"Hue: 0");
	hsv_s = subwindow2->add_statictext_to_panel(display_hsv,"Saturation: 0");
	hsv_v = subwindow2->add_statictext_to_panel(display_hsv,"Value: 0");

	GLUI_Panel* master_control = subwindow1->add_panel("Master Control");
	subwindow1->add_button_to_panel(master_control,"Change to Black",1,masterControl);
	subwindow1->add_button_to_panel(master_control,"Change to White",2,masterControl);
	change_step = subwindow1->add_spinner_to_panel(master_control,"Change Step:",GLUI_SPINNER_FLOAT,&del);
	change_step->set_float_limits(0.01f,100.0f);
	change_step->set_speed(1.0);
	refreshColor();
	glutMainLoop();
}
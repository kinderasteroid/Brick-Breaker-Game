#include <stdlib.h>    
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include <math.h>
//#include<iostream>
//using namespace std;


int score = 0;
int brick_color = 1,ball_color = 3,level = 0,paddle_color = 2,text_color = 5,size = 1;;
GLfloat twoModel[]={GL_TRUE};
int game_level[] = {7,5,2};
float rate = game_level[level];

GLfloat brick_color_array[][3] = {{1,0,0},{0,0,1},{0,1,0},{1,0,1},{1,1,0},{0,1,1}};
GLfloat paddle_color_array[][3] = {{1,0,0},{0,0,1},{0,1,0},{1,0,1},{1,1,0},{0,1,1}};
GLfloat text_color_array[][4] = {{1,0,0,1},{0,0,1,1},{0,1,0,1},{1,0,1,1},{1,1,0,1},{0,1,1,1}};
GLfloat paddle_size[] = {2,4,6};
//The grid parameters for the bricks
int rows = 4;
int columns = 10;
GLfloat px,bx = 0,by = -12.8 ,speed = 0,dirx=0,diry=0,start = 0;

void draw_paddle()
{
	glDisable(GL_LIGHTING);
	glColor3fv(paddle_color_array[paddle_color]);
	glBegin(GL_POLYGON);
	glVertex3f(-paddle_size[size]+px,0-15,0);
	glVertex3f(paddle_size[size]+px,0-15,0);
	glVertex3f(paddle_size[size]+px,1-15,0);
	glVertex3f(-paddle_size[size]+px,1-15,0);
	glEnd();
	glEnable(GL_LIGHTING);
}
void draw_ball()
{
	GLfloat ambient1[] = {1,1,1};
	GLfloat diffuse1[] = {0.4,0.4,0.4};
	GLfloat specular1[] = {1,1,1};
	
	GLfloat position[] = {0,0,-50,1};
	GLfloat ambient2[] = {0,0,0};
	GLfloat diffuse2[] = {1,1,1};
	GLfloat specular2[] = {0,1,1};
	
	float materialColours[][3]={{1,0,0},{0,0,1},{0,1,0},{1,0,1},{1,1,0},{0,1,1}};
	GLfloat matAmbient1[] = {1,1,1};
	GLfloat matDiffuse1[] = {1,1,1};
	GLfloat matSpecular1[] = {1,1,1};
	GLfloat shininess[] = {1000};
	
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular1);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse1);
	
	glLightfv(GL_LIGHT1,GL_POSITION,position);
	glLightfv(GL_LIGHT1,GL_SPECULAR,specular2);
	glLightfv(GL_LIGHT1,GL_AMBIENT,ambient2);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuse2);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours[ball_color]);
	
	
	
	glPushMatrix();
	glTranslatef(bx,by,0);
	glScalef(1.0, 1.0, 0.5);
	//glScalef(size[i], size[], size[]);
	glutSolidSphere(1.0, 52, 52);
	   
	glPopMatrix();
	
}
void display (void) {
	
	glClearColor (0.0,0.0,0.0,1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0,0,0,0,0,-25,0,1,0);
	glTranslatef(0,0,-25);
	draw_paddle(); 
	//draw_bricks();
	draw_ball();
	//text(score);
	glutSwapBuffers();
}
void change_paddle_color(int action)
{
	paddle_color = action -1;
}
void keyboard (unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'd': px+=3; break;
		case 'a': px-=3; break;
		case 'q': exit(0); break;
		case 's':
		if(!start)
		{
			dirx = diry= 1;
			rate = game_level[level];
			start = 1;
			score = 0;
			glutSetCursor(GLUT_CURSOR_NONE);
			
		}
		break;
	}
	if(px>15)
	{
		px=15;
	}
	if(px<-15)
	{
		px=-15;
	}
	if(start== 0)
	{
		px=0;
	}
	glutPostRedisplay();
}
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode (GL_MODELVIEW);
}

void idle()
{
	//hit();
	if(bx<-16 || bx>16 && start == 1)
	{
		dirx = dirx*-1;
	}
	if(by<-15 || by>14 && start == 1)
	{
		diry = diry*-1;
	}
	bx+=dirx/(rate);
	by+=diry/(rate);
	rate-=0.001; // Rate at which the speed of ball increases
	
	float x = paddle_size[size];
	//Make changes here for the different position of ball after rebounded by paddle
	if( by<=-12.8 && bx<(px+x*2/3) && bx>(px+x/3)&& start == 1 )
	{
		dirx = 1;
		diry = 1;
	}
	else if(by <=-12.8 && bx<(px-x/3) && bx>(px-x*2/3) && start == 1 )
	{
		dirx = -1;
		diry = 1;
	}
	else if( by<=-12.8 && bx<(px+x/3) &&bx>(px-x/3) && start == 1)
	{
		dirx = dirx;
		diry = 1;
	}
	else if(by <=-12.8 && bx<(px-(x*2/3)) && bx>(px-(x+0.3)) && start == 1 )
	{
		dirx = -1.5;
		diry = 0.8;
	}
	else if(by<=-12.8 && bx<(px+(x+0.3)) && bx>(px+x/3)&& start == 1 )
	{
		dirx = 1.5;
		diry = 0.8;
	}
	else if(by<-13)
	{
		start = 0;
		by = -12.8;
		bx = 0;
		dirx = 0;
		diry = 0;
		px = 0;	
	}
	glutPostRedisplay();
}
void lightsOn()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}
void change_ball_color(int action)
{
	
	ball_color=action-1;
}
int main (int argc,char **argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize (900, 900);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Brick Breaker");
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glEnable(GL_DEPTH_TEST);
	glutIdleFunc (idle);
	//glutPassiveMotionFunc(mousemotion);
	glutKeyboardFunc(keyboard);
	lightsOn();
	//addMenu();
	
	glutMainLoop ();
	return 0;
}

#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>
#include <string.h>

float rwrtx=0;
float rwrty=0;
int mx=0,my=0,drag=0;
float camera[]={0,0,-10.0};	
float BoxMat[]={	1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1};
int rotvert=0,rotside=0;
void display()
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
   glBegin(GL_LINES); //RED - X axis
  glColor3f(1.0,0.0,0.0);
  glVertex3f(1.5, 0.0, 0.0);
  glVertex3f(-1.5, 0.0, 0.0);
  glEnd();	
  glBegin(GL_LINES); //GREEN - Y axis
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, 1.5, 0.0);
  glVertex3f(0.0, -1.5, 0.0);
  glEnd();	
  glBegin(GL_LINES); //BLUE - Z axis 
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, 1.5);
  glVertex3f(0.0, 0.0, -1.5);
  glEnd();
  
  glPushMatrix();
    glLoadIdentity();
    if(rotside)glRotatef(rwrty,0,1,0);
    if(rotvert)glRotatef(rwrtx,1,0,0);
    glMultMatrixf(BoxMat);
    glGetFloatv(GL_MODELVIEW_MATRIX,BoxMat);
  glPopMatrix();
  
  
  glPushMatrix();
  glLoadIdentity();
  glMultMatrixf(BoxMat);
  
  glBegin(GL_POLYGON);						// Front face
	  glColor3f( 1.0, 1.0, 1.0 );
	  glVertex3f( 0.5, -0.5, 0.5 );
	  glVertex3f( 0.5, 0.5, 0.5 );
	  glVertex3f( -0.5, 0.5, 0.5 );
	  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
  
  glBegin(GL_POLYGON);						// Top face
	  glColor3f( 1.0, 0.0, 0.0 );
	  glVertex3f( 0.5, 0.5, 0.5 );
	  glVertex3f( 0.5, 0.5, -0.5 );
	  glVertex3f( -0.5, 0.5, -0.5 );
	  glVertex3f( -0.5, 0.5, 0.5 );
  glEnd();  
  
  glBegin(GL_POLYGON);						// Bottom face
	  glColor3f( 1.0, 0.27 , 0.0 );
	  glVertex3f( 0.5, -0.5, -0.5 );
	  glVertex3f( 0.5, -0.5, 0.5 );
	  glVertex3f( -0.5, -0.5, 0.5 );
	  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();  
  
  glBegin(GL_POLYGON);						// Left face
	  glColor3f( 0.0, 0.0, 1.0 );
	  glVertex3f( -0.5, -0.5, 0.5 );
	  glVertex3f( -0.5, 0.5, 0.5 );
	  glVertex3f( -0.5, 0.5, -0.5 );
	  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();  
  
  glBegin(GL_POLYGON);						// Right face
	  glColor3f( 0.0, 1.0, 0.0 );
	  glVertex3f( 0.5, -0.5, -0.5 );
	  glVertex3f( 0.5, 0.5, -0.5 );
	  glVertex3f( 0.5, 0.5, 0.5 );
	  glVertex3f( 0.5, -0.5, 0.5 );
  glEnd();  
  
  glBegin(GL_POLYGON);						// Back face		
	  glColor3f( 1.0, 1.0, 0.0 );
	  glVertex3f( 0.5, -0.5, -0.5 );
	  glVertex3f( 0.5, 0.5, -0.5 );
	  glVertex3f( -0.5, 0.5, -0.5 );
	  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
  
  glPopMatrix();
  
  char string[]="XYZ";
  glRasterPos2f(-.8, 0.8);
  glColor3f(1., 0., 0.);
  int len = strlen(string);
	for (int i = 0; i < len; i++) {
    	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
		}
  glFlush();
  
  glutSwapBuffers();
}

void keys( int key, int x, int y )
{
  rotvert=0;
  rotside=0;
  if (key == GLUT_KEY_UP)
  {
    rwrtx = -3;
    rotvert=1;
  }
  else if (key == GLUT_KEY_DOWN)
  {
    rwrtx = 3;
    rotvert=1;
  }
  else if (key == GLUT_KEY_RIGHT)
  {
    rwrty = 3;
    rotside=1;
  }
  else if (key == GLUT_KEY_LEFT)
  {
    rwrty = -3;
    rotside=1;
  }
  glutPostRedisplay();
}

void mousemove(int x, int y)
{
   if(drag)
   {
     if((mx- x)!=0 || (my- y)!= 0)
     {
        if (x - mx > 2)rwrty += 3;
        else if (x - mx < -2)rwrty -= 3;
        if (y - my > 2 )rwrtx += 3;
        else if (y - my < -2)rwrtx -= 3;
        mx = x;
        my = y;
        } 
     glutPostRedisplay();
      }
      
    } 
void mouse(int button, int state, int x, int y)
{
   printf("\nmx:%d my:%d x:%d y:%d",mx,my,x,y);
   if(button==GLUT_LEFT_BUTTON)
   {
       if(state==GLUT_DOWN)
       {
         drag=1;
       }
       if(state==GLUT_UP)
       {
         drag=0;
       }
   }
}

void reshape(int w, int h)
{
  float ar = (float)w/(float)h;
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);					//Matrix that defines the viewing volume
  glLoadIdentity();
  if (h < w)
  {
  	glOrtho(-1.0*ar, 1.0*ar,-1.0,1.0,-1.0,1.0);
  }
  else
  {
	glOrtho(-1.0,1.0,-1.0/ar, 1.0/ar,-1.0,1.0);
  }
	glMatrixMode(GL_MODELVIEW);
}

void initopengl()
{
	glClearColor(0.0f, 0.0f , 0.0f , 1.0f);			//  Specify background colour and alpha values.
  	glEnable(GL_DEPTH_TEST);				
  	glDepthFunc(GL_LEQUAL);					// Function to compare depths of different objects
}

int main(int argc, char* argv[])
{

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (500, 500);
  glutCreateWindow("Rubik's Cube");
  
  initopengl();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);	
  glutMotionFunc(mousemove);
  glutSpecialFunc(keys);
  glutMainLoop();
  return 0;
}

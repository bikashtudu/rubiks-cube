#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>
#include <string.h>


float rwrtx=0;
float rwrty=0;
float rwrtz=0;
  
int page=0;
int box_texture[7];
int is_rotating=1;
int direction=0;
int rotation=0;
float angle=0;
int mx=0,my=0,leftb=0,middle=0;
int steps[200];
int step_number=0;
float Mat[]={1,0,0,0,
	     0,1,0,0,
             0,0,1,0,
	     0,0,0,1};

int rotvert=0,rotside=0,rotz=0;

struct face_texture
{
int texture_id;
float xmin,ymin;
};
   


float cube_vertices[][8][3]={

		       {{-3.0,1.0,1.0},
                       {-1.0,1.0,1.0},
                       {-1.0,3.0,1.0},
                       {-3.0,3.0,1.0},       //top left front1
                       {-3.0,1.0,3.0},
                       {-1.0,1.0,3.0},
                       {-1.0,3.0,3.0},
                       {-3.0,3.0,3.0}},

                       {{-1.0,1.0,1.0},
                       {1.0,1.0,1.0},
                       {1.0,3.0,1.0},
                       {-1.0,3.0,1.0}, 	    //top front center2
                       {-1.0,1.0,3.0},
                       {1.0,1.0,3.0},
                       {1.0,3.0,3.0},
                       {-1.0,3.0,3.0}},
                      
		       {{1.0,1.0,1.0},
                       {3.0,1.0,1.0},
                       {3.0,3.0,1.0},
                       {1.0,3.0,1.0},       //top right  front3
                       {1.0,1.0,3.0},
                       {3.0,1.0,3.0},
                       {3.0,3.0,3.0},
                       {1.0,3.0,3.0}},                       

		       {{-3.0,-1.0,1.0},
                       {-1.0,-1.0,1.0},
                       {-1.0,1.0,1.0},
                       {-3.0,1.0,1.0},      //center left front4
                       {-3.0,-1.0,3.0},
                       {-1.0,-1.0,3.0},
                       {-1.0,1.0,3.0},
                       {-3.0,1.0,3.0}},

                       {{-1.0,-1.0,1.0},
                       {1.0,-1.0,1.0},
                       {1.0,1.0,1.0},
                       {-1.0,1.0,1.0},      //front face center5
                       {-1.0,-1.0,3.0},
                       {1.0,-1.0,3.0},
                       {1.0,1.0,3.0},
                       {-1.0,1.0,3.0}},

		       {{1.0,-1.0,1.0},
                       {3.0,-1.0,1.0},
                       {3.0,1.0,1.0},
                       {1.0,1.0,1.0},       //center right front6
                       {1.0,-1.0,3.0},
                       {3.0,-1.0,3.0},
                       {3.0,1.0,3.0},
                       {1.0,1.0,3.0}},

		       {{-3.0,-3.0,1.0},
                       {-1.0,-3.0,1.0},
                       {-1.0,-1.0,1.0},
                       {-3.0,-1.0,1.0},     //bottom left front7
                       {-3.0,-3.0,3.0},
                       {-1.0,-3.0,3.0},
                       {-1.0,-1.0,3.0},
                       {-3.0,-1.0,3.0}},
                       
		       {{-1.0,-3.0,1.0},
                       {1.0,-3.0,1.0},
                       {1.0,-1.0,1.0},
                       {-1.0,-1.0,1.0},     //bottom front center8
                       {-1.0,-3.0,3.0},
                       {1.0,-3.0,3.0},
                       {1.0,-1.0,3.0},
                       {-1.0,-1.0,3.0}},                       

		       {{1.0,-3.0,1.0},
                       {3.0,-3.0,1.0},
                       {3.0,-1.0,1.0},
                       {1.0,-1.0,1.0},      //bottom  right front9
                       {1.0,-3.0,3.0},
                       {3.0,-3.0,3.0},
                       {3.0,-1.0,3.0},
                       {1.0,-1.0,3.0}},

                       {{-3.0,1.0,-1.0},
                       {-1.0,1.0,-1.0},
                       {-1.0,3.0,-1.0},
                       {-3.0,3.0,-1.0},     //top left center10
                       {-3.0,1.0,1.0},
                       {-1.0,1.0,1.0},
                       {-1.0,3.0,1.0},
                       {-3.0,3.0,1.0}},

                       {{-1.0,1.0,-1.0},
                       {1.0,1.0,-1.0},
                       {1.0,3.0,-1.0},
                       {-1.0,3.0,-1.0},     //top face center11
                       {-1.0,1.0,1.0},
                       {1.0,1.0,1.0},
                       {1.0,3.0,1.0},
                       {-1.0,3.0,1.0}},

                       {{1.0,1.0,-1.0},
                       {3.0,1.0,-1.0},
                       {3.0,3.0,-1.0},
                       {1.0,3.0,-1.0},      //top right  center12
                       {1.0,1.0,1.0},
                       {3.0,1.0,1.0},
                       {3.0,3.0,1.0},
                       {1.0,3.0,1.0}},

                       {{-3.0,-1.0,-1.0},
                       {-1.0,-1.0,-1.0},
                       {-1.0,1.0,-1.0},
                       {-3.0,1.0,-1.0},     //left face center13
                       {-3.0,-1.0,1.0},
                       {-1.0,-1.0,1.0},
                       {-1.0,1.0,1.0},
                       {-3.0,1.0,1.0}},
                       
		       {{-1.0,-1.0,-1.0}, 
                       {1.0,-1.0,-1.0}, 
                       {1.0,1.0,-1.0},  
                       {-1.0,1.0,-1.0},     //Middle piece14
                       {-1.0,-1.0,1.0}, 
                       {1.0,-1.0,1.0},  
                       {1.0,1.0,1.0},   
                       {-1.0,1.0,1.0}},
                       

                       {{1.0,-1.0,-1.0},
                       {3.0,-1.0,-1.0},
                       {3.0,1.0,-1.0},
                       {1.0,1.0,-1.0},      //right face center15
                       {1.0,-1.0,1.0},
                       {3.0,-1.0,1.0},
                       {3.0,1.0,1.0},
                       {1.0,1.0,1.0}},

		       {{-3.0,-3.0,-1.0},
                       {-1.0,-3.0,-1.0},
                       {-1.0,-1.0,-1.0},
                       {-3.0,-1.0,-1.0},    //bottom left center16
                       {-3.0,-3.0,1.0},
                       {-1.0,-3.0,1.0},
                       {-1.0,-1.0,1.0},
                       {-3.0,-1.0,1.0}},
                       
                       {{-1.0,-3.0,-1.0},
                       {1.0,-3.0,-1.0},
                       {1.0,-1.0,-1.0},
                       {-1.0,-1.0,-1.0},    //bottom face center17
                       {-1.0,-3.0,1.0},
                       {1.0,-3.0,1.0},
                       {1.0,-1.0,1.0},
                       {-1.0,-1.0,1.0}},
                       

		       {{1.0,-3.0,-1.0},
                       {3.0,-3.0,-1.0},
                       {3.0,-1.0,-1.0},
                       {1.0,-1.0,-1.0},     //bottom  right center18
                       {1.0,-3.0,1.0},
                       {3.0,-3.0,1.0},
                       {3.0,-1.0,1.0},
                       {1.0,-1.0,1.0}},
                       
		       {{-3.0,1.0,-3.0},
                       {-1.0,1.0,-3.0},
                       {-1.0,3.0,-3.0},
                       {-3.0,3.0,-3.0},      //top left back19
                       {-3.0,1.0,-1.0},
                       {-1.0,1.0,-1.0},
                       {-1.0,3.0,-1.0},
                       {-3.0,3.0,-1.0}},

                       {{-1.0,1.0,-3.0},
                       {1.0,1.0,-3.0},
                       {1.0,3.0,-3.0},
                       {-1.0,3.0,-3.0},     //top back center20
                       {-1.0,1.0,-1.0},
                       {1.0,1.0,-1.0},
                       {1.0,3.0,-1.0},
                       {-1.0,3.0,-1.0}},

		       {{1.0,1.0,-3.0},
                       {3.0,1.0,-3.0},
                       {3.0,3.0,-3.0},
                       {1.0,3.0,-3.0},       //top right  back21
                       {1.0,1.0,-1.0},
                       {3.0,1.0,-1.0},
                       {3.0,3.0,-1.0},
                       {1.0,3.0,-1.0}},                       

		       {{-3.0,-1.0,-3.0},
                       {-1.0,-1.0,-3.0},
                       {-1.0,1.0,-3.0},
                       {-3.0,1.0,-3.0},     //center left back22
                       {-3.0,-1.0,-1.0},
                       {-1.0,-1.0,-1.0},
                       {-1.0,1.0,-1.0},
                       {-3.0,1.0,-1.0}},


                       {{-1.0,-1.0,-3.0},
                       {1.0,-1.0,-3.0},
                       {1.0,1.0,-3.0},
                       {-1.0,1.0,-3.0},     //back face center23
                       {-1.0,-1.0,-1.0},
                       {1.0,-1.0,-1.0},
                       {1.0,1.0,-1.0},
                       {-1.0,1.0,-1.0}},


		       {{1.0,-1.0,-3.0},
                       {3.0,-1.0,-3.0},
                       {3.0,1.0,-3.0},
                       {1.0,1.0,-3.0},      //center right back24
                       {1.0,-1.0,-1.0},
                       {3.0,-1.0,-1.0},
                       {3.0,1.0,-1.0},
                       {1.0,1.0,-1.0}},

		       {{-3.0,-3.0,-3.0},
                       {-1.0,-3.0,-3.0},
                       {-1.0,-1.0,-3.0},
                       {-3.0,-1.0,-3.0},    //bottom left back25
                       {-3.0,-3.0,-1.0},
                       {-1.0,-3.0,-1.0},
                       {-1.0,-1.0,-1.0},
                       {-3.0,-1.0,-1.0}},
                       
                       {{-1.0,-3.0,-3.0},
                       {1.0,-3.0,-3.0},
                       {1.0,-1.0,-3.0},
                       {-1.0,-1.0,-3.0},     //bottom back center26
                       {-1.0,-3.0,-1.0},
                       {1.0,-3.0,-1.0},
                       {1.0,-1.0,-1.0},
                       {-1.0,-1.0,-1.0}},
                       


		       {{1.0,-3.0,-3.0},
                       {3.0,-3.0,-3.0},
                       {3.0,-1.0,-3.0},
                       {1.0,-1.0,-3.0},     //bottom  right back27
                       {1.0,-3.0,-1.0},
                       {3.0,-3.0,-1.0},
                       {3.0,-1.0,-1.0},
                       {1.0,-1.0,-1.0}},
		       };
		       
struct face_texture face[][3][3] = {
			      {
				{{0,0,0.66},{0,0.33,0.66},{0,0.66,0.66}},
				{{0,0,0.33},{0,0.33,0.33},{0,0.66,0.33}},
				{{0,0,0},{0,0.33,0},{0,0.66,0}}
			      },
			      {
				{{1,0,0.66},{1,0.33,0.66},{1,0.66,0.66}},
				{{1,0,0.33},{1,0.33,0.33},{1,0.66,0.33}},
				{{1,0,0}   ,{1,0.33,0}   ,{1,0.66,0}}
			      },
			      {	
			   	{{2,0,0.66},{2,0.33,0.66},{2,0.66,0.66}},
				{{2,0,0.33},{2,0.33,0.33},{2,0.66,0.33}},
				{{2,0,0}   ,{2,0.33,0}   ,{2,0.66,0}}
			      },
			      {
			  	{{3,0,0.66},{3,0.33,0.66},{3,0.66,0.66}},
				{{3,0,0.33},{3,0.33,0.33},{3,0.66,0.33}},
				{{3,0,0}   ,{3,0.33,0}   ,{3,0.66,0}}
			      },
			      {    
			    	{{4,0,0.66},{4,0.33,0.66},{4,0.66,0.66}},
				{{4,0,0.33},{4,0.33,0.33},{4,0.66,0.33}},
				{{4,0,0}   ,{4,0.33,0}   ,{4,0.66,0}}
			      },
			 
			      {
			  	{{5,0,0.66},{5,0.33,0.66},{5,0.66,0.66}},
				{{5,0,0.33},{5,0.33,0.33},{5,0.66,0.33}},
				{{5,0,0}   ,{5,0.33,0}   ,{5,0.66,0}}
			      },
			      {
			  	{{6,0,0.66},{6,0.33,0.66},{6,0.66,0.66}},
				{{6,0,0.33},{6,0.33,0.33},{6,0.66,0.33}},
				{{6,0,0}   ,{6,0.33,0}   ,{6,0.66,0}}
			      },			      
			      
			    };	

		       
struct face_texture face1[][3][3] = {
			      {
				{{0,0,0.66},{0,0.33,0.66},{0,0.66,0.66}},
				{{0,0,0.33},{0,0.33,0.33},{0,0.66,0.33}},
				{{0,0,0},{0,0.33,0},{0,0.66,0}}
			      },
			      {
				{{1,0,0.66},{1,0.33,0.66},{1,0.66,0.66}},
				{{1,0,0.33},{1,0.33,0.33},{1,0.66,0.33}},
				{{1,0,0}   ,{1,0.33,0}   ,{1,0.66,0}}
			      },
			      {	
			   	{{2,0,0.66},{2,0.33,0.66},{2,0.66,0.66}},
				{{2,0,0.33},{2,0.33,0.33},{2,0.66,0.33}},
				{{2,0,0}   ,{2,0.33,0}   ,{2,0.66,0}}
			      },
			      {
			  	{{3,0,0.66},{3,0.33,0.66},{3,0.66,0.66}},
				{{3,0,0.33},{3,0.33,0.33},{3,0.66,0.33}},
				{{3,0,0}   ,{3,0.33,0}   ,{3,0.66,0}}
			      },
			      {    
			    	{{4,0,0.66},{4,0.33,0.66},{4,0.66,0.66}},
				{{4,0,0.33},{4,0.33,0.33},{4,0.66,0.33}},
				{{4,0,0}   ,{4,0.33,0}   ,{4,0.66,0}}
			      },
			 
			      {
			  	{{5,0,0.66},{5,0.33,0.66},{5,0.66,0.66}},
				{{5,0,0.33},{5,0.33,0.33},{5,0.66,0.33}},
				{{5,0,0}   ,{5,0.33,0}   ,{5,0.66,0}}
			      },
			      {
			  	{{6,0,0.66},{6,0.33,0.66},{6,0.66,0.66}},
				{{6,0,0.33},{6,0.33,0.33},{6,0.66,0.33}},
				{{6,0,0}   ,{6,0.33,0}   ,{6,0.66,0}}
			      },			      
			      
			    };	


		    
int order[][4] = {
			{4,5,6,7},
			{0,1,5,4},
			{0,4,7,3},
			{5,1,2,6},										
			{1,0,3,2},
			{7,6,2,3},
		 };	   
		 
int order1[][4] = {
			{4,5,6,7},
			{0,1,5,4},
			{0,4,7,3},
			{5,1,2,6},										
			{1,0,3,2},
			{7,6,2,3},
		 };	 
		       
float face_color[][3]=
		   {
		    {0.5,0.5,0.5},  //white		// In case texture is not required.
                    {1.0,0.5,0.0},  //orange
                    {0.0,0.0,1.0},  //blue
                    {0.0,1.0,0.0},  //green
                    {1.0,1.0,0.0},  //yellow
                    {1.0,0.0,0.0},  //red
                    {0.0,0.0,0.0}   //grey
		   };
		       
void draw_face(int cube, struct face_texture index , int face_index , int p[])
{
float xmin,xmax,ymin,ymax;
int a=p[0],b=p[1],c=p[2],d=p[3];
glLineWidth(2);
glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
		glVertex3fv(cube_vertices[cube-1][a]);
		glVertex3fv(cube_vertices[cube-1][b]);
		glVertex3fv(cube_vertices[cube-1][c]);
		glVertex3fv(cube_vertices[cube-1][d]);
	glEnd();

if(index.texture_id==6)
{
	glBegin(GL_POLYGON);
		glColor3fv(face_color[index.texture_id]);
		glVertex3fv(cube_vertices[cube-1][a]);
		glVertex3fv(cube_vertices[cube-1][b]);
		glVertex3fv(cube_vertices[cube-1][c]);
		glVertex3fv(cube_vertices[cube-1][d]);
	glEnd();	
}
else
{
xmin = index.xmin;
ymin = index.ymin;
xmax = xmin + 0.33;
ymax = ymin + 0.33;
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D,box_texture[index.texture_id]);
	glBegin(GL_POLYGON);
		glTexCoord2f(xmin, ymin); glVertex3fv(cube_vertices[cube-1][a]);
		glTexCoord2f(xmax, ymin); glVertex3fv(cube_vertices[cube-1][b]);
		glTexCoord2f(xmax, ymax); glVertex3fv(cube_vertices[cube-1][c]);
		glTexCoord2f(xmin, ymax); glVertex3fv(cube_vertices[cube-1][d]);
	glEnd();	
	glDisable(GL_TEXTURE_2D);
}

}

GLuint LoadBMP(const char *fileName)
{
	FILE *file;
	unsigned char header[54];
	unsigned int dataPos,size,width, height;
	file = fopen(fileName, "rb");
	fread(header, 1, 54, file);			//Windows BMP begin with 54 byte header
	dataPos		= *(int*)&(header[0x0A]);	//dec10, Actual BMP data
	size		= *(int*)&(header[0x22]);	//dec34, BMP Size
	width		= *(int*)&(header[0x12]);	//dec18, Image Width
	height		= *(int*)&(header[0x16]);	//dec22, Image Height
	if (size == 0)
		size = width * height * 3;
	if (dataPos == 0)
		dataPos = 54;
	unsigned char data[size];
	fread(data, 1, size, file);
	fclose(file);
	GLuint texture;
	glGenTextures(1, &texture);				//Generate (allocate) 1 texture name
	glBindTexture(GL_TEXTURE_2D, texture);	//Bind the 2D texture



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//MAG filter
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//MIN filter

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data); //target, level, internalFormatwidth, height,border, format, type, data 
	return texture;
}

void draw_cube1()
{
	draw_face(1, face[6][0][0] , 4, order[4]);//Back
	draw_face(1, face[5][2][0] , 5, order[5]);//Top
	draw_face(1, face[2][0][2] ,  2 , order[2]);//Left    // top left front
    	draw_face(1, face[6][0][0] , 3 , order[3]);//Right
	draw_face(1, face[0][0][0] , 0 , order[0]);//Front
	draw_face(1, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube2()
{
	draw_face(2, face[6][0][0] , 4, order[4]);//Back
	draw_face(2, face[5][2][1] , 5, order[5]);//Top
	draw_face(2, face[6][0][0] , 2 , order[2]);//Left    // top front center
    	draw_face(2, face[6][0][0] , 3 , order[3]);//Right
	draw_face(2, face[0][0][1] , 0 , order[0]);//Front
	draw_face(2, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube3()
{
	draw_face(3, face[6][0][0] , 4, order[4]);//Back
	draw_face(3, face[5][2][2] , 5, order[5]);//Top
	draw_face(3, face[6][0][0] , 2 , order[2]);//Left     // top right front
    	draw_face(3, face[3][0][0] ,  3 , order[3]);//Right
	draw_face(3, face[0][0][2] , 0 , order[0]);//Front
	draw_face(3, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube4()
{
	draw_face(4, face[6][0][0] , 4, order[4]);//Back
	draw_face(4, face[6][0][0] , 5, order[5]);//Top
	draw_face(4, face[2][1][2] ,  2 , order[2]);//Left    // center left front
    	draw_face(4, face[6][0][0] , 3 , order[3]);//Right
	draw_face(4, face[0][1][0] , 0 , order[0]);//Front
	draw_face(4, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube5()
{
	draw_face(5, face[6][0][0] , 4, order[4]);//Back
	draw_face(5, face[6][0][0] , 5, order[5]);//Top
	draw_face(5, face[6][0][0] , 2 , order[2]);//Left    // front center
    	draw_face(5, face[6][0][0] , 3 , order[3]);//Right
	draw_face(5, face[0][1][1] , 0 , order[0]);//Front
	draw_face(5, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube6()
{
	draw_face(6, face[6][0][0] , 4, order[4]);//Back
	draw_face(6, face[6][0][0] , 5, order[5]);//Top
	draw_face(6, face[6][0][0] , 2 , order[2]);//Left    //center right front
    	draw_face(6, face[3][1][0] ,  3 , order[3]);//Right
	draw_face(6, face[0][1][2] , 0 , order[0]);//Front
	draw_face(6, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube7()
{
	draw_face(7, face[6][0][0] , 4, order[4]);//Back
	draw_face(7, face[6][0][0] , 5, order[5]);//Top
	draw_face(7, face[2][2][2] ,  2 , order[2]);//Left     // bottom left front
    	draw_face(7, face[6][0][0] , 3 , order[3]);//Right
	draw_face(7, face[0][2][0] , 0 , order[0]);//Front
	draw_face(7, face[1][0][0] ,  1 , order[1]);//Bottom
}

void draw_cube8()
{
	draw_face(8, face[6][0][0] , 4, order[4]);//Back
	draw_face(8, face[6][0][0] , 5, order[5]);//Top
	draw_face(8, face[6][0][0] , 2 , order[2]);//Left    // bottom front center
    	draw_face(8, face[6][0][0] , 3 , order[3]);//Right
	draw_face(8, face[0][2][1] , 0 , order[0]);//Front
	draw_face(8, face[1][0][1] ,  1 , order[1]);//Bottom
}

void draw_cube9()
{
	draw_face(9, face[6][0][0] , 4, order[4]);//Back
	draw_face(9, face[6][0][0] , 5, order[5]);//Top
	draw_face(9, face[6][0][0] , 2 , order[2]);//Left    // bottom right front
    	draw_face(9, face[3][2][0] ,  3 , order[3]);//Right
	draw_face(9, face[0][2][2] , 0 , order[0]);//Front
	draw_face(9, face[1][0][2] ,  1 , order[1]);//Bottom
}

void draw_cube10()
{
	draw_face(10, face[6][0][0] , 4, order[4]);//Back
	draw_face(10, face[5][1][0] ,  5, order[5]);//Top
	draw_face(10, face[2][0][1] ,  2 , order[2]);//Left    // top left center
    	draw_face(10, face[6][0][0] , 3 , order[3]);//Right
	draw_face(10, face[6][0][0] , 0 , order[0]);//Front
	draw_face(10, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube11()
{
	draw_face(11, face[6][0][0] , 4, order[4]);//Back
	draw_face(11, face[5][1][1] ,  5, order[5]);//Top
	draw_face(11, face[6][0][0] , 2 , order[2]);//Left   // top center
    	draw_face(11, face[6][0][0] , 3 , order[3]);//Right
	draw_face(11, face[6][0][0] , 0 , order[0]);//Front
	draw_face(11, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube12()
{
	draw_face(12, face[6][0][0] , 4, order[4]);//Back
	draw_face(12, face[5][1][2] ,  5, order[5]);//Top
	draw_face(12, face[6][0][0] , 2 , order[2]);//Left    // top right center
    	draw_face(12, face[3][0][1] ,  3 , order[3]);//Right
	draw_face(12, face[6][0][0] , 0 , order[0]);//Front
	draw_face(12, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube13()
{
	draw_face(13, face[6][0][0] , 4, order[4]);//Back
	draw_face(13, face[6][0][0] , 5, order[5]);//Top
	draw_face(13, face[2][1][1] ,  2 , order[2]);//Left    // left center
    	draw_face(13, face[6][0][0] , 3 , order[3]);//Right
	draw_face(13, face[6][0][0] , 0 , order[0]);//Front
	draw_face(13, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube14()
{
	draw_face(14, face[6][0][0] , 4, order[4]);//Back
	draw_face(14, face[6][0][0] , 5, order[5]);//Top
	draw_face(14, face[6][0][0] , 2 , order[2]);//Left    //Middle piece
    	draw_face(14, face[6][0][0] , 3 , order[3]);//Right
	draw_face(14, face[6][0][0] , 0 , order[0]);//Front
	draw_face(14, face[6][0][0] , 1 , order[1]);//Bottom
}


void draw_cube15()
{
	draw_face(15, face[6][0][0] , 4, order[4]);//Back
	draw_face(15, face[6][0][0] , 5, order[5]);//Top
	draw_face(15, face[6][0][0] , 2 , order[2]);//Left   // right center
    	draw_face(15, face[3][1][1] ,  3 , order[3]);//Right
	draw_face(15, face[6][0][0] , 0 , order[0]);//Front
	draw_face(15, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube16()
{
	draw_face(16, face[6][0][0] , 4, order[4]);//Back
	draw_face(16, face[6][0][0] , 5, order[5]);//Top
	draw_face(16, face[2][2][1] ,  2 , order[2]);//Left    // bottom left center
    	draw_face(16, face[6][0][0] , 3 , order[3]);//Right
	draw_face(16, face[6][0][0] , 0 , order[0]);//Front
	draw_face(16, face[1][1][0] ,  1 , order[1]);//Bottom
}

void draw_cube17()
{
	draw_face(17, face[6][0][0] , 4, order[4]);//Back
	draw_face(17, face[6][0][0] , 5, order[5]);//Top
	draw_face(17, face[6][0][0] , 2 , order[2]);//Left    // bottom center 
    	draw_face(17, face[6][0][0] , 3 , order[3]);//Right
	draw_face(17, face[6][0][0] , 0 , order[0]);//Front
	draw_face(17, face[1][1][1] ,  1 , order[1]);//Bottom
}


void draw_cube18()
{
	draw_face(18, face[6][0][0] , 4, order[4]);//Back
	draw_face(18, face[6][0][0] , 5, order[5]);//Top
	draw_face(18, face[6][0][0] , 2 , order[2]);//Left     // bottom right center
    	draw_face(18, face[3][2][1] ,  3 , order[3]);//Right
	draw_face(18, face[6][0][0] , 0 , order[0]);//Front
	draw_face(18, face[1][1][2] ,  1 , order[1]);//Bottom
}

void draw_cube19()
{
	draw_face(19, face[4][0][2] ,  4, order[4]);//Back
	draw_face(19, face[5][0][0] ,  5, order[5]);//Top
	draw_face(19, face[2][0][0] ,  2 , order[2]);//Left    // top left back
    	draw_face(19, face[6][0][0] , 3 , order[3]);//Right
	draw_face(19, face[6][0][0] , 0 , order[0]);//Front
	draw_face(19, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube20()
{
	draw_face(20, face[4][0][1] ,  4, order[4]);//Back
	draw_face(20, face[5][0][1] ,  5, order[5]);//Top
	draw_face(20, face[6][0][0] , 2 , order[2]);//Left    // top back center
    	draw_face(20, face[6][0][0] , 3 , order[3]);//Right
	draw_face(20, face[6][0][0] , 0 , order[0]);//Front
	draw_face(20, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube21()
{
	draw_face(21, face[4][0][0] ,  4, order[4]);//Back
	draw_face(21, face[5][0][2] ,  5, order[5]);//Top
	draw_face(21, face[6][0][0] , 2 , order[2]);//Left   	 // top right back
    	draw_face(21, face[3][0][2] ,  3 , order[3]);//Right
	draw_face(21, face[6][0][0] , 0 , order[0]);//Front
	draw_face(21, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube22()
{
	draw_face(22, face[4][1][2] ,  4, order[4]);//Back
	draw_face(22, face[6][0][0] , 5, order[5]);//Top
	draw_face(22, face[2][1][0] ,  2 , order[2]);//Left     //center left back
    	draw_face(22, face[6][0][0] , 3 , order[3]);//Right
	draw_face(22, face[6][0][0] , 0 , order[0]);//Front
	draw_face(22, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube23()
{
	draw_face(23, face[4][1][1] ,  4, order[4]);//Back
	draw_face(23, face[6][0][0] , 5, order[5]);//Top
	draw_face(23, face[6][0][0] , 2 , order[2]);//Left    //  back center
    	draw_face(23, face[6][0][0] , 3 , order[3]);//Right
	draw_face(23, face[6][0][0] , 0 , order[0]);//Front
	draw_face(23, face[6][0][0] , 1 , order[1]);//Bottom
}


void draw_cube24()
{
	draw_face(24, face[4][1][0] ,  4, order[4]);//Back
	draw_face(24, face[6][0][0] , 5, order[5]);//Top
	draw_face(24, face[6][0][0] , 2 , order[2]);//Left     // center right back
    	draw_face(24, face[3][1][2] ,  3 , order[3]);//Right
	draw_face(24, face[6][0][0] , 0 , order[0]);//Front
	draw_face(24, face[6][0][0] , 1 , order[1]);//Bottom
}

void draw_cube25()
{
	draw_face(25, face[4][2][2] ,  4, order[4]);//Back
	draw_face(25, face[6][0][0] , 5, order[5]);//Top
	draw_face(25, face[2][2][0] ,  2 , order[2]);//Left     // bottom left back
    	draw_face(25, face[6][0][0] , 3 , order[3]);//Right
	draw_face(25, face[6][0][0] , 0 , order[0]);//Front
	draw_face(25, face[1][2][0] ,  1 , order[1]);//Bottom
}


void draw_cube26()
{
	draw_face(26, face[4][2][1] ,  4, order[4]);//Back
	draw_face(26, face[6][0][0] , 5, order[5]);//Top
	draw_face(26, face[6][0][0] , 2 , order[2]);//Left    // bottom back center
    	draw_face(26, face[6][0][0] , 3 , order[3]);//Right
	draw_face(26, face[6][0][0] , 0 , order[0]);//Front
	draw_face(26, face[1][2][1] ,  1 , order[1]);//Bottom
}


void draw_cube27()
{
	draw_face(27, face[4][2][0] ,  4, order[4]);//Back
	draw_face(27, face[6][0][0] , 5, order[5]);//Top
	draw_face(27, face[6][0][0] , 2 , order[2]);//Left    // bottom right back
    	draw_face(27, face[3][2][2] ,  3 , order[3]);//Right
	draw_face(27, face[6][0][0] , 0 , order[0]);//Front
	draw_face(27, face[1][2][2] ,  1 , order[1]);//Bottom
}




void Draw_full_cube()
{
draw_cube1();
draw_cube2();
draw_cube3();
draw_cube4();
draw_cube5();
draw_cube6();
draw_cube7();
draw_cube8();
draw_cube9();
draw_cube10();
draw_cube11();
draw_cube12();
draw_cube13();
draw_cube14();
draw_cube15();
draw_cube16();
draw_cube17();
draw_cube18();
draw_cube19();
draw_cube20();
draw_cube21();
draw_cube22();
draw_cube23();
draw_cube24();
draw_cube25();
draw_cube26();
draw_cube27();
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  glPushMatrix();
  	glLoadIdentity();
  	//glRotatef(rwrtx,1,0,0);
  	//glRotatef(rwrty,0,1,0);
  	//glRotatef(rwrtz,0,0,1);
  	if(rotside)glRotatef(rwrty,0,1,0);
  	if(rotvert)glRotatef(rwrtx,1,0,0);    
  	if(rotz)glRotatef(rwrtz,0,0,1);
  	
  	glMultMatrixf(Mat);
  	glGetFloatv(GL_MODELVIEW_MATRIX,Mat);
  glPopMatrix();
  
  
  glPushMatrix();
  	glLoadIdentity();	
  	glMultMatrixf(Mat);
  	 	
if(rotation==0)
{
	Draw_full_cube();
}
if(rotation==1)
{
	draw_cube4();
	draw_cube5();
	draw_cube6();
	draw_cube7();
	draw_cube8();
	draw_cube9();		
	draw_cube13();
	draw_cube14();
	draw_cube15();
	draw_cube16();
	draw_cube17();
	draw_cube18();	
	draw_cube22();
	draw_cube23();
	draw_cube24();
	draw_cube25();
	draw_cube26();
	draw_cube27();
	
	if(direction==1)
	{
		glRotatef(angle,0.0,1.0,0.0);
	}
	else 
	{
		glRotatef(-angle,0.0,1.0,0.0);
	}
	draw_cube1();			// Cubes in rotating layer
	draw_cube2();
	draw_cube3();
	draw_cube10();
	draw_cube11();	
	draw_cube12();
	draw_cube19();
	draw_cube20();
	draw_cube21();	
}
if(rotation==2)
{
	draw_cube1();
	draw_cube2();	
	draw_cube3();
	draw_cube4();
	draw_cube5();
	draw_cube6();
	draw_cube10();
	draw_cube11();
	draw_cube12();
	draw_cube13();
	draw_cube14();
	draw_cube15();			
	draw_cube19();	
	draw_cube20();
	draw_cube21();
	draw_cube22();
	draw_cube23();
	draw_cube24();
	if(direction==1)
	{
		glRotatef(angle,0.0,1.0,0.0);
	}
	else 
	{
		glRotatef(-angle,0.0,1.0,0.0);
	}
				
	draw_cube7();		// Cubes in rotating layer
	draw_cube8();
	draw_cube9();
	draw_cube16();
	draw_cube17();	
	draw_cube18();
	draw_cube25();
	draw_cube26();
	draw_cube27();
}
if(rotation==3)
{
	draw_cube2();
	draw_cube3();
	draw_cube5();
	draw_cube6();
	draw_cube8();
	draw_cube9();
	draw_cube11();
	draw_cube12();
	draw_cube14();
	draw_cube15();
	draw_cube17();
	draw_cube18();
	draw_cube20();
	draw_cube21();
	draw_cube23();
	draw_cube24();
	draw_cube26();
	draw_cube27();
	if(direction==1)
	{
		glRotatef(angle,1.0,0.0,0.0);
	}
	else
	{
		glRotatef(-angle,1.0,0.0,0.0);
	}
	draw_cube1();		// Cubes in rotating layer
	draw_cube4();
	draw_cube7();
	draw_cube10();
	draw_cube13();
	draw_cube16();
	draw_cube19();
	draw_cube22();
	draw_cube25();
}
if(rotation==4)
{
	draw_cube1();
	draw_cube2();
	draw_cube4();
	draw_cube5();
	draw_cube7();
	draw_cube8();
	draw_cube10();
	draw_cube11();
	draw_cube13();
	draw_cube14();
	draw_cube16();
	draw_cube17();
	draw_cube19();
	draw_cube20();
	draw_cube22();
	draw_cube23();
	draw_cube25();
	draw_cube26();
	
	if(direction==1)
	{
		glRotatef(angle,1.0,0.0,0.0);
	}
	else
	{
		glRotatef(-angle,1.0,0.0,0.0);
	}
	draw_cube3();		// Cubes in rotating layer
	draw_cube6();
	draw_cube9();
	draw_cube12();
	draw_cube15();
	draw_cube18();
	draw_cube21();
	draw_cube24();
	draw_cube27();
}
if(rotation==5)
{	
	draw_cube10();
	draw_cube11();
	draw_cube12();
	draw_cube13();
	draw_cube14();
	draw_cube15();
	draw_cube16();
	draw_cube17();
	draw_cube18();
	draw_cube19();
	draw_cube20();
	draw_cube21();
	draw_cube22();
	draw_cube23();
	draw_cube24();
	draw_cube25();
	draw_cube26();	
	draw_cube27();	
	if(direction==1)
	{
		glRotatef(angle,0.0,0.0,1.0);
	}

	else
	{
		glRotatef(-angle,0.0,0.0,1.0);
	}

	draw_cube1();		// Cubes in rotating layer
	draw_cube2();
	draw_cube3();
	draw_cube4();
	draw_cube5();
	draw_cube6();
	draw_cube7();
	draw_cube8();
	draw_cube9();
}
if(rotation==6)
{
	draw_cube1();		// Cubes in rotating layer
	draw_cube2();
	draw_cube3();
	draw_cube4();
	draw_cube5();
	draw_cube6();
	draw_cube7();
	draw_cube8();
	draw_cube9();
	draw_cube10();
	draw_cube11();
	draw_cube12();
	draw_cube13();
	draw_cube14();
	draw_cube15();
	draw_cube16();
	draw_cube17();
	draw_cube18();
		
	if(direction==1)
	{
		glRotatef(angle,0.0,0.0,1.0);
	}
	else
	{
		glRotatef(-angle,0.0,0.0,1.0);
	}
	draw_cube19();
	draw_cube20();
	draw_cube21();
	draw_cube22();
	draw_cube23();
	draw_cube24();
	draw_cube25();
	draw_cube26();	
	draw_cube27();	
}
  glPopMatrix();
  
  /*
  char string[]="XYZ";
  glRasterPos2f(-.8, 0.8);
  glColor3f(1., 0., 0.);
  int len = strlen(string);
	for (int i = 0; i < len; i++) {
    	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
		}
  glFlush();
  */
  
  glutSwapBuffers();
}


void face_transpose(int index,int dir)
{
int temp1;
struct face_texture temp;

if(dir==0)
{

	temp1=order[index][3];
	order[index][3]=order[index][2];
	order[index][2]=order[index][1];	
	order[index][1]=order[index][0];
	order[index][0]=temp1;
		
	temp=face[index][0][0];
	face[index][0][0]=face[index][2][0];
	face[index][2][0]=face[index][2][2];
	face[index][2][2]=face[index][0][2];
	face[index][0][2]=temp;
	
	temp=face[index][1][0];
    	face[index][1][0]=face[index][2][1];
	face[index][2][1]=face[index][1][2];
	face[index][1][2]=face[index][0][1];
	face[index][0][1]=temp;

}
else
{

	temp1=order[index][0];
	order[index][0]=order[index][1];
	order[index][1]=order[index][2];	
	order[index][2]=order[index][3];
	order[index][3]=temp1;

	temp=face[index][0][0];
	face[index][0][0]=face[index][0][2];
	face[index][0][2]=face[index][2][2];
	face[index][2][2]=face[index][2][0];
	face[index][2][0]=temp;	

	temp=face[index][1][0];
    	face[index][1][0]=face[index][0][1];
	face[index][0][1]=face[index][1][2];
	face[index][1][2]=face[index][2][1];
	face[index][2][1]=temp;
}

}

void top_rotate(int dir)
{
face_transpose(5,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[0][0][0];
temp2=face[0][0][1];
temp3=face[0][0][2];

face[0][0][0]=face[3][0][0];
face[0][0][1]=face[3][0][1];
face[0][0][2]=face[3][0][2];

face[3][0][0]=face[4][0][0];
face[3][0][1]=face[4][0][1];
face[3][0][2]=face[4][0][2];

face[4][0][0]=face[2][0][0];
face[4][0][1]=face[2][0][1];
face[4][0][2]=face[2][0][2];

face[2][0][0]=temp1;
face[2][0][1]=temp2;
face[2][0][2]=temp3;
}
else
{
temp1=face[0][0][0];
temp2=face[0][0][1];
temp3=face[0][0][2];

face[0][0][0]=face[2][0][0];
face[0][0][1]=face[2][0][1];
face[0][0][2]=face[2][0][2];

face[2][0][0]=face[4][0][0];
face[2][0][1]=face[4][0][1];
face[2][0][2]=face[4][0][2];

face[4][0][0]=face[3][0][0];
face[4][0][1]=face[3][0][1];
face[4][0][2]=face[3][0][2];

face[3][0][0]=temp1;
face[3][0][1]=temp2;
face[3][0][2]=temp3;
}

}

void bottom_rotate(int dir)
{
face_transpose(1,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[0][2][0];
temp2=face[0][2][1];
temp3=face[0][2][2];

face[0][2][0]=face[3][2][0];
face[0][2][1]=face[3][2][1];
face[0][2][2]=face[3][2][2];

face[3][2][0]=face[4][2][0];
face[3][2][1]=face[4][2][1];
face[3][2][2]=face[4][2][2];

face[4][2][0]=face[2][2][0];
face[4][2][1]=face[2][2][1];
face[4][2][2]=face[2][2][2];

face[2][2][0]=temp1;
face[2][2][1]=temp2;
face[2][2][2]=temp3;
}
else
{
temp1=face[0][2][0];
temp2=face[0][2][1];
temp3=face[0][2][2];

face[0][2][0]=face[2][2][0];
face[0][2][1]=face[2][2][1];
face[0][2][2]=face[2][2][2];

face[2][2][0]=face[4][2][0];
face[2][2][1]=face[4][2][1];
face[2][2][2]=face[4][2][2];

face[4][2][0]=face[3][2][0];
face[4][2][1]=face[3][2][1];
face[4][2][2]=face[3][2][2];

face[3][2][0]=temp1;
face[3][2][1]=temp2;
face[3][2][2]=temp3;
}
}

void left_rotate(int dir)
{
face_transpose(2,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[0][0][0];
temp2=face[0][1][0];
temp3=face[0][2][0];

face[0][0][0]=face[1][0][0];
face[0][1][0]=face[1][1][0];
face[0][2][0]=face[1][2][0];

face[1][0][0]=face[4][2][2];
face[1][1][0]=face[4][1][2];
face[1][2][0]=face[4][0][2];

face[4][2][2]=face[5][0][0];
face[4][1][2]=face[5][1][0];
face[4][0][2]=face[5][2][0];

face[5][0][0]=temp1;
face[5][1][0]=temp2;
face[5][2][0]=temp3;
}
else
{
temp1=face[0][0][0];
temp2=face[0][1][0];
temp3=face[0][2][0];

face[0][0][0]=face[5][0][0];
face[0][1][0]=face[5][1][0];
face[0][2][0]=face[5][2][0];

face[5][0][0]=face[4][2][2];
face[5][1][0]=face[4][1][2];
face[5][2][0]=face[4][0][2];

face[4][2][2]=face[1][0][0];
face[4][1][2]=face[1][1][0];
face[4][0][2]=face[1][2][0];

face[1][0][0]=temp1;
face[1][1][0]=temp2;
face[1][2][0]=temp3;
}

}

void right_rotate(int dir)
{
face_transpose(3,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[0][0][2];
temp2=face[0][1][2];
temp3=face[0][2][2];

face[0][0][2]=face[1][0][2];
face[0][1][2]=face[1][1][2];
face[0][2][2]=face[1][2][2];

face[1][0][2]=face[4][2][0];
face[1][1][2]=face[4][1][0];
face[1][2][2]=face[4][0][0];

face[4][2][0]=face[5][0][2];
face[4][1][0]=face[5][1][2];
face[4][0][0]=face[5][2][2];

face[5][0][2]=temp1;
face[5][1][2]=temp2;
face[5][2][2]=temp3;
}
else
{
temp1=face[0][0][2];
temp2=face[0][1][2];
temp3=face[0][2][2];

face[0][0][2]=face[5][0][2];
face[0][1][2]=face[5][1][2];
face[0][2][2]=face[5][2][2];

face[5][0][2]=face[4][2][0];
face[5][1][2]=face[4][1][0];
face[5][2][2]=face[4][0][0];

face[4][2][0]=face[1][0][2];
face[4][1][0]=face[1][1][2];
face[4][0][0]=face[1][2][2];

face[1][0][2]=temp1;
face[1][1][2]=temp2;
face[1][2][2]=temp3;
}

}

void front_rotate(int dir)
{
face_transpose(0,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[2][0][2];
temp2=face[2][1][2];
temp3=face[2][2][2];

face[2][0][2]=face[1][0][0];
face[2][1][2]=face[1][0][1];
face[2][2][2]=face[1][0][2];

face[1][0][0]=face[3][2][0];
face[1][0][1]=face[3][1][0];
face[1][0][2]=face[3][0][0];

face[3][2][0]=face[5][2][2];
face[3][1][0]=face[5][2][1];
face[3][0][0]=face[5][2][0];

face[5][2][2]=temp1;
face[5][2][1]=temp2;
face[5][2][0]=temp3;
}
else
{
temp1=face[2][0][2];
temp2=face[2][1][2];
temp3=face[2][2][2];

face[2][0][2]=face[5][2][2];
face[2][1][2]=face[5][2][1];
face[2][2][2]=face[5][2][0];


face[5][2][2]=face[3][2][0];
face[5][2][1]=face[3][1][0];
face[5][2][0]=face[3][0][0];

face[3][0][0]=face[1][0][2];
face[3][1][0]=face[1][0][1];
face[3][2][0]=face[1][0][0];

face[1][0][0]=temp1;
face[1][0][1]=temp2;
face[1][0][2]=temp3;

}

}

void back_rotate(int dir)
{
face_transpose(4,dir);
struct face_texture temp1,temp2,temp3;

if(dir==0)
{
temp1=face[2][0][0];
temp2=face[2][1][0];
temp3=face[2][2][0];

face[2][0][0]=face[1][2][0];
face[2][1][0]=face[1][2][1];
face[2][2][0]=face[1][2][2];

face[1][2][0]=face[3][2][2];
face[1][2][1]=face[3][1][2];
face[1][2][2]=face[3][0][2];

face[3][2][2]=face[5][0][2];
face[3][1][2]=face[5][0][1];
face[3][0][2]=face[5][0][0];

face[5][0][2]=temp1;
face[5][0][1]=temp2;
face[5][0][0]=temp3;
}
else
{
temp1=face[2][0][0];
temp2=face[2][1][0];
temp3=face[2][2][0];

face[2][0][0]=face[5][0][2];
face[2][1][0]=face[5][0][1];
face[2][2][0]=face[5][0][0];

face[5][0][0]=face[3][0][2];
face[5][0][1]=face[3][1][2];
face[5][0][2]=face[3][2][2];

face[3][0][2]=face[1][2][2];
face[3][1][2]=face[1][2][1];
face[3][2][2]=face[1][2][0];

face[1][2][0]=temp1;
face[1][2][1]=temp2;
face[1][2][2]=temp3;

}

}

void rotate_cube()
{
angle = angle + 2.5;
if(angle==360)
{
	angle=-360;
}
if(angle>=90)
{
is_rotating=0;
glutIdleFunc(NULL);	//

	if(rotation==1)
	{
		top_rotate(direction);
		
	}
	if(rotation==2)
	{
		bottom_rotate(direction);
	}
	if(rotation==3)
	{
		left_rotate(direction);
	}
	if(rotation==4)
	{
		right_rotate(direction);
	}		
	if(rotation==5)
	{
		front_rotate(direction);
	}
	if(rotation==6)
	{
		back_rotate(direction);
	}
	
rotation=0;
angle=0;
}
glutPostRedisplay();
}

void reset()
{
int i,j,k;

for(i=0;i<7;i++)
{
for(j=0;j<3;j++)
{
for(k=0;k<3;k++)
{
face[i][j][k]=face1[i][j][k];
}
}
}

for(i=0;i<6;i++)
{
for(j=0;j<4;j++)
{
order[i][j]=order1[i][j];
}
}
}


void keyboard(unsigned char key,int x,int y)
{
	rotvert=0,rotside=0,rotz=0;
	
	
	if(page==0)
	{
		if(key == 'p')
		{
			page = 2;
		}
		else if(key == 'i')
		{
			page = 1;
		}
		else if(key == 27)
		{
		exit(0);
		}
		glutPostRedisplay();
	}
	else if(page==1)
	{
		if(key=='b'||key=='B')
		{
			page=0;
		}
		glutPostRedisplay();
	}
	
	if(key==27)
	{
		exit(0);
	}
	
	if(key=='q' && is_rotating==0)		//Top
	{
		is_rotating=1;
          	rotation=1;
		direction=1;
		step_number++;		
		steps[step_number]=1;
		glutIdleFunc(rotate_cube);
	}
	if( key=='a' && is_rotating==0)
	{
		is_rotating=1;
        	rotation=1;
		direction=0;
		step_number++;
		steps[step_number]=-1;
		glutIdleFunc(rotate_cube);
	}

	if(key=='w' && is_rotating==0)		//Bottom
	{
		is_rotating=1;
          	rotation=2;
		direction=1;
		step_number++;
		steps[step_number]=2;
		glutIdleFunc(rotate_cube);
	}
	if( key=='s' && is_rotating==0)
	{
		is_rotating=1;
        	rotation=2;
		direction=0;
		step_number++;
		steps[step_number]=-2;
		glutIdleFunc(rotate_cube);
	}
	
	if(key=='e' && is_rotating==0)		//Left
	{
		is_rotating=1;
          	rotation=3;
		direction=1;
		step_number++;
		steps[step_number]=3;
		glutIdleFunc(rotate_cube);
	}
	if( key=='d' && is_rotating==0)
	{
		is_rotating=1;
        	rotation=3;
		direction=0;
		step_number++;
		steps[step_number]=-3;
		glutIdleFunc(rotate_cube);
	}

	if(key=='r' && is_rotating==0)		//Right
	{
		is_rotating=1;
          	rotation=4;
		direction=1;
		step_number++;
		steps[step_number]=4;
		glutIdleFunc(rotate_cube);
	}
	if( key=='f' && is_rotating==0)	
	{
		is_rotating=1;
        	rotation=4;
		direction=0;
		step_number++;
		steps[step_number]=-4;
		glutIdleFunc(rotate_cube);
	}
	
	if(key=='t' && is_rotating==0)		//Front
	{
		is_rotating=1;
          	rotation=5;
		direction=1;
		step_number++;
		steps[step_number]=5;
		glutIdleFunc(rotate_cube);
	}
	if( key=='g' && is_rotating==0)
	{
		is_rotating=1;
        	rotation=5;
		direction=0;
		step_number++;
		steps[step_number]=-5;
		glutIdleFunc(rotate_cube);
	}

	if(key=='y' && is_rotating==0)		//Back
	{
		is_rotating=1;
          	rotation=6;
		direction=1;
		step_number++;
		steps[step_number]=6;
		glutIdleFunc(rotate_cube);
	}
	if( key=='h' && is_rotating==0)
	{
		is_rotating=1;
        	rotation=6;
		direction=0;
		step_number++;
		steps[step_number]=-6;
		glutIdleFunc(rotate_cube);
	}

	if(key=='u' && is_rotating==0)
	{
		is_rotating=1;
		if(step_number>=0)
		{
			if(steps[step_number]>0)
			{
				rotation=steps[step_number];
				direction=0;
				glutIdleFunc(rotate_cube);
			}
			if(steps[step_number]<0)
			{
				rotation=steps[step_number]*(-1);
				direction=1;
				glutIdleFunc(rotate_cube);
			}
			step_number--;
		}
	glutIdleFunc(rotate_cube);
	}
	
	if(key=='l' && is_rotating==0)
	{
		rotation=0;
		reset();
		glutPostRedisplay();
	}
		

	if(key=='8' && is_rotating==0)
	{
		rotvert=1;
		rwrtx=-2.0;	
		glutIdleFunc(rotate_cube);
	}	
	if(key=='2' && is_rotating==0)
	{
		rotvert=1;
		rwrtx=+2.0;		
		glutIdleFunc(rotate_cube);
	}

	if(key=='6' && is_rotating==0)
	{
		rotside=1;
		rwrty=+2.0;
		glutIdleFunc(rotate_cube);
	}
	if(key=='4' && is_rotating==0)
	{
		rotside=1;
		rwrty=-2.0;
		glutIdleFunc(rotate_cube);
	}

	if(key=='9' && is_rotating==0)
	{
		rotz=1;
		rwrtz=+2.0;
		glutIdleFunc(rotate_cube);
	}

	if(key=='1' && is_rotating==0)
	{
		rotz=1;
		rwrtz=-2.0;
		glutIdleFunc(rotate_cube);
	}	


}

void mouse(int button, int state, int x, int y)
{
  
   if(button==GLUT_LEFT_BUTTON &&(state==GLUT_DOWN))
   {
	leftb = 1;
   }
   else
   {
	leftb = 0;
   }
   if(button==GLUT_RIGHT_BUTTON &&(state==GLUT_DOWN))
   {
	middle = 1;
   }
   else
   {
	middle = 0;
   }   
   mx = x;
   my = y;  
}

void motion(int x, int y)
{
   rotvert=0;
   rotside=0;
   if(leftb == 1)
   {
        rwrty = (x-mx)*0.5;
        if(rwrty!=0) rotside=1;
     glutPostRedisplay();
    }
    if(middle == 1)
   {
        rwrtx = (y-my)*0.5;
        if(rwrtx!=0) rotvert=1;
     glutPostRedisplay();
    }   
    mx = x;
    my = y;  
} 



void reshape(int w, int h)
{
  float ar = (float)w/(float)h;
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);					//Matrix that defines the viewing volume
  glLoadIdentity();
  if (h < w)
  {
  	glOrtho(-10.0*ar, 10.0*ar,-10.0,10.0,-10.0,10.0);
  }
  else
  {
	glOrtho(-10.0,10.0,-10.0/ar, 10.0/ar,-10.0,10.0);
  }
	glMatrixMode(GL_MODELVIEW);
}

void draw_text(int x, int y, char *text)
{
int i,l;
	glRasterPos2f(x, y);
	l = strlen(text);
	for (i=0;i<l;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}



void show_page1()						//Starting menu
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0,0,0,0.0);
	//glTranslatef(0.0,0.0,-6.0);
	//glTranslatef(0.0,-1.3,0.0);
	glColor3f(0.0,1.0,0.0);
	draw_text(-4.7,7.0," RUBIKS CUBE ");
	glColor3f(0.6,0.8,0.7);
	draw_text(-3.25,5," MENU ");
	glColor3f(0.0,0.0,1.0);
	draw_text(-4,3," Press 'P'   :      PLAY ");
	draw_text(-4,1," Press 'I'   :      HELP ");
	draw_text(-4,-1," Press 'Esc' :      EXIT ");
	
	glFlush();
	glutSwapBuffers();
}

void show_page2()							//Help menu		
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0,0,0,1.0);
	//glTranslatef(0.0,0.0,-6.0);
	//glTranslatef(0.0,-1.3,0.0);
	glColor3f(0.6,0.8,0.7);
	draw_text(-2.7,9.0," INSTRUCTIONS ");
	glColor3f(0.0,0.0,1.0);
	draw_text(-7,8," TOP INWARD                                  :  q" );
	draw_text(-7,7," TOP OUTWARD                              :  a" );	
	draw_text(-7,6," BOTTOM INWARD                         :  w" );
	draw_text(-7,5," BOTTOM OUTWARD                     :  s" );
	draw_text(-7,4," LEFT INWARD                                 :  e" );
	draw_text(-7,3," LEFT OUTWARD                             :  d" );
	draw_text(-7,2," RIGHT INWARD                              :  r" );
	draw_text(-7,1," RIGHT OUTWARD                          :  f" );
	draw_text(-7,0," FRONT INWARD                             :  t" );
	draw_text(-7,-1," FRONT OUTWARD                         :  g" );
	draw_text(-7,-2," BACK INWARD                                :  y" );
	draw_text(-7,-3," BACK OUTWARD                            :  h" );	
	draw_text(-7,-4," UNDO MOVE                                    :  u" );
	draw_text(-7,-5," RESET CUBE                                     :  l" );							
	draw_text(-7,-7," Press B to go back to main menu" );							

	glFlush();
	glutSwapBuffers();
}

void start_menu()
{
	if(page==0)
	{
		show_page1();
	}
	else if(page==1)
	{
		show_page2();
	}
	else
	{
		display();
	}
}

void initopengl()
{
	int i;
	char file_name[30];
	glClearColor(0.0f, 0.0f , 0.0f , 1.0f);			//  Specify background colour and alpha values.
  	glEnable(GL_DEPTH_TEST);				
  	glDepthFunc(GL_LEQUAL);					// Function to compare depths of different objects

	box_texture[0]=LoadBMP("box-texture[0].bmp");
	box_texture[1]=LoadBMP("box-texture[1].bmp");
	box_texture[2]=LoadBMP("box-texture[2].bmp");
	box_texture[3]=LoadBMP("box-texture[3].bmp");
	box_texture[4]=LoadBMP("box-texture[4].bmp");
	box_texture[5]=LoadBMP("box-texture[5].bmp");
	box_texture[6]=LoadBMP("box-texture[6].bmp");
}

int main(int argc, char* argv[])
{

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (500, 500);
  glutCreateWindow("Rubik's Cube");
  
  initopengl();
  glutDisplayFunc(start_menu);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);	
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(rotate_cube);
  glutMainLoop();
  return 0;
}

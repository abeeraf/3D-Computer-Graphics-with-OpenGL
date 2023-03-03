//HELP TAKEN FROM ---> "Mark J. Kilgard, 1994, 1997" Work Online 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>    
#include <GL/freeglut.h>  
#include "colors.h"
#ifndef M_PI
#define M_PI 3.14159265
#endif

static float jump = 0.0;
static float lightAngle = 0.0;
static float lightHeight = 20;
GLfloat angle = -150;
GLfloat angle2 = 30;

int moving, startx, starty;

//FLOOR COOKIES
static char *Pattern[] = {
  "....xxxx........",
  "..xxx..xxx......",
  ".xxx....xxx.....",
  ".xx......xx.....",
  "xx.oo..oo.xx....",
  "xx.o,..o,.xx....",
  "xx--....--xx....",
  "xx........xx....",
  ".xx.*..*.xx.....",
  ".xxx.**.xxx.....",
  "..xxx..xxx......",
  "....xxxx........",
  "................",
  "................",
  "................",
  "................",
};


  static char *Cat[] = {
//     12345678901234567890123456789012
/*18*/"................................",
/*17*/"..........yyyyyyyyyyyyyy........",
/*16*/"..llll...yvvvvvvvvvvvvvvy.......",
/*15*/".ltttlllyvvvvvvvvvvvvvvvvy......",
/*14*/".lltttttyvvvvvvvxxvvvvvvvy.xx...",
/*13*/"...lllttyvvvvvvxffxvvvvvvyxffx..",
/*12*/"......llyvvvvvvxfffxvvvvvxfffx..",
/*11*/"........yvvvvvvxffffxxxxxffffx..",
/*10*/"........yvvvvvvxfffffffffffffx..",
/*09*/".......lyvvvvvxfffxxxxffxxxxffx.",
/*08*/".....lltyvvvvvxfffxxxxffxxxxffx.",
/*07*/"....ltttyvvvvvxf--ffffffffff--x.",
/*06*/"....ltttyvvvvvxf--ffxffxffxf--x.",
/*05*/"....lttl.yvvvvvxfffffxxxxxfffx..",
/*04*/"....lll...yyyyyyxfffffffffffx...",
/*03*/".................xxxxxxxxxxx....",
/*02*/"...................ltl.ltl......",
/*01*/"....................ll..ll......",
}; 

static GLdouble bodyWidth = 3.0;

static GLfloat head[][2] = {{17,13},{17,10},{16,9},{16,6},{18,4},{28,4},{30,6},{30,9},{29,10},{29,13},{28,13},{25,10},{21,10},{18,13}}; 
static GLfloat smile[][2] = {{21,6},{22,5},{26,5},{27,6}};
static GLfloat leg1[][2] = {{3,15},{4,14},{7,14},{7,13},{8,13},{8,14},{5,14},{5,15}};
static GLfloat leg2[][2] = {{6,7},{6,5},{7,5},{8,6},{8,8},{7,7}};
static GLfloat leg3[][2] = {{21,2},{21,2}};
static GLfloat leg4[][2] = {{25,2},{25,2}};
static GLfloat heado[][2] = {{15,9},{15,6},{18,3},{28,3},{31,6},{31,10},{31,9},{30,10},{30,13},{29,14},{28,14},{25,11},{21,11},{18,14},{17,14},{16,13},{16,10}};
static GLfloat bodo[][2] = {{9, 6}, {11, 4}, {16, 4}, {14, 6},{14, 9}, {15, 10}, {15, 14}, {16, 14},{16,15}, {18, 15}, {21, 12}, {25, 12},{26, 13}, {26, 15}, {25, 16}, {24, 17},{11, 17},{9,15},{8,15},{6,15}, {6,16} , {3,16}, {2,15},{2,14},{3,14},{4,13},{6,13},{7,12},{8,12}, {9,12},{9,9},{8,9},{7,8},{6,8},{5,7},{5,4},{7,4}};

static GLfloat bod[][2] = { {10, 6},{11,5},{15,5}, {14, 6},{14, 9}, {15, 10}, {15, 14}, {16, 14},{16,15}, {18, 15}, {21, 12}, {25, 12},{26, 13}, {25, 15}, {24, 16}, {11, 16},{10, 15}};
static GLfloat leg1o[][2]= {{20,2},{21,1},{22,1},{22,2}};
static GLfloat leg2o[][2]= {{24,2},{25,1},{26,1},{26,2}};	
static GLfloat eye1[][2] = {{19,9},{19,8},{20,8}} ;
static GLfloat eye2[][2] = {{27,8},{28,8},{28,9}} ;	
static GLfloat sparkle1[][2] = {{19,9},{20,8},{20,9}};
static GLfloat sparkle2[][2] = {{27,8},{28,9},{27,9}};	
static GLfloat blush1[][2] = {{17,7},{17,6},{18,6},{18,7}};	
static GLfloat blush2[][2] = {{29,7},{29,6},{30,6},{30,7}};

static GLfloat lightPosition[4];
static void makeFloorTexture(void){

	GLubyte FloorPrint[16][16][3];
	GLubyte *loc;

	//Making an image for texture
	loc = (GLubyte*) FloorPrint;
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			if (Pattern[x][y] == 'x' || Pattern[x][y] == '-') {
				loc[0] = 0xe7;
				loc[1] = 0x54;
				loc[2] = 0x80;
			} 
			else if(Pattern[x][y] == '.')
			{
				loc[0] = 0xff;
				loc[1] = 0xB6;
				loc[2] = 0xC1;
			}
			else if(Pattern[x][y] == ',')
			{
				loc[0] = 0xff;
				loc[1] = 0xff;
				loc[2] = 0xff;
			}
			else if(Pattern[x][y] == '*' || Pattern[x][y] == 'o')
			{
				loc[0] = 0x00;
				loc[1] = 0x00;
				loc[2] = 0x00;
			}
			loc += 3;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 16, 16, 0,GL_RGB, GL_UNSIGNED_BYTE, FloorPrint);
	
}

//SHADOW MATRIX GLUT
void shadowMatrix(GLfloat shadowMat[4][4], GLfloat GROUND[4], GLfloat LIGHT[4]){
  
	GLfloat dot;
	//FLOOR NORMAL WAS CALCULATED 
	//THE BELOW CODE IS FROM OPENGL's OFFICIAL WEBSITE
	//https://www.opengl.org
	dot = 	GROUND[0] * LIGHT[0] + 
		GROUND[1] * LIGHT[1] + 
		GROUND[2] * LIGHT[2] + 
		GROUND[3] * LIGHT[3];

	shadowMat[0][0] = dot - LIGHT[0] * GROUND[0];
	shadowMat[1][0] = 0.f - LIGHT[0] * GROUND[1];
	shadowMat[2][0] = 0.f - LIGHT[0] * GROUND[2];
	shadowMat[3][0] = 0.f - LIGHT[0] * GROUND[3];

	shadowMat[0][1] = 0.f - LIGHT[1] * GROUND[0];
	shadowMat[1][1] = dot - LIGHT[1] * GROUND[1];
	shadowMat[2][1] = 0.f - LIGHT[1] * GROUND[2];
	shadowMat[3][1] = 0.f - LIGHT[1] * GROUND[3];

	shadowMat[0][2] = 0.f - LIGHT[2] * GROUND[0];
	shadowMat[1][2] = 0.f - LIGHT[2] * GROUND[1];
	shadowMat[2][2] = dot - LIGHT[2] * GROUND[2];
	shadowMat[3][2] = 0.f - LIGHT[2] * GROUND[3];

	shadowMat[0][3] = 0.f - LIGHT[3] * GROUND[0];
	shadowMat[1][3] = 0.f - LIGHT[3] * GROUND[1];
	shadowMat[2][3] = 0.f - LIGHT[3] * GROUND[2];
	shadowMat[3][3] = dot - LIGHT[3] * GROUND[3];

}

//FORMING THE PLANE WITH 3 POINTS
void findPlane(GLfloat plane[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3]){

	GLfloat vec1[3], vec2[3];
	//MAKING TWO VECTORS FROM 3 POINTS
	//VEC1 = V1 - V2
	//VEC2 = V3 - V2
	vec1[0] = v1[0] - v0[0];
	vec1[1] = v1[1] - v0[1];
	vec1[2] = v1[2] - v0[2];

	vec2[0] = v2[0] - v0[0];
	vec2[1] = v2[1] - v0[1];
	vec2[2] = v2[2] - v0[2];

	//SIMPLE CROSS PRODUCT FORMULA
	//TAKE CROSS PRODUCT OF VECTORS TO GET NORMAL
	
	//cx = aybz − azby 
	//cy = azbx − axbz 
	//cz = axby − aybx 

	plane[0] =   vec1[1] * vec2[2] - vec1[2] * vec2[1];
	plane[1] = -(vec1[0] * vec2[2] - vec1[2] * vec2[0]);
	plane[2] =   vec1[0] * vec2[1] - vec1[1] * vec2[0];

	//D = Ax + By + Cz 
	plane[3] = -(plane[0] * v0[0] + plane[1] * v0[1] + plane[2] * v0[2]);
}

////////////////////////////////////THE FOLLOWING FUCNTION WAS TAKEN FROM THE OPENGL CODE///////////////////////////
//https://afni.nimh.nih.gov
void VectortoPolygon(GLfloat data[][2], unsigned int dataSize, GLdouble thickness, GLuint side, GLuint edge, GLuint whole){
  
	static GLUtriangulatorObj *tobj = NULL;
	GLdouble vertex[3], dx, dy, len;
	int count = (int) (dataSize / (2 * sizeof(GLfloat)));

	if (tobj == NULL) 
	{
		tobj = gluNewTess();//Initialising Polygon Object
		gluTessCallback(tobj, GLU_BEGIN, glBegin);
		gluTessCallback(tobj, GLU_VERTEX, glVertex2fv);
		gluTessCallback(tobj, GLU_END, glEnd);
	}
	glNewList(side, GL_COMPILE);
	glShadeModel(GL_SMOOTH);//This is done to minimise tesealtions 
	gluBeginPolygon(tobj); //Start Making from here
	for (int i = 0; i < count; i++) 
	{
		vertex[0] = data[i][0];
		vertex[1] = data[i][1];
		vertex[2] = 0;
		gluTessVertex(tobj, vertex, data[i]);
	}
	gluEndPolygon(tobj);
	glEndList();
	glNewList(edge, GL_COMPILE);
	glShadeModel(GL_FLAT);
	glBegin(GL_QUAD_STRIP);
	
	for (int i = 0; i <= count; i++) 
	{
		//Taking mode so first and last edges can combine
		glVertex3f(data[i % count][0], data[i % count][1], 0.0);
		glVertex3f(data[i % count][0], data[i % count][1], thickness);
		//Calculating unit vectors to calcuate Normal and then we transform and save the matrix along the thickness to get 3D models
		dx = data[(i + 1) % count][1] - data[i % count][1];
		dy = data[i % count][0] - data[(i + 1) % count][0];
		len = sqrt(dx * dx + dy * dy);
		glNormal3f(dx / len, dy / len, 0.0);
	}
	glEnd();
	glEndList();
	glNewList(whole, GL_COMPILE);
	glFrontFace(GL_CW); //CLOCKWISE
	glCallList(edge);
	glNormal3f(0.0, 0.0, -1.0);//First Normal
	glCallList(side);
	glPushMatrix();
	glTranslatef(0.0, 0.0, thickness);
	glFrontFace(GL_CCW); //COUNTER CLOCKWISE
	glNormal3f(0.0, 0.0, 1.0);//Flipped Normal for Other Side
	glCallList(side);
	glPopMatrix();
	glEndList();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FOR DRAWING VERTEXES
typedef enum
{
  NEXT,
  
  BODY_SIDE, BODY_EDGE, BODY_WHOLE, 
  BODYo_SIDE, BODYo_EDGE, BODYo_WHOLE, 
  
  LEG1_SIDE, LEG1_EDGE, LEG1_WHOLE,
  LEG2_SIDE, LEG2_EDGE, LEG2_WHOLE,
  
  LEG1o_SIDE, LEG1o_EDGE, LEG1o_WHOLE,
  LEG2o_SIDE, LEG2o_EDGE, LEG2o_WHOLE,
  
  LEG3_SIDE, LEG3_EDGE, LEG3_WHOLE,
  LEG4_SIDE, LEG4_EDGE, LEG4_WHOLE,
   
  EYE1_SIDE, EYE1_EDGE, EYE1_WHOLE,
  EYE2_SIDE, EYE2_EDGE, EYE2_WHOLE,
  
  HEAD_SIDE, HEAD_EDGE, HEAD_WHOLE,
  HEADo_SIDE, HEADo_EDGE, HEADo_WHOLE,
  
  SP1_SIDE, SP1_EDGE, SP1_WHOLE,
  SP2_SIDE, SP2_EDGE, SP2_WHOLE,
  
  BL1_SIDE, BL1_EDGE, BL1_WHOLE,
  BL2_SIDE, BL2_EDGE, BL2_WHOLE,
  
  SMILE_SIDE, SMILE_EDGE, SMILE_WHOLE
}; 

static void DrawCatWithVertexes(void){

  VectortoPolygon(bod, 	sizeof(bod), 	bodyWidth,		BODY_SIDE, BODY_EDGE, BODY_WHOLE);
  VectortoPolygon(bodo, 	sizeof(bodo), 	bodyWidth /2, 	BODYo_SIDE, BODYo_EDGE, BODYo_WHOLE);
  VectortoPolygon(leg1, 	sizeof(leg1), 	bodyWidth,		LEG1_SIDE, LEG1_EDGE, LEG1_WHOLE);
  VectortoPolygon(leg2, 	sizeof(leg2), 	bodyWidth,	LEG2_SIDE, LEG2_EDGE, LEG2_WHOLE);
  VectortoPolygon(leg1o, 	sizeof(leg1o), bodyWidth,		LEG1o_SIDE, LEG1o_EDGE, LEG1o_WHOLE);
  VectortoPolygon(leg2o, 	sizeof(leg2o), bodyWidth, 	LEG2o_SIDE, LEG2o_EDGE, LEG2o_WHOLE);
  VectortoPolygon(leg3, 	sizeof(leg3), 	bodyWidth,		LEG3_SIDE, LEG3_EDGE, LEG3_WHOLE);
  VectortoPolygon(leg4, 	sizeof(leg4), 	bodyWidth,	LEG4_SIDE, LEG4_EDGE, LEG4_WHOLE);
  VectortoPolygon(eye1, 	sizeof(eye1), 	bodyWidth,		EYE1_SIDE, EYE1_EDGE, EYE1_WHOLE);
  VectortoPolygon(eye2, 	sizeof(eye2), 	bodyWidth, 	EYE2_SIDE, EYE2_EDGE, EYE2_WHOLE);
   VectortoPolygon(head, 	sizeof(head), 	bodyWidth,		HEAD_SIDE, HEAD_EDGE, HEAD_WHOLE);
  VectortoPolygon(heado, 	sizeof(heado), bodyWidth/2, 	HEADo_SIDE, HEADo_EDGE, HEADo_WHOLE);
  VectortoPolygon(sparkle1, 	sizeof(sparkle1),bodyWidth,	SP1_SIDE, SP1_EDGE, SP1_WHOLE);
  VectortoPolygon(sparkle2, 	sizeof(sparkle2),bodyWidth,	SP2_SIDE, SP2_EDGE, SP2_WHOLE);
  VectortoPolygon(blush1, 	sizeof(blush1),bodyWidth,		BL1_SIDE, BL1_EDGE, BL1_WHOLE);
  VectortoPolygon(blush2, 	sizeof(blush2), bodyWidth,	BL2_SIDE, BL2_EDGE, BL2_WHOLE);
  VectortoPolygon(smile, 	sizeof(smile), bodyWidth,	SMILE_SIDE, SMILE_EDGE, SMILE_WHOLE);
}

static void InitialiseCat(void) {

  glPushMatrix();
  //Putting Cat on the Middle of the cavas moving it 15 units ahead
  glTranslatef(-15, 0, -bodyWidth / 2);
  
  glTranslatef(0.0, jump, 0.0); //Translate in y Can add keys to it 

  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[BLACKO]);
  glCallList(BODYo_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[DEEP_PINK]);
  glCallList(BODY_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(BODY_WHOLE);
  
  glTranslatef(0.0, 0.0,+bodyWidth);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[BLACKO]);
  glCallList(HEADo_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[LIGHT_GRAY]);
  glCallList(HEAD_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(HEAD_WHOLE);
  
  glTranslatef(0.0, 0.0,+bodyWidth);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[BLACKO]);
  glCallList(LEG1o_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[LIGHT_GRAY]);
  glCallList(LEG1_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(LEG1_WHOLE);
  
  glTranslatef(0.0, 0.0,+bodyWidth);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[BLACKO]);
  glCallList(LEG2o_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[LIGHT_GRAY]);
  glCallList(LEG2_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(LEG2_WHOLE);
  
  glTranslatef(0.0, 0.0,+bodyWidth);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[LIGHT_GRAY]);
  glCallList(LEG3_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(LEG3_WHOLE);
  
  glTranslatef(0.0, 0.0,+bodyWidth);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[LIGHT_GRAY]);
  glCallList(LEG4_WHOLE);
  glTranslatef(0.0, 0.0, -bodyWidth);
  glCallList(LEG4_WHOLE);
  
  glTranslatef(0.0, 0.0, + bodyWidth + 1 + 1);
  glTranslatef(0.0, 0.0, - bodyWidth - 2 - 1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[BLACK]);
  glCallList(EYE1_WHOLE);
  glCallList(EYE2_WHOLE);
  glCallList(SP1_WHOLE);
  glCallList(SP2_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[WHITE]);
  glCallList(SMILE_WHOLE);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[VIOLET]);
  glCallList(BL1_WHOLE);
  glCallList(BL2_WHOLE);
  glPopMatrix();
}

static GLfloat floorVertices[4][3] = {
  { -20.0, 0.0,  20.0 },
  {  20.0, 0.0,  20.0 },
  {  20.0, 0.0, -20.0 },
  { -20.0, 0.0, -20.0 },
};

///////////////////////////////////////////////////////////////DRAW A PLANE FOR BASE////////////////////////////////////////////////////
static void drawFloor(void){

	//TOOK HELP HERE ONLINE BECAUSE WEIRD THINGS WERE HAPPENING WITH THE LIGHTING
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(floorVertices[0]); //FloorVertices has vectors on each index 
	glTexCoord2f(0.0, 16.0);
	glVertex3fv(floorVertices[1]);
	glTexCoord2f(16.0, 16.0);
	glVertex3fv(floorVertices[2]);
	glTexCoord2f(16.0, 0.0);
	glVertex3fv(floorVertices[3]);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}
/////////////////////////////////////////////// MAIN DISPLAY FUCNTION ///////////////////////////////////////////////////////////////
static GLfloat floorPlane[4];
static GLfloat floorShadow[4][4];

static void RotateScene(void){

	//GL ROTATE SCENE ACCORDING TO THE MOUSE
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	
}

static void Display(void){

	//Clearing Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	//New Position of the Light Source
	lightPosition[0] = 12 * cos(lightAngle);
	lightPosition[1] = lightHeight;
	lightPosition[2] = 12 * sin(lightAngle);
	
	//Directional Light so light only goes to (x, y, z) poition, if it was 1 it would go to all positions
	lightPosition[3] = 0.0;
	
	//Push Shadow Matrix With New Light Source
	shadowMatrix(floorShadow, floorPlane, lightPosition);
	glPushMatrix();
	//Rotate Scene According to the Mouse
	RotateScene();

	//Updating Light Position in GL
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	
	//The Below algorithm is taken from the Univesrity of DUKE Spring 15 cps124 course Notes
	/////////////////////////////////////////////////// REFLECTION START /////////////////////////////////////////////////////
	/////////////////////////////////////////////////// REFLECTION WITH STENCIL START ////////////////////////////////////////
	
	//Currently NYAN is shown under the floor too 
	//With stencil we will only draw the refelection where it clashes with the floor

	//Disabling the GLUT Depth Feature for now, so that the reflection does not go below the floor
	glDisable(GL_DEPTH_TEST);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	//Adding 1s to the Stencil Buffer where the refelction and the floor Meet
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	//ReDraw the floor, Floor pixels with the reflection will have the stencil value as 1
	drawFloor();

	//Re-enabling the DEPTH AND COLOUR MASKS
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	//Draw the Stencil
	//If Stencil Value is 1
	glStencilFunc(GL_EQUAL, 1, 0xffffffff);  
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	
	///////////////////////////////////////////REFLECTION WITH STENCIL END///////////////////////////////////////////////////
	glPushMatrix();
	
	//Now for Refelction Flip upon the Y coordinate, Give the Opposite Direction 
	glScalef(1.0, -1.0, 1.0);
	//ALso FLip the Light Position
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//To keep the normals the same we call this fucntion or they will flip with the light position
	//Doing it just for drawing the cat again
	glEnable(GL_NORMALIZE);
	//Draw the front face
	glCullFace(GL_FRONT);

	//Draw the Reflection
	InitialiseCat();

	//Now again disable Normalise
	glDisable(GL_NORMALIZE);
	glCullFace(GL_BACK);

	//Remove the Reflection
	glPopMatrix();

	//Change back the light Position
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//Now turn off the stencil test
	glDisable(GL_STENCIL_TEST);
	
	/////////////////////////////////////////////////// REFLECTION END ////////////////////////////////////////////////////////

	//Swith Orientation Again to Draw Bottom FLoor
	glColor4f(0.0, 0.1, 0.0, 1.0);
	glFrontFace(GL_CW); //Switch Orientation
	drawFloor();
	glFrontFace(GL_CCW); //Switch Orientation Back

	//Do the Same Stencil thing but now for Shadows
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 3, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//Blend the top floor
	//From OpenGL's official webiste and Suraj Sharma's Tutorials
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0.7, 0.0, 0.0, 0.3);
	glColor4f(1.0, 1.0, 1.0, 0.3);
	
	drawFloor();
	glDisable(GL_BLEND);
	//Draw the real cat again
	InitialiseCat();

	//////////////////////////////////////// MAKING THE SHADOW /////////////////////////////////////////////////////////////

	//////////////////////////////////////// MAKING THE SHADOW STENCIL /////////////////////////////////////////////////////////////
	
	//We had 1 in the stencil for reflections
	//We gave three for shadows
	//We will draw shadows where the value is 3 and update the value to 2
	//To Prevent reblending it
	//Getting the ones in the stencil fucn and replacing them
	
	glStencilFunc(GL_LESS, 2, 0xffffffff);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	
	//////////////////////////////////////// MAKING THE SHADOW STENCIL /////////////////////////////////////////////////////////////
	

	//Black Color with transparency 50% is rendered on top of the previous floor colour for shadows
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING); 
	glColor4f(0.0, 0.0, 0.0, 0.5);

	glPushMatrix();
	//drawing the Shadow now
	glMultMatrixf((GLfloat *) floorShadow);
	InitialiseCat();
	glPopMatrix();

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
	
	//////////////////////////////////////// MAKING THE SHADOW END/////////////////////////////////////////////////////////////

	//////////////////////////////////////// MAKING THE LIGHT /////////////////////////////////////////////////////////////
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.0);
	
	/* Draw an arrowhead. */
	glDisable(GL_CULL_FACE);
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glRotatef(lightAngle * -180.0 / M_PI, 0, 1, 0);
	glRotatef(atan(lightHeight/12) * 180.0 / M_PI, 0, 0, 1);
	// White side - BACK
	glBegin(GL_POLYGON);
	//glColor3f(   1.0,  1.0, 1.0 );
	glVertex3f(  0.5, -0.5, 0.5 );
	glVertex3f(  0.5,  0.5, 0.5 );
	glVertex3f( -0.5,  0.5, 0.5 );
	glVertex3f( -0.5, -0.5, 0.5 );
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	//glColor3f(  1.0,  0.0,  1.0 );
	glVertex3f( 0.5, -0.5, -0.5 );
	glVertex3f( 0.5,  0.5, -0.5 );
	glVertex3f( 0.5,  0.5,  0.5 );
	glVertex3f( 0.5, -0.5,  0.5 );
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	//glColor3f(   0.0,  1.0,  0.0 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	//glColor3f(   0.0,  0.0,  1.0 );
	glVertex3f(  0.5,  0.5,  0.5 );
	glVertex3f(  0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5, -0.5 );
	glVertex3f( -0.5,  0.5,  0.5 );
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	//glColor3f(   1.0,  0.0,  0.0 );
	glVertex3f(  0.5, -0.5, -0.5 );
	glVertex3f(  0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5,  0.5 );
	glVertex3f( -0.5, -0.5, -0.5 );
	glEnd();

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();
	glFinish();
	glutSwapBuffers();
}

////////////////////////////////////////////////////////MOUSE FUNCTIONALITY/////////////////////////////////////////////////////
static void motion(int x, int y){
	if (moving) 
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
	
}

static void mouseFunc(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) 
		{
			moving = 1;
			startx = x;
			starty = y;
		}
		if (state == GLUT_UP) 
		{
			moving = 0;
		}
	}
}

////////////////////////////////////////////////////////ROTATE LIGHT///////////////////////////////////////////////////////////////
static void MoveLight(void){

	lightAngle += 0.05;
	glutPostRedisplay();
}

////////////////////////////////////////////////////////KEYBOARD FUNCTIONALITY/////////////////////////////////////////////////////
static void keyBoardFunc(unsigned char c, int x, int y){

	if (c == 27) 
	exit(0);
	glutPostRedisplay();
}

static void specialFunc(int k, int x, int y)
{
	static float time = 0.0;
	switch(k)
	{
		case GLUT_KEY_UP:
			time = glutGet(GLUT_ELAPSED_TIME) / 500.0;
			jump = 4.0 * fabs(sin(time)*0.5);
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			lightAngle += 0.05;
			break;
		case GLUT_KEY_RIGHT:
			lightAngle -= 0.05;
			break;
	}
	glutPostRedisplay();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutCreateWindow("JUMPING NYAN CAT");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//GLUT CALL BACKS
	glutDisplayFunc(Display);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyBoardFunc);
	glutSpecialFunc(specialFunc);
	glutMotionFunc(motion);
	//Enable This Fucntion for auto Movement 
	//For now I have enabled movement of light with keys
	//glutIdleFunc(MoveLight);
	DrawCatWithVertexes();
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glLineWidth(3.0);//Rasterization Line Width

	glMatrixMode(GL_PROJECTION);
	gluPerspective( 40.0, 1.0, 20.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(	0.0, 8.0, 60.0, //Initial Eye Position
			0.0, 8.0, 0.0,      
			0.0, 1.0, 0.0);      

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, colors[WHITE]);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	makeFloorTexture();

	//Set up Floor For Shadow 
	findPlane(floorPlane, floorVertices[1], floorVertices[2], floorVertices[3]);
	glutMainLoop();
	
	return 0;
}

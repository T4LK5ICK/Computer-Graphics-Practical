//2018csc1055
//ArshdeepSinghBhatia

#include <GL/glut.h>
#include<stdlib.h>
#include <math.h>

#define PI 3.14159265f
// Global variables

GLfloat ballRadius = 0.3f;   // Radius of the smiley
GLfloat ballX = -1.0f;         // smiley's center (x, y) position
GLfloat ballY = -0.5f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin; // smiley's center (x, y) bounds
GLfloat xSpeed = -0.020f;      // smiley's speed in x and y directions
GLfloat ySpeed = 0.040f;
float xt=1.0,yt=1.0; 

// Projection clipping area
GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
void Osmiley()
{
   glPushMatrix();
   glPushMatrix();                   //face of smiley
   glColor3f(1.0,1.0,0.0);            //yellow
   glutSolidSphere(ballRadius,80,80);
   glPopMatrix();

   glPushMatrix();                 //Eyes of smiley
    glColor3f(0.0,0.0,0.0);        //black
    glTranslatef(0.1,0.10,0.0);
    glutSolidSphere(0.03,80,80);
    glPopMatrix();

    glPushMatrix();                 //Eyes of smiley
    glColor3f(0.0,0.0,0.0);         //black
    glTranslatef(-0.1,0.10,0.0);
    glutSolidSphere(0.03,80,80);
    glPopMatrix();


 glPopMatrix();
    glPushMatrix();                 //mouth of smiley
    glTranslatef(0.0,-0.15,0.0);
    glColor3f(0.0,0.0,0.0);         //black
    glutSolidSphere(0.06,80,80);
    glPopMatrix();
    glPopMatrix();
	

}



/* Callback handler for window re-paint event */
void display() {
	
    glClearColor(0.0, 0.0, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
   glLoadIdentity();              // Reset model-view matrix
   glBegin(GL_QUADS);
//red color
glColor3f(1.0,0.0,0.0);
glVertex2f(-1.0, 1.0);
glVertex2f(-1.0,-1.0);
//blue color
glColor3f(0.0,0.0,1.0);
glVertex2f(1.0,-1.0);
glVertex2f(1.0, 1.0);
glEnd();
	glTranslatef(xt,yt,0.0);
	glTranslatef(-1,-1,0.0);
  {glTranslatef(ballX, ballY, 0.0f);  // Translate to (xPos, yPos)
   // Use triangular segments to form a circle
   {glPushMatrix();
   Osmiley();
 
   glPopMatrix();
 
   }

   glutSwapBuffers();  // Swap front and back buffers (of double buffered mode)
// Animation Control - compute the location for the next refresh
   ballX += xSpeed;
   ballY += ySpeed;
   // Check if the smiley exceeds the edges
  {if (ballX > ballXMax) {
      ballX = ballXMax;
      xSpeed = -xSpeed;
   } else if (ballX < ballXMin) {
      ballX = ballXMin;
      xSpeed = -xSpeed;
   }
   if (ballY > ballYMax) {
      ballY = ballYMax;
      ySpeed = -ySpeed;
   } else if (ballY < ballYMin) {
      ballY = ballYMin;
      ySpeed = -ySpeed;
   }
   glutPostRedisplay();
  }
  }
}

/* Call back when the windows is re-sized */
void reshape(GLsizei width, GLsizei height) {
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);

   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset the projection matrix
   if (width >= height) {
      clipAreaXLeft   = -1.0 * aspect;
      clipAreaXRight  = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop    = 1.0;
   } else {
      clipAreaXLeft   = -1.0;
      clipAreaXRight  = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop    = 1.0 / aspect;
   }
   gluOrtho2D(clipAreaXLeft-0.5, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
   ballXMin = clipAreaXLeft + ballRadius;
   ballXMax = clipAreaXRight - ballRadius;
   ballYMin = clipAreaYBottom + ballRadius;
   ballYMax = clipAreaYTop - ballRadius;

}



void keyboardkey(GLubyte key, int x, int y) // For keyboard interactive
{
switch ( key )
{
case 'd':
xt += 0.05; 
glColor3f(0.0,1.0,0.0);
glutPostRedisplay();
break;

case 'a':
xt -= 0.05;
glColor3f(1.0,0.0,0.0);
glutPostRedisplay();
break;

case 's':
yt -= 0.05;
glColor3f(0.0,0.0,0.0);
glutPostRedisplay();
break;

case 'w':
yt += 0.05;
glColor3f(0.0,0.0,1.0);
glutPostRedisplay();
break;

case 'e':
xt += 0.05;
yt += 0.05;
glColor3f(1.0,0.0,1.0);
glutPostRedisplay();
break;

case 'q':
xt -= 0.05;
yt += 0.05;
glColor3f(0.0,1.0,1.0);
glutPostRedisplay();
break;
case 'c':
xt += 0.05;
yt -= 0.05;
glColor3f(1.0,0.0,1.0);
glutPostRedisplay();
break;
case 'z':
xt -= 0.05;
yt -= 0.05;
glColor3f(0.0,0.0,1.0);
glutPostRedisplay();
break;
case 'r':
xt +=rand()%(1-0 + 1) + 0;
yt += 0.05;
glColor3f(0.0,1.0,1.0);
glutPostRedisplay();
break;


default :exit(0);
break;
}
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutCreateWindow("Smiley");// Create window with given title
   glutFullScreen();
	
	
   glutDisplayFunc(display);     // Register callback handler for window re-paint
   
   glutKeyboardFunc(keyboardkey);
   
   glutMainLoop();               // Enter event-processing loop
   return 0;
}

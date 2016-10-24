

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <cstdlib>
#else
#include "freeglut.h"
#endif

#include <stdio.h>
#include <math.h>
// NATE ROBINS' OBJ MODEL LOADER (http://devernay.free.fr/hacks/glm/)
#include "glm.h" /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

float posx,posz,speed;
int pos_road;
GLfloat*	mat0_specular;
GLfloat*	mat0_diffuse;
GLfloat*	mat0_shininess;
GLfloat*	light0_position;

GLMmodel*	corner;
GLMmodel*   straight;
GLMmodel*   drive;
GLMmodel*   interior;
GLuint texturaS;
void init(void)
{
    posx=0;
    posz=0;
    speed=0.5;
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    //glGenTextures( 1, &texturaS );
    //glBindTexture( GL_TEXTURE_2D, texturaS);
    
    glClearColor(0.2, 0.2, 0.2, 1.0);

    straight = glmReadOBJ("/Users/Carly/Documents/Tec/7 semestre/Gráficas/Final project/FinalProject/FinalProject/straight.obj");
    drive = glmReadOBJ("/Users/Carly/Documents/Tec/7 semestre/Gráficas/Final project/FinalProject/FinalProject/drive.obj");
    interior = glmReadOBJ("/Users/Carly/Documents/Tec/7 semestre/Gráficas/Final project/FinalProject/FinalProject/car-interior.obj");
    // When the model is too big make it fit inside a 1x1x1 cube:
    glmUnitize(straight);
    glmUnitize(drive);
    glmUnitize(interior);
    // You can also scale it later:
    glmScale(straight,4.0f);
    glmScale(drive, 4.0f);
    glmScale(interior,0.5f);
    light0_position = new GLfloat[4];
    light0_position[0] = 3;
    light0_position[1] = 3;
    light0_position[2] = 0;
    light0_position[3] = 1; // POINT LIGHT
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    
    mat0_specular = new GLfloat[4];
    mat0_specular[0] = 1.0f;
    mat0_specular[1] = 1.0f;
    mat0_specular[2] = 1.0f;
    mat0_specular[3] = 1.0f;
    
    mat0_diffuse = new GLfloat[4];
    mat0_diffuse[0] = 0.8f;
    mat0_diffuse[1] = 0.7f;
    mat0_diffuse[2] = 0.6f;
    mat0_diffuse[3] = 1.0f;
    
    mat0_shininess = new GLfloat[1];
    mat0_shininess[0] = 100.0f;
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_TEXTURE_2D);
}

void display(void)
{
    posz+=speed;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posx,1.0,4.7-posz,posx,0,-posz,0,1,0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat0_shininess);
    glPushMatrix();{
        glTranslatef(posx,0.5f,4.0f-posz);
        glRotatef(180,0,1,0);
        glmDraw(interior, GLM_SMOOTH);
        
    }glPopMatrix();
    glPushMatrix();
    {
        glRotatef(90,0,1,0);
        glTranslatef(-8.0,0.0f,0.0f);
        for(int i=posz/2;i<20+posz;i++){
            glTranslatef(8.0,0.0f,0.0f);
            glmDraw(drive,GLM_SMOOTH | GLM_TEXTURE);
            glTranslatef(8.0,0.0f,0.0f);
            glmDraw(straight, GLM_SMOOTH | GLM_TEXTURE);
        }
    }glPopMatrix();
    glutSwapBuffers();
    
}

void idle (void)
{
    
    glutPostRedisplay ();
}

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 0.01, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.1,4.8, 0, 0, 0, 0, 1,0);
}
void keyboard( unsigned char key, int x, int y )
{
    switch( key )
    {
        case 'a':
            if(posx>-1.5){
                posx-=1;
            }
            break;
        case 's':
            if(posx<1.5){
                posx+=1;
            }
            break;
        case 'w':
            speed+=0.1;
            break;
        case 'z':
            speed-=0.1;
            break;
        case 27:
            //glmDelete( sintel );
            //exit(0);
            break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 800); 
    glutInitWindowPosition (100, 50);
    glutCreateWindow ("OBJ Loader!");
    glutReshapeFunc (reshape);
    init ();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); 
    glutIdleFunc (idle);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}




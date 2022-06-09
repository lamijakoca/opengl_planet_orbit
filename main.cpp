/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <GL/glut.h>

float rotationSpeed = 0.0;
float rotationSpeed01 = 0.0;
float rotationSpeed02 = 0.0;
float rotationSpeed03 = 0.0;
float selfAngle = 0.0;

void createPlanet(float rad){
    float _angle = 0.0f;
    glLineWidth(3.0);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 100; i++)
        {
            _angle = 2 * 3.1416 * i/100;
            glVertex3f(rad*cos(_angle), 0.0, rad*sin(_angle));
        }
    glEnd();
}
void scene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(-60,40,0,0,0,0,0,1,0);

    //sunce
    glPushMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(1.0,0.5,0.0);
        glutSolidSphere(6.5,15,15);
        glEnable(GL_LIGHTING);
    glPopMatrix();

    //merkur
    createPlanet(12.0);
    glPushMatrix();
        glTranslatef(12 * cos(rotationSpeed/0.25), 0, 12.0 * sin(rotationSpeed/0.25));
        glRotatef(selfAngle, 0.0, 1.0, 0.0);
        glDisable(GL_LIGHTING);
        glColor3f(0.0,0.7,0.4); //zeleno
        glutSolidSphere(1.5, 15, 15);
        glEnable(GL_LIGHTING);
    glPopMatrix();

    //venera
    createPlanet(19.0);
    glPushMatrix();
        glTranslatef(19.0*cos(rotationSpeed01/0.25), 0.0, 19.0*sin(rotationSpeed01/0.25));
        glRotatef(selfAngle, 0.0f, 1.0f, 0.0f);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 0.9, 0.7); //puder
        glutSolidSphere(3.0, 15, 15);
        glEnable(GL_LIGHTING);
    glPopMatrix();
    //zemlja
    createPlanet(27.0);
    glPushMatrix();
        glTranslatef(27.0*cos(rotationSpeed02/0.25), 0.0, 27.0*sin(rotationSpeed02/0.25));
        glRotatef(selfAngle, 0.0f, 1.0f, 0.0f);
        glDisable(GL_LIGHTING);
        glColor3f(0.0, 0.5, 0.9); //plavo
        glutSolidSphere(3.5, 15, 15);
        glEnable(GL_LIGHTING);
    glPopMatrix();

    //jupter
    createPlanet(35.0);
    glPushMatrix();
        glTranslatef(35.0*cos(rotationSpeed01/0.25), 0.0, 35.0*sin(rotationSpeed01/0.25));
        glRotatef(selfAngle, 0.0f, 1.0f, 0.0f);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 0.5, 0.9); //rozikasto
        glutSolidSphere(5.0, 15, 15);
        glEnable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();
}
void initialization(){
    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);

    GLfloat shiness[] = {50.0};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {0.0, 1.0, 1.0, 0.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_DEPTH_TEST);
}

void handleKeys(unsigned char key, int x, int y){
    switch(key){
    case 27:    //esc
        exit(0);
    }
}

void spining(void)
{
    rotationSpeed = rotationSpeed + 0.0006;
    rotationSpeed01 = rotationSpeed01 + 0.0004;
    rotationSpeed02 = rotationSpeed02 + 0.0002;
    rotationSpeed03 = rotationSpeed03 + 0.0001;
    glutPostRedisplay();
}
void reshaping(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.4,0.4,-0.3,0.3,0.5,2000);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void spining(int x)
{
    selfAngle = selfAngle + 1.5f;
    if(selfAngle > 360)
    {
        selfAngle = -360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, spining, 0);

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Planet Orbit");

    initialization();

    glutDisplayFunc(scene);
    glutReshapeFunc(reshaping);
    glutIdleFunc(spining);
    glutKeyboardFunc(handleKeys);
    glutTimerFunc(25, spining, 0);

    glutMainLoop();
}

/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

 /*
  * robot.c
  * This program shows how to composite modeling transformations
  * to draw translated and rotated hierarchical models.
  * Interaction:  pressing the s and e keys (shoulder and elbow)
  * alters the rotation of the robot arm.
  */
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>


static int shoulder = 0, elbow = 0, fingerBase = 0, fingerUp = 0;
int moving, startx, starty;


GLfloat angle1 = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle1, 0.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(1.0, 0.3, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, -0.3, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.6, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
    //Draw finger flangBase 1 mid
    glTranslatef(1.0, 0.2, 0.0);
    glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.05, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flangBase 2  most right 
    //glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.25);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();


    //Draw finger flangBase 3 most left 
    //glRotatef((GLfloat)fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -0.5);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();


    //Draw finger flangup 2  mid
    glTranslatef(0.15, -0.05, 0.25);
    glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.05, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flangup 3 most right
    //glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.25);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flangup 4 most left
    //glRotatef((GLfloat)fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -0.5);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();



    glPopMatrix();

    //Draw finger flangBase 4 down 
    glTranslatef(1.0, -0.2, 0.0);
    glRotatef((GLfloat)-fingerBase, 0.0, 0.0, 1.0);
    glTranslatef(0.15, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    //Draw finger flangup 1 down 
    glTranslatef(0.15, 0.0, 0.0);
    glRotatef((GLfloat)-fingerUp, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.3, 0.1, 0.1);
    glutWireCube(1);
    glPopMatrix();

    std::cout << "shoulder angel:" <<shoulder << std::endl;
    std::cout << "elbow angel:" << elbow << std::endl;
    std::cout << "fingerBase angel:" << fingerBase << std::endl;
    std::cout << "fingerUp angel:" << fingerUp << std::endl;

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)width / (GLfloat)height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        shoulder += 5;
        if (shoulder > 60) shoulder = 60;
        glutPostRedisplay();
        break;
    case 'S':
        shoulder -= 5;
        if (shoulder < -80) shoulder = -80;
        glutPostRedisplay();
        break;
    case 'e':
        elbow += 5;
        if (elbow > 160) elbow = 160;
        glutPostRedisplay();
        break;
    case 'E':
        elbow -= 5;
        if (elbow < 0) elbow = 0;
        glutPostRedisplay();
        break;
    case 'f':
        fingerBase += 5;
        if (fingerBase > 0) fingerBase = 0;
        glutPostRedisplay();
        break;
    case 'F':
        fingerBase -= 5;
        if (fingerBase < -((fingerUp + 45) / 2)) fingerBase += 5;
        glutPostRedisplay();
        break;
    case 'g':
        fingerUp += 5;
        if (fingerUp > 0) fingerUp = 0;
        glutPostRedisplay();
        break;
    case 'G':
        fingerUp -= 5;
        if (fingerUp < -45 - 2 * fingerBase) fingerUp += 5;
        glutPostRedisplay();
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle1 = angle1 + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(400, 200);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
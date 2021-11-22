#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define PI 3.14

static int shoulder = 0, elbow = 0, body = 0;
static int leftLegZ = 0, leftLegX = 0, leftKneeZ = 0, leftKneeX = 0, LeftFoot = 0;
//static int fingerBase1 = 0, fingerUp1 = 0;
//static int fingerBase2 = 0, fingerUp2 = 0;
//static int fingerBase3 = 0, fingerUp3 = 0;
//static int fingerBase4 = 0, fingerUp4 = 0;
//static int fingerBase5 = 0, fingerUp5 = 0;


static int shoulder_2 = 0, elbow_2 = 0;
static int rightLegZ = 0, rightLegX = 0, rightKneeZ = 0, rightKneeX = 0, RightFoot = 0;
//static int fingerBase1_2 = 0, fingerUp21 = 0;
//static int fingerBase22 = 0, fingerUp22 = 0;
//static int fingerBase23 = 0, fingerUp23 = 0;
//static int fingerBase24 = 0, fingerUp24 = 0;
//static int fingerBase25 = 0, fingerUp25 = 0;

int moving, startx, starty;

GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

//  camera
double eye[] = { 0, 0, 2 };
double center[] = { 0, 0, 0 };
double up[] = { 0.0, 1.0, 0.0 };


void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, 1.0, 1.0, 20.0);

}

void reset()
{
    double e[] = { 0.0, 0.0, 2 };
    double c[] = { 0.0, 0.0, 1.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
    shoulder = 0, elbow = 0, body = 0, leftLegZ = 0, leftLegX = 0, leftKneeZ = 0, leftKneeX = 0;
    shoulder_2 = 0, elbow_2 = 0, rightLegZ = 0, rightLegX = 0, rightKneeZ = 0, rightKneeX = 0;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);

    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);

    // The Chest(body) of robot:
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)body, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.5, 4.0, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    //  The Head of Robot:
    glPushMatrix();
    glTranslatef(0.0, 2.6, 0.0);
    glutWireSphere(0.42, 10, 10);
    glPopMatrix();
    glPopMatrix();

    //  The Right Arm of Robot:
    // The Shoulder:
    glPushMatrix();
    glTranslatef(-0.9, 1.85, 0.0);
    glRotatef((GLfloat)shoulder_2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    // The Elbow:
    glTranslatef(-0.15, -0.625, 0.0);
    glRotatef((GLfloat)elbow_2, 0.0, 0.0, 1.0);
    glTranslatef(0.15, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    //The Fingers:
    //The first finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, -0.1);
    //glRotatef((GLfloat)fingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    // the second finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    // the third finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.1);
    //glRotatef((GLfloat)fingerBase3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    // the fourth finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    //  The Left Arm of Robot:
    //  The Shoulder
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.9, 1.85, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    //  The Elbow:
    glTranslatef(0.15, -0.625, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(-0.15, -0.625, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    // The fingers:
    //  The first finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, -0.1);
    //glRotatef((GLfloat)fingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The second finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The third finger:
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.1);
    //glRotatef((GLfloat)fingerBase3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    //  The fourth finger:
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    //glRotatef((GLfloat)fingerBase4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    //glRotatef((GLfloat)fingerUp4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();


    //   The Right Leg of Robot:
    // The leg
    glPushMatrix();
    glTranslatef(-0.55, -2.0, 0.0);
    glRotatef((GLfloat)rightLegZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightLegX, 1.0, 0.0, 0.0);
    glTranslatef(0.05, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    // The Knee:
    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)rightKneeZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightKneeX, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    // The foot:
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)RightFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();


    //  The Left Leg of Robot:
    // The leg:
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.55, -2.0, 0.0);
    glRotatef((GLfloat)leftLegZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftLegX, 1.0, 0.0, 0.0);
    glTranslatef(-0.05, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    // The Knee:
    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)leftKneeZ, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftKneeX, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    // The Foot:
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)LeftFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();

}

// Turn Camera Right:

void lookRight()
{
    rotatePoint(up, PI / 20, eye);
}

// Turn Camera Left:
void lookLeft()
{
    rotatePoint(up, -PI / 20, eye);
}

// Turn Camera Up:
void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 20, eye);
    rotatePoint(horizontal, PI / 20, up);
}

// Turn Camera Down:
void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 20, eye);
    rotatePoint(horizontal, -PI / 20, up);
}

// Move Forward :
void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    double speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;
    // restriction for the forward limit:
    if (eye[2] < -3.6) eye[2] = -3.6;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;


    if (center[2] < -5.6) center[2] = -5.6;

}

// Move Backword:
void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    double speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;
    // restriction for the backward limit:
    if (eye[2] > 13.2) eye[2] = 13.2;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;

    
    if (center[2] > 11.2) center[2] = 11.2;


}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

// Camera Tranformations:
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        //camera's keys
    case '+':
        moveForward();
        glutPostRedisplay();
        break;
    case '-':
        moveBackword();
        glutPostRedisplay();
        break;
        //Reset:
    case '0':
        reset();
        glutPostRedisplay();
        break;

        //   Left Arm
        // Shoulder 
    case 's':
        shoulder += 5;
        if (shoulder > 140) shoulder = 140;
        glutPostRedisplay();
        break;
    case 'S':
        shoulder -= 5;
        if (shoulder < 0) shoulder = 0;
        glutPostRedisplay();
        break;
        //elbow:
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

        //  right Arm
        // Shoulder 
    case 'a':
        shoulder_2 -= 5;
        if (shoulder_2 < -140) shoulder_2 = -140;
        glutPostRedisplay();
        break;
    case 'A':
        shoulder_2 += 5;
        if (shoulder_2 > 0) shoulder_2 = 0;
        glutPostRedisplay();
        break;
        // Elbow
    case 'w':
        elbow_2 -= 5;
        if (elbow_2 < -160) elbow_2 = -160;
        glutPostRedisplay();
        break;
    case 'W':
        elbow_2 += 5;
        if (elbow_2 > 0) elbow_2 = 0;
        glutPostRedisplay();
        break;

        // Right Leg
        //Leg rotation about x axis:
    case 'x':
        rightLegX -= 5;
        if (rightLegX < -90) rightLegX = -90;
        glutPostRedisplay();
        break;
    case 'X':
        rightLegX += 5;
        if (rightLegX > 35) rightLegX = 35;
        glutPostRedisplay();
        break;
        //Leg rotation about z axis:
    case 'd':
        rightLegZ -= 5;
        if (rightLegZ < -25) rightLegZ = -25;
        glutPostRedisplay();
        break;
    case 'D':
        rightLegZ += 5;
        if (rightLegZ > 10) rightLegZ = 10;
        glutPostRedisplay();
        break;
        //Knee rotation about x axis:
    case 'z':
        rightKneeX -= 5;
        if (rightKneeX < 0) rightKneeX = 0;
        glutPostRedisplay();
        break;
    case 'Z':
        rightKneeX += 5;
        if (rightKneeX > 90) rightKneeX = 90;
        glutPostRedisplay();
        break;
        //Knee rotation about z axis:
    case 'r':
        rightKneeZ -= 5;
        if (rightKneeZ < -10) rightKneeZ = -10;
        glutPostRedisplay();
        break;
    case 'R':
        rightKneeZ += 5;
        if (rightKneeZ > 30) rightKneeZ = 30;
        glutPostRedisplay();
        break;
        //Foot:
    case 'n':
        RightFoot += 5;
        if (RightFoot > 30) RightFoot = 30;
        glutPostRedisplay();
        break;
    case 'N':
        RightFoot -= 5;
        if (RightFoot < -10) RightFoot = -10;
        glutPostRedisplay();
        break;


        // Left Leg
        //leg rotation about z axis:
    case 'f':
        leftLegZ += 5;
        if (leftLegZ > 25) leftLegZ = 25;
        glutPostRedisplay();
        break;
    case 'F':
        leftLegZ -= 5;
        if (leftLegZ < -10) leftLegZ = -10;
        glutPostRedisplay();
        break;
        //leg rotation about x axis:
    case 'c':
        leftLegX -= 5;
        if (leftLegX < -90) leftLegX = -90;
        glutPostRedisplay();
        break;
    case 'C':
        leftLegX += 5;
        if (leftLegX > 35) leftLegX = 35;
        glutPostRedisplay();
        break;

        //Knee rotation about z axis:
    case 't':
        leftKneeZ += 5;
        if (leftKneeZ > 10) leftKneeZ = 10;
        glutPostRedisplay();
        break;
    case 'T':
        leftKneeZ -= 5;
        if (leftKneeZ < -30) leftKneeZ = -30;
        glutPostRedisplay();
        break;

        //Knee rotation about x axis:
    case 'v':
        leftKneeX -= 5;
        if (leftKneeX < 0) leftKneeX = 0;
        glutPostRedisplay();
        break;
    case 'V':
        leftKneeX += 5;
        if (leftKneeX > 90) leftKneeX = 90;
        glutPostRedisplay();
        break;
        //Foot:
    case 'm':
        LeftFoot += 5;
        if (LeftFoot > 30) LeftFoot = 30;
        glutPostRedisplay();
        break;
    case 'M':
        LeftFoot -= 5;
        if (LeftFoot < -10) LeftFoot = -10;
        glutPostRedisplay();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(300, 70);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}

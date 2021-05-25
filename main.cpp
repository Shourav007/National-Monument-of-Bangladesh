
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include<bits/stdc++.h>
#include "bmploader.h"

using namespace std;

#define PI 3.1415927

unsigned int ID;
static int slices = 16;
static int stacks = 16;

const int width = 500;
const int height = 500;
vector <int> v;


GLfloat eyex = 1;
GLfloat eyey = 13;
GLfloat eyez =40;

GLfloat refx = 0;
GLfloat refy = 10;
GLfloat refz = -5;

double r =0;

float l_height = 10;
float spt_cutoff = 40;


float rot = 0;

bool light1=true, light2=false, light3=false;
bool diff_light_on=true, spec_light_on=true, amb_light_on=true;

bool spotlight_on = true;



bool monument_emission=true;
bool light_led_emission =true;
bool a=true;
bool d=true;
bool s = true;


static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte quadIndices[1][4] =
{
    {0, 3, 2, 1}
};

static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};



static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1,
                        GLfloat x2, GLfloat y2, GLfloat z2,
                        GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}



void drawpyramid(float r, float g, float b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_pyramid[quadIndices[i][0]][0], v_pyramid[quadIndices[i][0]][1], v_pyramid[quadIndices[i][0]][2],
                    v_pyramid[quadIndices[i][1]][0], v_pyramid[quadIndices[i][1]][1], v_pyramid[quadIndices[i][1]][2],
                    v_pyramid[quadIndices[i][2]][0], v_pyramid[quadIndices[i][2]][1], v_pyramid[quadIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 1.0,150.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}




static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {3,1,5,7},  //front
    {6,4,0,2},  //back
    {2,3,7,6},  //top
    {1,0,4,5},  //bottom
    {7,5,4,6},  //right
    {2,0,1,3}   //left
};



void set_mat_prop(float colR=0.5, float colG=0.5, float colB=0.5, bool em=false, float shine=128)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { colR, colG, colB, 1.0 };
    GLfloat mat_diffuse[] = { colR, colG, colB, 1.0 };
    GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_emission[] = {colR, colG, colB, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(em)
        glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission);
    else
        glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);
}

void cube(float colR=0.5, float colG=0.5, float colB=0.5,
          bool em=false, float val=1, float shine=128)
{
    set_mat_prop(colR,colG,colB,em,shine);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        glTexCoord2f(0,val);
        glVertex3fv(&v_cube[c_ind[i][0]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[c_ind[i][1]][0]);
        glTexCoord2f(val,0);
        glVertex3fv(&v_cube[c_ind[i][2]][0]);
        glTexCoord2f(val,val);
        glVertex3fv(&v_cube[c_ind[i][3]][0]);
    }
    glEnd();
}


void axes()
{
    float length = 15;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}

void MonumentDesign()
{




    float x1 = 0.2, x2, _x1 = -.2, _x2, _z1 = -0.2, _z2, y1 = 3.0, y2;
    float r = 1, g = 1, b = 1;

    for(int i = 0; i < 7; i++)
    {
        x2 = x1+0.1;
        _x2 = _x1-0.1;
        _z2 = _z1-0.1;
        y2 = y1+0.1;

        //glColor3d(r,g,b);
        set_mat_prop(r,g,b,monument_emission);

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, _z1);//v2
        glVertex3f(x1, 0, 0);//v1
        glVertex3f(0, y1, _z1);//v3
        glVertex3f(_x1, 0, 0);//v4
        glEnd();


        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, 0, _z2);//v2
        glVertex3f(x2, 0, 0);//v1
        glVertex3f(0, y2, _z1-0.1);//v3
        glVertex3f(_x2, 0, 0);//v4
        glEnd();

        //glColor3d(r-.1,g-.1,b-.1);
        set_mat_prop(r-.1,g-.1,b-.1,monument_emission);

        glBegin(GL_QUADS);
        glVertex3f(x1, 0, 0);
        glVertex3f(x2, 0, 0);
        glVertex3f(0, y2, _z1-0.1);
        glVertex3f(0, y1, _z1);
        glEnd();


        glBegin(GL_QUADS);
        glVertex3f(_x1, 0, 0);
        glVertex3f(_x2, 0, 0);
        glVertex3f(0, y2, _z1-0.1);
        glVertex3f(0, y1, _z1);
        glEnd();

        x1 += 0.3;
        _x1 -= 0.3;
        _z1 -= 0.3;
        y1 -= 0.4;


        r -= 0.05;
        g -= 0.05;
        b -= 0.05;
    }


}

void MonumentFront()
{
    //glColor3d(.9,0.9,0.9);
    set_mat_prop(.9,0.9,0.9);
    glBegin(GL_QUADS);
    glVertex3f(-0.1, 1.55, -0.1);
    glVertex3f(-0.1, 1.45, -0.1);
    glVertex3f(0.1, 1.45, -0.1);
    glVertex3f(0.1, 1.55, -0.1);
    glEnd();

    //glColor3d(0.8,0.8,0.8);
    set_mat_prop(0.8,0.8,0.8);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.25, -0.2);//v2
    glVertex3f(-0.1, 1.45, -0.1);//v1
    glVertex3f(0.1, 1.45, -0.1);//v3
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0, 2.7, -0.2);//v2
    glVertex3f(-0.1, 1.55, -0.1);//v1
    glVertex3f(0.1, 1.55, -0.1);//v3
    glEnd();
}

void myFlag()
{
    glColor3f(0.8,0.4,0.2);
    glBegin(GL_QUADS);
    glVertex3f(1.5,0,0.5);
    glVertex3f(1.6,0,0.5);
    glVertex3f(1.6,2.5,0.5);
    glVertex3f(1.5,2.5,0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.5,0,0.45);
    glVertex3f(1.6,0,0.45);
    glVertex3f(1.6,2.5,0.45);
    glVertex3f(1.5,2.5,0.45);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.5,0,0.5);
    glVertex3f(1.5,0,0.45);
    glVertex3f(1.5,2.5,0.45);
    glVertex3f(1.5,2.5,0.5);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.6,0,0.5);
    glVertex3f(1.6,0,0.45);
    glVertex3f(1.6,2.5,0.45);
    glVertex3f(1.6,2.5,0.5);
    glEnd();

    glColor3f(0,0.5,0.1);

    glBegin(GL_QUADS);
    glVertex3f(1.6,2.3,0.5);
    glVertex3f(1.6,1.6,0.5);
    glVertex3f(2.5,1.6,0.5);
    glVertex3f(2.5,2.3,0.5);
    glEnd();

    glColor3f(1, 0, 0);
    glTranslated(2.08,1.96,0.52);
    glScalef(0.2,0.2,0);
    glutSolidSphere(1,slices,stacks);


}

void myTranslate(GLfloat dx,GLfloat dy, GLfloat dz)
{
    //GLfloat dx=0,dy=0,dz=0;
    //unsigned char k;

    GLfloat m[15];
    m[0] = 1;
    m[4] = 0;
    m[8] = 0;
    m[12] = dx;
    m[1] = 0;
    m[5] = 1;
    m[9] = 0;
    m[13] = dy;
    m[2] = 0;
    m[6] = 0;
    m[10] = 1;
    m[14] = dz;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[15] = 1;

    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);



}


float Cos(float theta)
{
    return cos(theta*3.1416/180);
}

float Sin(float theta)
{
    return sin(theta*3.1416/180);
}

float tanI(float val)
{
    return atan(val);
}
static void rotateCamera( float theta=5.0)
{
    float newx =  eyex - refx;   //x-refX;
    float newz =  eyez - refz;               //y-refY;

    float rx, rz;
    rx = newx*Cos(theta)-newz*Sin(theta);
    rz = newx*Sin(theta)+newz*Cos(theta);

    newx = rx+refx;
    newz = rz+refz;
    eyex = newx;
    eyez = newz;
    //cout<<newx<<" "<<newy<<endl;
    //return cod;

}

static void rotate_by_clockwise(bool state=1)
{
    r = sqrt( (eyex - refx)*(eyex - refx) + (eyez - refz)*(eyez - refz));
    printf("r = %lf\n",r);
    if(state )
    {
        if(eyex<=r && eyex>=0)
        {
            if(eyez<=r && eyez>=0)
            {
                eyex +=1;
                eyez -=1;
            }
            else if(eyez<=0 && eyez>=-r)
            {
                eyex -=1;
                eyez -=1;
            }
        }
        else if(eyex<=0 && eyex>=-r)
        {
            if(eyez<=r && eyez>=0)
            {
                eyex +=1;
                eyez +=1;
            }
            else if(eyez<=0 && eyez>=-r)
            {
                eyex -=1;
                eyez +=1;
            }
        }

    }
    printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
}



static void rotate_by_anticlockwise(bool state=1)
{

    r = sqrt( (eyex - refx)*(eyex - refx) + (eyez - refz)*(eyez - refz));
    printf("r = %lf\n",r);
    if(state )
    {
        if(eyex<=r && eyex>=0)
        {
            if(eyez<=r && eyez>=0)
            {
                eyex -=1;
                eyez +=1;
            }
            else if(eyez<=0 && eyez>=-r)
            {
                eyex +=1;
                eyez +=1;
            }
        }
        else if(eyex<=0 && eyex>=-r)
        {
            if(eyez<=r && eyez>=0)
            {
                eyex -=1;
                eyez -=1;
            }
            else if(eyez<=0 && eyez>=-r)
            {
                eyex +=1;
                eyez -=1;
            }
        }

    }
    printf("anti %f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
}


void sphere(float rad, int slices, int stacks,
            float colR=0.5, float colG=0.5, float colB=0.5, bool em=false, float shine=128)
{
    set_mat_prop(colR,colG,colB,em,shine);
    glutSolidSphere(rad, slices, stacks);
}


void light(GLenum light_num, float posX, float posY, float posZ,
           bool spot=false, float spot_cut=15, float amb=0.2, float homogeneous=1)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {amb, amb, amb, 1.0};
    GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1, 1, 1, 1.0};
    GLfloat light_position[] = {posX, posY, posZ, homogeneous};
    GLfloat light_attenuation[] = {1,0,0.0002};


    glEnable(light_num);

    if(amb_light_on)
        glLightfv(light_num, GL_AMBIENT, light_ambient);
    else
        glLightfv(light_num, GL_AMBIENT, no_light);

    if(diff_light_on)
        glLightfv(light_num, GL_DIFFUSE, light_diffuse);
    else
        glLightfv(light_num, GL_DIFFUSE, no_light);

    if(spec_light_on)
        glLightfv(light_num, GL_SPECULAR, light_specular);
    else
        glLightfv(light_num, GL_SPECULAR, no_light);

    glLightf(light_num, GL_CONSTANT_ATTENUATION, light_attenuation[0]);
    glLightf(light_num, GL_LINEAR_ATTENUATION, light_attenuation[1]);
    glLightf(light_num, GL_QUADRATIC_ATTENUATION, light_attenuation[2]);

    glLightfv(light_num, GL_POSITION, light_position);

    if(spot)
    {
        GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
        glLightfv(light_num, GL_SPOT_DIRECTION, spot_direction);
        glLightf( light_num, GL_SPOT_CUTOFF, spot_cut);
    }
}


void light_off(GLenum light_num)
{
    glDisable(light_num);
}


void drawSun()
{
    glPushMatrix();
    //glTranslatef(-10,25,0);
    glTranslatef(1,1,1);
    sphere(1,25,25, 0.8,0,0,1);
    light(GL_LIGHT1, -10, 20, 0 );
    glPopMatrix();
}

void draw_cylinder(GLfloat radius=1,
                   GLfloat height=10,
                   GLubyte R=0,
                   GLubyte G=.392,
                   GLubyte B=0)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    //glColor3ub(R-40,G-40,B-40);
    set_mat_prop(0.000, 0.392, 0.000,light_led_emission);

    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */

    //glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI )
    {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawLightStand()
{
            glTranslatef(6,0,2);
            //glScalef(0.4,0.4,0.4);
            glPushMatrix();

            glTranslatef(0,0,-5);
            //glTranslatef(0,0,0);
            glRotatef(270, 1.0,0.0,0.0);
            draw_cylinder();

            glTranslatef(0,0,10);
            glTranslatef(0,0,0);
            sphere(5, 15, 15,0.855, 0.439, 0.839, light_led_emission);

            glPopMatrix();


}
void drawTree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[1]);
    glPushMatrix();

    glScalef(2,7,2);
    cube();
    glBindTexture(GL_TEXTURE_2D, v[2]);
    glTranslatef(-0.5,0.5,-0.5);
    glScalef(1,0.5,1);
    drawpyramid(1,1,1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


static void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3d(1,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyex,eyey,eyez,refx,refy,refz, 0,1,0);

    //glRotated(0,0,0,0);
    //glRotated(a,0,1,0);
    //drawSun();
    light(GL_LIGHT3,0,25,25,false);


    drawTree();

   // drawLightStand();

        glPushMatrix();
       glScalef(10,10,10);
        glTranslatef(5,5,5);
       MonumentDesign();
        MonumentFront();
        glPopMatrix();
    //light(GL_LIGHT0, 1, 1, 1);


    //myTable();
    //myRoom();
    // myFlag();



    glutSwapBuffers();
}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;
    case ',':
        rotateCamera(5); //clockwise
        //rotate_by_clockwise(1);
        //rot+=2;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case '.':
        rotateCamera(-5);  //anticlockwise
        //rotate_by_anticlockwise(1);
        //rot-=2;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;

    case '-':
        //eZ--;
        eyex-=(eyex-refx)*0.05;
        eyez -=(eyez-refz)*0.05;
        //lZ--;
        //refz--;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case '=':
        //eZ++;
        //lZ++;
        eyex+=(eyex-refx)*0.05;
        eyez +=(eyez-refz)*0.05;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;

    case 'U':
        //eY--;
        eyey--;
        break;
    case 'u':
        //eY++;
        eyey++;
        break;
    case 'Y':
        //eY--;
        refy--;
        eyey--;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case 'y':
        //eY++;
        refy++;
        eyey++;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case  'f':
        refx -=(refx-eyex)*0.05;
        refz -=(refz-eyez)*0.05;
        //lZ--;
        //refz--;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case  'F':
        refx +=(refx-eyex)*0.05;
        refz +=(refz-eyez)*0.05;
        //lZ--;
        //refz--;
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case '1':
        if(monument_emission)
        {
            monument_emission = false;
        }
        else
        {
            monument_emission = true;
        }
        break;
    case '2':
        if(light_led_emission)
        {
            light_led_emission = false;
        }
        else
        {
            light_led_emission = true;
        }
        break;
    case '7':
        //refx += 2;
        break;

    case '8':
        //refx -=2;
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);  //glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void texture_image()
{
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\monument.bmp");
    v.push_back(ID);
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\wood.bmp");
    v.push_back(ID);
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\tree_leaves.bmp");
    v.push_back(ID);

}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Home Work");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glDisable(GL_CULL_FACE);  //back side disable or enable
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glEnable(GL_LIGHTING);
    //GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    texture_image();

    glutMainLoop();

    return 0;
}

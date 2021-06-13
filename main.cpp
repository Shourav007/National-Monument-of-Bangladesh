
#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include<mmsystem.h>
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
GLfloat eyez =140;

GLfloat refx = 0;
GLfloat refy = 10;
GLfloat refz = -5;

double r =0;

float l_height = 10;
float spt_cutoff = 40;


float rot = 0;

bool light1=true, light2=false, light3=false;
bool diffuse_light_on=true, specular_light_on=true, ambient_light_on=true;

bool spotlight_on = true;



bool monument_emission=true;
bool light_led_emission =true;
bool sun_emission = true;
bool flag_emission = true;
bool choose_display = true;
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
    glFrustum(-ar, ar, -1.0, 1.0, 1.0,600.0);

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



void set_mat_prop(float colR=0.5, float colG=0.5, float colB=0.5, bool emission=false, float shine=128)
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

    if(emission)
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


void axes(float length = 10,  float width = 0.3)
{


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
        set_mat_prop(r-.1,g-.1,b-.1);//,monument_emission);

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

        MonumentFront();
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

static void rotateReference( float theta=5.0)
{
    float newx =  refx-eyex;   //refX-x;
    float newz =  refz-eyez;               //refY-y;

    float rx, rz;
    rx = newx*Cos(theta)-newz*Sin(theta);
    rz = newx*Sin(theta)+newz*Cos(theta);

    newx = rx+eyex;
    newz = rz+eyez;
    refx = newx;
    refz = newz;
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
           bool spot=false, float spot_cut=15, float amb=0.2)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {amb, amb, amb, 1.0};
    GLfloat light_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1, 1, 1, 1.0};
    GLfloat light_position[] = {posX, posY, posZ, 1};
    GLfloat light_attenuation[] = {1,0,0.0002};


    glEnable(light_num);

    if(ambient_light_on)
        glLightfv(light_num, GL_AMBIENT, light_ambient);
    else
        glLightfv(light_num, GL_AMBIENT, no_light);

    if(diffuse_light_on)
        glLightfv(light_num, GL_DIFFUSE, light_diffuse);
    else
        glLightfv(light_num, GL_DIFFUSE, no_light);

    if(specular_light_on)
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
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[11]);
    glTranslatef(0,45,0);
    if(sun_emission)
    {
        light(GL_LIGHT1, 0, 42, 0 ,1, 60);
    }
    glPushMatrix();
    set_mat_prop(1,1,1, sun_emission);
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90.0f, -0.5f, 1.0f, 1.0f);
    gluSphere(qobj, 5, 50, 50);
    gluDeleteQuadric(qobj);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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
            //glScalef(0.4,0.4,0.4);
            glPushMatrix();

            glTranslatef(0,0,-5);
            //glTranslatef(0,0,0);
            glRotatef(270, 1.0,0.0,0.0);
            draw_cylinder();

            glTranslatef(0,0,10);
            glTranslatef(0,0,0);
            sphere(4, 15, 15,0.855, 0.439, 0.839, light_led_emission);

            glPopMatrix();


}

void lightStands()
{
    glPushMatrix();
    if(light_led_emission)
    {
        light(GL_LIGHT5,30,10,10);
    }

    glTranslatef(30,0,10);
    drawLightStand();
    glPopMatrix();

    glPushMatrix();
    if(light_led_emission)
    {
        light(GL_LIGHT6,-30,10,10);
    }
    glTranslatef(-30,0,10);
    drawLightStand();
    glPopMatrix();

    glPushMatrix();
    if(light_led_emission)
    {
         light(GL_LIGHT7,30,10,-45/3);
    }

    glTranslatef(30,0,-45/3);
    drawLightStand();
    glPopMatrix();

    glPushMatrix();
    if(light_led_emission)
    {
        light(GL_LIGHT2,30,10,-45/3);
    }
    glTranslatef(-30,0,-45/3);
    drawLightStand();
    glPopMatrix();
}


void lineTo(float x, float y, float len, float angle)
{
    set_mat_prop(0, 1, 0.04);
    glLineWidth(5);
    glBegin(GL_LINES);

    glVertex2f(x, y);
    glVertex2f(x+len*cos(angle), y+len*sin(angle));
    glEnd();
}


void fractal_tree(float x, float y, float len, float angle, float len_div, float angle_dif, int depth)
{
    //set_mat_prop(0.000, 1.000, 0.000);
    lineTo(x, y, len, angle);
    if(depth == 0) return;

    // left
    fractal_tree(x+len*cos(angle), y+len*sin(angle), len*len_div, angle-angle_dif, len_div, angle_dif, depth-1);

    // right
    fractal_tree(x+len*cos(angle), y+len*sin(angle), len*len_div, angle+angle_dif, len_div, angle_dif, depth-1);
}

void drawTree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[1]);
    glPushMatrix();
    glScalef(2.5,2.5,2.5);
    glScalef(3,7,3);
    cube();
    glBindTexture(GL_TEXTURE_2D, v[2]);
    glTranslatef(-0.5,0.5,-0.5);
    glScalef(1,0.5,1);
    drawpyramid(1,1,1);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void trees()
{
    //glScalef(2.0,2.0,2.0);
    glPushMatrix();
    glTranslatef(60,0,-60);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,0,-60);
    drawTree();
    glPopMatrix();

}

void floor(float width =30, float depth=1, float lenth = 30, float a=0, float b=-0.5, float c=0)
{
    glPushMatrix();
    glTranslatef(a,b,c);
    glScalef(width, depth, lenth);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(1,1,1);
    glPopMatrix();
}

void box(float boxWidth=50, float boxdepth=2, float boxLength=10,float a=0, float b=0, float c=0)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[1]);
    glPushMatrix();
    glTranslatef(a,b,c);
    floor(boxWidth,boxdepth,boxLength,0,-boxdepth/2,0); //bottom  brick
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void building(float roomWidth=50, float walldepth=2, float roomLength=100, float roomHeight = 30){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[9]);
    glPushMatrix();
    floor(roomWidth,walldepth,roomLength,0,-walldepth/2,0); //bottom  floordesign.bmp
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[7]);
    glPushMatrix();
    floor(walldepth,roomHeight,roomLength,(roomWidth/2-walldepth/2),roomHeight/2,0);    //left
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[8]);
    glPushMatrix();
    floor(walldepth,roomHeight,roomLength,-(roomWidth/2-walldepth/2),roomHeight/2,0);   //right
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[10]);         //kuet cse positve z axis   //back.bmp
    glPushMatrix();
    floor(roomWidth,roomHeight,walldepth,0,roomHeight/2,(roomLength/2-walldepth/2));    //front
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[6]);   //bangladesh potaka negative z axis
    glPushMatrix();
    floor(roomWidth,roomHeight,walldepth,0,roomHeight/2,-(roomLength/2-walldepth/2));    //back
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //floor(roomWidth,walldepth,roomLength,0,-walldepth/2,0); //bottom
    //floor(roomWidth,walldepth,roomLength,0,roomHeight+walldepth/2,0);   //top
    //floor(walldepth,roomHeight,roomLength,(roomWidth/2-walldepth/2),roomHeight/2,0);    //left
    //floor(walldepth,roomHeight,roomLength,-(roomWidth/2-walldepth/2),roomHeight/2,0);   //right
    //floor(roomWidth,roomHeight,walldepth,0,roomHeight/2,(roomLength/2-walldepth/2));    //back
}

void skydome()
{
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, v[3]);
    glBindTexture(GL_TEXTURE_2D, v[4]);
    glPushMatrix();
    set_mat_prop(1,1,1, monument_emission);
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    glRotatef(90.0f, -0.5f, 1.0f, 1.0f);
    gluSphere(qobj, 300, 50, 50);
    gluDeleteQuadric(qobj);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

GLfloat ya = 0, xa=0; bool yflag =1, xflag =1;

void animation()
{
    if(yflag)
    {
        if(ya>=-50 )
        {
            ya = ya - 0.4;
        }
        if(ya<=-50)
        {
            yflag = 0;
        }
    }
    else
    {
        if(ya<=50 )
        {
            ya = ya+0.4;
        }
        if(ya>=50)
        {
            yflag = 1;
        }
    }
    if(xflag)
    {
        if(xa>=-10 )
        {
            xa = xa - 0.1;
        }
        if(xa<=-10)
        {
            xflag = 0;
        }
    }
    else
    {
        if(xa<=10)
        {
            xa = xa+0.1;
        }
        if(xa>=10)
        {
            xflag = 1;
        }
    }
    glutPostRedisplay();
}

void drawcurve()
{
    glTranslatef(-5,-5,-5);
    glPushMatrix();
    set_mat_prop(1,0.5,1,flag_emission);
    glScalef(10,10,10);
    GLdouble x[4],y1[4],y2[4];
    GLdouble xt[200], y1t[200],y2t[200], t;
    glClear(GL_COLOR_BUFFER_BIT);
    int i=0;
    x[0] = 100/100; x[1] = 200/100;     x[2] = 200/100;     x[3] = (300-xa)/100;
    y1[0]=470/100;   y1[1]=(470+ya)/100;    y1[2]=(470-ya)/100;    y1[3]=470/100;
    y2[0]=330/100;   y2[1]=(330+ya)/100;    y2[2]=(330-ya)/100;    y2[3]=330/100;

    for(t=0; t<=1;i++, t+=0.005)
    {
        xt[i] = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*pow(t,2)*(1-t)*x[2] + pow(t,3)*x[3];
        y1t[i] = pow(1-t,3)*y1[0] + 3*t*pow(1-t,2)*y1[1] + 3*pow(t,2)*(1-t)*y1[2] + pow(t,3)*y1[3];
        y2t[i] = pow(1-t,3)*y2[0] + 3*t*pow(1-t,2)*y2[1] + 3*pow(t,2)*(1-t)*y2[2] + pow(t,3)*y2[3];
    }
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, v[12]);
    glBegin(GL_QUAD_STRIP); float j;
        for(i=0,j=1; i<200; j++,i++)
        {
            glVertex2d(xt[i], y1t[i]);
            glTexCoord2f(1,j/200);
            glVertex2d(xt[i], y2t[i]);
            glTexCoord2f(0,j/200);
        }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    set_mat_prop(0.8,0.4,0.2);
    glTranslatef(-0.5,0.7,-1.45);
    glScalef(1,1.5,3);
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
    glPopMatrix();
}

void flag()
{
    //glColor3f(0.8,0.4,0.2);

    set_mat_prop(0.8,0.4,0.2);
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

    //glColor3f(0,0.5,0.1);
    set_mat_prop(0,0.5,0.1);

    glBegin(GL_QUADS);
    glVertex3f(1.6,2.3,0.5);
    glVertex3f(1.6,1.6,0.5);
    glVertex3f(2.5,1.6,0.5);
    glVertex3f(2.5,2.3,0.5);
    glEnd();

    //glColor3f(1, 0, 0);
    set_mat_prop(1, 0, 0);
    glTranslated(2.08,1.96,0.52);
    glScalef(0.2,0.2,0);
    glutSolidSphere(1,slices,stacks);


}

void renderBitmapString(void *font=GLUT_BITMAP_9_BY_15, float x=100, float y=100, float z=100,char *sting = "abcd" )
{

    glColor4f(1.0,1.0,1.0,1.0);
    glRasterPos3f(x,y,z);
    //glDisable(GL_LIGHTING);

    for (int i=0, len = strlen(sting); i <len; i++)
    {
        glutBitmapCharacter(font, (int)sting[i]);
    }

    //glEnable(GL_LIGHTING);
}

void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back=0, float ambFactor=1.0, float specFactor=1.0);
int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=0;
int animat = 0;
const int L=31;
const int dgre=3;
int ncpt=L+1;
int clikd=1;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;
GLfloat ctrlpoints[L+1][3] =
{
{7.9750, 1.7500, 13.0000},
{7.7500, 1.5250, 13.0000},
{7.4000, 1.2500, 13.0000},
{7.1000, 0.9750, 13.0000},
{6.6500, 0.7000, 13.0000},
{6.2250, 0.9750, 13.0000},
{5.9250, 1.5750, 13.0000},
{5.7000, 2.2750, 13.0000},
{5.2250, 2.9000, 13.0000},
{4.7250, 3.5500, 13.0000},
{3.8500, 4.2000, 13.0000},
{2.7500, 4.3000, 13.0000},
{1.8000, 4.0000, 13.0000},
{0.9000, 3.4000, 13.0000},
{0.3000, 2.7500, 13.0000},
{-0.1250, 2.1500, 13.0000},
{-0.2500, 1.4000, 13.0000},
{-0.2750, 0.9000, 13.0000},
{-0.2750, 0.5000, 13.0000},
{-0.2250, 0.2000, 13.0000},
{-0.2000, 0.0250, 13.0000}

};
double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

float wcsClkDn[3],wcsClkUp[3];
///////////////////////////////
class point1
{
public:
    point1()
    {
        x=0;
        y=0;
    }
    int x;
    int y;
} clkpt[2];
int f=0;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16]; //var to hold the projection matrix info

//////////////////////////

//void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back=0, float ambFactor=1.0, float specFactor=1.0);
///////////////////////////

//void scsToWcs(float sx,float sy, float wcsv[3] )
//{
//
//    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
//    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates
//
//    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
//    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
//    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info
//
//    winX = sx;
//    winY = (float)viewport[3] - (float)sy;
//    winZ = 0;
//
//    //get the world coordinates from the screen coordinates
//    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
//    wcsv[0]=worldX;
//    wcsv[1]=worldY;
//    wcsv[2]=worldZ;
//
//
//}
void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back, float ambFactor, float specFactor)
{

    const GLfloat mat_ambient[]    = { kdr*ambFactor, kdg*ambFactor, kdb*ambFactor, 1.0f };
    const GLfloat mat_diffuse[]    = { kdr, kdg, kdb, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f*specFactor, 1.0f*specFactor, 1.0f*specFactor, 1.0f };
    const GLfloat high_shininess[] = { shiny };
    if(frnt_Back==0)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    }
    else if(frnt_Back==1)
    {
        glMaterialfv(GL_BACK, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_BACK, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_BACK, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_BACK, GL_SHININESS, high_shininess);
    }
    else if(frnt_Back==2)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    }

}

long long nCr(int n, int r)
{
    if(r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve ( double t,  float xy[2], GLfloat ctrlpoints[][3], int L)
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<L+1; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}

void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
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

    glNormal3f(-Nx,-Ny,-Nz);
}


void hollowBezier(GLfloat ctrlpoints[][3], int L)
{
    L-=2;
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy, ctrlpoints, L);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy, ctrlpoints, L);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}



void DrawCurved(GLfloat ctrlpoints[][3], int L)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 5000.0;
    const double a = t*90.0;

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(wired)
    {
        glPolygonMode( GL_FRONT, GL_LINE ) ;
        glPolygonMode( GL_BACK, GL_LINE ) ;

    }
    else
    {
        glPolygonMode( GL_FRONT,GL_FILL ) ;
        glPolygonMode( GL_BACK, GL_FILL ) ;
    }

    glPushMatrix();

    if(animat)
        glRotated(a,0,0,1);

    glRotatef( anglex, 1.0, 0.0, 0.0);
    glRotatef( angley, 0.0, 1.0, 0.0);         	//rotate about y-axis
    glRotatef( anglez, 0.0, 0.0, 1.0);

    glRotatef( 90, 0.0, 0.0, 1.0);
    glTranslated(-3.5,0,0);
    //glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info

   // matColor(0.5,0.0,0.1,20);   // front face color
   // matColor(0.0,0.5,0.8,20,1);  // back face color


    //hollowBezier(ctrlpoints, L);
    hollowBezier(ctrlpoints, L);
    //hollowBezier(ctrlpoints1, 14);

//
//    if(shcpt)
//    {
//        matColor(0.0,0.0,0.9,20);
//        showControlPoints(ctrlpoints, L);
//        showPoints();
//    }

    glPopMatrix();



    //glutSwapBuffers();
}

void display5(void)
{


    renderBitmapString(GLUT_BITMAP_HELVETICA_18, 180,40,80, "This is a computer graphics project");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, 180,30,80, "Project Name: Artificial National Monument of Bangladesh");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, 180,20,80, "Name:    Shourav Paul   ");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, 180,10,80, "Roll:    1607007   ");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, -180,40,80, "Instructions");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, -180,30,80, "Press \",\"  \".\" for object rotation");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, -180,20,80, "Press  \"<\"   \">\" for eye postion rotation");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, -180,10,80, "Press \"1\" to \"8\" for different light function");
    renderBitmapString(GLUT_BITMAP_HELVETICA_18, -180, 0,80, "Press q for quiting the program");




}

void display(void)
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3d(1,0,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyex,eyey,eyez,refx,refy,refz, 0,1,0);

    //glRotated(0,0,0,0);
    //glRotated(a,0,1,0);
    //drawSun();

    //light(GL_LIGHT3,0,15,15,false);
    glPushMatrix();
    glTranslatef(5,0,-7);
    drawcurve();
    glPopMatrix();

    glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, v[1]);

    glTranslatef(-4,10,-70);
    glRotatef(180,0,0,1);
    glTranslatef(0,0,0);
    fractal_tree(10, 10, 10.0, -PI/2.0, 0.8, PI/18.0, 12);
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(refx,refy,refz);
    glTranslatef(eyex,eyey,eyez);
    skydome();
    glPopMatrix();


    glPushMatrix();
    building(150,1,150,50);
    glPopMatrix();

    glPushMatrix();
    box(50, 3, 35,0,3.5,-35/4 );
    glPopMatrix();

    glPushMatrix();
    drawSun();
    glPopMatrix();

    glPushMatrix();
    //glScalef(5,5,5);
    //glTranslatef(0,3.5,0);
    trees();
    glPopMatrix();


    glPushMatrix();
    lightStands();
    glPopMatrix();

    //drawTree();

    //drawLightStand();

        glPushMatrix();
        glTranslatef(0,3.5,0);
       glScalef(10,10,10);

       MonumentDesign();
        glPopMatrix();


    glPushMatrix();
    glScalef(3,3,3);
    glTranslatef(15,3.5,20);
    set_mat_prop(0.545, 0.000, 0.000);
    DrawCurved(ctrlpoints, 22) ;
    glPopMatrix();

    glPushMatrix();
    glScalef(3,3,3);
    glTranslatef(-15,3.5,20);
    set_mat_prop(0.545, 0.000, 0.000);
    DrawCurved(ctrlpoints, 22) ;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,3.5,0);
    glScalef(10,8,10);
    //flag();
    glPopMatrix();
    display5();

glutSwapBuffers();

}


//void display_all()
//{
//    if(choose_display==1)
//    {
//        display_control();
//    }
//    else if(choose_display==3)
//    {
//        display();
//    }
//
//}

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
    case '<':
        rotateReference(-5);
        printf("%f %f %f %f %f %f\n",eyex, eyey, eyez, refx, refy, refz);
        break;
    case '>':
        rotateReference(5);
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
    case '3':
        if(ambient_light_on)
        {
            ambient_light_on = false;
        }
        else
        {
            ambient_light_on = true;
        }

        printf("ambient light status: %d \n", ambient_light_on);
        break;
    case '4':
        if(diffuse_light_on)
        {
            diffuse_light_on = false;
        }
        else
        {
            diffuse_light_on = true;
        }
        printf("diffuse light status: %d \n", diffuse_light_on);
        break;
    case '5':
        if(specular_light_on)
        {
            specular_light_on = false;
        }
        else
        {
            specular_light_on = true;
        }
        printf("specular light status: %d \n", specular_light_on);
        break;
    case '6':
        if(sun_emission)
        {
            sun_emission = false;
        }
        else
        {
            sun_emission = true;
        }
        printf("sun light status: %d \n", sun_emission);
        break;
    case '7':
        light_off(GL_LIGHT5);
        light_off(GL_LIGHT6);
        light_off(GL_LIGHT7);
        light_off(GL_LIGHT2);
        break;
    case '8':
        if(flag_emission)
        {
            flag_emission = false;
        }
        else
        {
            flag_emission = true;
        }
        printf("flag status: %d \n", flag_emission);
        break;
    case 'n':
        choose_display = 2;
        break;
    case 'm':
        choose_display = 3;
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
    v.push_back(ID);                                                                                            //0
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\wood.bmp");
    v.push_back(ID);                                                                                            //1
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\tree_leaves.bmp");
    v.push_back(ID);                                                                                                //2
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\clouds.bmp");
    v.push_back(ID);                                                                                                //3
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\clouds1.bmp");
    v.push_back(ID);                                                                                                //4
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\brick.bmp");
    v.push_back(ID);                                                                                                //5
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\front.bmp");
    v.push_back(ID);                                                                                                //6
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\left.bmp");
    v.push_back(ID);                                                                                                //7
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\right.bmp");
    v.push_back(ID);//8
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\floordesign.bmp");
    v.push_back(ID);//9
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\back.bmp");
    v.push_back(ID);//10
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\sun.bmp");
    v.push_back(ID);//11
    LoadTexture("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\flag.bmp");
    v.push_back(ID);//12



}

int sound_status=1;

int main(int argc, char *argv[])
{
    //sndPlaySound("Mora.wav", SND_ASYNC);
    PlaySound("E:\\CSE reception\\Welcome 2K16\\fourth year 2nd term(4-2)\\Computer graphics\\LAB\\Lab 04\\cg1\\Mora.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    glutInit(&argc, argv);
    glutInitWindowSize(1000,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("National Monument of Bangladesh");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animation);
    glDisable(GL_CULL_FACE);  //back side disable or enable
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glEnable(GL_LIGHTING);
    //GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    texture_image();
    //PlaySound("Mora.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    glutMainLoop();

    return 0;
}

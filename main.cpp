/***
        Catch Falling Eggs
        ________________________________________________________________________

        This is a simple graphical game.
        The objective of the game is to catch falling eggs in the basket.
***/


#include<windows.h>
#include<iostream>
#include<math.h>
#include<GL/glut.h>

#define CIRCLE_RADIUS  0.15f
#define PI 3.14159265358979323846

using namespace std;


int egg_xc, egg_yc;  // for coordinates of egg
int basket_x, basket_y;  // for coordinates of basket
int a=600,b=650; // for default size of the screen
int s=0;
int w = 48, h = 48, t = 10, e = 9, g = 12;

int dropped_eggs = 0,
    eggs_caught = 0,
    missed_eggs = 0,
    level_count = 1,
    points = 0;

int speed_1 = 1,
    speed_2 = 1.5,
    speed_3 = 1.8,
    speed_4 = 2.3,
    speed_5 = 2.6,
    speed_6 = 3;


void myinit()
{
    glViewport(0,0,a,b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,(GLdouble)a,0,(GLdouble)b);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}


void start_screen(int i,int j)
{
    char start[23]="Press S/s key to Start";

    glColor3f(1,1,01); // color: white
    glRasterPos2i(210,200);
    for(int i=0; i<23; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, start[i]);

    glColor3f(1,.5,.5);
}


void sun()
{

    float theta;

    GLfloat angle;
    glLineWidth(1.5);
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);

    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(500+80*cos(theta)/2, 600+80*sin(theta)/2);
    }

    glEnd();
    glFlush();
}


void cloud1()
{

    float theta;

    GLfloat angle;
    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(100+50*cos(theta)/2, 590+50*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(130+50*cos(theta)/2, 580+50*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(140+50*cos(theta)/2, 600+50*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(170+50*cos(theta)/2, 590+50*sin(theta)/2);
    }

    glEnd();
    glFlush();
}

void cloud2()
{
    float theta;
    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(420+45*cos(theta)/2, 540+45*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(455+45*cos(theta)/2, 550+45*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(455+45*cos(theta)/2, 530+45*sin(theta)/2);
    }
    glEnd();

    glLineWidth(1.5);
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for (int i = 0; i <360 ; i++)
    {
        theta  = i*PI*i/180;
        glVertex2f(490+45*cos(theta)/2, 540+45*sin(theta)/2);
    }
    glEnd();
    glFlush();
}


void backk(int i, int j)
{
    glColor3f(0, .5, 1);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i,0.0+j);
    glVertex2f(600.0+i, 0.0+j);
    glVertex2f(600.0+i,-500+j);
    glVertex2f(0.0+i,-500+j);
    glEnd();
    glFlush();
}


void ground(int i, int j)
{
    glBegin(GL_QUADS);
    glColor3f(0,0,1);
    glVertex2f(0.0+i,0.0+j);
    glVertex2f(600.0+i, 0.0+j);
    glVertex2f(600.0+i,-j);
    glVertex2f(0.0+i,-j);
    glEnd();
}


void egg()
{
    float x,y,z;
    int t;
    glColor3f(1.0,10,1.0);
    glBegin(GL_POLYGON);
    for(t=0; t<=360; t+=1)
    {
        x = egg_xc+8*(cos(t));
        y = egg_yc+16*(sin(t));
        z = 0;
        glVertex3f(x,y,z);
    }
    glEnd();
}


void basket(int i,int j)
{
    j=10;
    if(i>=a-60)i=a-60;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i,30.0+j);
    glVertex2f(10.0+i,10.0+j);
    glVertex2f(50.0+i,10.0+j);
    glVertex2f(60.0+i,30.0+j);
    glEnd();
}


void bird(int i,int j)
{
    int h;
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(45+i,45+j);
    glVertex2f(70+i,20+j);
    glVertex2f(95+i,20+j);
    glVertex2f(120+i,45+j);
    glVertex2f(95+i,70+j);
    glVertex2f(70+i,70+j);
    glVertex2f(95+i,95+j);
    glVertex2f(82.5+i,107.5+j);
    glVertex2f(32.5+i,57.5+j);
    glEnd();
    glFlush();

    for(h=0; h<13; h+=4)
    {
        glBegin(GL_LINES);
        glColor3f(0.7,0.4,0);
        glVertex2f(57.5+h+i,52.5+h+j);
        glVertex2f(100+h+i,30+h+j);
        glEnd();
        glFlush();
    }

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(82.5+i,107.5+j);
    glVertex2f(65+i,107.5+j);
    glVertex2f(50+i,95+j);
    glVertex2f(70+i,95+j);
    glEnd();
    glFlush();

    glColor3f(0.0,0.0,0.0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(76+i,101+j);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(72.5+i,107.5+j);
    glVertex2f(67.5+i,112.5+j);
    glVertex2f(72.5+i,110+j);
    glVertex2f(77.5+i,112.5+j);
    glEnd();
    glFlush();
}


void print_score()
{
    cout << " Level reached     : " << level_count << endl << endl;
    cout << " Total Dropped Eggs: " << dropped_eggs << endl;
    cout << " Total Caught  Eggs: " << eggs_caught << endl;
    cout << " Total Missed  Eggs: " << missed_eggs << endl;

    exit(0);
}


void egg_start()
{
    dropped_eggs++;

    if(missed_eggs>=10)
    {
        cout << endl << endl << "\t\t\t\tGAME OVER" << endl << endl;
        print_score();
    }

    egg_yc=375;
    switch(rand()%9)
    {
        case 0:
            egg_xc=115;
            break;
        case 1:
            egg_xc=255;
            break;
        case 2:
            egg_xc=390;
            break;
        case 5:
            egg_xc=115;
            break;
        case 3:
            egg_xc=255;
            break;
        case 4:
            egg_xc=390;
            break;
        case 7:
            egg_xc=115;
            break;
        case 6:
            egg_xc=255;
            break;
        case 8:
            egg_xc=390;
            break;
    }
}


void score()
{
    if((egg_yc <= 50) && (egg_xc >= basket_x) && (egg_xc<=basket_x+60))
    {
        printf("\a");
        eggs_caught++;
        egg_yc=-10;
    }
    missed_eggs=dropped_eggs-eggs_caught;
}


void set_basket(int a,int b)
{
    basket_x = a;
    basket_y = b;
    glutPostRedisplay();
}


void level_and_speed_controller()
{
    int i;
    char z[12]="FORHAD";
    char level1[12]="LEVEL 1";
    char level2[12]="LEVEL 2";
    char level3[12]="LEVEL 3";
    char level4[12]="LEVEL 4";
    char level5[12]="LEVEL 5";
    char level6[12]="LEVEL 6";

    if(s>=1)
    {
        glColor3f(0,0,1);

        glRasterPos2i(10,10);
        for(i=0; i<12; i++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13,z[i]);

        if(level_count==1)
        {
            glColor3f(1,1,1);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level1[i]);
        }
        else if(level_count==2)
        {
            glColor3f(0,1,0);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level2[i]);
        }
        else if(level_count==3)
        {
            glColor3f(1,1,1);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level3[i]);
        }
        else if(level_count==4)
        {
            glColor3f(0,1,0);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level4[i]);
        }
        else if(level_count==5)
        {
            glColor3f(0,1,0);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level5[i]);
        }
        if(level_count==6)
        {
            glColor3f(0,1,0);
            glRasterPos2i(500,300);
            for(i=0; i<12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level6[i]);
        }
        if(egg_yc<=10)
                egg_start();

        egg();
        basket(basket_x,basket_y);
        if(eggs_caught >= 10)
        {
            egg_yc -= speed_2;
            level_count = 2;
        }
        if(eggs_caught >= 20)
        {
            egg_yc -= speed_3;
            level_count = 3;
        }
        if(eggs_caught >= 30)
        {
            egg_yc -= speed_4;
            level_count = 4;
        }
        if(eggs_caught >= 40)
        {
            egg_yc -= speed_5;
            level_count = 5;
        }
        if(eggs_caught >= 50)
        {
            egg_yc -= speed_6;
            level_count = 6;
        }
        else
            egg_yc -= speed_1;
        score();
    }
    else
        start_screen(40,300);

    glFlush();
    glutSwapBuffers();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    ground(0, 650);
    backk(0, 650);
    bird(40,375);
    bird(180,375);
    bird(320,375);
    sun();
    cloud1();
    cloud2();
    level_and_speed_controller();
}


void myReshape(int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
    a=w;
    b=h;
}


void keys(unsigned char key,int x,int y)
{
    if(key=='s'||key=='S')
        s+=1;

    if(key=='q'||key=='Q')
    {
        printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
        print_score();
    }

    // shift egg to the left
    if(key=='a'||key=='A')
    {
        egg_xc-=10;
        if(egg_xc<=0) egg_xc=10;
    }

    // shift egg to the right
    if(key=='d'||key=='D')
    {
        egg_xc+=10;
        if(egg_xc>=500) egg_xc=490;
    }

}


void menu(int id)
{
    switch(id)
    {
    case 1:
        s+=1;
        break;
    case 2:
        print_score();
        break;
    case 3:
        cout << "\n\n\n\t\t GAME QUITS " << endl;
        break;
    default:
        exit(0);
    }
    glutPostRedisplay();
}


void prompt()
{
    cout << endl << endl;
    cout << " ---------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t Catch Falling Eggs" << endl;
    cout << " ---------------------------------------------------------------------------------" << endl;
    cout << endl << endl;

    cout << " ---------------------------------  Instructions  --------------------------------" << endl;
    cout << endl;
    cout << " > The objective of the game is to catch falling eggs in the basket." << endl;
    cout << " > To move Basket use mouse." << endl;
    cout << " > To Start, press key 'S' or click right mouse button then click 'Start Game'." << endl;
    cout << " > To change the falling eggs direction to the left, press 'A' key." << endl;
    cout << " > To change the falling eggs direction to the right, press 'D' key." << endl;
    cout << " > To Quit manually, press key 'Q' or click right mouse button then click 'Quit'." << endl;
    cout << endl << endl;

    cout << " ------------------------------------  Rules  ------------------------------------" << endl;
    cout << endl;
    cout << " > If the player catches 10 eggs, then level upgrades." << endl;
    cout << " > For each new level, speed of falling eggs is increased." << endl;
    cout << " > If the player misses 10 eggs,then game is over." << endl;
    cout << endl << endl;

    cout << " ====================================  ENJOY  ====================================" << endl;
    cout << endl << endl;
}


int main(int argc,char **argv)
{
    prompt();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(a,b);
    glutCreateWindow("Catch Falling Eggs");
    myinit();
    glutInitWindowPosition (100, 100);
    glutCreateMenu(menu);
    glutAddMenuEntry("Start Game",1);
    glutAddMenuEntry("Score",2);
    glutAddMenuEntry("Quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutPassiveMotionFunc(set_basket);
    glutIdleFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();
}



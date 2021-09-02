#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

int count=0;
int nx=1,ny=1;
int p1=0, p2=0;                             //POINTS
double angle=45,dx= 0,dy=-350;              //BALL MOVEMENT
double h=25, w=150;                         //BOARD'S HEIGHT & WIDTH
double incx=-75,incy=400;                   //UPPER BOARD
double x2=-75,y2=-400;                      //LOWER BOARD
double bWidth=60, bHeight=20, gap=10;       //BRICKS WIDTH, HEIGHT, DISTANCE
int state=1, page=0, result;
struct point
{
	double x,y,z;
};

struct bricks
{
	int x,y,flag;
} brick[22];

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

        case 'a':
            incx -= 15;
			break;
        case 'd':
            incx += 15;
            break;
        case 's':
            page=1;
            break;
        case 'g':
            break;
        case 'w':
            incx+=1;
            break;
        case 'c':
            //code
            break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			break;
		case GLUT_KEY_UP:		// up arrow key
			break;

		case GLUT_KEY_RIGHT:
            x2 += 15;
			break;
		case GLUT_KEY_LEFT:
		    x2 -=15;
			break;


		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
		    //code
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void draw_tri()
{
    glBegin(GL_POLYGON);
        glVertex2f(10, 10);
        glVertex2f(10, 0);
        glVertex2f(-10, 0);
    glEnd();
}
void push_pop(void)
{
    glPushMatrix();
        //glRotatef(45, 0, 0, 1);

        glPushMatrix(); // Furthest Triangle, Draw first
            //glRotatef(45, 0, 0, 1);
            glTranslatef(-20, 0, 0);
            //glScaled(2, 1, 0);
            glColor3f(0.0, 0.0, 1.0);
            draw_tri();

        glPopMatrix();

        glPushMatrix(); // Middle Triangle, Draw 2nd
            glTranslatef(0, 20, 0);
            glColor3f(0.0, 1.0, 0.0);
            draw_tri();
        glPopMatrix();

        glPushMatrix(); // Nearest Triangle, Draw last
            glTranslatef(20, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            draw_tri();
        glPopMatrix();


    glPopMatrix();

}


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);

        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}


void drawCircle(float radius_x, float radius_y)
{
	int i = 0;

	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;

			glColor3f(0, 0.8, 0.8);

			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 2);
		}

    }
	glEnd();
}

void rec_animation()
{
    glTranslatef(dx, dy, 0);
    glRotatef(angle, 0, 0, 1);
    drawCircle(20, 20);
}
void draw_border()
{
    // BORDER
    glColor3f(0.4,0.6,0.9);
    glBegin(GL_QUADS);{
		glVertex3f(-500, 550,2);
		glVertex3f(500, 550,2);
		glVertex3f(500,421,2);
		glVertex3f(-500, 421,2);
	}glEnd();

    glBegin(GL_QUADS);{
		glVertex3f(-500, -550,2);
		glVertex3f(500, -550,2);
		glVertex3f(500,-421,2);
		glVertex3f(-500, -421,2);
	}glEnd();

    glBegin(GL_QUADS);{
		glVertex3f(470, 550,2);
		glVertex3f(420, 550,2);
		glVertex3f(420,-550,2);
		glVertex3f(470, -550,2);
	}glEnd();

    glBegin(GL_QUADS);{
		glVertex3f(-470, 550,2);
		glVertex3f(-420, 550,2);
		glVertex3f(-420,-500,2);
		glVertex3f(-470, -500,2);
	}glEnd();
}
void draw_board1()
{
	glBegin(GL_QUADS);{
		glVertex3f(incx, incy,2);
		glVertex3f(incx+w, incy,2);
		glVertex3f(incx+w,incy+h,2);
		glVertex3f(incx, incy+h,2);
	}glEnd();
}

void draw_board2()
{
    glBegin(GL_QUADS);{
		glVertex3f(x2, y2,2);
		glVertex3f(x2+w, y2,2);
		glVertex3f(x2+w, y2-h,2);
		glVertex3f(x2, y2-h,2);
	}glEnd();
}
void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);
    //glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);
    //glPopMatrix();

    glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,0,1);
    drawSquare(10);

}
void draw_brick()
{
    int i,a,b;
    glColor3f(0.3,0.55,0.5);

    a = -300;
    b = 40;
    for(i=0; i<7; i++)                  // UPPER ROW - 7 BRICKS
    {
        a += bWidth;
        if(brick[i].flag)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(a, b,2);
                glVertex3f(a+bWidth, b,2);
                glVertex3f(a+bWidth, b-bHeight,2);
                glVertex3f(a, b-bHeight,2);
            }glEnd();
        }
        a += gap;
    }

    a = -340;
    b = 10;
    for(i=7; i<15; i++)                  // MIDDLE ROW - 8 BRICKS
    {
        a += bWidth;
        if(brick[i].flag)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(a, b,2);
                glVertex3f(a+bWidth, b,2);
                glVertex3f(a+bWidth, b-bHeight,2);
                glVertex3f(a, b-bHeight,2);
            }glEnd();
       }
        a += gap;
    }

    a = -300;
    b = -20;
    for(i=15; i<22; i++)                  // LOWER ROW - 7 BRICKS
    {
        a += bWidth;
        if(brick[i].flag)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(a, b,2);
                glVertex3f(a+bWidth, b,2);
                glVertex3f(a+bWidth, b-bHeight,2);
                glVertex3f(a, b-bHeight,2);
            }glEnd();
        }
        a += gap;
    }
}
bool brickExist()
{
    int i;
    for(i=0; i<22; i++)
    {
        if(brick[i].flag == 0)
            continue;
        else
            break;
    }
    if(i==22)
    {
        page=2;
        return false;
    }
}
void simple_trans()
{
    glColor3f(0.5, 0.5, 0.5);

    //BOARD 1 (UPPER)
    glPushMatrix();
        draw_board1();
    glPopMatrix();

    //BOARD 2 (LOWER)
    glPushMatrix();
        draw_board2();
    glPopMatrix();
}
double curve_by_points()
{
    ///
}
double func(double x)
{
    return x*x;
}
void curve()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    for(double i =-180; i<180;i+=.5)
    {
        glVertex2d(i,10*func(i));
        glVertex2d(i+.5, 10*func(i+.5));
    }
     // It can be any type Gl_POINT,_LINE
    glEnd();

}

void displayRasterText(float x ,float y ,float z ,char *stringToDisplay)
{
	int length;
	glRasterPos3f(x, y, z);
    length = strlen(stringToDisplay);
	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}
void pages(int result)
{
    char temp[40];
	glColor3f(1 ,0 ,0);
	glColor3f(0 ,0 ,0);


	if(page==2)
    {
        if(!brickExist)
        {
            if(p1>p2)
                result=1;
            if(p1<p2)
                result=2;
            if(p1==p2)
                result=0;
        }
        if(result==1)
        {
            sprintf(temp,":::::GAME OVER:::::");
            displayRasterText(-200 ,350 ,0 ,temp);
            sprintf(temp,"PLAYER 1 WINS");
            displayRasterText(-200 ,60 ,0 ,temp);
            sprintf(temp,"PLAYER 1: %d POINTS", p1);
            displayRasterText(-240 ,-10 ,0 ,temp);
            sprintf(temp,"PLAYER 2: %d POINTS", p2);
            displayRasterText(-240 ,-50 ,0 ,temp);
        }
        if(result==2)
        {
            sprintf(temp,":::::GAME OVER:::::");
            displayRasterText(-200 ,350 ,0 ,temp);
            sprintf(temp,"PLAYER 2 WINS");
            displayRasterText(-200 ,60 ,0 ,temp);
            sprintf(temp,"PLAYER 1: %d POINTS", p1);
            displayRasterText(-240 ,-10 ,0 ,temp);
            sprintf(temp,"PLAYER 2: %d POINTS", p2);
            displayRasterText(-240 ,-50 ,0 ,temp);
        }
        if(result==0)
        {
            sprintf(temp,":::::GAME OVER:::::");
            displayRasterText(-200 ,350 ,0 ,temp);
            sprintf(temp,"MATCH DRAW");
            displayRasterText(-200 ,60 ,0 ,temp);
        }
    }
    if(page==0)
    {
        sprintf(temp,":::::DX BALL:::::");
        displayRasterText(-200 ,350 ,0 ,temp);

        sprintf(temp,"INSTRUCTIONS");
        displayRasterText(-200 ,60 ,0 ,temp);

        sprintf(temp,"Press S to start the game");
        displayRasterText(-260 ,0 ,0 ,temp);

        sprintf(temp,"Use a & d to move the upper board");
        displayRasterText(-320 ,-30 ,0 ,temp);

        sprintf(temp,"Use right & left arrow to move the lower board");
        displayRasterText(-400 ,-70 ,0 ,temp);
    }
}

void display()
{
    //clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,550,	0,0,0,	0,1,0);
	glMatrixMode(GL_MODELVIEW);

    if(page==0)
    {
        glClearColor(0.4,0.6,0.6,1);
        pages(result);
    }

    if(page==1)
    {
        glClearColor(1,1,1,1);
        draw_brick();
        draw_border();
        simple_trans();
        rec_animation();
    }

    if(page==2)
    {
       glClearColor(0.4,0.6,0.6,1);
       pages(result);
    }

    glutSwapBuffers();
}


void animate()
{
    if(page==1)
    {
        angle-= 0.5;
        dy += (0.025*ny);
        dx += (0.05*nx);

        //BALL HITS WALL
        if(dx>400)
            nx=-1;
        if(dx<-400)
            nx=1;

        // GAME OVER
        if(dy>500)
        {
            result=2;
            page=2;
        }
        if(dy<-500)
        {
            result=1;
            page=2;
        }
        //HIT THE UPPER BOARD
        if((dy+20>=incy && dy+20<incy+h) && (dx>incx && dx<incx+w))
        {
            ny=-1;
            state = 0;
        }

        //HIT THE LOWER BOARD
        if((dy-20<=y2 && dy-20>y2-h) && (dx>x2 && dx<x2+w))
        {
            ny=1;
            state = 1;
        }

        //BOARD MOVEMENT
        if(incx > 270)
            incx = 270;
        if(incx <-420)
            incx = -420;

        if(x2 > 270)
            x2 = 270;
        if(x2 <-420)
            x2 = -420;

        //BALL HITS A BRICK
        int k;
        for(k=0; k<22; k++)
        {
            //HIT FROM UPPER Board
            if(state==0 && (dx>=brick[k].x && dx<=brick[k].x+bWidth) && (dy-20<=brick[k].y && dy-20>=brick[k].y-bHeight))
            {
                ny=1;
                p1 += 50;
                brick[k].flag = 0;
                printf("PLAYER 1 HITS A BRICK! P1: %d POINTS & P2: %d POINTS\n",p1,p2);
                brick[k].x = 999;
                brick[k].y = 999;
            }

            //HIT FROM LOWER Board
            if(state==1 && (dx>=brick[k].x && dx<=brick[k].x+bWidth) && (dy+20<=brick[k].y && dy+20>=brick[k].y-bHeight))
            {
                ny=-1;
                p2 += 50;
                brick[k].flag = 0;
                printf("PLAYER 2 HITS A BRICK! P1: %d POINTS & P2: %d POINTS\n",p1,p2);
                brick[k].x = 999;
                brick[k].y = 999;
            }
        }


    }
    glutPostRedisplay();
}

void init(){
	//codes for initialization
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);
	int i,j,k;
	if(count<1)
    {
        for(i=0; i<22; i++)
        {
            brick[i].x = 0;
            brick[i].y = 0;
            brick[i].flag = 1;
        }

        k=-240;
        for(j=0; j<7; j++)
        {
            brick[j].x = k+(j*70);
            brick[j].y = 40;
        }
        k=-280;
        for(j=7; j<15; j++)
        {
            brick[j].x = k+((j-7)*70);
            brick[j].y = 10;
        }
        k=-240;
        for(j=15; j<22; j++)
        {
            brick[j].x = k+((j-15)*70);
            brick[j].y = -20;
        }
        count++;
    }
    printf("GAME RULES:\n50 POINTS FOR HITTING EACH BRICK. AT THE END OF THE GAME,\n");
    printf("THE PLAYER WITH HIGHEST POINTS IS THE WINNER. BUT THE GAME DOESN'T END UNTIL ALL THE BRICKS ARE VANISHED\n");
    printf("SO, YOUR POINTS DON'T MATTER,IF YOU MISS THE BALL. HIT IT OR LOSE IT\n\n\n\n\nGAME PROGRESS:\n");


	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("DX BALL");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	//glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}



#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
double angle;
double incx, ani_angle;
struct point
{
	double x,y,z;
};

struct point pos,l,u,r;
double X=0,Z=0;
int Y=-1;
struct point arra[100];
void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
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


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}



void drawCone(double radius,double height,int segments)
{
    int i;
    double shade,r,g,b;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x= radius * cos(((double)i/(double)segments)*2*pi);
        points[i].y= radius * sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i%2==0)
        {
            glColor3f(0,0,1);
        }
        else
        {
           glColor3f(1,1,0);
        }


        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x= r * cos(((double)j/(double)slices)*2*pi);
			points[i][j].y= r * sin(((double)j/(double)slices)*2*pi);
			points[i][j].z= h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere

                glColor3f(1.0,(double)i/(double)stacks,(double)i/(double)stacks);
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void quad()
{
        glBegin(GL_QUADS);

            glColor3f(0.0f,1.0f,0.0f);

            glVertex3f(1.0f,1.0f,8.0f);					    // Top front Of The Quad (right)
            glVertex3f(1.0f,1.0f,1.0f);					// Top back Of The Quad (right)
            glVertex3f(1.0f,-1.0f,1.0f);					// Bottom back Of The Quad (right)
            glVertex3f(1.0f,-1.0f,8.0f);					// Bottom front Of The Quad (right)

            glColor3f(1.0f,1.0f,0.0f);

            glVertex3f(-1.0f,1.0f,8.0f);					// Top front Of The Quad (left)
            glVertex3f(-1.0f,1.0f,1.0f);					// Top back Of The Quad (left)
            glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom back Of The Quad (left)
            glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom front Of The Quad (left)


            glColor3f(1.0f,0.0f,1.0f);

            glVertex3f(1.0f,1.0f,8.0f);					    // Right front Of The Quad (top)
            glVertex3f(1.0f,1.0f,1.0f);					    // Right back Of The Quad (top)
            glVertex3f(-1.0f,1.0f,1.0f);				    // Left back Of The Quad (top)
            glVertex3f(-1.0f,1.0f,8.0f);				    // Left front Of The Quad (top)


            glColor3f(0.0f,1.0f,1.0f);

            glVertex3f(1.0f,-1.0f,8.0f);					// Right front Of The Quad (bottom)
            glVertex3f(1.0f,-1.0f,1.0f);					// Right back Of The Quad (bottom)
            glVertex3f(-1.0f,-1.0f,1.0f);				    // Left back Of The Quad (bottom)
            glVertex3f(-1.0f,-1.0f,8.0f);				    // Left front Of The Quad (bottom)


            glColor3f(0.0f,0.0f,1.0f);

            glVertex3f(1.0f,1.0f,1.0f);					 // Top Right Of The Quad (Back)
            glVertex3f(-1.0f,1.0f,1.0f);					// Top Left Of The Quad (Back)
            glVertex3f(-1.0f,-1.0f,1.0f);					// Bottom Left Of The Quad (Back)
            glVertex3f(1.0f,-1.0f,1.0f);				// Bottom Right Of The Quad (Back)


            glColor3f(1.0f,0.0f,0.0f);

            glVertex3f(1.0f,1.0f,8.0f);					    // Top Right Of The Quad (Front)
            glVertex3f(-1.0f,1.0f,8.0f);					// Top Left Of The Quad (Front)
            glVertex3f(-1.0f,-1.0f,8.0f);					// Bottom Left Of The Quad (Front)
            glVertex3f(1.0f,-1.0f,8.0f);			// Bottom Right Of The Quad (Front)

        glEnd();
}
void pyramid()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1,1,0);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glColor3f(1,0.5,0);

    glVertex3d(0,5,0);
    glVertex3d(5,-3,0);
    glVertex3d(0,0,5);

    glColor3f(0.5,0.5,0);

    glVertex3d(0,5,0);
    glVertex3d(0,0,5);
    glVertex3d(-5,-3,0);

    glColor3f(0.5,1,0);

    glVertex3d(0,0,5);
    glVertex3d(5,-3,0);
    glVertex3d(-5,-3,0);

    glEnd();
}

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);

    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);
}

void keyboardListener(unsigned char key, int xx,int yy){
    double x,y,z;
    double rate = 0.025;
	switch(key){

		case '1':
			{
                x=l.x;
                y=l.y;
                z=l.z;

                l.x = l.x*cos(rate)+1*r.x*sin(rate);
                l.y = l.y*cos(rate)+r.y*sin(rate);
                l.z = l.z*cos(rate)+r.z*sin(rate);

                r.x = r.x*cos(rate)-x*sin(rate);
                r.y = r.y*cos(rate)-y*sin(rate);
                r.z = r.z*cos(rate)-z*sin(rate);
			}
			break;
        case '2':
			{
                x=l.x;
                y=l.y;
                z=l.z;

                l.x = l.x*cos(-rate)+r.x*sin(-rate);
                l.y = l.y*cos(-rate)+r.y*sin(-rate);
                l.z = l.z*cos(-rate)+r.z*sin(-rate);

                r.x = r.x*cos(-rate)-x*sin(-rate);
                r.y = r.y*cos(-rate)-y*sin(-rate);
                r.z = r.z*cos(-rate)-z*sin(-rate);
			}
			break;
        case '3':
            {
                x=l.x;
                y=l.y;
                z=l.z;

                l.x = l.x*cos(rate)+u.x*sin(rate);
                l.y = l.y*cos(rate)+u.y*sin(rate);
                l.z = l.z*cos(rate)+u.z*sin(rate);

                u.x = u.x*cos(rate)-x*sin(rate);
                u.y = u.y*cos(rate)-y*sin(rate);
                u.z = u.z*cos(rate)-z*sin(rate);
            }
			break;
        case '4':
            {
                x=l.x;
                y=l.y;
                z=l.z;

                l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
                l.y = l.y*cos(-rate)+u.y*sin(-rate);
                l.z = l.z*cos(-rate)+u.z*sin(-rate);

                u.x = u.x*cos(-rate)-x*sin(-rate);
                u.y = u.y*cos(-rate)-y*sin(-rate);
                u.z = u.z*cos(-rate)-z*sin(-rate);
            }
			break;
        case '5':
            {
                x=r.x;
                y=r.y;
                z=r.z;

                r.x = r.x*cos(-rate)+u.x*sin(-rate);
                r.y = r.y*cos(-rate)+u.y*sin(-rate);
                r.z = r.z*cos(-rate)+u.z*sin(-rate);

                u.x = u.x*cos(-rate)-x*sin(-rate);
                u.y = u.y*cos(-rate)-y*sin(-rate);
                u.z = u.z*cos(-rate)-z*sin(-rate);
            }
			break;
        case '6':
            {
                x=r.x;
                y=r.y;
                z=r.z;

                r.x = r.x*cos(rate)+u.x*sin(rate);
                r.y = r.y*cos(rate)+u.y*sin(rate);
                r.z = r.z*cos(rate)+u.z*sin(rate);

                u.x = u.x*cos(rate)-x*sin(rate);
                u.y = u.y*cos(rate)-y*sin(rate);
                u.z = u.z*cos(rate)-z*sin(rate);
            }
			break;
		default:
			break;
	}

}


void specialKeyListener(int key, int x,int y)
{
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			pos.x+=l.x;
			pos.y+=l.y;
			pos.z+=l.z;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			pos.x-=l.x;
			pos.y-=l.y;
			pos.z-=l.z;
			break;

		case GLUT_KEY_LEFT :
			pos.x+=r.x;
			pos.y+=r.y;
			pos.z+=r.z;
			break;
		case GLUT_KEY_RIGHT :
			pos.x-=r.x;
			pos.y-=r.y;
			pos.z-=r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;
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


void mouseListener(int button, int state, int x, int y)
{	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

			}
			break;


		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

				//(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
			}
			break;
			//........

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void animation3d()
{
    //glTranslated(20,0,20);
    //glRotated(ani_angle,0,0,1 );
    //glTranslated(20,0,0);
    glColor3f(1,0.2,0);
    drawSphere(5,10,10);

    glPushMatrix();

    glColor3f(0,0.5,0.5);
    glRotated(ani_angle,0,0,1);
    glTranslated(20,0,0);
    glRotated(3*ani_angle,0,0,1);
    drawSphere(3,10,10);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.5,0.0,0.5);
    glRotated(ani_angle,0,0,1);
    glTranslated(30,0,0);
    drawSphere(4,10,10);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.5,0.5,0.5);
    glRotated(-2*ani_angle+60,0,1,1);
    glTranslated(45,0,0);
    drawSphere(10,40,40);

    glPopMatrix();

}

void funnel(double radius1,double height1,double radius2,double height2,int segments)
{
     int i;
     struct point points[2][100];
     for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius1*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius1*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=0;

        points[1][i].x=radius1*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius1*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height1;
    }

    for (i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);{

                glColor3f((i)%2,(i)%2,(i+1)%2);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);

				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}

    }


    for(i=0;i<=segments;i++)
    {
        points[0][i].x=radius2*cos(((double)i/(double)segments)*2*pi);
        points[0][i].y=radius2*sin(((double)i/(double)segments)*2*pi);
        points[0][i].z=height1+height2;

        points[1][i].x=radius1*cos(((double)i/(double)segments)*2*pi);
        points[1][i].y=radius1*sin(((double)i/(double)segments)*2*pi);
        points[1][i].z=height1;
    }

    for (i=0;i<segments;i++)
    {
        glBegin(GL_QUADS);{

                glColor3f((i)%2,(i)%2,(i+1)%2);
				glVertex3f(points[0][i].x,points[0][i].y,points[0][i].z);
				glVertex3f(points[0][i+1].x,points[0][i+1].y,points[0][i+1].z);

				glVertex3f(points[1][i+1].x,points[1][i+1].y,points[1][i+1].z);
				glVertex3f(points[1][i].x,points[1][i].y,points[1][i].z);

			}

    }glEnd();
}

void display()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.x,pos.y,pos.z, pos.x+l.x,pos.y+l.y,pos.z+l.z, u.x,u.y,u.z);
	glMatrixMode(GL_MODELVIEW);

	drawAxes();
	drawGrid();
    funnel(5,30,20,10,50);

	glutSwapBuffers();
}


void animate(){

    incx+=0.05;
    ani_angle+=0.1;
	glutPostRedisplay();
}

void init(){
	glClearColor(0,0,0,0);

    pos.x=0;
    pos.y=-20;
    pos.z=-20;
    l.x=0;u.x=-1;r.x=0;
    l.y=0;u.y=0;r.y=1;
    l.z=1;u.z=0;r.z=0;
	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("FUNNEL");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

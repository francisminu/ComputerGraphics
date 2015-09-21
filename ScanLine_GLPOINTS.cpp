
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int frontCount=0;
int backCount=3;
int octantVal;
bool drawName = true;
bool drawHouse = false;
bool fillHouse = false;

	void myInit (void)
	{
	     glClearColor(0.0,0.0,0.0,0.0); // sets background color to black
	     glPointSize(2.0); // sets a point to be 4x4 pixels
	     glMatrixMode(GL_PROJECTION);
	     glLoadIdentity();
	     gluOrtho2D(0.0, 800.0, 0.0, 800.0); // the display area in world coordinates.
	}

	void plotPoints(int x1,int y1)
	{
		int temp,x,y;
		switch(octantVal)
		{
			case 1:
			{
				x=x1;
				y=y1;
				break;
			}
			case 2:
			{
				x=y1;
				y=x1;
				break;
			}
			case 3:
			{
				x=-y1;
				y=x1;
				break;
			}
			case 4:
			{
				x=-x1;
				y=y1;
				break;
			}
			case 5:
			{
				x=-x1;
				y=-y1;
				break;
			}
			case 6:
			{
				x=-y1;
				y=-x1;
				break;
			}
			case 7:
			{
				x=y1;
				y=-x1;
				break;
			}
			case 8:
			{
				x=x1;
				y=-y1;
				break;
			}
			default: 
				break;	
		}
		glBegin(GL_POINTS);
			glVertex2i (x, y);
		glEnd();
	}

	/* The below algorithm implements the Construction of a line using Bresenhams Mid Point algorithm */
	
	void drawBresenhamsLine(int x1,int y1,int x2,int y2)
	{
		int dx = x2-x1;
		int dy = y2-y1;
		int d = 2*dy-dx;	// Decision variable that determines the next pixel that has to be chosen
		int incrHor = 2*dy;	// Horizontal increment (for eg: if East point is chosen in case of Octant 1)
		int incrDiag = 2*(dy-dx);	// Diagonal Increment (for eg: if NE is chosen in case of Octant 2)
		plotPoints(x1,y1);
		while(x1<x2)
		{
			if(d<=0)
			{
				d += incrHor;
				x1++;
			}
			else
			{
				d += incrDiag;
				x1++;
				y1++;
			}
			plotPoints(x1,y1);
		}
	}

	/*
		The below function computes the Octant based 
		on the slope of the line to be drawn and returns
		the same to the drawLine() function
	*/	

	int findOctant(int x1,int y1,int x2,int y2)
	{

		float dx = x2-x1;
		float dy = y2-y1;
		float m = dy/dx;
		if(m>=0)
		{
			if(dy>=0 && dx>=0)
			{
				if(abs(dy)<=abs(dx))
					octantVal = 1;
				else if(abs(dy)>abs(dx))
					octantVal = 2;
			}
			else if(dy<=0 && dx<=0)
			{
				if(abs(dy)<=abs(dx))
					octantVal = 5;
				else if(abs(dy)>abs(dx))
					octantVal = 6;
			}
		}
		else if(m<0)
		{
			if(dx<=0 && dy>=0)
			{
				if(abs(dy)>=abs(dx))
					octantVal = 3;
				else if(abs(dy)<abs(dx))
					octantVal = 4;
			}
			else if(dy<=0 && dx>=0)
			{
				if(abs(dy)>=abs(dx))
					octantVal = 7;
				else if(abs(dy)<abs(dx))
					octantVal = 8;
			}
		}

		return octantVal;
	}	

	void drawLine(int x1,int y1,int x2,int y2)
	{
		int x3,y3,x4,y4;
		int octantVal = findOctant(x1,y1,x2,y2);
		switch(octantVal)
		{
			case 1:
			{
				x3=x1;
				y3=y1;
				x4=x2;
				y4=y2;
				break;
			}
			case 2:
			{
				x3=y1;
				y3=x1;
				x4=y2;
				y4=x2;
				break;
			}
			case 3:
			{
				x3=y1;
				y3=-x1;
				x4=y2;
				y4=-x2;
				break;
			}
			case 4:
			{
				x3=-x1;
				y3=y1;
				x4=-x2;
				y4=y2;
				break;
			}
			case 5:
			{
				x3=-x1;
				y3=-y1;
				x4=-x2;
				y4=-y2;
				break;
			}
			case 6:
			{
				x3=-y1;
				y3=-x1;
				x4=-y2;
				y4=-x2;
				break;
			}
			case 7:
			{
				x3=-y1;
				y3=x1;
				x4=-y2;
				y4=x2;
				break;
			}
			case 8:
			{
				x3=x1;
				y3=-y1;
				x4=x2;
				y4=-y2;
				break;
			}
			default: 
				break;
		}
		drawBresenhamsLine(x3,y3,x4,y4); 
	}
	

	void drawBaseRectangle()
	{
		// Drawing the base Rectangle
		glColor3f(127.0f,127.0f,0.0f);
		drawLine(250,500,250,300);
		drawLine(250,300,550,300);
		drawLine(550,300,550,500);
		drawLine(550,500,250,500);
	}

	void drawDoorRectangle()
	{
		// Drawing the door Rectangle
		glColor3f(0.0f,0.0f,135.0f);
		drawLine(300,300,300,400);
		drawLine(300,400,350,400);
		drawLine(350,400,350,300);
		drawLine(350,300,300,300);
	}

	void drawPolygon()
	{
		// Drawing the hexagon
		int x1,y1,x2,y2,i;
		glColor3f(50.0f,128.0f,60.0f);

		for (i = 0; i <= 6; i++)
		{
    			x1 = 450 + 30 * cos(i * 2*3.14/6);
    			y1 = 450 + 30 * sin(i * 2*3.14/6);
			if(i>0)
			{
				drawLine(x1,y1,x2,y2);
			}
			x2=x1;
			y2=y1;
		}

		/*drawLine(430,470,450,470);
		drawLine(430,440,450,440);
		drawLine(420,455,430,440);
		drawLine(450,440,460,455);
		drawLine(450,470,460,455);		
		drawLine(420,455,430,470);*/

	}

	void drawTriangle()
	{
		// Drawing the Triangle
		
		glColor3f(128.0f,0.0f,128.0f);
		drawLine(200,500,600,500);
		drawLine(200,500,400,720);
		drawLine(600,500,400,720);
					
	}
	
	void circleCordinates(int x,int y,int x1,int y1)
	{
		glColor3f(0.0f,150.0f,0.0f);
		glBegin(GL_POINTS);
			glVertex2i (x1+x, y1+y);
			glVertex2i (x1+y,y1+x);
			glVertex2i (x1+y,y1-x);
			glVertex2i (x1+x, y1-y);
			glVertex2i (x1-x, y1-y);
			glVertex2i (x1-y,y1 -x);
			glVertex2i (x1-y,y1+x);
			glVertex2i (x1-x, y1+y);
	     	glEnd();
	}

	void drawCircle(int radius)
	{
		
		int x = 0;
		int y = radius;
		int d = 1 - radius;
		circleCordinates(x,y,400,610);
		while(y>x)
		{
			if(d<0) // E is chosen 
			{
				d += 2*x + 3;
			}
			else // SE is chosen 
			{
				d += 2*(x-y)+5;
				y--;
			}
			x++;
			circleCordinates(x,y,400,610);
		}
	} 

	void dispHouse()
	{
		drawTriangle();
		drawBaseRectangle();
		drawDoorRectangle();
		drawCircle(20);
		drawPolygon();	
	}

	void dispName()
	{
		
		glColor3f(0.0f,255.0f,128.0f);
		//M
		drawLine(100,450,100,550);
		drawLine(120,450,120,530);
		drawLine(130,550,150,520);
		drawLine(150,520,170,550);
		drawLine(120,530,140,500);
		drawLine(140,500,160,500);
		drawLine(160,500,180,530);
		drawLine(180,530,180,450);
		drawLine(200,550,200,450);
		drawLine(100,550,130,550);
		drawLine(170,550,200,550);
		drawLine(100,450,120,450);
		drawLine(180,450,200,450);
		//I
		drawLine(230,450,230,550);
		drawLine(230,550,250,550);
		drawLine(250,550,250,450);
		drawLine(250,450,230,450);	

		//N
		drawLine(280,450,280,550);
		drawLine(300,450,300,530);
		drawLine(310,550,340,470);
		drawLine(300,530,330,450);
		drawLine(340,470,340,550);
		drawLine(360,450,360,550);
		drawLine(280,550,310,550);
		drawLine(330,450,360,450);
		drawLine(280,450,300,450);
		drawLine(340,550,360,550);
		drawLine(360,450,340,450);
		
		//U
		
		drawLine(390,470,390,550);
		drawLine(410,480,410,550);
		drawLine(450,480,450,550);
		drawLine(470,470,470,550);
		drawLine(410,450,450,450);
		drawLine(420,470,440,470);
		drawLine(390,470,410,450);
		drawLine(410,480,420,470);
		drawLine(450,450,470,470);
		drawLine(450,480,440,470);
		drawLine(390,550,410,550);
		drawLine(450,550,470,550);
		

		//F
		drawLine(100,300,100,400);
		drawLine(100,400,160,400);
		drawLine(160,400,160,380);
		drawLine(160,380,120,380);
		drawLine(120,380,120,360);
		drawLine(120,360,150,360);
		drawLine(150,360,150,340);
		drawLine(150,340,120,340);
		drawLine(120,340,120,300);
		drawLine(120,300,100,300);

		
		//R
		drawLine(190,300,190,400);
		drawLine(190,400,240,400);
		drawLine(240,400,250,390);
		drawLine(250,390,250,350);
		drawLine(250,350,240,340);
		drawLine(240,340,235,340);
		drawLine(235,340,250,300);
		drawLine(250,300,235,300);
		drawLine(235,300,220,340);
		drawLine(220,340,210,340);
		drawLine(210,340,210,300);
		drawLine(210,300,190,300);
		drawLine(210,380,225,380);
		drawLine(225,380,230,375);
		drawLine(230,375,230,365);
		drawLine(230,365,225,360);
		drawLine(225,360,210,360);
		drawLine(210,360,210,380);

		//A
		drawLine(280,300,310,400);
		drawLine(280,300,300,300);
		drawLine(310,400,330,400);		
		drawLine(330,400,360,300);
		drawLine(340,300,360,300);
		drawLine(300,300,305,330);
		drawLine(340,300,335,330);
		drawLine(305,330,335,330);
		drawLine(320,390,305,340);
		drawLine(320,390,335,340);
		drawLine(305,340,335,340);

		//N
		drawLine(390,300,390,400);
		drawLine(410,300,410,380);
		drawLine(420,400,450,320);
		drawLine(410,380,440,300);
		drawLine(450,320,450,400);
		drawLine(470,300,470,400);
		drawLine(390,400,420,400);
		drawLine(440,300,470,300);
		drawLine(390,300,410,300);
		drawLine(450,400,470,400);
		drawLine(470,300,450,300);
	}

	void dispFillHouse()
	{
		drawLine(400,100,420,200);
	}

	void dispLine(void)
	{
	     glClear(GL_COLOR_BUFFER_BIT); // clears the screen
	     if(drawName==true){
		     dispName();}
	     if(drawHouse==true){
		     dispHouse();}
	     if(fillHouse==true){
		    dispFillHouse();}
    	     glutSwapBuffers();
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		//cout<<key<<endl;
		switch (key)
		{
			case 27:       //ESCAPE key
				exit(0);
				break;

			case ('d'):   
					frontCount=frontCount+1;   
					if(frontCount==0)
					{
						drawName = true;
						drawHouse = false;
						fillHouse = false;
						break;
					}
					if(frontCount==1)
					{
						drawName = false;
						drawHouse = true;
						fillHouse = false;
						break;
					}
					if(frontCount>=2)
					{
						drawName = false;
						drawHouse = false;
						fillHouse = true;
						backCount=2;
						frontCount=2;
						break;
					}
					
			case 'a':
			{
				backCount = backCount - 1;
				if(backCount==2)
				{
					drawName = false;
					drawHouse = false;
					fillHouse = true;
					break;	
				}
				else if(backCount==1)
				{
					drawName = false;
					drawHouse = true;
					fillHouse = false;
					break;
				}
				else if(backCount<=0)
				{
					drawName = true;
					drawHouse = false;
					fillHouse = false;
					frontCount=0;	
					break;
				}
			}
			
			default : exit(0);
					break;
	}
}

	int main(int argc, char** argv)
	{
	     glutInit (&argc, argv); // to initialize the toolkit;
	     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // sets the display mode
	     glutInitWindowSize (800, 800); // sets the window size
	     glutInitWindowPosition (0, 0); // sets the starting position for the window
	     glutCreateWindow ("Assignment 1"); // creates the window and sets the title
	     glutKeyboardFunc (Keyboard);
	     glutDisplayFunc (dispLine);
	     glutIdleFunc(dispLine);
	     myInit(); // additional initializations as necessary
	     glutMainLoop(); // go into a loop until event occurs
	     return (EXIT_SUCCESS);
	}


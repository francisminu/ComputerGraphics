
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

		glColor3f(140.0f,0.0f,0.0f);
		drawLine(430,470,450,470);
		drawLine(430,440,450,440);
		drawLine(420,455,430,440);
		drawLine(450,440,460,455);
		drawLine(450,470,460,455);		
		drawLine(420,455,430,470);

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
		//drawLine(100,350,700,350);
		//drawLine(100,450,700,450);
		//M
		drawLine(100,350,100,450);
		drawLine(120,350,120,430);
		drawLine(130,450,150,420);
		drawLine(150,420,170,450);
		drawLine(120,430,140,400);
		drawLine(140,400,160,400);
		drawLine(160,400,180,430);
		drawLine(180,430,180,350);
		drawLine(200,450,200,350);
		drawLine(100,450,130,450);
		drawLine(170,450,200,450);
		drawLine(100,350,120,350);
		drawLine(180,350,200,350);
		//I
		drawLine(230,350,230,450);
		drawLine(230,450,250,450);
		drawLine(250,450,250,350);
		drawLine(250,350,230,350);	

		//N
		drawLine(280,350,280,450);
		drawLine(300,350,300,430);
		drawLine(310,450,340,370);
		drawLine(300,430,330,350);
		drawLine(340,370,340,450);
		drawLine(360,350,360,450);
		drawLine(280,450,310,450);
		drawLine(330,350,360,350);
		drawLine(280,350,300,350);
		drawLine(340,450,360,450);
		drawLine(360,350,340,350);
		
		//U
		
		drawLine(390,370,390,450);
		drawLine(410,380,410,450);
		drawLine(450,380,450,450);
		drawLine(470,370,470,450);
		drawLine(410,350,450,350);
		drawLine(420,370,440,370);
		drawLine(390,370,410,350);
		drawLine(410,380,420,370);
		drawLine(450,350,470,370);
		drawLine(450,380,440,370);
		drawLine(390,450,410,450);
		drawLine(450,450,470,450);
		

		//F
		drawLine(100,200,100,300);
		drawLine(100,300,160,300);
		drawLine(160,300,160,280);
		drawLine(160,280,120,280);
		drawLine(120,280,120,265);
		drawLine(120,260,150,260);
		drawLine(150,260,150,240);
		drawLine(150,240,120,240);
		drawLine(120,240,120,200);
		drawLine(120,200,100,200);

		
		//R
		drawLine(190,200,190,300);
		drawLine(190,300,240,300);
		drawLine(240,300,250,290);
		drawLine(250,290,250,250);
		drawLine(250,250,240,240);
		drawLine(240,240,235,240);
		drawLine(235,240,250,200);
		drawLine(250,200,235,200);
		drawLine(235,200,220,240);
		drawLine(220,240,210,240);
		drawLine(210,240,210,200);
		drawLine(210,200,190,200);
		drawLine(210,280,225,280);
		drawLine(225,280,230,275);
		drawLine(230,275,230,265);
		drawLine(230,265,225,260);
		drawLine(225,260,210,260);
		drawLine(210,260,210,280);
	}

	void dispFillHouse()
	{
		drawLine(400,100,420,200);
	}

	void dispLine(void)
	{
	     glClear(GL_COLOR_BUFFER_BIT); // clears the screen
	     //dispHouseShape();
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
					if(frontCount==2)
					{
						drawName = false;
						drawHouse = false;
						fillHouse = true;
						break;
					}
					if(frontCount>=3)
					{
						backCount==2;
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
				else if(backCount==0)
				{
					drawName = true;
					drawHouse = false;
					fillHouse = false;
					
					break;
				}
				else if(backCount<0)
				{
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


#pragma once
//TANK WARS
//#1. Tank Wars
//This File Contains All the Essential Structs And enums Used in the game.
#include<GL/glut.h>
#include<math.h>

int GAME_WIDTH  = 1355;									//width of game
int GAME_HEIGHT = 720;									//height of game
int GAME_MENU_AREA = 55;							    //top area of the game

enum STATE
{
	FORWARD=0,BACKWARD,UPWARD,DOWNWARD, NEUTRAL,DASH,RANDOM
};

enum ControllerState{KEYBOARD,MOUSE,KEYBOARDSPECIAL};
struct Vector2										//point in 2D
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}

	void operator () (double x = 0, double y = 0) 
	{
		this->x = x;
		this->y = y;
	}

	double operator-(const Vector2 &b)
	{
		return abs(sqrt ((x-b.x)*(x-b.x) - (y-b.y)*(y-b.y)));
	}
};

struct Color										
{
	float r, g, b;

	Color(int r=255,int g=0,int b=0)
	{
		this->r = (float)r/255;
		this->g = (float)g/255;
		this->b = (float)b/255;
	}

	//set color of object
	void SetColor(int r, int g , int b)
	{
		this->r = (float)r / 255;
		this->g = (float)g / 255;
		this->b = (float)b / 255;
	}

	void SetColor(const Color& c)
	{
		this->r = c.r;
		this->g = c.g;
		this->b = c.b;
	}
	//change color of OpenGL
	void SetGLColor()
	{
		glColor3f(r,g,b);
	}

	//some Static Colors
	static Color BLACK()      { Color temp(0, 0, 0)      ; return temp; }
	static Color WHITE()      { Color temp(255, 255, 255); return temp; }
	static Color RED()        {	Color temp(255, 0, 0)    ;return temp;  }
	static Color GREEN()      {	Color temp(0,255, 0)     ;return temp;  }
	static Color BLUE()       {	Color temp(0, 0, 255)    ;return temp;  }
	static Color CYAN()       {	Color temp(0, 255, 255)  ;return temp;  }
	static Color MAGENTA()    {	Color temp(255, 0, 255)  ;return temp;  }
	static Color YELLOW()     {	Color temp(255, 255, 0)  ;return temp;  }
	static Color SPRINGGREEN(){	Color temp(20, 255, 127) ;return temp;  }
	static Color TEAL()       {	Color temp(0,128,128)    ;return temp;  }
	static Color OBSTACLE_DARK(){Color temp{33,33,33}    ;return temp;  }
	static Color OBSTACLE_LIGHT(){Color temp{131,140,125}    ;return temp;  }

	static Color ARROWHEAD1() { return Color::YELLOW(); }
	static Color ARROWHEAD2() { return Color::YELLOW(); }
};


//support function to reduce code size somewhere :)
//draws Filled rectangle with centre,length,width
void DrawRectangle(double x,double y,double len,double wid)
{
	glBegin(GL_QUADS);
	glVertex2d(x + len / (double)2, y + wid / (double)2);//1st quad
	glVertex2d(x + len / (double)2, y - wid / (double)2);//4th quad
	glVertex2d(x - len / (double)2, y - wid / (double)2);//3rd quad
	glVertex2d(x - len / (double)2, y + wid / (double)2);//2nd quad
	glEnd();
}

//support function to reduce code size somewhere :)
//draws Filled rectangle with bottomleft,topright points
void DrawRectangleCorner(double x_min, double y_min, double x_max, double y_max, bool filled = true)
{
	if(filled)
		glBegin(GL_QUADS);
	else
		glBegin(GL_LINE_LOOP);
	glVertex2d(x_min,y_min);
	glVertex2d(x_max,y_min);
	glVertex2d(x_max,y_max);
	glVertex2d(x_min,y_max);
	glEnd();
}

//for debugging purposes
void DText(string text, int x, int y, const Color& c = Color::RED(), int font = 5)
{
	Color textColor = c;
	textColor.SetGLColor();

	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
}
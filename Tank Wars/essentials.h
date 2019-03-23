#pragma once
//#1. Tank Wars
//This File Contains All the Essential Structs And enums Used in the game.
#include<GL/glut.h>

int WIDTH = 1355;									//width of game
int HEIGHT=720;										//height of game

enum STATE
{
	FORWARD=1,BACKWARD,UPWARD,DOWNWARD, NEUTRAL,DEAD
};

enum ControlState
{
	KEYBOARD, KEYBOARDSPECIAL, MOUSE
};

struct Vector2										//point in 2D
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
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

	//change color of OpenGL
	void SetGLColor()
	{
		glColor3f(r,g,b);
	}

	//some Static Colors
	static Color RED()        {	Color temp(255, 0, 0)    ;return temp;}
	static Color GREEN()      {	Color temp(0,255, 0)     ;return temp;}
	static Color BLUE()       {	Color temp(0, 0, 255)    ;return temp;}
	static Color CYAN()       {	Color temp(0, 255, 255)  ;return temp;}
	static Color MAGENTA()    {	Color temp(255, 0, 255)  ;return temp;}
	static Color YELLOW()     {	Color temp(255, 255, 0)  ;return temp;}
	static Color SPRINGGREEN(){	Color temp(20, 255, 127) ;return temp;}
	static Color TEAL()       {	Color temp(0,128,128)    ;return temp;}

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
void DrawRectangleCorner(double x_min, double y_min, double x_max, double y_max)
{
	glBegin(GL_QUADS);
	glVertex2d(x_min,y_min);
	glVertex2d(x_max,y_min);
	glVertex2d(x_max,y_max);
	glVertex2d(x_min,y_max);
	glEnd();
}
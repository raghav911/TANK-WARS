#pragma once
//#1.
//This File Contains All the Essential Structs And enums Used in the game.
#include<GL/glut.h>

int width = 1355;
int height=720;

enum STATE
{
	FORWARD=1,BACKWARD,UPWARD,DOWNWARD, DEAD
};

enum ControlState
{
	KEYBOARD, KEYBOARDSPECIAL, MOUSE
};

struct Vector2
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
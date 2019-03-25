//TANK WARS
#pragma once
//#8.
//this File is Responsible for all the Initialization and registering GLUT callbacks.


//width and height already defined in essentials.h
//int width = 650;
//int height = 400;


//callbacks
void Reshape(int,int);
void Display();
void Keyboard(unsigned char,int,int);
void KeyboardSpec(int, int, int);
void MouseFunc(int,int,int,int);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//					:~>  INITIALIZERS <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------~>[ INIT ]<~---------------------
void InitCallbackFunc();
void Init()
{
	//initialize window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(GAME_WIDTH,GAME_HEIGHT);
	glutCreateWindow("TANK WARS");

	//initialize viewport
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	gluOrtho2D(0, GAME_WIDTH, 0, GAME_HEIGHT);
	//glMatrixMode(GL_MODELVIEW);

	//set bg color
	glClearColor((double)57/255, (double)64/255, (double)62/255,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	InitCallbackFunc();
}

//---------------------~>[ CLEAR ]<~---------------------
void clear()
{
	glClearColor((double)57 / 255, (double)64 / 255, (double)62 / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//---------------------~>[ CALL_BACKS ]<~---------------------
void InitCallbackFunc()
{
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseFunc);
	glutSpecialFunc(KeyboardSpec);
	glutReshapeFunc(Reshape);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
//					:~>  CALLBACKS <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ Reshape ]<~---------------------
void Reshape(int x,int y)
{
	if (GAME_WIDTH == x && GAME_HEIGHT == y) return;
	
	//preventing user from reshaping the window :)
	glutReshapeWindow(GAME_WIDTH,GAME_HEIGHT);
	clear();
}

//---------------------~>[ Dispaly ]<~---------------------
void Display(){}

//---------------------~>[ MOUSE ]<~---------------------
void MouseFunc(int button, int state, int x, int y)
{
	y = -y + GAME_HEIGHT;
	if(state==GLUT_DOWN)
	PlayerControls((int)button, MOUSE);

	if (isGamepaused)
	{
		xMouseClick = x;
		yMouseClick = y;
	}
}
//---------------------~>[ Keyboard ]<~---------------------
void Keyboard(unsigned char key, int, int)
{
	//std::cout << (int)key;
	PlayerControls((int)key,KEYBOARD);

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'r':
		if (!isGameRunning)
			ResetGame();
		break;
	case 'p':
		isGamepaused = true;
		//Canvas::Update();
		break;
	}
//----------------------------------------------------------------------------------------
	//	//mapdesign
	//case 't':
	//	gameObstacles[gameObstacles.size() - 1]->MoveUpward();
	//	break;
	//case 'g':
	//	gameObstacles[gameObstacles.size() - 1]->MoveDownward();
	//	break;
	//case 'f':
	//	gameObstacles[gameObstacles.size() - 1]->MoveBackward();
	//	break;
	//case 'h':
	//	gameObstacles[gameObstacles.size() - 1]->MoveForward();
	//	break;
	//case 'j':
	//	gameObstacles[gameObstacles.size() - 1]->ShowPoints();
	//	break;
	//case '0':
	//	gameObstacles[gameObstacles.size() - 1]->IncreaseSpeed();
	//	break;
	//case '9':
	//	gameObstacles[gameObstacles.size() - 1]->DecreaseSpeed();
	//	break;
	//case '8':
	//	gameObstacles[gameObstacles.size() - 1]->NeutralSpeed();
	//	break;
	//default:
	//	gameObstacles[gameObstacles.size() - 1]->StopMovement();
	//	break;
	//}
	//helpers ends here
}

//---------------------~>[ Keyboard_Special ]<~---------------------
void KeyboardSpec(int key, int, int)
{
	PlayerControls(key, KEYBOARDSPECIAL);
	
	//map design helpers
	//switch(key)
	//{
	//case GLUT_KEY_UP:
	//	gameObstacles[gameObstacles.size() - 1]->IncreaseHeight();
	//	break;
	//case GLUT_KEY_DOWN:
	//	gameObstacles[gameObstacles.size() - 1]->DecreaseHeight();
	//	break;
	//case GLUT_KEY_RIGHT:
	//	gameObstacles[gameObstacles.size() - 1]->IncreaseWidth();
	//	break;
	//case GLUT_KEY_LEFT:
	//	gameObstacles[gameObstacles.size() - 1]->DecreaseWidth();
	//	break;
	//default:
	//	gameObstacles[gameObstacles.size() - 1]->StopMovement();
	//	break;
	//}
	//helpers ends
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
//					:~>  GAME_AREA <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ RESET GAME ]<~---------------------
void ResetGame()
{
	if (P1) delete P1;
	if (P2) delete P2;

	//Level::RandomLevel(gameObstacles);
	Level::RandomLevel(gameObstacles);


	P1Bullet.clear();
	P2Bullet.clear();

	P1HitTaken = 0;
	P2HitTaken = 0;

	//Player Colors
	P1color.SetColor(Color::CYAN());
	P2color.SetColor(Color::MAGENTA());

	P1 = new Player(30, GAME_HEIGHT/2,FORWARD);
	P1->SetInternalColor(Color::BLUE());
	P1->SetColor(P1color);
	P1->Draw();
	P1Alive = true;
	
	P2 = new Player(GAME_WIDTH-30, GAME_HEIGHT/2,BACKWARD);
	P2->SetInternalColor(Color::BLUE());
	P2->SetColor(P2color);
	P2->Draw();
	P2Alive = true;

	glFlush();
	isGameRunning = true;
	Canvas::Update();
}

//---------------------~>[ PLAYER CONTROLS ]<~---------------------
void P1Shoots()					//P1 Shooting Controls
{
	if (P1->GetDrawState() != NEUTRAL && P1Bullet.size() < projectileCount)
	{
		P1Bullet.push_back(new Projectile(P1->GetCentre()));//P1 bullet based on the curr location of P1
		P1Bullet[P1Bullet.size() - 1]->SetState(P1->GetDrawState());
		P1Bullet[P1Bullet.size() - 1]->SetColor(P1->GetPlayerColor());
	}
}
void P2Shoots()					//P2 Shooting Controls
{
	if (P2Alive && P2->GetDrawState() != NEUTRAL && P2Bullet.size() < projectileCount)
	{
		P2Bullet.push_back(new Projectile(P2->GetCentre()));//P1 bullet based on the curr location of P1
		P2Bullet[P2Bullet.size() - 1]->SetState(P2->GetDrawState());
		P2Bullet[P2Bullet.size() - 1]->SetColor(P2->GetPlayerColor());
	}
}


void PlayerControls(int key,int controllerType)
{
	if (isGamepaused)  return;
	switch (controllerType)//who is calling this 
	{
	case KEYBOARD:
		if(P1Alive)//Player 1 Controls
		switch (key)
		{
		case 'w':
			P1->MoveUpward();
			break;
		case 's':
			P1->MoveDownward();
			break;
		case 'd':
			P1->MoveForward();
			break;
		case 'a':
			P1->MoveBackward();
			break;
		case 'f':
			P1->Dash();
			break;
		case 32://P1 Shoots(space)
			P1Shoots();
			break;
			//P1 controls ends here
		case 13://P2 Shoots
			P2Shoots();
		}
		//keyboard ends here
		break;
	//-----------------:~> 2nd CASE <~:-----------------
	case KEYBOARDSPECIAL:
		if(P2Alive)//P2 Alive
		switch (key)//P2 Controls
		{
		case GLUT_KEY_UP:
			P2->MoveUpward();
			break;
		case GLUT_KEY_DOWN:
			P2->MoveDownward();
			break;
		case GLUT_KEY_RIGHT:
			P2->MoveForward();
			break;
		case GLUT_KEY_LEFT:
			P2->MoveBackward();
			break;
		}
		//Keyboard_Special ends here
		break;
	//-----------------:~> 3rd CASE <~:-----------------
	case MOUSE:
		if(P2Alive)
		switch (key)
		{
		case GLUT_LEFT_BUTTON:
			P2Shoots();
			break;
		}
	
		//MOUSE ends here
		break;
	}//switch controller type ends here
}
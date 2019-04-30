//TANK WARS
#pragma once
//#8.
//this File is Responsible for all the Initialization and registering GLUT callbacks.


//width and height already defined in essentials.h
//int width = 650;
//int height = 400;

//game Area
void DrawPlayers();


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
	gluOrtho2D(0, GAME_WIDTH, 0, GAME_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);

	//set bg color
	glClearColor((double)57/255, (double)64/255, (double)62/255,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
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
	//glutFullScreen();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
//					:~>  CALLBACKS <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

void Reshape(int w, int h)
{
	if (w == 0 || h == 0) return;

	//Level::SetLevelScale((double)w/1355,(double)h/720);
	//Level::SetLevelScale(0.5,0.5);

	GAME_WIDTH = w;
	GAME_HEIGHT = h;
	Level::CurrentLevel(gameObstacles);
	DrawPlayers();
}


//---------------------~>[ Dispaly ]<~---------------------
void Display(){}

//---------------------~>[ MOUSE ]<~---------------------
void MouseFunc(int button, int state, int x, int y)
{
	y = -y + GAME_HEIGHT;
	if(state==GLUT_DOWN)
	PlayerControls(button,MOUSE);

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
		isGamepaused = !isGamepaused;
		break;
	case 'b':
		autoPlay = !autoPlay;
		if (autoPlay)
			BotPlay(botReactionTime);
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
	PlayerControls(key,KEYBOARDSPECIAL);
	
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


//---------------------~>[ PLAYER CONTROLS ]<~---------------------
void P1Shoots()					//P1 Shooting Controls
{
	if (P1->GetDrawState() != NEUTRAL && P1Bullet.size() < projectileCount)
	{
		double bulletDamage=1;
		double speedInc=0;
		if (P1->RageMode())
		{
			speedInc = 2.0;
			bulletDamage = 2.0;
		}

		P1Bullet.push_back(new Projectile(P1->GetCentre(),bulletDamage));//P1 bullet based on the curr location of P1
		P1Bullet[P1Bullet.size() - 1]->SetState(P1->GetDrawState());
		P1Bullet[P1Bullet.size() - 1]->SetColor(P1->GetPlayerColor());
		P1Bullet[P1Bullet.size() - 1]->IncreaseSpeed(speedInc);
	}
}
void P2Shoots()					//P2 Shooting Controls
{
	if (P2Alive && P2->GetDrawState() != NEUTRAL && P2Bullet.size() < projectileCount)
	{
		double bulletDamage = 1;
		double speedInc = 0;
		if (P2->RageMode())
		{
			speedInc = 2.0;
			bulletDamage = 2.0;
		}

		P2Bullet.push_back(new Projectile(P2->GetCentre(),bulletDamage));//P1 bullet based on the curr location of P1
		P2Bullet[P2Bullet.size() - 1]->SetState(P2->GetDrawState());
		P2Bullet[P2Bullet.size() - 1]->SetColor(P2->GetPlayerColor());
		P2Bullet[P2Bullet.size() - 1]->IncreaseSpeed(speedInc);
	}
}


void PlayerControls(int key,ControllerState controller)
{
	if (isGamepaused)  return;
	//P1Controls
	if (P1Alive)
	{
		if(controller==KEYBOARD)
		switch (key)
		{
		case 'w':
			P1->Move(UPWARD);
			break;
		case 's':
			P1->Move(DOWNWARD);
			break;
		case 'd':
			P1->Move(FORWARD);
			break;
		case 'a':
			P1->Move(BACKWARD);
			break;
		case 'f':
			//P1->Dash();
			break;
		case 32://P1 Shoots(space)
			P1Shoots();
			break;
		}
	}

	//P2 Controls
	if (P2Alive && !autoPlay)
	{
		if (controller == KEYBOARDSPECIAL)
			switch (key)
			{
			case GLUT_KEY_UP:
				P2->Move(UPWARD);
				break;
			case GLUT_KEY_DOWN:
				P2->Move(DOWNWARD);
				break;
			case GLUT_KEY_RIGHT:
				P2->Move(FORWARD);
				break;
			case GLUT_KEY_LEFT:
				P2->Move(BACKWARD);
				break;
			}
		if (controller == KEYBOARD)
			switch (key)
			{
			case 13://enter
				P2Shoots();
				break;
			}
		if (controller == MOUSE)
			switch (key)
			{
			case GLUT_LEFT_BUTTON:
				P2Shoots();
				break;
			}
	}
}


//---------------------~>[ RESET GAME ]<~---------------------

void DrawPlayers()
{
	if (P1) delete P1;
	if (P2) delete P2;

	P1color.SetColor(Color::RED());
	P1 = new Player(30, GAME_HEIGHT / 2, FORWARD);
	P1->SetInternalColor(Color::YELLOW());
	P1->SetColor(P1color);
	P1->Draw();

	P2color.SetColor(Color::GREEN());
	P2 = new Player(GAME_WIDTH - 30, GAME_HEIGHT / 2, BACKWARD);
	P2->SetInternalColor(Color::BLUE());
	P2->SetColor(P2color);
	P2->Draw();
}


void ResetGame()
{
	if(GAME_WIDTH== 1355 && GAME_HEIGHT== 720)
	 Level::RandomLevel(gameObstacles);
	else
	 Level::BasicLevel(gameObstacles);

	P1Bullet.clear();
	P1Alive = true;

	P2Bullet.clear();
	P2Alive = true;

	DrawPlayers();

	glFlush();
	isGameRunning = true;
	Canvas::Update();
}

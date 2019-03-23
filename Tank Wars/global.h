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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//					:~>  INITIALIZERS <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//---------------------~>[ INIT ]<~---------------------
void InitCallbackFunc();
void Init()
{
	//initialize window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("TANK WARS");

	//initialize viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_MODELVIEW);

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
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(KeyboardSpec);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//
//					:~>  CALLBACKS <~:
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<//

//---------------------~>[ Reshape ]<~---------------------
void Reshape(int x,int y)
{
	if (WIDTH == x && HEIGHT == y) return;
	
	//preventing user from reshaping the window :)
	glutReshapeWindow(WIDTH,HEIGHT);
	clear();
}

//---------------------~>[ Dispaly ]<~---------------------
void Display(){}

//---------------------~>[ Keyboard ]<~---------------------
void Keyboard(unsigned char key, int, int)
{
	//std::cout << (int)key;
	PlayerControls((int)key,KEYBOARD);

	switch (key)
	{
	case 'r':
		if(!isGameRunning)
		ResetGame();
		break;
	}
}

//---------------------~>[ Keyboard_Special ]<~---------------------
void KeyboardSpec(int key, int, int)
{
	//std::cout << (int)key;
	PlayerControls(key, KEYBOARDSPECIAL);
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

	P1Bullet.clear();
	P2Bullet.clear();

	P1HitTaken = 0;
	P2HitTaken = 0;

	P1 = new Player(20, HEIGHT/2,FORWARD);
	P1->SetColor(Color::CYAN());
	P1->Draw();
	P1Alive = true;
	
	P2 = new Player(WIDTH-20, HEIGHT/2,BACKWARD);
	P2->SetColor(Color::MAGENTA());
	P2->Draw();
	P2Alive = true;

	glFlush();
	isGameRunning = true;
	Canvas::Update();
}

//---------------------~>[ PLAYER CONTROLS ]<~---------------------
void PlayerControls(int key,int controllerType)
{
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

		case 32://P1 Shoots(space)
 			if (P1->GetDrawState()!=NEUTRAL && P1Bullet.size() < projectileCount)
			{
				P1Bullet.push_back(new Projectile(P1->GetCentre()));//P1 bullet based on the curr location of P1
				P1Bullet[P1Bullet.size() - 1]->SetState(P1->GetDrawState());
				P1Bullet[P1Bullet.size() - 1]->SetColor(P1->GetPlayerColor());
			}
			break;
			//P1 controls ends here
		case 13://P2 Shoots
			if (P2Alive && P2->GetDrawState() != NEUTRAL && P2Bullet.size() < projectileCount)
			{
					P2Bullet.push_back(new Projectile(P2->GetCentre()));//P1 bullet based on the curr location of P1
					P2Bullet[P2Bullet.size() - 1]->SetState(P2->GetDrawState());
					P2Bullet[P2Bullet.size() - 1]->SetColor(P2->GetPlayerColor());
			}
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

	}//switch controller type ends here
}
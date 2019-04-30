#pragma once
//for singleplayer
//this is experimental bot this controls player 2 when autoplay is enabled

//ansillary
void Evade();
void DontStop();

void BotPlay(int time)
{
	if (!autoPlay)  return;
	if (!P2)  return;
	
	Evade();
	DontStop();
	//P2Shoots();
	glutTimerFunc(time,BotPlay,time);
}

void Evade()
{
	
	for (int i = 0; i < P1Bullet.size(); ++i)
	{
		cout <<"Dist: "<< P1Bullet[i]->GetCentre() - P2->GetCentre()<<endl;
		if ((P1Bullet[i]->GetCentre() - P2->GetCentre()) < 140)
		{
			switch (P1Bullet[i]->GetState())
			{
			case FORWARD:
				P2->Move(UPWARD);
				break;
			case BACKWARD:
				P2->Move(DOWNWARD);
				break;
			case UPWARD:
				P2->Move(FORWARD);
				break;
			case DOWNWARD:
				P2->Move(BACKWARD);
				break;
			}
		}

	}
}

void DontStop()
{
	if (P2->GetState() == NEUTRAL)
	{
		P2->Move(RANDOM);
	}
}
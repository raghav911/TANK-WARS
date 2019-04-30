#pragma once
//Previous Detection Logic
/*switch (obj1->GetState())
	{
	case FORWARD:
		if (P1topRight.y > P2bottomLeft.y+offset && P1bottomLeft.y < P2topRight.y-offset && P1topRight.x >= P2bottomLeft.x && P1topRight.x < P2topRight.x)
			hasCollided = true;
		break;
	case BACKWARD:
		if (P1topRight.y > P2bottomLeft.y+offset && P1bottomLeft.y < P2topRight.y-offset && P1bottomLeft.x <= P2topRight.x && P1bottomLeft.x > P2bottomLeft.x)
			hasCollided = true;
		break;
	case UPWARD:
		if (P1topRight.x > P2bottomLeft.x+offset && P1bottomLeft.x < P2topRight.x-offset && P1topRight.y >= P2bottomLeft.y && P1topRight.y < P2topRight.y)
			hasCollided = true;
		break;
	case DOWNWARD:
		if (P1topRight.x > P2bottomLeft.x+offset && P1bottomLeft.x < P2topRight.x-offset && P1bottomLeft.y <= P2topRight.y && P1bottomLeft.y > P2bottomLeft.y)
			hasCollided = true;
		break;
	}

	return hasCollided;*/
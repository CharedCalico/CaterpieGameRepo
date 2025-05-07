#include "Treats.h"


Treats::Treats()
{

	if (!POI_sprite.loadFromFile("gfx/Candy.png")) std::cout << "Error loading ball sprite";
	setTexture(&POI_sprite);
	setSize({ 60,60 });
	setCollisionBox(0, 0, 50, 50);
	//Erin is making a change
}

Treats::~Treats()
{
	//std::cout << "POI reached";
}


int Treats::randomisePOI()
{
	PoiSpot =1 + rand() % 10 ;
	audio->playSoundbyName("CollectTreat");
	switch (PoiSpot)
	{

		break;

	case 1:
		// set position = (500,500)
		// set visable to true
		setPosition(500, 500);
		break;

	case 2:
		// set position = (500,500)
		// set visable to true
		setPosition(3000, 1500);
		break;
	case 3:
		// set position = (500,500)
		// set visable to true
		setPosition(50, 1875);
		break;
	case 4:
		// set position = (500,500)
		// set visable to true
		setPosition(750, 100);
		break;
	case 5:
		// set position = (500,500)
		// set visable to true
		setPosition(3440, 300);
		break;
	case 6:
		// set position = (500,500)
		// set visable to true
		setPosition(2940, 1670);
		break;
	
	case 7:
		// set position = (500,500)
		// set visable to true
		setPosition(1500, 1300);
		break;

	case 8:
		// set position = (500,500)
		// set visable to true
		setPosition(1240, 700);
		break;

	case 9:
		// set position = (500,500)
		// set visable to true
		setPosition(900, 1900);
		break;

	case 10:
		// set position = (500,500)
		// set visable to true
		setPosition(3010, 1080);
		break;

	default:
		setPosition(40, 500);
		break;
	}
	return 0;
}

void Treats::setAudioManager(AudioManager* _aud)
{
	audio = _aud;
}

#include "UI.h"
UI::UI(sf::View* Nview, Player* plyr, int type, sf::Vector2f og,sf::Font* nFont)
{
	font = nFont;
	setFont(*font);//font passed through constructor
	rotL = false;
	textType = type; //type is passed by for loop when UI is made
	switch (type)//selects what type of UI element the object will be
	{
	case HEALTH:
		textType = type;
		rect.setOrigin(0, 32);
		rect.setPosition(50, 100);
		sprite.loadFromFile("Heart.png");
		rect.setTexture(&sprite);//uses spriteSheet to display health
		rect.setSize(sf::Vector2f(512, 64));
		rect.setScale({ .8,.8 });
		break;


	case AMMO:
		setString("Ammo: 0");
		setCharacterSize(30);
		setStyle(sf::Text::Bold);
		setOutlineThickness(3);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(170, 140, 170, 255));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		break;

	case SCORE:
		setString("Score: 0");
		setCharacterSize(30);
		setStyle(sf::Text::Bold);
		setOutlineThickness(3);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(240, 162, 5, 255));
		setPosition(sf::Vector2f(50, 50));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		break;

	case TIME:
		setString("Time: 0s");
		setCharacterSize(30);
		setStyle(sf::Text::Bold);
		setOutlineThickness(3);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(240, 162, 5, 255));
		setPosition(sf::Vector2f(50, 50));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		break;

	case WEAPON1:
		setString(plyr->getWeaponFromSlot(0)->getName()); //displays name of weapons in player's first slot
		setCharacterSize(15);
		setStyle(sf::Text::Bold);
		setOutlineThickness(2);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(170, 140, 170, 255));
		setPosition(sf::Vector2f(50, 50));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		rect.setSize({ 100,125 });		//displays a background for the text and weapon sprite
		rect.setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		rect.setFillColor(sf::Color(255, 255, 255, 255));
		rect.setPosition(0, 0);
		sprite.loadFromFile("gfx/bgUI.png");
		rect.setTexture(&sprite);

		weapon.setSize({ 25,25 });		//displays the texture of the weapon in player first slot
		weapon.setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
		weapon.setPosition(0, 0);
		weapon.setFillColor(sf::Color(255, 255, 255, 255));
		weapon.setTexture(plyr->getWeaponFromSlot(0)->getTexture());
		weapon.setSize(sf::Vector2f(plyr->getWeaponFromSlot(0)->getTexture()->getSize().x ,
									plyr->getWeaponFromSlot(0)->getTexture()->getSize().y));
		weapon.setScale(1.5, 1.5);
		break;

	case WEAPON2:
		setString(plyr->getWeaponFromSlot(1)->getName()); //displays name of weapons in player's second slot
		setCharacterSize(15);
		setStyle(sf::Text::Bold);
		setOutlineThickness(2);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(170, 140, 170, 255));
		setPosition(sf::Vector2f(50, 50));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		rect.setSize({ 100,125 });
		rect.setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		rect.setPosition(0, 0);
		rect.setFillColor(sf::Color(255, 255, 255, 255));
		sprite.loadFromFile("gfx/bgUI.png");
		rect.setTexture(&sprite);

		weapon.setSize({ 25,25 });			//displays the texture of the weapon in player first slot
		weapon.setOrigin(getLocalBounds().width / 2, getLocalBounds().height/2);
		weapon.setPosition(0, 0);
		weapon.setFillColor(sf::Color(255, 255, 255, 255));
		weapon.setTexture(plyr->getWeaponFromSlot(1)->getTexture());
		weapon.setSize(sf::Vector2f( plyr->getWeaponFromSlot(1)->getTexture()->getSize().x ,
									 plyr->getWeaponFromSlot(1)->getTexture()->getSize().y ));//sets size of sprite to size of texture
		weapon.setScale(1.5, 1.5);

		break;

	case LOSE: //lose screen to be called when player dies
		rect.setPosition(10, 10);
		sprite.loadFromFile("LoseScreen.png");
		rect.setTexture(&sprite);
		rect.setSize(Nview->getSize());
		rect.setOrigin({rect.getSize().x/2,rect.getSize().y/2});
		rect.setFillColor(sf::Color(255, 255, 255, 0));//starts as invisible
		break;
	case OBJ: //current objective
		setString("COLLECT 10 PUMKINS TO ESCAPE");
		setCharacterSize(30);
		setStyle(sf::Text::Bold);
		setOutlineThickness(3);
		setOutlineColor(sf::Color(60, 29, 74, 255));
		setFillColor(sf::Color(240, 162, 5, 255));
		setPosition(sf::Vector2f(500, 50));
		setOrigin(getLocalBounds().width / 2, getLocalBounds().height);
		break;

	}
	player = plyr;
	camera = Nview;

	sf::Vector2f topCorner = { camera->getCenter().x - (camera->getSize().x / 2),0 };

}

UI::~UI()
{
}

void UI::setTimer(float dt ,float timeRemaning )	//time keeping function
{
	setString("Time: " + std::to_string(static_cast<int>(round(timeRemaning))) + "s");

	if (timeRemaning < 20 && timeRemaning>0)//rotates and shakes timer when time is runing low
	{
		setFillColor(sf::Color(240, 51, 5, 255));

		if (!rotL)
		{
			setRotation(getRotation() + (dt * (1000 - (timeRemaning * 50))));
			if (getRotation() < 100 && getRotation() > 44)
			{
				rotL = true;
			}
		}

		if (rotL)
		{
			setRotation(getRotation() - (dt * (1000 - (timeRemaning * 50))));
			if (getRotation() < 315 && getRotation() > 50)
			{
				rotL = false;
			}
		}
	}
	else//returns to normal when regain time
	{
		setFillColor(sf::Color::White);
		setRotation(0);
	}

}



void UI::update(float dt,float timeRemaining)
{

	switch (textType)
	{
	case HEALTH:

		if (player->getHp() <= 0)
		{
			rect.setFillColor(sf::Color::Transparent);//texture has minimum of 1 heart, so goes transparent when at 0
		}
		else {
			rect.setPosition((camera->getCenter().x - 925), (camera->getCenter().y - 500));//sets position
			sprite.loadFromFile("Heart.png", sf::IntRect(0, 0, player->getHp() * 64, 64));//updates texture to current health val from player
			rect.setTexture(&sprite);
			rect.setFillColor(sf::Color::White);
		}
		break;
		
	case AMMO:
		setPosition((camera->getCenter().x + 800), (camera->getCenter().y + 375));//set pos
		//sets ammo for each weapon currently equipped
		setString("" + std::to_string(player->getWeaponFromSlot(0)->getAmmo()) + "/" + std::to_string(player->getWeaponFromSlot(0)->getAmmoMax()) + 
				"	     " + std::to_string(player->getWeaponFromSlot(1)->getAmmo()) + "/" + std::to_string(player->getWeaponFromSlot(1)->getAmmoMax()));
	
		break;

	case SCORE:
		setPosition((camera->getCenter().x + 850), (camera->getCenter().y - 500)); //sets position
		break;
		
	case TIME:
		setPosition((camera->getCenter().x + 850), (camera->getCenter().y - 450)); //set position
		break;

	case WEAPON1:
		setPosition((camera->getCenter().x + 750), (camera->getCenter().y + 400));//set pos
		rect.setPosition(getPosition().x -5, getPosition().y - 3);
		weapon.setPosition(getPosition().x + 25, getPosition().y + 30);

		break;

	case WEAPON2:
		setPosition((camera->getCenter().x + 875), (camera->getCenter().y + 400));//set pos
		rect.setPosition(getPosition().x-(getLocalBounds().width/4), getPosition().y - 5);
		weapon.setPosition(getPosition().x+15, getPosition().y + 25);
		break;

	case LOSE:
		break;
	case OBJ:
		setPosition((camera->getCenter().x + 1250), (camera->getCenter().y - 450)); //set position
		break;

	}

}

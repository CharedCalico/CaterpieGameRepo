#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
class UI : public sf::Text
{

public:
	UI(sf::View* Nview, Player* plyr, int type, sf::Vector2f og,sf::Font* nFont);
	~UI();
	void setTimer(float dt, float timeRemaning);
	void update(float dt, float timeRemaining);
	sf::RectangleShape rect;
	sf::RectangleShape weapon;


private:

	sf::Font* font;
	sf::Text text;
	enum typeEnum {HEALTH,AMMO,SCORE,TIME,WEAPON1,WEAPON2,LOSE,OBJ};
	int textType;
	Player* player;
	sf::Texture sprite;
	sf::View* camera;
	bool rotL;
	float offset;
	
};


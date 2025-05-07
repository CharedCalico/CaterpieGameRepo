#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Treats.h"
#include "Player.h"

class Arrow : public GameObject
{
public:

	Arrow();
	~Arrow();

	void treat(Treats);
	void update(float dt,Treats* treats);
	void setplayer(Player* player);
	bool isDrawable() { return drawable; }

private:
	sf::Texture Arrow_sprite;
	Treats treats;
	Player *player;
	bool drawable;

	const float MINIMUM_VIEW_DISTANCE = 250.f;	// TUNABLE
};


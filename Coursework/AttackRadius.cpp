#include "AttackRadius.h"

AttackRadius::AttackRadius()
{
	setType(PROJECTILE);
	setSize({ 100,100 });
	setOrigin(0, 0);
	setCollisionBox(0, 0, 100, 100);
	setAlive(true);

	if (!Circle_sprite.loadFromFile("gfx/ring.png")) std::cout << "Error loading Friend sprite";
	setTexture(&Circle_sprite);
}

AttackRadius::~AttackRadius()
{
}



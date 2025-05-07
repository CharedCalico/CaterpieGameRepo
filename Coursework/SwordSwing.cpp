#include "SwordSwing.h"

SwordSwing::SwordSwing()
{
	setType(PROJECTILE);
	setCollisionBox({ 0,0,24,32 });
	setOrigin(-6,8);
	setSize({24,32});
	setPosition(0,0);
	setRotation(0);
	if (!sprite.loadFromFile("gfx/SwordSwingTest.png")) std::cout << "Failed to load sword swing";
	setTexture(&sprite);
	timer = 10;
	setAlive(true);
}

SwordSwing::SwordSwing(sf::Vector2f _pos, int _ang, sf::RenderWindow* _win)
{
	setType(PROJECTILE);
	setCollisionBox({ 0,0,24,32 });
	setVelocity(0,0);
	setOrigin(-12, 16);
	setSize({ 24,32 });
	setPosition(_pos);
	setRotation(_ang);
	if (!sprite.loadFromFile("gfx/SwordSwingTest.png")) std::cout << "Failed to load sword swing";
	setTexture(&sprite);
	timer = 10;
	setAlive(true);
	//std::cout << "Created\n";
}

SwordSwing::~SwordSwing()
{
	std::cout << "Sword swung" << std::endl;
}

void SwordSwing::update(float dt)
{
	timer-=dt;
	//std::cout << timer << std::endl;
	if (timer <= 0)
	{
		setAlive(false);
	}
}

void SwordSwing::collisionResponse(GameObject* collider)
{
	return;
}

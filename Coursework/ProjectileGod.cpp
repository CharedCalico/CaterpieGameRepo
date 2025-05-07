#include "ProjectileGod.h"

ProjectileGod::ProjectileGod()
{
	speed = 20;
	setType(PROJECTILE);
	setPosition(100, 100);
	setOrigin(4, 4);
	setVelocity({speed,speed});
	setSize({ 8,8 });
	setCollisionBox({0,0,8,8});
	dmg = 10;
	projAccel = 0;
	projDecel = 0;
	if (!sprite.loadFromFile("testBullet.png")) std::cout << "Error loading bullet sprite";
	setTexture(&sprite);
	alive = true;
	//std::cout << getPosition().x << ", " << getPosition().y;
}

ProjectileGod::ProjectileGod(sf::Vector2f _speed, sf::Vector2f _pos, float _accel, float _decel, sf::RenderWindow* window)
{
	speed = 20;
	setType(PROJECTILE);
	setPosition(_pos.x,_pos.y);
	setOrigin(4,4);
	setVelocity(_speed*speed);
	setSize({ 8,8 });
	setCollisionBox({ 0,0,8,8 });
	dmg = 10;
	projAccel = _accel;
	projDecel = _decel;
	if (!sprite.loadFromFile("testBullet.png")) std::cout << "Error loading bullet sprite";
	setTexture(&sprite);
	alive = true;

	setWindow(window);
	//std::cout << _speed.x << ", " << _speed.y<<"\n\n";
}

ProjectileGod::~ProjectileGod()
{
	std::cout << "projectile destroyed";
}

void ProjectileGod::update(float dt)
{
	move({ velocity.x * dt * 100,velocity.y * dt * 100 });

	if (getPosition().y > window->getView().getCenter().y+window->getView().getSize().y + 30
		|| getPosition().y < window->getView().getCenter().y - window->getView().getSize().y - 30
		|| getPosition().x > window->getView().getCenter().x + window->getView().getSize().x + 30
		|| getPosition().x < window->getView().getCenter().x - window->getView().getSize().x - 30) {
		alive = false;
	}
}

void ProjectileGod::collisionResponse(GameObject* collider)
{
	if (collider->getType() == ENEMY)
	{
		setAlive(false);
	}
}


#pragma once
#include "ProjectileGod.h"
class SwordSwing : public ProjectileGod
{
public:
	SwordSwing();
	SwordSwing(sf::Vector2f _pos, int _ang, sf::RenderWindow* _win);
	~SwordSwing();
	void update(float dt) override;
	void collisionResponse(GameObject* collider) override;

protected:
	int timer;
};
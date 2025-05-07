#pragma once
#include "Framework/GameObject.h"
#include "Enemy.h"
#include "Framework/AudioManager.h"

class ProjectileGod : public GameObject
{
public:
	ProjectileGod();
	ProjectileGod(sf::Vector2f _speed, sf::Vector2f _pos, float _accel, float _decel, sf::RenderWindow* window);
	~ProjectileGod();
	virtual void update(float dt) override;
	virtual void collisionResponse(GameObject* collider) override;
protected:
	float projAccel;
	float projDecel;
	float speed;
	int dmg;
	sf::Texture sprite;
};
#pragma once
#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"
#include "Player.h"
#include "AttackRadius.h"

class AiCompanion : public GameObject
{

protected:
	sf::Texture Friend_sprite;
	int health;
	float Accel;
	float MaxSpeed;
	float iTime;
	sf::Vector2f Targetpos;
	AudioManager* audio;
	Player player;
	WeaponGod weapon;
	AttackRadius attackR;
public:
	AiCompanion();
	~AiCompanion();
	void setHealth(int _health);
	int getHealth();
	void collisionResponse(GameObject* collider);
	void Update(float dt);
	void setTargetPos(sf::Vector2f _targetPos);
	void minusHp();
};


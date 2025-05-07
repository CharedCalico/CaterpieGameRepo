#pragma once
#include <string>
#include "Framework/GameObject.h"
#include "ProjectileGod.h"
#include "Framework/AudioManager.h"


class Enemy : public GameObject
{
protected:
	int health;
	float maxSpeed;
	float accel;
	sf::Vector2f targetPos;
	int scoreValue;
	sf::Texture sprite;
	AudioManager* audio;
public:
	Enemy();
	Enemy(sf::Vector2f _pos, AudioManager* _aud);
	~Enemy();

	virtual void update(float dt);
	void setTargetPos(sf::Vector2f _targetPos);
	void collisionResponse(GameObject* collider);
	//int collisionDetect(std::vector<ProjectileGod*> _projectiles);

	int getScoreVal();
	void setScoreVal(int _val);
	int getHealth();
};


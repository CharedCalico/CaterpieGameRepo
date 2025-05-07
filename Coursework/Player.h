#pragma once

#include "Framework/GameObject.h"
#include "ProjectileGod.h"
#include "WeaponGod.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void handleInput(float dt, Physics* _projectileContainer);
	void update(float dt);
	void addScore(int score);
	int getScore();
	void setScore(int score);


	void setHp(int _hp);
	int getHp();

	void setActiveWeapon(bool _active);
	bool getActiveWeapon();

	void setWeaponInSlot(WeaponGod* _weapon, int _slot, sf::RenderWindow* _win, Input* _in);
	WeaponGod* getWeaponFromSlot(int _slot);

	virtual void collisionResponse(GameObject* collider) override;
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setAudioManager(AudioManager* _aud);

private:
	float playAccel;
	float playDecel;
	float playMaxSpeed;
	sf::Texture spriteSheet;
	sf::Texture sprite[2];
	int playerScore;
	int hp;
	bool activeWeapon;
	WeaponGod* weapons[2];
	AudioManager* audio;

	float timeKeeper;
	float iTime;
	bool shootTrigger;
};

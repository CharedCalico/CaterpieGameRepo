#pragma once
#include "Framework/GameObject.h"
#include <iostream>
#include "ProjectileGod.h"
#include "Physics.h"

class WeaponGod : public GameObject
{
public:

	WeaponGod();
	WeaponGod(GameObject* _use, float _cdm, float _kb, float _spr, int _sh, int _amm, float _rl, AudioManager* _aud);
	~WeaponGod();

	virtual void update(float dt); 
	virtual void shoot(float dt, Physics* _projectileContainer); //Places projectiles into the physics handler

	//setters
	void setCoolDown(float _cd);
	void setCoolDownMax(float _cdm);
	void setKickback(float _kb);
	void setSpread(float _spr);
	void setShots(int _sh);
	void setAmmo(int _am);
	void setAmmoMax(int _amm);
	void setReloadTime(float _rl);
	void setUser(GameObject* _use);

	//getters
	float getCoolDown();
	float getCoolDownMax();
	float getKickBack();
	float getSpread();
	int getShots();
	int getAmmo();
	int getAmmoMax();
	float getReloadTime();
	GameObject* getUser();
	std::string getName();

protected:

	float coolDown; //Used to check how long until the next shot can be fired
	float coolDownMax; //Time between shots
	float kickBack; //Used to apply recoil to the player
	float spread; //Used to apply slight variation to bullet paths
	int shots; //number of shots at once, used for multiprojectile weapons like shotguns
	int ammo; //Current ammo
	int ammoMax; //Number of shots before reload
	float reloadTime; //Time taken to reload
	std::string sound; //Name of sound in audio manager, passed in shoot function to play the right noise. Overwritten in every child class
	std::string name; //Name of the weapon, for use in UI and text

	AudioManager* audio; //Allows weapons to make noises like shooting and swiping
	GameObject* user; //Usually will be player, may be used to make enemies carry weapons later.
	sf::Texture tex; //Used to store texture
};
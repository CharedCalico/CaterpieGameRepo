#pragma once
#include "WeaponGod.h"
class Shotgun : public WeaponGod
{
public:
	Shotgun();
	Shotgun(GameObject* _use, float _cdm, float _kb, float _spr, int _sh, int _amm, float _rl, AudioManager* _aud);
	//void shoot(std::vector<ProjectileGod*>* _projectileContainer) override;
};


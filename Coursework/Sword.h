#pragma once
#include "WeaponGod.h"
#include "SwordSwing.h"
class Sword : public WeaponGod
{
public:
	Sword();
	Sword(GameObject* _use, float _cdm, AudioManager* _aud);
	void shoot(float dt, Physics* _projectileContainer) override;
};


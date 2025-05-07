#include "Shotgun.h"

Shotgun::Shotgun()
{
	setType(WEAPON);
	user = nullptr;
	coolDownMax = 0;
	coolDown = 0;
	kickBack = 0;
	spread = 0;
	shots = 0;
	ammo = 0;
	ammoMax = 0;
	reloadTime = 0;

	setTextureRect({ 0,0,31,11 });
	if (!tex.loadFromFile("WeaponTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({ 31,11 });
	setOrigin(4, 6);

	audio = nullptr;
	sound = "ShotgunShoot";
	name = "Shotgun";
	setScale(1.5, 1.5);

}

Shotgun::Shotgun(GameObject* _use, float _cdm, float _kb, float _spr, int _sh, int _amm, float _rl, AudioManager* _aud)
{
	setType(WEAPON);
	user = _use;
	coolDown = 0;
	coolDownMax = _cdm;
	kickBack = _kb;
	spread = _spr;
	shots = _sh;
	ammo = _amm;
	ammoMax = _amm;
	reloadTime = _rl;

	setTextureRect({ 0,0,31,11 });
	if (!tex.loadFromFile("WeaponTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({ 31,11 });
	setOrigin(4, 6);

	audio = _aud;
	sound = "ShotgunShoot";
	name = "Shotgun";
	setScale(1.5, 1.5);

}


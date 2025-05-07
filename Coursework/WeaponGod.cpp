#include "WeaponGod.h"

//WeaponGod will never be loaded as its own weapon, but was used for initial testing of the weapon system, so it needed
//constructors
WeaponGod::WeaponGod() 
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
	if (!tex.loadFromFile("WeaponTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({12,4});
	setOrigin(0,2);
	audio = nullptr;
	sound = "DefaultShoot";
	name = "DefaultWeapon";

}

WeaponGod::WeaponGod(GameObject* _use, float _cdm, float _spr, float _kb, int _sh, int _amm, float _rl, AudioManager* _aud)
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
	if (!tex.loadFromFile("WeaponTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({ 12,4 });
	setOrigin(0, 2);
	audio = _aud;
	sound = "DefaultShoot";
	name = "DefaultWeapon";
}

WeaponGod::~WeaponGod()
{
}

//Default weapon update, keeps the weapon on top of its user and points it to the mouse
//Would need to be overwritten for any unconventially moving weapons or potential weapons held by enemies
void WeaponGod::update(float dt) 
{
	pointTo(sf::Mouse::getPosition(), window->getPosition());
	setPosition(user->getPosition());
	if (coolDown >= 0) coolDown -= dt * 100;
	else if (ammo <= 0) {
		ammo = ammoMax;
	}
	
}


void WeaponGod::shoot(float dt,Physics* _projectileContainer)
{
	srand(time(NULL));
	
	coolDown = coolDownMax;
	//std::cout << ammo << std::endl;

	audio->playSoundbyName(sound);
	float ang = findAngleTo(sf::Mouse::getPosition() - window->getPosition(), getPosition(), false);

	//if the player is not at the edge of the window throw them backwards when firing
	float kbRange = 10;
	if (user->getPosition().x < window->getSize().x * 3 + kbRange && user->getPosition().x > kbRange &&
		user->getPosition().y < window->getSize().y * 3 + kbRange && user->getPosition().y > kbRange) {
		user->setVelocity(cos(ang) * -kickBack, sin(ang) * -kickBack);
	}

	for (int i = 0; i < shots; i++)
	{
		ang += (float)(((rand() % ((int)spread * 100) + (-(int)spread * 100)))) / 10000;
		_projectileContainer->getVectorPointer()->push_back(new ProjectileGod({ cos(ang), sin(ang) }, getPosition(), 0, 0, window));
	}
	ammo--;
	if (ammo <= 0) coolDown = reloadTime;
	
}

void WeaponGod::setCoolDown(float _cd)
{
	coolDown = _cd;
}

void WeaponGod::setCoolDownMax(float _cdm)
{
	coolDownMax = _cdm;
}

void WeaponGod::setKickback(float _kb)
{
	kickBack = _kb;
}

void WeaponGod::setSpread(float _spr)
{
	spread = _spr;
}

void WeaponGod::setShots(int _sh)
{
	shots = _sh;
}

void WeaponGod::setAmmo(int _am)
{
	ammo = _am;
}

void WeaponGod::setAmmoMax(int _amm)
{
	ammoMax = _amm;
}

void WeaponGod::setReloadTime(float _rl)
{
	reloadTime = _rl;
}

void WeaponGod::setUser(GameObject* _use)
{
	user = _use;
}

float WeaponGod::getCoolDown()
{
	return coolDown;
}

float WeaponGod::getCoolDownMax()
{
	return coolDownMax;
}

float WeaponGod::getKickBack()
{
	return kickBack;
}

float WeaponGod::getSpread()
{
	return spread;
}

int WeaponGod::getShots()
{
	return shots;
}

int WeaponGod::getAmmo()
{
	return ammo;
}

int WeaponGod::getAmmoMax()
{
	return ammoMax;
}

float WeaponGod::getReloadTime()
{
	return reloadTime;
}


GameObject* WeaponGod::getUser()
{
	return user;
}

std::string WeaponGod::getName()
{
	return name;
}

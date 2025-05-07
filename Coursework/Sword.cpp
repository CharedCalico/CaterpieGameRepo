#include "Sword.h"

Sword::Sword(){
	setType(WEAPON);
	user = nullptr;
	coolDownMax = 0;
	coolDown = 0;
	kickBack = 0;
	spread = 0;
	shots = 0;
	ammo = 1;
	ammoMax = 1;
	reloadTime = 0;

	setTextureRect({ 0,0,32,32 });
	if (!tex.loadFromFile("gfx/SwordTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({ 32,32 });
	setOrigin(16, 24);
	setScale(1.5, 1.5);

	
	audio = nullptr;
	sound = "SwordShoot";
	name = "Sword";
}

Sword::Sword(GameObject* _use, float _cdm, AudioManager* _aud)
{
	setType(WEAPON);
	user = _use;
	coolDownMax = _cdm;
	coolDown = _cdm;
	kickBack = 0;
	spread = 0;
	shots = 0;
	ammo = 1;
	ammoMax = 1;
	reloadTime = 0;
	
	setTextureRect({0,0,32,32});
	if (!tex.loadFromFile("gfx/SwordTest.png")) std::cout << "Error loading weapon texture";
	setTexture(&tex);
	setSize({ 32,32 });
	setOrigin(12, 28);
	setScale(1.5, 1.5);

	audio = _aud;
	sound = "SwordShoot";
	name = "Sword";

}

void Sword::shoot(float dt, Physics* _projectileContainer)
{
	coolDown = coolDownMax;
	float ang = findAngleTo(sf::Mouse::getPosition() - window->getPosition(), getPosition(), true);
	audio->playSoundbyName(sound);
	_projectileContainer->getVectorPointer()->push_back(new SwordSwing(getPosition(),ang,window));
}

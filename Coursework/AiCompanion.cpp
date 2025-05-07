#include "AiCompanion.h"
AiCompanion::AiCompanion()
{
	setType(COM);
	Accel = 2;
	MaxSpeed = 10;
	health = 5;
	iTime = 0;
	setSize({90,90});
	setOrigin(0, 0);
	setCollisionBox(0, 0, 120, 120);
	setPosition(2000,0);
	//setAlive(true);
	if (!Friend_sprite.loadFromFile("gfx/Friend.png")) std::cout << "Error loading Friend sprite";
	setTexture(&Friend_sprite);
	
	audio = nullptr;
}

AiCompanion::~AiCompanion()
{
	std::cout << "Friend destroyed"; //if he dies :(
}

void AiCompanion::setHealth(int _health)
{
	health = _health;
}

int AiCompanion::getHealth()
{
	return health;
}

//if Ai colibes with enemy ai takes danmage
void AiCompanion::collisionResponse(GameObject* collider)
{
	if (alive) {
		if (collider->getType() == ENEMY) {
			//take damage when hit, or die if health =0
			if (health > 0) {
				health --;
			}
			//else setAlive(false);
		}
	}


}

void AiCompanion::Update(float dt)
{
	attackR.setPosition(getPosition());

	//move relative to the enemy target position (enemy's position)
	if (getPosition().x < Targetpos.x + 1000 && getPosition().x > Targetpos.x - 1000 &&
		getPosition().y < Targetpos.y + 1000 && getPosition().y > Targetpos.y - 1000) {
		MaxSpeed = 12;
		Accel = 1;
	}


	//move the Companion in the direction with a slow deccel to mimic floating
	if (Targetpos.x < getPosition().x) {
		if (velocity.x <MaxSpeed && velocity.x > MaxSpeed * -1.) velocity.x += Accel  * dt * -1.f;
		else velocity.x = MaxSpeed * -1.f;
	}
	if (Targetpos.x > getPosition().x) {
		if (velocity.x <MaxSpeed && velocity.x > MaxSpeed * -1) velocity.x += Accel  * dt;
		else velocity.x = MaxSpeed;
	}
	if (Targetpos.y < getPosition().y) {
		if (velocity.y <MaxSpeed && velocity.y > MaxSpeed * -1) velocity.y += Accel  * dt * -1.f;
		else velocity.y = MaxSpeed * -1.f;
	}
	if (Targetpos.y > getPosition().y) {
		if (velocity.y <MaxSpeed && velocity.y > MaxSpeed * -1) velocity.y += Accel  * dt;
		else velocity.y = MaxSpeed;
	}

	//move 
	move(velocity*dt*15.f);

}

void AiCompanion::setTargetPos(sf::Vector2f _aiTargetPos)
{
	Targetpos = _aiTargetPos;
}

void AiCompanion::minusHp()
{
	health--;
}


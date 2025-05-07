#include "Enemy.h"



Enemy::Enemy()
{
	//set default values
	setType(ENEMY);
	health = 3;
	maxSpeed = 2;
	accel = 1.05;
	scoreValue = 5;

	setOrigin(14, 8);
	setCollisionBox(0, 0, 48, 30);
	setSize({ 48, 30 });
	setAlive(true);

	if (!sprite.loadFromFile("gfx/batEnemy.png")) std::cout << "Error loading sprite from file";
	setTexture(&sprite);

	audio = nullptr;
}

Enemy::Enemy(sf::Vector2f _pos, AudioManager* _aud){
	setType(ENEMY);
	health = 3;
	maxSpeed = 50;
	accel = 10;
	scoreValue = 5;
	setOrigin(14, 8);
	setCollisionBox(0, 0, 48, 30);
	setSize({ 48, 30 });
	setAlive(true);
	setPosition(_pos);

	
	if (!sprite.loadFromFile("gfx/batEnemy.png")) std::cout << "Error loading sprite from file";
	setTexture(&sprite);

	audio = _aud;
}

//this is mostly to check enemies delete themselves
Enemy::~Enemy()
{
	std::cout << "Enemy Dead"<<std::endl;
}

void Enemy::update(float dt)
{

	//move relative to the target position (player's position)
	if (getPosition().x < targetPos.x + 1000 && getPosition().x > targetPos.x - 1000 &&
		getPosition().y < targetPos.y + 1000 && getPosition().y > targetPos.y - 1000) {
		maxSpeed = 10;
		accel = 1.5;
	}
	else {
		//make the enemies jump to player when they fall out of range
		maxSpeed = 500;
		accel = 500;
	}

	//move the enemy in the direction of the player with a slow deccel to mimic floating
	if (targetPos.x < getPosition().x) {
		if (velocity.x <maxSpeed && velocity.x > maxSpeed * -1) velocity.x += accel * dt * -1.f;
		else velocity.x = maxSpeed * -1.f;
	}
	if (targetPos.x > getPosition().x) {
		if (velocity.x <maxSpeed && velocity.x > maxSpeed * -1) velocity.x += accel * dt ;
		else velocity.x = maxSpeed;
	}
	if (targetPos.y < getPosition().y) {
		if (velocity.y <maxSpeed && velocity.y > maxSpeed * -1) velocity.y += accel * dt * -1.f;
		else velocity.y = maxSpeed * -1.f;
	}
	if (targetPos.y > getPosition().y) {
		if(velocity.y <maxSpeed && velocity.y > maxSpeed * -1) velocity.y += accel * dt;
		else velocity.y = maxSpeed;
	}
	
	//move :}
	move(velocity*dt*20.f);


}

void Enemy::setTargetPos(sf::Vector2f _targetPos)
//takes in the player's position so the enemies can accurately move towards them
{
	targetPos = _targetPos;
}


void Enemy::collisionResponse(GameObject*  collider)
{
	if (alive) {
		if (collider->getType() == PROJECTILE) {
			//take damage when hit, or die if health =0
			if (health > 0) {
				health -= 1;
			}
			else setAlive(false);
			audio->playSoundbyName("EnemyDeath");
		}
	}
	if (alive) {
		if (collider->getType() == COM) {
			//take damage when hit, or die if health =0
			if (health > 0) {
				health -= 2;
			}
			else setAlive(false);
			audio->playSoundbyName("EnemyDeath");
		}
	}
}


int Enemy::getScoreVal()
{
	//tell the level how much to increment the scorecounter by on death
	return scoreValue;
}

void Enemy::setScoreVal(int _val)
{
	//set the score value of an enemy
	scoreValue = _val;
}

//im not sure if this is ever called but it returns enemy health
int Enemy::getHealth() {
	return health;
}
#include "Player.h"

Player::Player()
{
	setType(PLAYER);
	velocity.x = 0;
	velocity.y = 0;
	playAccel = 2;
	playDecel = 1;
	playMaxSpeed = 7;
	playerScore = 0;
	hp = 5;
	setOrigin(17, 22);
	setPosition(1800, 200);
	setCollisionBox(0, 0, 35, 45);
	setSize({ 35,45 });
	/*if (!sprite.loadFromFile("gfx/Beach_Ball.png")) std::cout << "Error loading sprite from file";
	setTexture(&sprite);*/
	setAlive(true);
	//std::cout << getPosition().x << ", " << getPosition().y;
	activeWeapon = 0;
	weapons[0] = nullptr;
	weapons[1] = nullptr;
	iTime = 0;
	audio = nullptr;
	timeKeeper = 0;


	//load and cut up spritesheets
	sf::Vector2i playerSize = { 7, 9 };
	if (!spriteSheet.loadFromFile("gfx/triggertreatPlayer.png")) std::cout << "Error loading player sprites from file";
	else {
		for (int i = 0; i < std::size(sprite); i++) {
			sf::Vector2i pos = { playerSize.x * i, 0};
			sf::IntRect textureRect(pos.x, pos.y, playerSize.x, playerSize.y);
			sprite[i].loadFromImage(spriteSheet.copyToImage(), textureRect);
			setTexture(&sprite[0]);
		}
		
	}
}

Player::~Player()
{
	std::cout << "Player destroyed";
}


void Player::addScore(int Score)
{
	playerScore = playerScore + Score;
}
int Player :: getScore()
{
	return playerScore;
}
void Player::setScore(int score)
{
	playerScore = score;
}

void Player::setHp(int _hp)
{
	hp = _hp;
}

int Player::getHp()
{
	return hp;
}

void Player::setActiveWeapon(bool _active)
{
	if (weapons[_active] != nullptr && _active != activeWeapon) activeWeapon = !activeWeapon;
}

bool Player::getActiveWeapon()
{
	return activeWeapon;
}

void Player::setWeaponInSlot(WeaponGod* _weapon, int _slot, sf::RenderWindow* _win, Input* _in)
{
	_weapon->setInput(_in);
	_weapon->setWindow(_win);
	weapons[_slot] = _weapon;
}

WeaponGod* Player::getWeaponFromSlot(int _slot)
{
	return weapons[_slot];
}

void Player::collisionResponse(GameObject* collider)
{
if (collider->getType() == GameObject::ENEMY && iTime <= 0  ) {
		hp--;
		iTime = 1;
		audio->playSoundbyName("PlayerHit");
}

if (collider->getType() == GameObject::TREE && iTime <= 0) {
	hp--;
	iTime = 1;
	audio->playSoundbyName("PlayerHit");
}


}

void Player::setAudioManager(AudioManager* _aud)
{
	audio = _aud;
}


void Player::handleInput(float dt, Physics* _projectileContainer)
{
	shootTrigger = false;
	//horizontal direction value (-1 for left, 0 for 0, 1 for right)
	int8_t hVal = input->isKeyDown(sf::Keyboard::D) - input->isKeyDown(sf::Keyboard::A);

	//vertical direction value (1 for down, 0 for 0, -1 for up)
	int8_t vVal = input->isKeyDown(sf::Keyboard::S) - input->isKeyDown(sf::Keyboard::W);

	//mouse button value (-1 for left mouse, 0 for both or neither, 1 for right mouse down)
	int8_t mVal = input->isRightMouseDown() - input->isLeftMouseDown();



	//If moving vertically
	if (hVal != 0)
	{
		//if the player is not trying to move off screen
		if ((getPosition().x < (window->getSize().x)*3 && getPosition().x > 0) || //if the player is within the window
			(getPosition().x >= (window->getSize().x)*3 && hVal < 0) ||//or at the right edge and not moving right
			(getPosition().x <= 0 && hVal > 0)) { //or at the left edge and not moving left
				//if the player is not at max speed, accellerate in the direction its moving
				if (velocity.x < playMaxSpeed && velocity.x > playMaxSpeed * -1) velocity.x += playAccel * hVal * dt * 100;
				//if the player is above max speed, decrease the value
				else if (velocity.x > playMaxSpeed) velocity.x -= playDecel * dt * 100;
				else if (velocity.x < -playMaxSpeed) velocity.x += playDecel * dt * 100;
				//if player speed is close enough to max speed, set max speed to prevent jittering
				else if (velocity.x > hVal * (playMaxSpeed - playDecel) && velocity.x < hVal * (playMaxSpeed + playDecel)) velocity.x = playMaxSpeed;
		}

	}
	else
	{
		//deccelerate the player horizontally when at rest
		if (velocity.x > 0) velocity.x -= playDecel * dt * 100;
		else if (velocity.x < 0) velocity.x += playDecel * dt * 100;
		//set speed to 0 when close enough
		if (velocity.x < playDecel && velocity.x > playDecel * -1) velocity.x = 0;
	}

	//if moving vertically
	if (vVal != 0)
	{
		if ((getPosition().y < (window->getSize().y) * 3 && getPosition().y > 0) || //if the player is within the window
			(getPosition().y >= (window->getSize().y) * 3 && vVal < 0) ||//or at the bottom edge and not moving down
			(getPosition().y <= 0 && vVal > 0)) { //or at the top edge and not moving up

				//if the player is not at max speed, accellerate in the direction its moving
				if (velocity.y < playMaxSpeed && velocity.y > playMaxSpeed * -1) velocity.y += playAccel * vVal * dt * 100;
				//if the player is above max speed, decrease the value
				else if (velocity.y > playMaxSpeed) velocity.y -= playDecel * dt * 100;
				else if (velocity.y < -playMaxSpeed) velocity.y += playDecel * dt * 100;
				//if player speed is close enough to max speed, set max speed to prevent jittering
				else if (velocity.y > vVal * (playMaxSpeed - playDecel) && velocity.y < vVal * (playMaxSpeed + playDecel)) velocity.y = playMaxSpeed;
		}
	}
	else
	{
		//deccelerate the player vertically when at rest
		if (velocity.y > 0) velocity.y -= playDecel * dt * 100;
		else if (velocity.y < 0) velocity.y += playDecel * dt * 100;
		//set speed to 0 when close enough
		if (velocity.y < playDecel && velocity.y > playDecel * -1) velocity.y = 0;
	}

	//if a mouse button is pressed
	if (mVal != 0)
	{
		//if the button pressed is the right mouse button and the RMB weapon slot is not empty
		if (mVal<0 && weapons[0] != nullptr)
		{
			//if the player has not switched to this weapon
			if (activeWeapon)
			{
				//switch to RMB weapon
				activeWeapon = !activeWeapon;
				//update the weapon object
				weapons[0]->update(dt);
				//std::cout << "Weapon 0 active" << std::endl;
			}
		}
		//if the button pressed is the left mouse button and the LMB weapon slot is not empty
		else if (mVal>0 && weapons[1] != nullptr)
		{
			//if the player has not switched to this weapon
			if (!activeWeapon)
			{
				//switch to LMB weapon
				activeWeapon = !activeWeapon;
				//update the weapon object to set its position to the player's
				weapons[1]->update(dt);
				//std::cout << "Weapon 1 active" << std::endl;
			}
		}
		getWeaponFromSlot(activeWeapon)->update(dt);

		//if the weapon is not on a cooldown, use it
		if (getWeaponFromSlot(activeWeapon)->getCoolDown() <=0 && getWeaponFromSlot(activeWeapon)->getAmmo()>0) {
			getWeaponFromSlot(activeWeapon)->shoot(dt, _projectileContainer);
			//std::cout << "shoot" << std::endl;
		}
	}
}

void Player::update(float dt)
{
	move({ velocity.x * dt * 100,velocity.y * dt * 100 });
	//pointTo(sf::Mouse::getPosition(), window->getPosition());
	if (velocity.x > 0 && getScale().x != 1) setScale(1, 1);
	else if (velocity.x < 0 && getScale().x != -1) setScale(-1, 1);
	if (iTime >=0) iTime -= dt;

	//interrupt player movement if they try to go off screen
	if ((getPosition().x >= (window->getSize().x) * 3 && velocity.x > 0) ||
		(getPosition().x <= 0 && velocity.x < 0)) velocity.x = 0;

	if ((getPosition().y >= (window->getSize().y * 3) && velocity.y > 0) ||
		(getPosition().y <= 0 && velocity.y < 0)) velocity.y = 0;

	if (iTime >= 0)
	{

		if (iTime >=.9 || iTime >=.6 && iTime <=.7 || iTime >= .3 && iTime <= .4)
		{
		setFillColor(sf::Color(255, 255, 255, 100));
		}
		else
		{
			setFillColor(sf::Color(255, 255, 255, 255));
		}
		iTime -= dt;
		
	}
	
	//walk animation (player legs move slightly)
	if (velocity.x != 0 || velocity.y != 0) {
		if (getTexture() == &sprite[0]) {
			setTexture(&sprite[1]);
			timeKeeper += dt;
		}
		else if (timeKeeper >= 10) {
			setTexture(&sprite[0]);
			timeKeeper = 0;
		}
	}
	else setTexture(&sprite[0]);


}



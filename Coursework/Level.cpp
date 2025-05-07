#include "Level.h"
#include "Camera.h"
#include <vector>
#include "Player.h"

//Declared before constructor because not doing so caused errors
void Level::spawnEnemy(Player* _player)
{
	sf::Vector2f randPos;
	int playerPosX = _player->getPosition().x;
	int playerPosY = _player->getPosition().y;


	int LorR = rand() % 2;
	
	switch (LorR) {
	case 0:
		randPos.x = rand() % (playerPosX + 20) + (playerPosX + 70);
		break;
	case 1:
	default:
		randPos.x = rand() % (playerPosX - 20) + (playerPosX - 70);
		break;
	}

	int UorD = rand() % 2;

	switch(UorD) {
	case 0:
		randPos.y = rand() % (playerPosY + 20) + (playerPosY + 70);
		break;
	case 1:
	default:
		randPos.y = rand() % (playerPosY - 20) + (playerPosY - 70);
		break;
	}
	Enemy* tempEnemy = (new Enemy(randPos, audio));
	collision->addObject(tempEnemy);
	allEnemies.push_back(tempEnemy);
}



Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	window->setFramerateLimit(120);

	maxEnemies = 20;
	nextLevel = false;
	returnToMain = false;
	// initialise game objects
	
	//initialise player
	//camera = new Camera(window, &player);
	player.setInput(input);
	player.setWindow(window);
	player.setWeaponInSlot(new Shotgun(&player, 60, 30, 15, 4, 7, 110, audio), 0, window, in);
	player.setWeaponInSlot(new Sword(&player, 20, audio), 1, window, in);
	player.setAudioManager(audio);
	//player is handled in level rather than physics because it handles the weapons which 
	//could have created circular dependencies with projectiles, physics, weapons and player

	background_tex.loadFromFile("gfx/sample.png");
	background.setTexture(&background_tex);
	background.setSize(sf::Vector2f(window->getSize().x*3, window->getSize().y*3));
	background.setPosition(0, 0);
	background.setCollisionBox(0, 0, window->getSize().x * 3, window->getSize().y * 3);
	//std::cout << window->getSize().x*3 << ", " << window->getSize().y*3 << std::endl;
	
	
	camera = new Camera(window, &player, background.getCollisionBox());
	
	timeRemaning = 20;


	//UI:

	font.loadFromFile("font/arial.ttf");

	for (int x = 0;x < menuItems;x++)
	{
		menu[x] = new Button(camera, &player, x, sf::Vector2f((camera->getCenter().x - 32), (camera->getCenter().y - (300 - (x * 128)))));
		menu[x]->setInput(input);
		menu[x]->setWindow(window);
	}
	for (int x = 0;x < 7;x++)
	{
		ui[x] = new UI(camera, &player, x, sf::Vector2f((camera->getCenter().x - 32), (camera->getCenter().y - (200 - (x * 64)))), &font);
	}

	collision = new Physics(aud);
	for (int i = 0; i < maxEnemies; i++) {
		spawnEnemy(&player);
	}
	companion.setAlive(true);
	//Treats
	attackR.setWindow(window);
	companion.setWindow(window);
	collision->getVectorPointer()->push_back(&attackR);
	collision->getVectorPointer()->push_back(&player);
	collision->getVectorPointer()->push_back(&companion);
	//Mak eplayer referrable in physics so it can collide with things

	arrow.setWindow(window);
	treats.setAudioManager(audio);
	treats.randomisePOI();
	arrow.setplayer(&player);
	arrow.treat(treats);



	
}




Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isPressed(sf::Keyboard::Tab) || menu[0]->playGame())
	{
		if (isPaused)
		{
			isPaused = false;
			for (int x = 0;x < menuItems;x++)
			{
				menu[x]->setVisible(false);
			}
		}

		else
		{
			isPaused = true;
			for (int x = 0;x < menuItems;x++)
			{
				menu[x]->setVisible(true);
			}
		}
	}

	//pause menu
	if (isPaused)
	{
		for (int x = 0;x < menuItems;x++)
		{
			menu[x]->handleInput(dt);

		}
		if (menu[2]->playGame())
		{
			returnToMain = true;

		}

		return;

	}

	player.handleInput(dt,collision);


}

// Update game objects
void Level::update(float dt)
{
	if (isPaused)
	{
		for (int x = 0;x < menuItems;x++)
		{
			menu[x]->update(dt);
		}
		return;
	}

	player.getWeaponFromSlot(player.getActiveWeapon())->update(dt);

	sf::Vector2f playerPos = player.getPosition();


	int enemies = 0;
	int increment = 0;
	std::vector<GameObject*> Thanatos;
	for (GameObject* currentObject : collision->getVectorObject()) {
		if (currentObject != nullptr) {
			if (currentObject == dynamic_cast<Enemy*>(currentObject)) {
				if (currentObject->isAlive()) {
					enemies++;
					dynamic_cast<Enemy*>(currentObject)->setTargetPos(playerPos); //move to enemy update
					//currentObject->update(dt);
				}
			}
			currentObject->update(dt);
			if(!currentObject->isAlive())
			{
				Thanatos.push_back(collision->getVectorObject()[increment]);
			}
		}
		increment++;
	}



	int kill = Thanatos.size()-1;
	if (Thanatos.size()>0)
	{
		for (kill; kill >= 0; kill--)
		{
			int i = 0; //Used to get indexes of the Physics Object vector in the foreach loop
			for (GameObject* currentObject : collision->getVectorObject())
			{
				if (Thanatos[kill] == collision->getVectorObject()[i]) //Only when an object marked for death has been reached
				{
					//Erase the object from the Physics vector at position i,
					collision->getVectorPointer()->erase(collision->getVectorPointer()->begin() + i);
					i--; 
					//decrement i back to where it was before we destroyed the object
					//This prevents any objects that should be destroyed from being skipped
					if (Thanatos[kill]->getType() == GameObject::ENEMY) 
					//Using an enum tag to check for dead enemies instead of dynamic casting to the enemy class for ease
					{
						player.addScore(5); 
					}
				}
				i++;
			}
			delete Thanatos[kill]; //Delete data of dead object
			Thanatos.erase(Thanatos.begin() + kill); 
			//Remove null pointer from Thanatos to prevent errors when ovewriting it next frame
		}
	}


	//ensure an appropriate amount of enemies
	if (enemies < maxEnemies) {
		spawnEnemy(&player);
	}
	

	

	camera->update(dt);
	for (int x = 0; x < 7; x++)
	{
		ui[x]->update(dt, timeRemaning);

	}

	if (player.getHp() <= 0) {
		timeRemaning = 0;
	}

	if (timeRemaning > 0)
	{
		timeRemaning = timeRemaning - dt;
		//timer goes red and starts shaking when you're running low on time
		ui[3]->setTimer(dt , timeRemaning);
	}
	else
	{		
		//hearts start being consumed when time reaches zero
		if (player.getHp() > 0)
		{
			player.setHp(player.getHp() - 1);
			timeRemaning += 3;
			audio->playSoundbyName("TimerDamage");
		}
		else
		{
			//lose screen appears when timer reachers zero and no hearts left
			ui[6]->rect.setPosition(camera->getCenter().x, camera->getCenter().y);
			ui[6]->rect.setFillColor(sf::Color(255, 255, 255, 255));
			dead = true;
			for (int x = 0;x < menuItems;x++)
			{
				menu[x]->setVisible(true);
			}
			isPaused = true;
			audio->playSoundbyName("Death");
		}

	}


 // arrow code ------
	if (player.getCollisionBox().intersects(treats.getCollisionBox()))
	{

		treats.randomisePOI();
		player.addScore(+100);
		timeRemaning += 5;
		collected++;
		std::cout << "collected";
		
	}

	

	arrow.setPosition(playerPos);

	arrow.update(dt,&treats);
	
	ui[2]->setString("Score: " + std::to_string((player.getScore()))); //sets score counters


	//ai companion 

	companion.Update(dt);
	companion.setTargetPos(playerPos); //move to enemy update
	collision->update(dt);
	//attackR.update(dt);

	if (collected >= 10 )
	{
	
		nextLevel==true;
	}

	
}
 


// Render level
void Level::render()
{
	beginDraw();
	//window->clear(sf::Color(0,0,0));
	window->setView(*camera);
	window->draw(background);
	window->draw(treats);
	window->draw(player);
	
	//window->draw(attackR);
	if (arrow.isDrawable()) window-> draw(arrow);

	window->draw(companion);
	

	for (int i = 0; i < collision->getVectorObject().size(); i++) {
		if (collision->getVectorObject()[i] != nullptr) {
			window->draw(*collision->getVectorObject()[i]);
		}
	}

	window->draw(*player.getWeaponFromSlot(player.getActiveWeapon()));


	for (int x = 0;x < 7;x++)
	{
		if (x == 0 || (x >= 4 && x <= 6))
		{
			window->draw(ui[x]->rect);
		}
		window->draw(ui[5]->weapon);
		window->draw(ui[4]->weapon);
		window->draw(*ui[x]);

	}



	for (int x = dead;x < menuItems;x++)
	{
		window->draw(*menu[x]);
	}


	
	endDraw();
}
bool Level::Nextlevel()
{
	if (collected>=15)
	{
		return true;
	}
	return false;
}


//return to main menu
bool Level::mainMenu()
{

	if (returnToMain)
	{
			//resets all variables to defaults
			player.setPosition(1800, 200);
			player.setHp(5);
			player.setScore(0);
			player.getWeaponFromSlot(0)->setAmmo(player.getWeaponFromSlot(0)->getAmmoMax());
			player.getWeaponFromSlot(1)->setAmmo(player.getWeaponFromSlot(1)->getAmmoMax());
			timeRemaning = 30;

			isPaused = false;
			returnToMain = false;
			dead = false;
			ui[6]->rect.setFillColor(sf::Color(255, 255, 255, 0));
			spriteSheet.loadFromFile("ButtonSheet.png");

			for (int x = 0; x < collision->getVectorObject().size();x++) //kills all enemies
			{
				if (collision->getVectorPointer()->at(x)->getType() == GameObject::ENEMY)
				{
					collision->getVectorPointer()->at(x)->setTexture(&spriteSheet);
					collision->getVectorPointer()->at(x)->setAlive(false);
				}
			}

			for (int x = 0;x < menuItems;x++)//makes menu visible
			{
				menu[x]->setVisible(false);
			}
			return true;
			
	}
	return false;
}

bool Level::level2()
{

	if (nextLevel)
	{
		//resets all variables to defaults
		player.setPosition(1800, 200);
		player.setHp(5);
		player.setScore(0);
		player.getWeaponFromSlot(0)->setAmmo(player.getWeaponFromSlot(0)->getAmmoMax());
		player.getWeaponFromSlot(1)->setAmmo(player.getWeaponFromSlot(1)->getAmmoMax());
		timeRemaning = 30;
		

		
		isPaused = false;
		nextLevel = false;
		dead = false;
		ui[6]->rect.setFillColor(sf::Color(255, 255, 255, 0));
		spriteSheet.loadFromFile("ButtonSheet.png");


		for (int x = 0; x < collision->getVectorObject().size(); x++) //kills all enemies
		{
			if (collision->getVectorPointer()->at(x)->getType() == GameObject::ENEMY)
			{
				collision->getVectorPointer()->at(x)->setTexture(&spriteSheet);
				collision->getVectorPointer()->at(x)->setAlive(false);
			}
		}



	}
	return false;
	
	
}


	






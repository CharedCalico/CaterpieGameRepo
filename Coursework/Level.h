#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "ProjectileGod.h"
#include "SwordSwing.h"
#include "Button.h"
#include "Physics.h"
#include "Camera.h"
#include "Sword.h"
#include "Shotgun.h"
#include "Treats.h"
#include "Player.h"
#include "Arrow.h"
#include "AiCompanion.h"
#include"UI.h"

 


class Level : BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();
	void handleInput(float dt) override;
	void update(float dt);
	void render();
	void spawnEnemy(Player* _player);
	bool mainMenu();
	bool level2();
	bool Nextlevel();

private:
	// Default functions for rendering to the screen.
	
	// Default variables for level class.
	sf::Texture playTex;
	sf::Font font;
	sf::Texture playerSpriteSheet;
	Player player;
	Enemy enemy;
	Treats treats;
	Arrow arrow;
	AiCompanion companion;
	AttackRadius attackR;
	Physics* collision;

	std::vector<ProjectileGod*> projectiles;
	std::vector<GameObject*> allEnemies;

	const int menuItems = 3;
	Button* menu[4];
	std::vector<Enemy*> enemies;
	UI* ui[7];

	Camera* camera;	
	sf::Texture spriteSheet;

	bool isPaused = false;
	float timeRemaning;
	bool rotL =false;
	int maxEnemies;
	bool returnToMain;
	bool nextLevel;
	bool dead;
	int collected;

	//Background

	sf::Texture background_tex;
	GameObject background;
};
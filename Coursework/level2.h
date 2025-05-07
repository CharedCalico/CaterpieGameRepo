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
#include "Tree.h"
#include "AiCompanion.h"
#include"UI.h"


class level2:BaseLevel

{
public:
	level2(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~level2();


	void handleInput(float dt) override;
	void update(float dt);
	void render();
	void spawnEnemy(Player* _player);

	
private:
	
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
	Tree tree[20];

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
	bool rotL = false;
	int maxEnemies;
	bool returnToMain;
	bool nextLevel;
	bool dead;

	//Background

	sf::Texture background_tex;
	GameObject background;

};


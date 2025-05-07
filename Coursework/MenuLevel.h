#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Button.h"



class MenuLevel : BaseLevel {
public:
	MenuLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~MenuLevel();

	void handleInput(float dt) override;
	void update(float dt);
	void render();
	bool startGame();

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.

	Button* menu[4];

	//Background

	sf::Texture background_tex;
	GameObject background;
};
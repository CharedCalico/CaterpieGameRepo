#include "MenuLevel.h"

MenuLevel::MenuLevel(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	background_tex.loadFromFile("MainMenu.png");
	background.setTexture(&background_tex);
	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color::White);

	for (int x = 0;x < 2;x++)
	{
		menu[x] = new Button(x, sf::Vector2f((1400), (25 + (300 + (x * 450)))),true);
		menu[x]->setInput(input);
		menu[x]->setWindow(window);
	}
	menu[2] = new Button(3, sf::Vector2f(1400, 550), true);
	menu[2]->setInput(input);
	menu[2]->setWindow(window);
	menu[2]->htp.setPosition(hwnd->getDefaultView().getCenter());
}

MenuLevel::~MenuLevel()
{
}

void MenuLevel::handleInput(float dt)
{
	for (int x = 0; x < 3; x++)
	{
		menu[x]->handleInput(dt);
	}
	if (input->isPressed(sf::Keyboard::Escape))
	{
		menu[2]->htp.setFillColor(sf::Color::Transparent);
	}
}

void MenuLevel::update(float dt)
{
}

void MenuLevel::render()
{
	beginDraw();
	window->setView(window->getDefaultView());

	window->draw(background);
	for (int x = 0; x < 3; x++)
	{
		window->draw(*menu[x]);
	}
	window->draw(menu[2]->htp);
	endDraw();
}

bool MenuLevel::startGame()
{
	if (menu[0]->playGame())
	{
		return true;
	}
	return false;
}

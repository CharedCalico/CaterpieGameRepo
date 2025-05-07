// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Level2.h"
#include "MenuLevel.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"

void windowProcess(sf::RenderWindow* window, Input* in)
{
	// Handle window events.
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::PRESSED);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::PRESSED);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}

int main()
{
	srand(time(NULL));
	//Create the window
	sf::RenderWindow window(sf::VideoMode(3840, 2160), "CMP105_Coursework", sf::Style::Fullscreen);//originaly 1200/675


	// Initialise input and level objects.
	AudioManager audioManager;
	Input input;
	GameState gameState;
	//sets default game state
	gameState.setCurrentState(State::MENU );
	Level level(&window, &input, &gameState, &audioManager);
	MenuLevel menuLevel(&window, &input, &gameState, &audioManager);
	level2 level2(&window, &input, &gameState, &audioManager);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;
	audioManager.playMusicbyName("TitleMusic");
	// Game Loop
	while (window.isOpen())
	{
		//Process window events
		windowProcess(&window, &input);

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)

		switch (gameState.getCurrentState())
		{
		case State::MENU:
			menuLevel.handleInput(deltaTime);
			menuLevel.update(deltaTime);
			menuLevel.render();
			if (menuLevel.startGame())	//checks to leave main menu and go to Level
			{
				gameState.setCurrentState(State::LEVEL);
				audioManager.stopAllMusic();
				audioManager.playMusicbyName("GameplayMusic");
			}

			break;

		case State::LEVEL:
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();

			if (level.mainMenu())	//checks to leave to main menu from level
			{

				
				audioManager.stopAllMusic();
				audioManager.stopAllSounds();
				audioManager.playMusicbyName("TitleMusic");
			}
			if (level.Nextlevel())
			{
				gameState.setCurrentState(State::LEVEL2);
				audioManager.stopAllMusic();
				audioManager.playMusicbyName("GameplayMusic");

			}
			break;

		case State::LEVEL2:
			level2.handleInput(deltaTime);
			level2.update(deltaTime);
			level2.render();
			
			if (level.level2())	//checks to leave to level2
			{

				gameState.setCurrentState(State::MENU);
				audioManager.stopAllMusic();
				audioManager.stopAllSounds();
				audioManager.playMusicbyName("TitleMusic");
			}
		}

		

		// Update input class, handle pressed keys
		// Must be done last.
		input.update();
	}
	return 0;
}

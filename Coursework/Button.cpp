#include "Button.h"
#include <iostream>
#include "Player.h"

Button::Button(sf::View* Nview, Player* plyr, int type,sf::Vector2f og)
{
	isMouseOver = false;
	isVisible = false;
	setInput(&in);
	//loading the sprites for default and highlighted
	sprite[0].loadFromFile("ButtonSheet3.png", sf::IntRect(buttonType * 256, 0, (buttonType + 1) * 256, 128));
	sprite[1].loadFromFile("ButtonSheet3.png", sf::IntRect(buttonType * 256, 128, (buttonType + 1) * 256, 256));
	setTexture(&sprite[0]);
	float spriteWidth = sprite[0].getSize().x;
	float spriteHeight = sprite[0].getSize().y;
	buttonSize = {spriteWidth,spriteHeight};
	setSize(sf::Vector2f(spriteWidth,spriteHeight));
	setOutlineThickness(3);
	setOutlineColor(sf::Color(255, 255, 255, 0));
	setFillColor(sf::Color::Transparent);
	//sets coords of creation point, allows for offset logic in mouseOver()
	origin = og;
	setPosition(og);

	click = false;
	mainMenu = false;

	buttonType = type;

	//loads textures
	sprite[0].loadFromFile("ButtonSheet3.png", sf::IntRect(type * 256, 0, (type + 1) * 256, 128));
	sprite[1].loadFromFile("ButtonSheet3.png", sf::IntRect(type * 256, 128, (type + 1) * 256, 256));

	setTexture(&sprite[0]);

	//sets refs to player and camera
	player = plyr;
	view = Nview;


}


Button::Button(int type, sf::Vector2f og, bool mm)
{
	isMouseOver = false;
	isVisible = true;
	mainMenu = mm;
	setInput(&in);
	sprite[0].loadFromFile("ButtonSheet3.png", sf::IntRect(buttonType * 256, buttonType * 128, (buttonType + 1) * 256, (buttonType + 1) * 128));
	sprite[1].loadFromFile("ButtonSheet3.png", sf::IntRect(buttonType * 256, buttonType * 256, (buttonType + 1) * 256, (buttonType + 1) * 256));
	setTexture(&sprite[0]);
	float spriteWidth = sprite[0].getSize().x;
	float spriteHeight = sprite[0].getSize().y;
	setSize(sf::Vector2f(spriteWidth, spriteHeight));
	setOutlineThickness(3);
	setOutlineColor(sf::Color(255, 255, 255, 0));
	setScale(1.5, 1.5);
	buttonSize = { spriteWidth,spriteHeight};
	origin = og;
	click = false;

	//sets the type of button, all button logic is done through a switch/case statement, this typing governs that
	buttonType = type;
	setPosition(og);


	sprite[0].loadFromFile("ButtonSheet3.png", sf::IntRect(type * 256, 0, (type + 1) * 256, 128));
	sprite[1].loadFromFile("ButtonSheet3.png", sf::IntRect(type * 256, 128, (type + 1) * 256, 256));

	setTexture(&sprite[0]);

	//altered for main menu
	setOrigin(getSize().x / 2, getSize().y / 2);
	setScale(2, 2);
	setCollisionBox(0, 0, getSize().x, getSize().y);

	// rectagleShape for control screen
	htp.setFillColor(sf::Color::Transparent);
	htpText.loadFromFile("Tutorals.png");
	htp.setTexture(&htpText);

	htp.setSize(sf::Vector2f( htp.getTexture()->getSize().x,htp.getTexture()->getSize().y ));
	htp.setOrigin(htp.getSize().x / 2, htp.getSize().y / 2);
}


Button::~Button()
{
	std::cout << "button destroyed";
}

//getter for type of button
int Button::getButtonType()
{
	return buttonType;
}

//returns true when specific buttons are pressed, play and main menu
bool Button::playGame()
{
	if (click)
	{
		click = false;
		return true;
	}
	else
	{

		return false;
	}
}



//function for setting visibility of buttons, called in level whenever the game is paused/unpaused
void Button::setVisible(bool vis)
{
	if (vis)
	{
		setFillColor(sf::Color(255, 255, 255, 255));
		isVisible = true;
	}
	else
	{
		setFillColor(sf::Color(255, 255, 255, 0));
		setOutlineColor(sf::Color(255, 255, 255, 0));
		isVisible = false;
	}
}

//for detecting if mouse is over the button, in main menu. Seperate due to the camera causing an offset of mouse coords in level
bool Button::getMouseOverMain()
{
	//vectr of mouse pos, casted to cmap coords to acocunt for resizing
	sf::Vector2i mouse = { input->getMouseX(), input->getMouseY() };
	mouse = { static_cast<int>(window->mapPixelToCoords(mouse).x),static_cast<int>(window->mapPixelToCoords(mouse).y) };

	// if we're in the main menu and the mouse is over the button
	if (Collision::checkBoundingBox(this, mouse))
	{
		isMouseOver = true;
		//set the texture to the highlighted version
		setTexture(&sprite[1]);
		return true;
	}

	else
	{
		//set the texture back to normal
		setTexture(&sprite[0]);
		isMouseOver = false;
		return false;
	}
}

//returns true when mouse is over the button while in Level.cpp
bool Button::getMouseOver()
{
	if (isVisible)
	{
		if (
			// bounding box check adjusting for camera view
			(input->getMouseX() - buttonSize.x/4 > (getPosition().x - (view->getCenter().x - origin.x))) &&
			(input->getMouseX() - buttonSize.x /4< ((getPosition().x + buttonSize.x) - (view->getCenter().x - origin.x))) &&
			(input->getMouseY() > (getPosition().y - ((view->getCenter().y - (300 - (buttonType * 128))) - origin.y))) &&
			(input->getMouseY() < ((getPosition().y + buttonSize.y) - ((view->getCenter().y - (300 - (buttonType * 128))) - origin.y))))
		{
			isMouseOver = true;
			//set texture to higlighted
			setTexture(&sprite[1]);

			return true;
		}
		else
		{
			//set texture to normal
			setTexture(&sprite[0]);
			isMouseOver = false;
			return false;
		}
	}
	else return false;
}


void Button::update(float dt)
{

	if (!mainMenu)
	{
		//sets position to centre of view
		setPosition((view->getCenter().x - (buttonSize.x / 2)), (view->getCenter().y - (300 - (buttonType * 128))));

	}
}


void Button::handleInput(float dt)
{
	//checks if visible, only possible in level when paused, true by default in menulevel
	if (isVisible)
	{
		//checks if main menu for mouseOver logic
		if (mainMenu)
		{
			getMouseOverMain();
		}
		else 
		{
			getMouseOver();
		}



		//click detected while mouse is over button
		if ((input->isLeftMousePressed()) && (isMouseOver == true))
		{
			//checks the type of button when it is clicked 
			switch (buttonType)
			{

			case PLAY:		//play Game, either from the pause or main menu
				click = true;

				break;

			case CLOSE:		//closes window
				window->close();
				break;


			case MAIN:		//returns to main Menu
				click = true;
				break;

			case HTP:		//(How To Play, displays controls
				htp.setFillColor(sf::Color::White);
				break;

			}
		}

	}

	
}

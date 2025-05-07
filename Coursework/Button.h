#pragma once

#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "player.h"
class Button : public GameObject
{

public:
	//constructor for Buttons in Level, for when the player and camera is present
	Button(sf::View* Nview, Player* plyr, int type,sf::Vector2f og);
	//constructor overload for MainMenu, since there is no player or camera present
	Button(int type, sf::Vector2f og, bool mainMenu);

	~Button();


	void handleInput(float dt);
	bool getMouseOver();
	bool getMouseOverMain();
	//void setButtonType(int type);
	int getButtonType();
	bool playGame();
	void setVisible(bool vis);
	void update(float dt);
	sf::RectangleShape htp;


private:

	bool mainMenu;
	//bool toggle;
	bool click;
	bool isVisible;
	bool isMouseOver;
	sf::Vector2f buttonSize;
	Input in;
	sf::Vector2f mousPos;
	sf::Texture sprite[2];
	enum typeEnum {PLAY,CLOSE,MAIN,HTP,MUTE};
	int buttonType;
	sf::Vector2f origin;
	//sf::RenderWindow* window;
	Player* player;
	sf::View* view;
	sf::Texture htpText;
protected:

};


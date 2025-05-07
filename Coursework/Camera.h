#pragma once
#include "SFML/Graphics.hpp"
#include "Framework/GameObject.h"
#include "Framework/Input.h"

class Camera : public sf::View
{
public:
	//constructor 
	Camera(sf::RenderWindow* wndw, GameObject* GameObject = nullptr, sf::FloatRect Bounds = sf::FloatRect());
	Camera(sf::RenderWindow* wndw, class Input* inpt = nullptr);
	//update the camera every frame
	void update(float dt);

	void setBounds(sf::FloatRect NewBounds) { mBoundingBox = NewBounds; }
	sf::FloatRect getBounds() { return mBoundingBox; }
	sf::FloatRect getCollider() { return sf::FloatRect(getCenter().x, getCenter().y, getCenter().x + (getSize().x), getCenter().y + (getSize().y)); }
private:
	//window to render
	sf::RenderWindow* mWindow;
	//object to follow
	GameObject* mGameObject;
	
	Input* input;
	//maximuim distance the camera can be from the object
	float maxDist;

	sf::FloatRect mBoundingBox;
};


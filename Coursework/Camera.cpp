#include "Camera.h"
#include <cmath>
#include <iostream>
#include "Framework/Input.h"

float Dist(sf::Vector2f Obj1, sf::Vector2f Obj2)
{
	return sqrt(pow(Obj2.x - Obj1.x, 2) + pow(Obj2.y - Obj1.y, 2));
}
//constructor for the camera
Camera::Camera(sf::RenderWindow* wndw, GameObject* gameObject, sf::FloatRect Bounds)
	:sf::View(wndw->getView())
	, mBoundingBox(Bounds)
{
	mWindow = wndw;
	mGameObject = gameObject;
	maxDist = sqrt(pow(mGameObject->getSize().x, 2) + pow(mGameObject->getSize().x, 2)) * 2.f; // maximium distance the object can go before camera speeds up by a factor of 5;
	input = nullptr;
}
Camera::Camera(sf::RenderWindow* wndw, Input* inpt)
	:sf::View(wndw->getView())
{
	mWindow = wndw;
	mGameObject = nullptr;
	maxDist = 0.0f;

	input = inpt;

}
//update the camera
void Camera::update(float dt)
{
	sf::Vector2f movement;
	if (input == nullptr)
	{ 
		//move the camera by the distance between the object and the camera 
		movement = mGameObject->getPosition() - getCenter();
		//stop the camera when it reaches the center of the object
		if (fabs(movement.x) < 0.1f)
		{
			movement.x = 0.f;
		}

		if (fabs(movement.y) < 0.1f)
		{
			movement.y = 0.f;
		}

		//Stop the object from escape;
		if (Dist(mGameObject->getPosition(), getCenter()) > maxDist)
		{
			movement = movement * 5.f;
		}
		//BoundCheck
		sf::Vector2f NewPos = getCenter() + (movement * dt);
		if (mBoundingBox.left >= NewPos.x - (getSize().x / 2.f) - 10 && !mBoundingBox.contains(sf::Vector2f(NewPos.x - (getSize().x / 2.f), NewPos.y)))
		{
			movement.x = 0.f;
		}

		if (mBoundingBox.top >= NewPos.y - (getSize().y / 2.f) - 10 && !mBoundingBox.contains(sf::Vector2f(NewPos.x, NewPos.y - (getSize().y / 2.f))))
		{
			movement.y = 0.f;
		}

		if (mBoundingBox.left + mBoundingBox.width <= NewPos.x + (getSize().x / 2.f) && !mBoundingBox.contains(sf::Vector2f(NewPos.x + (getSize().x / 2.f), NewPos.y)))
		{
			movement.x = 0.f;
		}
		if (mBoundingBox.top + mBoundingBox.height <= NewPos.y + (getSize().y / 2.f) && !mBoundingBox.contains(sf::Vector2f(NewPos.x, NewPos.y + (getSize().y / 2.f))))
		{
			movement.y = 0.f;
		}
		//move the camera
		move(movement * dt); 
	}
	else
	{
		if (input->isKeyDown(sf::Keyboard::Up))
		{
			movement.y -= 500.0f;
		}
		
		if (input->isKeyDown(sf::Keyboard::Down))
		{
			movement.y += 500.0f;
		}
		  
		if (input->isKeyDown(sf::Keyboard::Left))
		{
			movement.x -= 500.0f;
		}

		if (input->isKeyDown(sf::Keyboard::Right))
		{
			movement.x += 500.0f;
		}

		move(movement * dt);
	}
}

#include "GameObject.h"

GameObject::GameObject()
{
	input = nullptr;
}

GameObject::~GameObject()
{

}

// Override this function to provide input handling for the derived class
void GameObject::handleInput(float dt)
{
}

// override this function to provide functionality
void GameObject::update(float dt)
{
}

// Sets the velocity of the sprite
void GameObject::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}
void GameObject::setVelocity(float vx, float vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

// get sprite velocity
sf::Vector2f GameObject::getVelocity()
{
	return velocity;
}

//pointAt is a vector2i because this was mainly built to make things point at the mouse and mouse coordinates use Vector2i
//I tried to make it work with Vector2f, it simply did not, I apologise
float GameObject::findAngleTo(sf::Vector2i pointAt, sf::Vector2f myPos, bool degOrRad)
{
	pointAt.x += (window->getView().getCenter().x - window->getSize().x / 2);
	pointAt.y +=  (window->getView().getCenter().y - window->getSize().y / 2);
	sf::Vector2i socatoa = sf::Vector2i(pointAt.x - myPos.x, pointAt.y - myPos.y);
	float theta = getRotation();
	if (socatoa.x != 0)
	{
		if (degOrRad) theta = atan2(socatoa.y, socatoa.x) * (180 / (2 * acos(0.0))); //Return degrees
		else theta = atan2(socatoa.y, socatoa.x); //Return radians
		//There were points where both degress and radians were needed from this function, so it can do both
	}
	return theta;
}

float GameObject::pointTo(sf::Vector2i mPos, sf::Vector2i winPos)
{
	mPos.x -= winPos.x;
	mPos.y -= winPos.y;
	float theta = findAngleTo(mPos, getPosition(), true);
	setRotation(theta);
	return theta;
}

// Returns collision box + position, giving the collision box in the correct position
sf::FloatRect GameObject::getCollisionBox() {
	
	return sf::FloatRect(collisionBox.left + getPosition().x - getOrigin().x, collisionBox.top + getPosition().y - getOrigin().y, collisionBox.width, collisionBox.height); 
}

// Reponse function, what the sprite does based on collision
// Colliding object is passed in for information
// e.g. compare sprite positions to determine new velocity direction.
// e.g. checking sprite type (world, enemy, bullet etc) so response is based on that.
void GameObject::collisionResponse(GameObject * collider)
{
}

void GameObject::setType(Type _type)
{
	type = _type;
}

GameObject::Type GameObject::getType()
{
	return type;
}

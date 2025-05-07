#include "Arrow.h"
#include "Framework/VectorHelper.h"



Arrow::Arrow()
{
	if (!Arrow_sprite.loadFromFile("gfx/Arrow.png")) std::cout << "Error loading ball sprite";
	setTexture(&Arrow_sprite);
	setSize({ 50,50 });
	setOrigin(-25, 25);

	
}

Arrow::~Arrow()
{
}

void Arrow::treat(Treats a)
{
	treats = a;
}

void Arrow::update(float dt, Treats* treats)
{

	// check distance from arrow to object
		// hint: Collision::magnitude
	// set drawable is distance > minimum_view_distance

	sf::Vector2f vectorTotreat = (treats->getPosition() - getPosition());
	/*if (VectorHelper::magnitude(vectorTotreat) > MINIMUM_VIEW_DISTANCE)
		drawable = true;
	else
		drawable = false;*/

	drawable = (VectorHelper::magnitude(vectorTotreat) > MINIMUM_VIEW_DISTANCE) ? true : false;

	sf::Vector2i mid_treat = sf::Vector2i(treats->getPosition().x, treats->getPosition().y);
	mid_treat += static_cast<sf::Vector2i>(treats->getSize()) / 2;

	float rot = atan2(vectorTotreat.y, vectorTotreat.x) * (180/3.14);
	//std::cout << "rotation: " << rot << " // position of treats = " << treats->getPosition().x << "," << treats->getPosition().y << "\n";
	setRotation(rot);
}

void Arrow::setplayer(Player* b)
{
	player = b;
}


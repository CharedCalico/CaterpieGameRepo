#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"
#include "Physics.h"
class Tree : public GameObject
{

public:

	Tree();
	~Tree();
	// use point to
	
	private:
	int maxTrees;
	sf::Texture Tree_sprite;
	AudioManager* audio;
	


};


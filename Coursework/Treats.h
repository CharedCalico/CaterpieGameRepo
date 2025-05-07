#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"

class Treats : public GameObject
{

public:

	Treats();
	~Treats();


	// use point to

	int randomisePOI();
	int PoiSpot;
	void setAudioManager(AudioManager* _aud);
private:
	sf::Texture POI_sprite;
	AudioManager* audio;
};


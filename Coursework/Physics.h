#pragma once

#include "Framework/AudioManager.h"
#include "Framework/GameObject.h"

class Physics
{
protected:
	std::vector<GameObject*> colliders;
	AudioManager* audio;
public:
	Physics(AudioManager* _aud);
	void addObject(GameObject* _object);
	std::vector<GameObject*> getVectorObject();
	void update(int dt);
	std::vector<GameObject*>* getVectorPointer();

};


#include "Physics.h"

Physics::Physics(AudioManager* _aud)
{
	colliders.push_back(nullptr);
	audio = _aud;
}

void Physics::addObject(GameObject* _object)
{
	colliders.push_back(_object);
}

std::vector<GameObject*> Physics::getVectorObject()
{
	return colliders;
}

void Physics::update(int dt)
{
	for (int x = 0; x < std::size(colliders); x++) {
		for (int y = 0; y < std::size(colliders); y++) {
			if (colliders[x] == nullptr) {
				colliders.erase(colliders.begin() + x);
			}
			else if (colliders[y] == nullptr && x != y) {
				colliders.erase(colliders.begin() + y);
			}
			
			else if (colliders[x]->getCollisionBox().intersects(colliders[y]->getCollisionBox())) {
				if (x != y) {
					colliders[x]->collisionResponse(colliders[y]);
					colliders[y]->collisionResponse(colliders[x]);
				}
			}
			
		}
		//colliders[x]->update(dt);
	}

}

std::vector<GameObject*>* Physics::getVectorPointer()
{
	return &colliders;
}



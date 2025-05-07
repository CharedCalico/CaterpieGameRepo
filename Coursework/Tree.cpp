#include "Tree.h"

Tree::Tree()
{
	setType(TREE);
	if (!Tree_sprite.loadFromFile("gfx/Tree.png")) std::cout << "Error loading ball sprite";
	setTexture(&Tree_sprite);
	setSize({ 100,150 });
	setCollisionBox(0, 0, 50, 90);
	maxTrees = 10;


}
Tree::~Tree()
{
	
}


#ifndef LEAF_H
#define LEAF_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Tile.h"
#include <iostream> 
#include <math.h>

class Leaf: public Tile{
public:
	Leaf(sf::Vector2<int> loc, sf::Sprite sprite, int);
	void SetCollision(bool);
	void Update(sf::Time);
	bool Burning() const;
private:
	bool mCollision, mBurned;
	float mElapsedTime;
};
#endif
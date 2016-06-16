#ifndef BATTERY_H
#define BATTERY_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Tile.h"
#include <iostream> 
#include <math.h>

class Battery: public Tile{
public:
	Battery(sf::Vector2<int> loc, sf::Sprite sprite, int);
	void SetCollision(bool);
	void Update(sf::Time);
	bool Charged() const;
private:
	bool mCollision, mCharged;
	float mElapsedTime;
};
#endif


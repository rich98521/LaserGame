#ifndef DIAMOND_H
#define DIAMOND_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Tile.h" 

class Diamond : public Tile
{
private:
	int mRadius;
public:
	Diamond(sf::Vector2<int>, sf::Sprite, int tileSize);
	int Radius() const { return mRadius; }
};


#endif
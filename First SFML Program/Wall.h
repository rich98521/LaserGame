#ifndef WALL_H
#define WALL_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Tile.h"

class Wall: public Tile{
public:
	Wall(sf::Vector2<int> loc, sf::Sprite sprite, int);
private:
};
#endif


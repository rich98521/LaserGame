#include "stdafx.h" 
#include "Wall.h"

Wall::Wall(sf::Vector2<int> loc, sf::Sprite sprite, int tileSize): Tile(loc, 0, sprite, tileSize)
{
	mIsFloor = false;

}
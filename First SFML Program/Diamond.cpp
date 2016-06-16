#include "stdafx.h" 
#include "Diamond.h"

Diamond::Diamond(sf::Vector2<int> loc, sf::Sprite sprite, int tileSize)
	: Tile(loc, 0, sprite, tileSize), mRadius(10)
{
	mIsFloor = false;
	mCanSelect = true;
}
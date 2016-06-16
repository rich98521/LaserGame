#include "stdafx.h" 
#include "LaserEmitter.h"

LaserEmitter::LaserEmitter(sf::Vector2<int> loc, float ang, sf::Sprite sprite, int tileSize, sf::Sprite laserSprite, sf::Vector2<int> bounds)
	: Tile(loc, ang, sprite, tileSize), mLaser(loc, ang, tileSize, laserSprite, bounds)
{
	SetAngle(ang);
	mIsFloor = false;
}

void LaserEmitter::SetAngle(float ang)
{
    float roundTo = acos(0);
    mAngle = ((int)(((ang + (roundTo / 2.0f)) / roundTo)) * roundTo);
}


void LaserEmitter::Draw(sf::RenderWindow* window, sf::Vector2<int> offset)
{
	Tile::Draw(window, offset);
	mLaser.Draw(window, offset);
}

void LaserEmitter::CalculateLaserPath(std::vector<std::vector<Tile*>> tiles)
{
	mLaser.CalculatePath(tiles);
}
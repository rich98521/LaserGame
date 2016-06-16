#include "stdafx.h" 
#include "Tile.h"

Tile::Tile(sf::Vector2<int> loc, float ang, sf::Sprite sprite, int tileSize)
	:mLocation(loc), mAngle(ang), mTileSize(tileSize), mIsFloor(true), mSprite(sprite), mCanSelect(false)
{
	mSprite.setOrigin(tileSize/2,tileSize/2);
	mSprite.setRotation(mAngle);
	mSprite.setPosition(mLocation.x, mLocation.y);
}

Tile::Tile(sf::Vector2<int> loc, float ang, int tileSize)
	:mLocation(loc), mAngle(ang), mTileSize(tileSize), mIsFloor(true), mCanSelect(false)
{
}

sf::Vector2<int> Tile::Location() const
{
	return mLocation;
}

float Tile::GetAngle() const
{
	return mAngle;
}

bool Tile::IsFloor() const
{
	return mIsFloor;
}

bool Tile::CanSelect() const
{
	return mCanSelect;
}

void Tile::SetAngle(float ang)
{
	float angDeg = (ang/acos(0)) * 90;
	mAngle = ang;
	mSprite.setRotation(angDeg);
}

void Tile::Draw(sf::RenderWindow* window, sf::Vector2<int> offset)
{
	sf::Transform t;
	t.translate(sf::Vector2f(offset));
	sf::RenderStates rs(t);
	window->draw(mSprite, rs);
}

void Tile::SetLocation(sf::Vector2<int> pos)
{
	mLocation = pos + sf::Vector2<int>(mTileSize/2,mTileSize/2);
	mSprite.setPosition(mLocation.x, mLocation.y);
}
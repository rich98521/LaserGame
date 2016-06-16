#include "stdafx.h" 
#include "Portal.h"

Portal::Portal(sf::Vector2<int> loc, float ang, sf::Sprite sprite, int tileSize)
	:Tile(loc, 0, sprite, tileSize)
{
	mEdges.resize(2);
	mIsFloor = false;
	mCanSelect = true;
	SetAngle(ang);
}

void Portal::SetAngle(float ang)
{
	Tile::SetAngle(ang);
	UpdateEdges();
}

void Portal::SetOutPortal(Portal * p)
{
	mOutPort = p;
}

void Portal::UpdateEdges()
{
	const sf::Vector2<float> arr[] = {sf::Vector2<float>(mLocation.x  + cos(mAngle) *( mTileSize/2), mLocation.y  + sin(mAngle) * (mTileSize/2)), 
		sf::Vector2<float>(mLocation.x + cos(mAngle + acos(0)*2) * (mTileSize/2), mLocation.y + sin(mAngle + acos(0)*2) * (mTileSize/2)) };
	mEdges = std::vector<sf::Vector2<float>>(arr, arr + sizeof(arr) / sizeof(arr[0]) );
}

void Portal::SetLocation(sf::Vector2<int> pos)
{
	Tile::SetLocation(pos);
	UpdateEdges();
}

std::vector<sf::Vector2<float>> Portal::Edges()
{
	return mEdges;
}
Portal* Portal::outPort()
{
	return mOutPort;
}
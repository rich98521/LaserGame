#include "stdafx.h" 
#include "Battery.h"

Battery::Battery(sf::Vector2<int> loc, sf::Sprite sprite, int tileSize): Tile(loc, 0, sprite, tileSize)
{
	mIsFloor = false;
	mElapsedTime = 0;
	mCollision = false;
}

void Battery::SetCollision(bool c)
{
	mCollision = c;
}

void Battery::Update(sf::Time t)
{
	if(mCollision)
	{
		mElapsedTime += t.asSeconds();
		if((int)mElapsedTime<3)
		{
			mSprite.setTextureRect(sf::IntRect(32*(int)mElapsedTime,0,32,32));
			mCharged = false;
		}
		else
		{
			mSprite.setTextureRect(sf::IntRect(96,0,32,32));
			mCharged = true;
		}
	}
	else
	{
		mSprite.setTextureRect(sf::IntRect(0,0,32,32));
		mElapsedTime = 0;
		mCharged = false;
	}
}


bool Battery::Charged() const
{
	return mCharged;
}
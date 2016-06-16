#include "stdafx.h" 
#include "Leaf.h"

Leaf::Leaf(sf::Vector2<int> loc, sf::Sprite sprite, int tileSize): Tile(loc, 0, sprite, tileSize)
{
	mIsFloor = false;
	mElapsedTime = 0;
	mCollision = false;
}

void Leaf::SetCollision(bool c)
{
	mCollision = c;
}

void Leaf::Update(sf::Time t)
{
	if(mCollision)
	{
		mElapsedTime += t.asSeconds()*10;
		if((int)mElapsedTime<5)
		{
			mSprite.setTextureRect(sf::IntRect(32*(int)mElapsedTime,0,32,32));
			mBurned = false;
		}
		else
		{
			mSprite.setTextureRect(sf::IntRect(96,0,32,32));
			//mBurned = true;
			mElapsedTime = 1;
		}
	}
	else
	{
		mSprite.setTextureRect(sf::IntRect(0,0,32,32));
		mElapsedTime = 0;
		mBurned = false;
	}
}


bool Leaf::Burning() const
{
	return mBurned;
}
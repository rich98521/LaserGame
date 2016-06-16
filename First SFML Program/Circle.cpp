#include "stdafx.h" 
#include "Circle.h"
#include <math.h>

Circle::Circle()
	:mPos((rand() % 760),(rand() % 560)), mVel((rand() % 100)-50,(rand() % 100)-50), mCircle(20)
{
	float l = sqrt(mVel.x*mVel.x + mVel.y*mVel.y);
	mVel = sf::Vector2f((mVel.x/l)*4,(mVel.y/l)*4);
	mCircle.setFillColor(sf::Color(rand()%255,rand()%255,rand()%255));
}

void Circle::Draw(sf::RenderWindow* window)
{
	mPos += mVel;
	if(mPos.x<0)
	{
		mPos.x = 0;
		mVel.x = -mVel.x;
	}
	else if(mPos.x>760)
	{
		mPos.x = 760;
		mVel.x = -mVel.x;
	}
	if(mPos.y<0)
	{
		mPos.y = 0;
		mVel.y = -mVel.y;
	}
	else if(mPos.y>560)
	{
		mPos.y = 760;
		mVel.y = -mVel.y;
	}
	mCircle.setPosition(mPos);
	(*window).draw(mCircle);
}
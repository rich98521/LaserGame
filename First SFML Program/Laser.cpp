#include "stdafx.h" 
#define _USE_MATH_DEFINES
#include <math.h>
#include "Laser.h"

Laser::Laser(sf::Vector2<int> location, float angle, int tileSize, sf::Sprite sprite,sf::Vector2<int> bounds)
	:mTileSize(tileSize), mSprite(sprite), mBounds(bounds)
{
	mLaserPaths.push_back(std::vector<sf::Vector2<int>>());
	mLaserPaths[0].push_back(location);
	startAngle = angle;
	startPos = location;
}

bool IsIntersecting(sf::Vector2<float> a, sf::Vector2<float> b, sf::Vector2<float> c, sf::Vector2<float> d)
{
    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

void Laser::CalculatePath(std::vector<std::vector<Tile*>> tiles)
{
	mLaserPaths.clear();
	mLaserPaths.push_back(std::vector<sf::Vector2<int>>());
	mLaserPaths[0].push_back(startPos);
	portalSkips.clear();
    std::vector<float> angles;
	angles.push_back(startAngle);
	sf::Vector2<float> lastLoc = sf::Vector2<float>(startPos);
	sf::Vector2<int> hitIndex;
	int maxLength = 2000, length = 0;
	for(int i = 0; i < mLaserPaths.size(); i++)
	{
		portalSkips.push_back(std::list<int>());
		bool hitBlock = true;
		sf::Vector2<float> dir = sf::Vector2<float>(cos(angles[i]), sin(angles[i]));
		bool pathEnd = false;
		unsigned int maxPoints = 400;
		lastLoc = sf::Vector2<float>(mLaserPaths[i][0]);
		while (!pathEnd)
		{
			length++;
			sf::Vector2f loc = sf::Vector2f(lastLoc.x + dir.x * 2, lastLoc.y + dir.y * 2);
			int xIndex = (int)(loc.x / mTileSize), yIndex = (int)(loc.y / mTileSize);
			if (xIndex >= 0 && xIndex < mBounds.x && yIndex >= 0 && yIndex < mBounds.y && length < maxLength && mLaserPaths[i].size() < maxPoints)
			{
				if(!(hitBlock && hitIndex == sf::Vector2<int>(xIndex,yIndex)))
				{
					Mirror* mir = dynamic_cast<Mirror*>((tiles.at(xIndex).at(yIndex)));
					if(mir != 0)
					{
						if (IsIntersecting(loc, lastLoc, mir->Edges()[0], mir->Edges()[1]))
						{
							hitBlock = true;
							hitIndex == sf::Vector2<int>(xIndex,yIndex);
							mLaserPaths[i].push_back(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y));
							angles[i] = (float)(mir->GetAngle() * 2 - (angles[i]));
							dir = sf::Vector2<float>(cos(angles[i]), sin(angles[i]));
							loc = lastLoc;
						}
					}
					Battery* bat = dynamic_cast<Battery*>((tiles.at(xIndex).at(yIndex)));
					if(bat != 0)
					{
						hitBlock = true;
						hitIndex == sf::Vector2<int>(xIndex,yIndex);
						mLaserPaths[i].push_back(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y));
						bat->SetCollision(true);
						pathEnd = true;
					}
					Wall* wall = dynamic_cast<Wall*>((tiles.at(xIndex).at(yIndex)));
					if(wall != 0)
					{
						hitBlock = true;
						hitIndex == sf::Vector2<int>(xIndex,yIndex);
						mLaserPaths[i].push_back(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y));
						pathEnd = true;
					}
					Leaf* lea = dynamic_cast<Leaf*>((tiles.at(xIndex).at(yIndex)));
					if(lea != 0)
					{
						lea->SetCollision(true);
					}
					Portal* port = dynamic_cast<Portal*>((tiles.at(xIndex).at(yIndex)));
					if(port != 0)
					{
						if (IsIntersecting(loc, lastLoc, port->Edges()[0], port->Edges()[1]))
						{
							hitBlock = true;
							hitIndex == sf::Vector2<int>(xIndex,yIndex);
							portalSkips[i].push_back(mLaserPaths[i].size());
							mLaserPaths[i].push_back(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y));
							sf::Transform t;
							t.rotate((port->outPort()->GetAngle()-port->GetAngle())/M_PI*180+180);
							sf::Vector2<int> p = port->outPort()->Location()+sf::Vector2<int>(t.transformPoint(sf::Vector2f(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y) - port->Location() )));
							mLaserPaths[i].push_back(p);	
							angles[i] = angles[i]-port->GetAngle() + port->outPort()->GetAngle()+M_PI;
							dir = sf::Vector2<float>(cos(angles[i]), sin(angles[i]));
							loc = sf::Vector2f(p)+dir*2.0f;
						}
					}
					Diamond* dia = dynamic_cast<Diamond*>((tiles.at(xIndex).at(yIndex)));
					if(dia != 0)
					{
						sf::Vector2f diff = loc - sf::Vector2f(dia->Location());
						if(sqrt(diff.x*diff.x+diff.y+diff.y)<dia->Radius())
						{
							hitBlock = true;
							hitIndex = sf::Vector2<int>(xIndex,yIndex);
							mLaserPaths[i].push_back(sf::Vector2<int>((int)lastLoc.x, (int)lastLoc.y));
							mLaserPaths[i].push_back(dia->Location());
							float angle = M_PI+atan2(mLaserPaths[i][mLaserPaths[i].size()-3].y-dia->Location().y,mLaserPaths[i][mLaserPaths[i].size()-3].x-dia->Location().x);
							float ang = angle-M_PI/3;
							angles[i] = angle+M_PI/3;
							dir = sf::Vector2<float>(cos(angles[i]), sin(angles[i]));
							angles.push_back(ang);
							loc = sf::Vector2f(dia->Location());
							mLaserPaths.push_back(std::vector<sf::Vector2<int>>());
							mLaserPaths[mLaserPaths.size()-1].push_back(dia->Location());
						}
					}
				}
			}
			else
			{
				mLaserPaths[i].push_back(sf::Vector2<int>( std::max((int)loc.x,0), std::max((int)loc.y,0)));
				pathEnd = true;
			}
			lastLoc = loc;
		}
	}
}

void Laser::Draw(sf::RenderWindow* window, sf::Vector2<int> offset)
{
	sf::Transform t;
	t.translate(sf::Vector2f(offset));
	sf::RenderStates rs(t);
	mSprite.setOrigin(0,2);
	for(int i = 0;i<mLaserPaths.size();i++)
		for(int i2 = 0;i2<mLaserPaths[i].size()-1;i2++)
		{
			if(std::find(portalSkips[i].begin(),portalSkips[i].end(),i2)==portalSkips[i].end())
			{
				sf::Vector2f start = sf::Vector2f(mLaserPaths[i].at(i2));
				sf::Vector2f end = sf::Vector2f(mLaserPaths[i].at(i2+1));
				sf::Vector2f diff = start-end;
				sf::Vector2f temp;
				float distance = sqrt(diff.x*diff.x+diff.y*diff.y);
				sf::Vector2f dir = -diff / distance;
				for(int i2 = 0; i2 < distance; i2+=1)
				{
					temp = start + sf::Vector2f(dir.x*i2,dir.y*i2);
					mSprite.setPosition(temp.x, temp.y);
					float ang = atan2(dir.y,dir.x);
					mSprite.setRotation((ang/M_PI)*180);
					window->draw(mSprite, rs);
				}
			}
		}
}
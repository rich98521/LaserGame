#ifndef LASER_H
#define LASER_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Tile.h"
#include "Tile.h"
#include "Mirror.h"
#include "Battery.h"
#include "Wall.h"
#include "Portal.h"
#include "Diamond.h"
#include "Leaf.h"
#include <list>

class Laser
{
private: 
	std::vector<std::vector<sf::Vector2<int>>> mLaserPaths;
	float startAngle;
	sf::Vector2<int> startPos;
	int mTileSize;
	sf::Sprite mSprite;
	std::vector<std::list<int>> portalSkips;
	sf::Vector2<int> mBounds;
public:
	Laser(sf::Vector2<int>, float, int, sf::Sprite,sf::Vector2<int> );
	Laser(){};
	void Draw(sf::RenderWindow*, sf::Vector2<int>);
	void CalculatePath(std::vector<std::vector<Tile*>>);
};



#endif
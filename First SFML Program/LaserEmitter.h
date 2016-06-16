#ifndef LASEREMITTER_H
#define LASEREMITTER_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Tile.h" 
#include "Laser.h"

class LaserEmitter : public Tile
{
private:
	Laser mLaser;
public:
	LaserEmitter(sf::Vector2<int>, float, sf::Sprite, int tileSize, sf::Sprite,sf::Vector2<int>);
	LaserEmitter(){};
	void SetAngle(float ang);
	void Draw(sf::RenderWindow*, sf::Vector2<int>);
	void CalculateLaserPath(std::vector<std::vector<Tile*>>);
};


#endif
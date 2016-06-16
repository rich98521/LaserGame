#ifndef MIRROR_H
#define MIRROR_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Tile.h" 

class Mirror : public Tile
{
private:
	std::vector<sf::Vector2<float>> mEdges;
	void UpdateEdges();
public:
	Mirror(sf::Vector2<int>, float, sf::Sprite, int tileSize);
	Mirror(){};
	void SetAngle(float);
	std::vector<sf::Vector2<float>> Edges();
	void SetLocation(sf::Vector2<int>);
};


#endif
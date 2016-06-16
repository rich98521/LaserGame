#ifndef PORTAL_H
#define PORTAL_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include "Tile.h"

class Portal: public Tile{
public:
	Portal(){};
	Portal(sf::Vector2<int>, float, sf::Sprite, int);
	Portal* outPort();
	void SetAngle(float);
	std::vector<sf::Vector2<float>> Edges();
	void SetLocation(sf::Vector2<int>);
	void SetOutPortal(Portal*);
private:
	Portal* mOutPort;
	std::vector<sf::Vector2<float>> mEdges;
	void UpdateEdges();
};
#endif


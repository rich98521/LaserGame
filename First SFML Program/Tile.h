#ifndef TILE_H
#define TILE_H
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

class Tile
{
protected:
	sf::Vector2<int> mLocation;
    float mAngle;
	sf::RectangleShape rec;
	sf::Sprite mSprite;
	int mTileSize;
	bool mIsFloor, mCanSelect;
public:
	Tile(sf::Vector2<int>, float, sf::Sprite, int);
	Tile(sf::Vector2<int>, float, int);
	Tile(){};
	sf::Vector2<int> Location() const;
	virtual void SetLocation(sf::Vector2<int>);
	virtual float GetAngle() const;
	bool IsFloor() const;
	bool CanSelect() const;
	virtual void SetAngle(float);
	virtual void Draw(sf::RenderWindow*, sf::Vector2<int>);
};

#endif
#ifndef define "CIRCLE_H"
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

class Circle
{
private:
	sf::Vector2f mPos;
	sf::Vector2f mVel;
	sf::CircleShape mCircle;
public:
	Circle();
	void Draw(sf::RenderWindow*);
};


#endif // !define "CIRCLE_H"

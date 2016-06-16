
//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#include <iostream> 
#include <math.h>
#include "Tile.h"
#include "Mirror.h"
#include "LaserEmitter.h"
#include "Laser.h"
#include "Level.h"
#include "Battery.h"

int main() 
{ 
	int width = 1000, height = 900;
	sf::RenderWindow window(sf::VideoMode(width, height, 32), "Laser Game");
	sf::Clock clock;
	srand(time(NULL));
	window.setFramerateLimit(60);
	int tileSize = 32;
	Level map(tileSize, width, height);
	bool rotating = false, lDown = false, gamePlaying = true;
	float startAngle, mirrorStartAngle;
	sf::Font font;
	sf::Text text;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	text.setFont(font);
	string winString = "You Win!\nClick To Continue";
	text.setString(winString);
	text.setColor(sf::Color(0,0,0));
	text.setStyle(sf::Text::Underlined| sf::Text::Italic | sf::Text::Bold);
	text.setCharacterSize(50);
	text.setPosition((width-text.getLocalBounds().width)/2,(height-text.getLocalBounds().height)/2);
	while (window.isOpen()) 
	{ 
		sf::Event Event;
		while (window.pollEvent(Event)) 
		{ 
			if (Event.type == sf::Event::Closed) 
				window.close(); 

			if ((Event.type == sf::Event::KeyPressed) ) 
				if(Event.key.code == sf::Keyboard::Escape)
					window.close(); 
				else if (Event.key.code == sf::Keyboard::Right)
					map.NextLevel();
				else if (Event.key.code == sf::Keyboard::Left)
					map.PrevLevel();
			if ((Event.type == sf::Event::MouseButtonPressed))
			{
				sf::Vector2<int> mousePos(Event.mouseButton.x-map.Offset().x ,Event.mouseButton.y-map.Offset().y);
				if(mousePos.x>0&&mousePos.y>0&&mousePos.x<map.Width()*tileSize&&mousePos.y<map.Height()*tileSize)
					if(map.LevelCompleted())
					{
						map.NextLevel();
					}
					else if(Event.mouseButton.button == sf::Mouse::Button::Left)
					{
						lDown = true;

						if(map.TileSelected())
						{
							sf::Vector2<int> diff = ((map.SelectedTile()*tileSize)+sf::Vector2<int>(tileSize/2,tileSize/2))-sf::Vector2<int>(mousePos.x,mousePos.y);
							float distance = sqrt(diff.x*diff.x + diff.y*diff.y);
							if(distance < 55 && distance > 40)
							{
								Tile* t = map.GetTiles().at(map.SelectedTile().x).at(map.SelectedTile().y);
								rotating = true;
								mirrorStartAngle = map.GetTiles().at(map.SelectedTile().x).at(map.SelectedTile().y)->GetAngle();
								startAngle = (float)atan2(mousePos.y - (t->Location().y), mousePos.x - (t->Location().x));
							}
						}
						if(!rotating)
							map.Select(mousePos.x,mousePos.y);
					}
			}
			if ((Event.type == sf::Event::MouseButtonReleased))
			{
				if(Event.mouseButton.button == sf::Mouse::Button::Left)
				{
					map.UpdateRotateCircle((map.SelectedTile()*tileSize).x,(map.SelectedTile()*tileSize).y);
					lDown = false;
					rotating = false;
				}
			}
			if ((Event.type == sf::Event::MouseMoved))
			{
				sf::Vector2<int> mousePos(Event.mouseMove.x-map.Offset().x, Event.mouseMove.y-map.Offset().y);
				if(lDown)
				{
					Tile* t = map.GetTiles().at(map.SelectedTile().x).at(map.SelectedTile().y);
					if(rotating)
					{
						map.UpdateRotateCircle(mousePos.x,mousePos.y);
						float ang = (float)atan2(mousePos.y - (t->Location().y), mousePos.x - (t->Location().x));
						t->SetAngle(mirrorStartAngle+ang-startAngle);
					}
					else if(mousePos.x>0&&mousePos.y>0&&mousePos.x<map.Width()*tileSize&&mousePos.y<map.Height()*tileSize)
					{
						int xIndex = (mousePos.x/tileSize), yIndex = (mousePos.y/tileSize);
						map.SwapSelected(xIndex, yIndex);
					}
				}
			}
		}
		map.Update(clock.getElapsedTime());
		clock.restart();
		window.clear();
		map.Draw(&window);
		if(map.LevelCompleted())
			window.draw(text);
		window.display(); 
	}
	return EXIT_SUCCESS; 
}
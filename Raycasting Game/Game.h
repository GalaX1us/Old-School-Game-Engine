#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	float deltaTime;
	sf::Clock dtClock;

	void initWindow();
public:
	Game();             //constructor
	virtual ~Game();    //destructor

	void run();
	void updateDt();
	void updateSFMLEvents();
	void update();
	void render();
};


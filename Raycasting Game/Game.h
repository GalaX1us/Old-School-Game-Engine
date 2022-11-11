#pragma once
#include"Global.h"
#include"Map.h"
#include"Player.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	Map* map;
	Player* player;

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


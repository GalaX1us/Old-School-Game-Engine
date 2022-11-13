#pragma once
#include"Global.h"
#include"Map.h"

class Player
{
private:
	sf::Vector2f coords;
	float angle;
	
	
	sf::Vector2i direction;
	sf::Vector2f velocity;

	float walkSpeed;
	float runSpeed;

	float acceleration;
	float movementSpeed;
	float rotationSpeed;


	void movement(Map* map, float dTime);
	void checkWallCollision(float dx, float dy, Map* map);
public:
	Player();             //constructor

	void update(Map* map, float dTime);
	void render(sf::RenderTarget* target);
};


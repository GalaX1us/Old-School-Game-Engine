#pragma once
#include"Global.h"
#include"Map.h"

class Player
{
private:
	sf::Vector2f coords;
	sf::Vector2f direction;
	sf::Vector2f cameraPlane;
	sf::Vector2f velocity;

	float walkSpeed;
	float runSpeed;

	float acceleration;
	float movementSpeed;
	float rotationSpeed;


	void movement(Map& map, float dTime);
	void checkWallCollision(float dx, float dy, Map& map);
public:
	Player();

	sf::Vector2f getCoords();
	sf::Vector2f getDirection();
	sf::Vector2f getCameraPlane();
	void update(Map& map, float dTime);
	void render(sf::RenderTarget* target);
};


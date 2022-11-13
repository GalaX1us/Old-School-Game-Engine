#include "Player.h"
#include<math.h>
#include<iostream>

Player::Player()
{
	this->coords = { 1.5f,5.0f };
	this->angle = -1.57079632679f;
	this->direction = {0, 0};
	this->velocity = {0.0f, 0.0f};

	this->movementSpeed = 0.0f;
	this->walkSpeed = 2.5f;
	this->runSpeed = 4.5f;

	this->rotationSpeed = 2.5f;
	this->acceleration = 7.0f;
}

void Player::update(Map* map, float dTime)
{
	this->movement(map, dTime);
}

void Player::render(sf::RenderTarget* target)
{
	sf::CircleShape player(20);
	player.setFillColor(sf::Color::Green);
	player.setOrigin(player.getRadius(), player.getRadius());
	player.setPosition(this->coords.x* 100.0f, this->coords.y * 100.0f);
	target->draw(player);
}

void Player::checkWallCollision(float dx, float dy, Map* map)
{
	if (!map->isWall(static_cast<int>(this->coords.x + dx), static_cast<int>(this->coords.y))) {
		this->coords.x += dx;
	}
	if (!map->isWall(static_cast<int>(this->coords.x), static_cast<int>(this->coords.y + dy))) {
		this->coords.y += dy;
	}

}

void Player::movement(Map* map, float dTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->direction = { static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) - static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::D)),
							static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) - static_cast<int>(sf::Keyboard::isKeyPressed(sf::Keyboard::S))};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			this->movementSpeed = this->runSpeed;
		}
		else{
			this->movementSpeed = this->walkSpeed;
		}
	}
	else {
		this->movementSpeed = 0;
	}
	
	int nbKeys = abs(this->direction.x) + abs(this->direction.y);

	this->velocity = {	std::lerp(this->velocity.x, this->movementSpeed*this->direction.x, dTime * this->acceleration),
						std::lerp(this->velocity.y, this->movementSpeed*this->direction.y, dTime * this->acceleration)};

	float dx = (this->velocity.x * dTime * sin(this->angle)) + (this->velocity.y * dTime * cos(this->angle));
	float dy = (this->velocity.x * dTime * -cos(this->angle)) + (this->velocity.y * dTime * sin(this->angle));

	
	if (nbKeys == 2) { dx /= sqrt2; dy /= sqrt2; }
	
	this->checkWallCollision(dx, dy, map);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->angle -= rotationSpeed * dTime;
		this->angle = fmod(this->angle, tau);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->angle += rotationSpeed * dTime;
		this->angle = fmod(this->angle, tau);
	}
}

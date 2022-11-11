#include "Player.h"
#include<math.h>

Player::Player()
{
	this->coords = { 1.5f,5.0f };
	this->angle = -1.57079632679f;
	this->movementSpeed = 3.0f;
	this->rotationSpeed = 2.5f;
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
	if (map->isWall(static_cast<int>(this->coords.x + dx), static_cast<int>(this->coords.y))) {
		this->coords.x += dx;
	}
	if (map->isWall(static_cast<int>(this->coords.x), static_cast<int>(this->coords.y + dy))) {
		this->coords.y += dy;
	}

}

void Player::movement(Map* map, float dTime)
{

	float speed = this->movementSpeed * dTime;

	float dx = 0.0f;
	float dy = 0.0f;

	float cos_speed = speed * cos(this->angle);
	float sin_speed = speed * sin(this->angle);

	int nbKeys = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		nbKeys++;
		dx += cos_speed;
		dy += sin_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		nbKeys++;
		dx += sin_speed;
		dy += -cos_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		nbKeys++;
		dx += -cos_speed;
		dy += -sin_speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		nbKeys++;
		dx += -sin_speed;
		dy += cos_speed;
	}

	if (nbKeys == 2) { dx /= sqrt2;dy /= sqrt2; }
	if (nbKeys) { this->checkWallCollision(dx, dy, map); }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->angle -= rotationSpeed * dTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->angle += rotationSpeed * dTime;
	}

	this->angle = fmod(this->angle, tau);
}

#include "Game.h"
#include "Global.h"

Game::Game()
{
	this->initWindow();
	this->window->setFramerateLimit(144);
	this->map = new Map();
	this->player = new Player();
}

Game::~Game()
{
	delete this->window;
	delete this->map;
	delete this->player;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blank Screen", sf::Style::Close);
}

void Game::updateDt()
{
	this->deltaTime = this->dtClock.restart().asSeconds();
}


void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	this->updateDt();
	this->window->setTitle(std::to_string(this->deltaTime));
	this->updateSFMLEvents();
	this->player->update(this->map, this->deltaTime);
}

void Game::render()
{
	this->window->clear(sf::Color(0, 0, 0));

	//draw all the stuff
	this->map->render(this->window);
	this->player->render(this->window);

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}


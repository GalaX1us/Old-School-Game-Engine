#include "Game.h"

Game::Game()
{
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Blank Screen", sf::Style::Close);
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
	this->updateSFMLEvents();
}

void Game::render()
{
	this->window->clear();

	//draw all the stuff

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


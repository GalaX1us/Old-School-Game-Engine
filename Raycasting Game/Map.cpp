#include "Map.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>


Map::Map()
{
    this->initMap();
    this->getMap();
}

Map::~Map()
{
}

bool Map::isWall(int x, int y)
{
    return this->world_map.find(std::make_pair(x, y)) == this->world_map.end();
}

void Map::initMap()
{
    this->miniMap = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
}

void Map::getMap()
{
    for (size_t i = 0; i < MAP_HEIGHT; i++)
    {
        for (size_t j = 0; j < MAP_WIDTH; j++)
        {
            int value = this->miniMap[i][j];
            if (value)
            {
                this->world_map[std::make_pair(j, i)] = value;
            }
        }
    }
}

void Map::render(sf::RenderTarget* target)
{
    for (const auto& [key, value] : this->world_map) {
        sf::RectangleShape tile(sf::Vector2f(100.0f, 100.0f));
        tile.setPosition(key.first*100.0f, key.second*100.0f);
        target->draw(tile);

    }
}

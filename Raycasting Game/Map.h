#pragma once

#include <vector>
#include "Global.h"
#include <unordered_map>

class Map
{
private:
    std::vector<std::vector<int>> miniMap;
	std::map<std::pair<int,int>, int> world_map;

	void initMap();
	void getMap();
public:
	Map();             //constructor
	virtual ~Map();    //destructor

	bool isWall(int x, int y);
	int getTile(int x, int y);

	void update();
	void render(sf::RenderTarget* target);
};


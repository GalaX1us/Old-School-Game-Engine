#pragma once
#include"Global.h"
#include"Map.h"
#include "Player.h"

class RayCasting
{
private:
	int nbRays;
public:
	RayCasting();
	void castRays(Player& player, Map& map, sf::RenderTarget* target);
};


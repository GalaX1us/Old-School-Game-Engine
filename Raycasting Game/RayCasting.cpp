#include "RayCasting.h"

RayCasting::RayCasting()
{
	this->nbRays = NBRAYS;
}

void RayCasting::castRays(Player& player, Map& map, sf::RenderTarget* target)
{
    for (int x = 0; x < this->nbRays; x++)
    {
        //calculate ray position and direction
        float cameraX = 2 * x / (float)this->nbRays - 1; //x-coordinate in camera space
        sf::Vector2f rayDir = { player.getDirection().x + player.getCameraPlane().x * cameraX, player.getDirection().y + player.getCameraPlane().y * cameraX};
        
        //which box of the map we're in
        sf::Vector2i mapCoords = { int(player.getCoords().x), int(player.getCoords().y) };
   
        //length of ray from current position to next x or y-side
        sf::Vector2f sideDist;

        sf::Vector2f deltaDist = { (rayDir.x == 0) ? 1e30f : std::abs(1 / rayDir.x), (rayDir.y == 0) ? 1e30f : std::abs(1 / rayDir.y) };

        float perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        sf::Vector2i step;

        bool hit = false; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        //calculate step and initial sideDist
        if (rayDir.x < 0)
        {
            step.x = -1;
            sideDist.x = (player.getCoords().x - mapCoords.x) * deltaDist.x;
        }
        else
        {
            step.x = 1;
            sideDist.x = (mapCoords.x + 1.0f - player.getCoords().x) * deltaDist.x;
        }
        if (rayDir.y < 0)
        {
            step.y = -1;
            sideDist.y = (player.getCoords().y - mapCoords.y) * deltaDist.y;
        }
        else
        {
            step.y = 1;
            sideDist.y = (mapCoords.y + 1.0f - player.getCoords().y) * deltaDist.y;
        }
        //perform DDA
        while (!hit)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDist.x < sideDist.y)
            {
                sideDist.x += deltaDist.x;
                mapCoords.x += step.x;
                side = 0;
            }
            else
            {
                sideDist.y += deltaDist.y;
                mapCoords.y += step.y;
                side = 1;
            }
            //Check if ray has hit a wall
            if (map.isWall(mapCoords.x, mapCoords.y)) hit = true;
        }
        
        if (side == 0)  perpWallDist = (sideDist.x - deltaDist.x);
        else            perpWallDist = (sideDist.y - deltaDist.y);

        //Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        //choose wall color
        sf::Color color;
        switch (map.getTile(mapCoords.x, mapCoords.y))
        {
        case 1:  color = sf::Color(10,105,188,255);    break; //red
        case 2:  color = sf::Color::Green;  break; //green
        case 3:  color = sf::Color::Red;   break; //blue
        case 4:  color = sf::Color::White;  break; //white
        default: color = sf::Color::White; break; //yellow
        }

        //give x and y sides different brightness
        if (side == 1) { color.a /= 2; }

        sf::RectangleShape rectangle(sf::Vector2f(2.0f, (float)lineHeight));
        rectangle.setFillColor(color);
        rectangle.setPosition(sf::Vector2f(2.0f * x, (float)drawStart));
        target->draw(rectangle);
    }
}

#include "endScreens.h"

EndScreens::EndScreens()
{
	createEndScreens();
}

void EndScreens::createEndScreens()
{
	blackWins.path = assetsPath.concatenate("images\\blackwins.png");
	blackWins.texture.loadFromFile(blackWins.path);
	blackWins.sprite.setTexture(blackWins.texture);
	blackWins.sprite.setPosition(sf::Vector2f(200, 300));

	whiteWins.path = assetsPath.concatenate("images\\whitewins.png");
	whiteWins.texture.loadFromFile(whiteWins.path);
	whiteWins.sprite.setTexture(whiteWins.texture);
	whiteWins.sprite.setPosition(sf::Vector2f(200, 300));

	draw.path = assetsPath.concatenate("images\\draw.png");
	draw.texture.loadFromFile(draw.path);
	draw.sprite.setTexture(draw.texture);
	draw.sprite.setPosition(sf::Vector2f(200, 300));
}
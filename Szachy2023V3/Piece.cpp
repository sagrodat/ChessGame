#include "Piece.h"


Piece::Piece(bool color, int type, int x, int y, sf::Sprite sprite)
{
	this->color = color;
	this->type = type;
	sprite.setPosition(sf::Vector2f(x, y));
	this->setStablePosition(sf::Vector2f(x, y));
	this->sprite = sprite;
	this->isPickedUp = 0;
	this->isPlaying = 1;
}

sf::Vector2f Piece::getPosition()
{
	return sprite.getPosition();
}
field_t Piece::getPosAsField()
{
	sf::Vector2f pos = sprite.getPosition();
	return field_t{ (int)(pos.y / 100), (int)(pos.x / 100) };
}
field_t Piece::getStablePositionAsField()
{
	field_t field;
	return field_t{ (int)((*this).stablePosition.y / 100), (int)((*this).stablePosition.x / 100) };
}

void Piece::setPosition(sf::Vector2f newPos)
{
	sprite.setPosition(newPos);
}
void Piece::setPosition(field_t field)
{
	sprite.setPosition(sf::Vector2f(field.col * 100, field.row * 100));
}
void Piece::setStablePosition(sf::Vector2f newPos)
{
	(*this).stablePosition.x = newPos.x;
	(*this).stablePosition.y = newPos.y;
}
void Piece::setStablePosition(field_t field)
{
	(*this).stablePosition.x = field.col * 100;
	(*this).stablePosition.y = field.row * 100;
}

sf::Sprite Piece::getSpriteCopy()
{
	sf::Sprite copy;
	copy = (*this).sprite;
	copy.setScale(sf::Vector2f(1, 1));
	return copy;

}

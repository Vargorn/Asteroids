#include "Enemy.h"


Enemy::Enemy(sf::Texture *texture, float posX, float posY)
{
	this->points = rand() % 10 + 1;
	this->shape.setRadius(static_cast <float>((this->points * 6)));
	this->shape.setPointCount(rand() % 58 + 3);
	this->shape.setTexture(texture);
	this->shape.setPosition(posX, posY);
	this->damage = this->points;
	this->speedX = static_cast<float>(rand() % 11 - 5);
	this->speedY = static_cast<float>(this->points + 2);
}

Enemy::Enemy(sf::Texture * texture, float posX, float posY, unsigned int points)
{
	this->points = points / 2;
	this->shape.setRadius(static_cast <float>((this->points * 6)));
	this->shape.setPointCount(rand() % 58 + 3);
	this->shape.setTexture(texture);
	this->shape.setPosition(posX, posY);
	this->damage = this->points/2;
	this->speedX = static_cast<float>(rand() % 11 - 5)/2;
	this->speedY = static_cast<float>(this->points + 2)/2;
}

Enemy::~Enemy()
{
}

const sf::Vector2f Enemy::getPosition() const
{
	return this->shape.getPosition();
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int & Enemy::getDamage() const
{
	return this->damage;
}

const unsigned int & Enemy::getPoints() const
{
	return this->points;
}

void Enemy::update()
{
	this->shape.move(this->speedX, this->speedY);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

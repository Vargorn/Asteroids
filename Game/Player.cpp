#include "Player.h"

void Player::initSpriteAndTexture()
{
	if (!this->texture.loadFromFile("Data/SpaceShip.png")) {
		std::cout << "Faied to load data";
	}
	
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(0.2f, 0.2f);

}

Player::Player()
{
	this->speed = 8.f;
	this->attackCooldownMax = 30;
	this->attackCooldown = this->attackCooldownMax;
	this->initSpriteAndTexture();
	this->healthMax = 100;
	this->health = this->healthMax;
}

Player::~Player()
{
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const int & Player::getHp() const 
{
	return this->health;
}

const int & Player::getHpMax() const
{
	return this->healthMax;
}

void Player::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Player::setHp(const int & hp)
{
	this->health = hp;
	if (this->health < 0) {
		this->health = 0;
	}
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->speed * dirX, this->speed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 1.f;
	}
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

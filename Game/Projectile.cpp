#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::Projectile(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float speed)
{
	this->sprite.setTexture(*texture);
	this->sprite.setScale(0.2f, 0.2f);
	this->sprite.setPosition(posX, posY);
	this->dir.x = dirX;
	this->dir.y = dirY;
	this->speed = speed;
}

Projectile::~Projectile()
{
}

const sf::FloatRect Projectile::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Projectile::update()
{
	this->sprite.move(this->dir * this->speed);
}

void Projectile::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

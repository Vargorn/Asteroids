#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Projectile
{
private:
	sf::Sprite sprite;
	sf::Vector2f dir;
	float speed;

public:
	Projectile();
	Projectile(sf::Texture *texture, float posX, float posY, float dirX, float dirY, float speed);
	~Projectile();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};


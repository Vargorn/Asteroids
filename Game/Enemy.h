#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Enemy
{
private:
	sf::CircleShape shape;
	unsigned int points;
	int damage;
	float speedX;
	float speedY;
public:
	Enemy(sf::Texture *texture, float posX, float posY);
	Enemy(sf::Texture *texture, float posX, float posY, unsigned int points);
	~Enemy();

	const sf::Vector2f getPosition() const;
	const sf::FloatRect getBounds() const;

	const int& getDamage() const;
	const unsigned int& getPoints() const;

	void update();
	void render(sf::RenderTarget* target);
};


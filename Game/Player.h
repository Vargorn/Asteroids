#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	float attackCooldown;
	float attackCooldownMax;
	int health;
	int healthMax;

	void initSpriteAndTexture();
public:
	Player();
	~Player();

	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPosition() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void setPosition(float posX, float posY);
	void setHp(const int& hp);

	void move(const float dirX, const float dirY);
	const bool canAttack();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};


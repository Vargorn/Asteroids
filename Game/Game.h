#pragma once
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include<map>
#include<vector>
#include<sstream>

/*
	Game engine class
	wrapper class
*/

class Game
{
private:
	//variables
	//window
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event event;

	sf::SoundBuffer shot_bf;
	sf::Sound shot_sn;

	sf::SoundBuffer boom_bf;
	sf::Sound boom_sn;

	sf::SoundBuffer damage_bf;
	sf::Sound damage_sn;

	sf::SoundBuffer game_over_bf;
	sf::Sound game_over_sn;

	sf::SoundBuffer its_over_bf;
	sf::Sound its_over_sn;

	sf::Music ambient;

	std::map<std::string, sf::Texture*> textures;
	std::vector<Projectile*> projectiles;

	Player *player;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBack;

	std::vector<Enemy*> enemies;
	Enemy *enemy;
	float spawnTimer;
	float spawnTimerMax;
	unsigned int points;

	sf::Font font;
	sf::Text text;
	sf::Text gameOverText;

	sf::Texture background_t;
	sf::RectangleShape background;

	//private functions
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initVariables();
public:
	//constructors and destructors
	Game();
	~Game();
	//accessors
	const bool getWindowIsOpen() const;
	//functions
	void pollEvents();
	void updateText();
	void updateCollision();
	void updatePlayer();
	void updateProjectiles();
	void updateEnemies();
	void update();
	void renderText();
	void render();
};


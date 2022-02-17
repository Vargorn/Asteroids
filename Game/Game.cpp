#include "Game.h"
void Game::initPlayer()
{
	this->player = new Player();
}
void Game::initEnemies()
{
	this->spawnTimerMax = 20.f;
	this->spawnTimer = spawnTimerMax;
}
void Game::initVariables()
{
	this->shot_bf.loadFromFile("Data/SpaceLaser.wav");
	this->shot_sn.setBuffer(this->shot_bf);
	this->shot_sn.setVolume(4);

	this->boom_bf.loadFromFile("Data/Boom.wav");
	this->boom_sn.setBuffer(this->boom_bf);
	this->boom_sn.setVolume(20);

	this->damage_bf.loadFromFile("Data/Damage.wav");
	this->damage_sn.setBuffer(this->damage_bf);
	this->damage_sn.setVolume(20);

	this->game_over_bf.loadFromFile("Data/GameOver.wav");
	this->game_over_sn.setBuffer(this->game_over_bf);
	this->game_over_sn.setVolume(100);

	this->its_over_bf.loadFromFile("Data/ItsOver.wav");
	this->its_over_sn.setBuffer(this->its_over_bf);
	this->its_over_sn.setVolume(100);

	this->ambient.openFromFile("Data/Ambient.wav");
	this->ambient.play();

	this->font.loadFromFile("Data/IdealGothicBold.otf");
	this->text.setFont(font);
	this->text.setCharacterSize(22);
	this->text.setFillColor(sf::Color::Blue);
	this->text.setPosition(600, 20);

	this->gameOverText.setFont(font);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("GAME OVER!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f
	);

	this->healthBar.setSize(sf::Vector2f(300.f, 20.f));
	this->healthBar.setFillColor(sf::Color::Green);
	this->healthBar.setPosition(sf::Vector2f(20.f, 20.f));
	this->healthBarBack = this->healthBar;
	this->healthBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	this->background_t.loadFromFile("Data/Space.png");
	this->background.setTexture(&this->background_t);
	this->background.setSize(sf::Vector2f(800, 600));

	this->points = 0;


}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game1");
	this->window->setFramerateLimit(60);
}
void Game::initTextures()
{
	this->textures["PROJECTILE"] = new sf::Texture;
	this->textures["PROJECTILE"]->loadFromFile("Data/Projectile.png");
	this->textures["METEOR"] = new sf::Texture;
	this->textures["METEOR"]->loadFromFile("Data/Meteor.png");
	this->textures["GAMEOVER"] = new sf::Texture;
	this->textures["GAMEOVER"]->loadFromFile("Data/GameOver.jpg");
}
// consructors destructors
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->player;
	delete this->window;
	for (auto &i : this->textures) {
		delete i.second;
	}
	for (auto *i : this->projectiles) {
		delete i;
	}
	for (auto *i : this->enemies) {
		delete i;
	}
}
// accessors
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}
//functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event)) { // reaction to events
		switch (this->event.type)
		{
		case sf::Event::Closed: this->window->close(); break;
		case sf::Event::KeyPressed: {
			if (this->event.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
		}

	}
}
void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->text.setString(ss.str());
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->healthBar.setSize(sf::Vector2f(this->healthBarBack.getSize().x * hpPercent, this->healthBar.getSize().y));
}
void Game::updateCollision()
{
	if (this->player->getBounds().left <= 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	} // Left
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	} //Right
	if (this->player->getBounds().top <= 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0.f);
	} // Top
	else if (this->player->getBounds().top + this->player->getBounds().height >= window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}
void Game::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player->move(0, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player->move(0.f, 1.f);
	}
	if (this->player->getHp() > 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack() || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
			this->projectiles.push_back(new Projectile(this->textures["PROJECTILE"], this->player->getPosition().x + this->player->getBounds().width / 2, this->player->getPosition().y, 0.f, -1.f, 5.f));
			shot_sn.play();
		}
	}
}
void Game::updateProjectiles()
{
	unsigned int counter = 0;
	for (auto *projectile : this->projectiles)
	{
		projectile->update();
		if (projectile->getBounds().top + projectile->getBounds().height < 0.f) {
			delete this->projectiles.at(counter);
			this->projectiles.erase(this->projectiles.begin() + counter);
			--counter;
		}
		++counter;
	}

}
void Game::updateEnemies()
{

	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(this->textures["METEOR"], rand() % this->window->getSize().x -50.f, -100.f));
		this->spawnTimer = 0.f;

	}
	for (size_t i = 0; i < this->enemies.size(); ++i)
	{
		this->enemies[i]->update();
		bool enemyRemoved = false;
		for (size_t k = 0; k < this->projectiles.size() && enemyRemoved == false; k++)
		{
			if (this->projectiles[k]->getBounds().intersects(this->enemies[i]->getBounds())) {
				this->points += this->enemies[i]->getPoints();
				this->boom_sn.play();
				delete this->projectiles[k];
				this->projectiles.erase(this->projectiles.begin() + k);
				if (this->enemies[i]->getPoints() >= 2) {
					this->enemies.push_back(new Enemy(this->textures["METEOR"], this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y, this->enemies[i]->getPoints()));
					this->enemies.push_back(new Enemy(this->textures["METEOR"], this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y, this->enemies[i]->getPoints()));
				}
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				enemyRemoved = true;
			}
		}
		if (enemyRemoved == false) {
			if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
			}
			else if (this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
				this->player->setHp(this->player->getHp() - this->enemies[i]->getDamage());
				damage_sn.play();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);
				if (this->player->getHp() == 0) {
					this->ambient.pause();
					this->game_over_sn.play();
					this->its_over_sn.play();
					this->background.setTexture(this->textures["GAMEOVER"]);
				}
			}
		}
		
	}
	this->spawnTimer += 1.f;
}
void Game::update()
{
	this->pollEvents();
	this->updateText();
	this->updatePlayer();
	this->player->update();
	this->updateCollision();
	this->updateProjectiles();
	this->updateEnemies();
}

void Game::renderText()
{
	this->window->draw(this->text);
}
void Game::render()
{
	this->window->clear();

	//draw stuff
	if (this->player->getHp() > 0) {
		this->window->draw(this->background);
		this->window->draw(this->healthBarBack);
		this->window->draw(this->healthBar);
		this->renderText();
		this->player->render(*this->window);

		for (auto *projectile : this->projectiles)
		{
			projectile->render(this->window);
		}
		for (auto *enemy : this->enemies)
		{
			enemy->render(this->window);
		}
	}
	else {
		this->window->draw(this->background);
		window->draw(this->gameOverText);
	}

	this->window->display();
}


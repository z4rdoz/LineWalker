#include "MainMenu.h"
#include "Game.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Show(sf::RenderWindow& window) {
	sf::Text title, inst;
	sf::Font font;
	if (!font.loadFromFile("assets/fonts/pixel.ttf")) {
		//error
	}

	title.setFont(font); 
	inst.setFont(font);

	title.setString("LINEWALKER");
	inst.setString("PRESS ANY KEY TO START");

	title.setCharacterSize(100);
	inst.setCharacterSize(50);

	title.setColor(sf::Color::White);
	inst.setColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	inst.setStyle(sf::Text::Bold);

	title.setPosition(Game::SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, 200);
	inst.setPosition(Game::SCREEN_WIDTH / 2 - inst.getLocalBounds().width / 2, 400);

	window.draw(title);
	window.draw(inst);

	window.display();
}

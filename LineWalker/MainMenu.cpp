#include "MainMenu.h"
#include "Game.h"


MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::Show(sf::RenderWindow& window) {
	sf::Text title, instructions;
	sf::Font font;
	if (!font.loadFromFile("assets/fonts/pixel.ttf")) {
		//error
	}

	title.setFont(font); 
	instructions.setFont(font);

	title.setString("LINEWALKER");
	instructions.setString("PRESS ANY KEY TO START");

	title.setCharacterSize(100);
	instructions.setCharacterSize(50);

	title.setColor(sf::Color::White);
	instructions.setColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	instructions.setStyle(sf::Text::Bold);

	title.setPosition(Game::SCREEN_WIDTH / 2 - title.getLocalBounds().width / 2, 200);
	instructions.setPosition(Game::SCREEN_WIDTH / 2 - instructions.getLocalBounds().width / 2, 400);

	window.draw(title);
	window.draw(instructions);

	window.display();
}

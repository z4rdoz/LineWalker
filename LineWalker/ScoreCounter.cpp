#include "ScoreCounter.h"



ScoreCounter::ScoreCounter()
{
	Score = 0;
	HighScore = 0;
}


ScoreCounter::~ScoreCounter()
{
}

void ScoreCounter::DrawInGame(sf::RenderWindow & window) {
	sf::Text scoreText;
	sf::Font font;
	if (!font.loadFromFile("assets/fonts/pixel.ttf")) {
		//error
	}

	scoreText.setFont(font);

	scoreText.setString("Score: " + std::to_string(Score));

	scoreText.setCharacterSize(24);

	scoreText.setColor(sf::Color::White);

	scoreText.setPosition(10,10);

	window.draw(scoreText);
}
void ScoreCounter::Increment() {
	Score += 10;
}
void ScoreCounter::Reset() {
	Score = 0;
}
int ScoreCounter::Score, ScoreCounter::HighScore;

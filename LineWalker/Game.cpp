#include "Game.h"
#include "MainMenu.h"
#include "Player.h"
#include "Particle.h"
#include "GameMaster.h"

void Game::Start(void)
{
	LineWidth = 26;
	LineTop = SCREEN_HEIGHT / 2 - LineWidth / 2;
	LineBottom = LineTop + LineWidth;

	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "LINEWALKER");
	_gameState = Game::ShowingMenu;

	_mainWindow.clear(sf::Color(0, 0, 0));

	while (!isExiting())
	{
		gameLoop();
	}

	_mainWindow.close();
}

void Game::AddObject(std::string name, VisibleGameObject * obj)
{
	_gameObjectManager.Add(name, obj);
}

bool Game::isExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::gameLoop()
{		
	float timeDelta = _mainClock.restart().asSeconds();	

	switch (_gameState)
	{
		case Game::ShowingMenu:
			showMenu();
			break;
		case Game::Test:
			//particleTest
		{
			///* Load a font and setup some texty-type stuff */
			//sf::Font font;
			//if (!font.loadFromFile("assets/fonts/pixel.ttf"))
			//	return;
			//sf::Text text("", font, 12);
			//text.setPosition(
			//	static_cast<float>(_mainWindow.getSize().x) * 0.01f,
			//	static_cast<float>(_mainWindow.getSize().y) * 0.01f);

			///* Create the particle system and give it some fuel */
			//ParticleSystem particleSystem(_mainWindow.getSize());
			//particleSystem.fuel(10);
			//particleSystem.setShape(Shape::SQUARE);
			///* Let's make a clock and junk for timing stuff! */
			//sf::Clock timer;
			//const sf::Uint32 UPDATE_STEP = 20;
			//const sf::Uint32 MAX_UPDATE_SKIP = 5;
			//sf::Uint32 nextUpdate = timer.getElapsedTime().asMilliseconds();

			///* For some fancy mouse stuff */
			//sf::Vector2f lastMousePos(static_cast<sf::Vector2f>(_mainWindow.getSize()));

			///* Main Loop */
			//while (_mainWindow.isOpen())
			//{
			//	/* Init a skipped frame counter */
			//	sf::Uint32 frameSkips = 0;

			//	/* Throttle handlers and update to every UPDATE_STEP */
			//	while (timer.getElapsedTime().asMilliseconds() > nextUpdate
			//		&& frameSkips < MAX_UPDATE_SKIP)
			//	{
			//		/* Handle events */
			//		sf::Event event;
			//		while (_mainWindow.pollEvent(event))
			//		{
			//			switch (event.type)
			//			{
			//				case(sf::Event::Closed) :
			//				{
			//					_mainWindow.close();
			//					break;
			//				}
			//				case(sf::Event::KeyPressed) :
			//				{
			//					if (event.key.code == sf::Keyboard::Escape)
			//						_mainWindow.close();
			//					if (event.key.code == sf::Keyboard::Space)
			//						particleSystem.setDissolve();
			//					if (event.key.code == sf::Keyboard::A)
			//					{
			//						if (particleSystem.getDissolutionRate() > 0)
			//							particleSystem.setDissolutionRate(
			//								particleSystem.getDissolutionRate() - 1);
			//					}
			//					if (event.key.code == sf::Keyboard::S)
			//						particleSystem.setDissolutionRate(
			//							particleSystem.getDissolutionRate() + 1);
			//					if (event.key.code == sf::Keyboard::W)
			//						particleSystem.setParticleSpeed(
			//							particleSystem.getParticleSpeed()
			//							+ particleSystem.getParticleSpeed() * 0.1);
			//					if (event.key.code == sf::Keyboard::Q
			//						&& particleSystem.getParticleSpeed() > 0)
			//						particleSystem.setParticleSpeed(
			//							particleSystem.getParticleSpeed()
			//							- particleSystem.getParticleSpeed() * 0.1);
			//					if (event.key.code == sf::Keyboard::E)
			//						particleSystem.setDistribution();
			//					break;
			//				}
			//				default:
			//					break;
			//			}
			//		}

			//		/* Mouse Input */
			//		/* Set the position to match the mouse location */
			//		sf::Vector2f mousePos =
			//			static_cast<sf::Vector2f>(sf::Mouse::getPosition(_mainWindow));

			//		/* Update Particle Emitter to Mouse Position */
			//		if (mousePos.x > 0
			//			|| mousePos.y > 0
			//			|| mousePos.x < _mainWindow.getSize().x
			//			|| mousePos.y < _mainWindow.getSize().y)
			//			particleSystem.setPosition(mousePos);

			//		/* Mouse Clicks */
			//		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			//			particleSystem.fuel(10);
			//		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			//		{
			//			sf::Vector2f newGravity = lastMousePos - mousePos;
			//			newGravity *= 0.75f;
			//			particleSystem.setGravity(newGravity);
			//		}
			//		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			//			particleSystem.setGravity(0.0f, 0.0f);

			//		/* Update Last Mouse Position */
			//		lastMousePos = mousePos;

			//		/* Push Diag Text */
			//		std::ostringstream buffer;
			//		buffer << "Q/W to Decrease/Increase Particle Speed\n"
			//			<< "A/S to Decrease/Increase Decay Rate\n"
			//			<< "Right Click+Drag to Shift Gravity\n"
			//			<< "E to Change Distribution Type\n"
			//			<< "Middle Click clears Gravity\n"
			//			<< "Left Click to Add\n"
			//			<< "Particles: " << particleSystem.getNumberOfParticles();
			//		text.setString(buffer.str());

			//		/* Update particle system */
			//		particleSystem.update(static_cast<float>(UPDATE_STEP) / 1000);

			//		frameSkips++;
			//		nextUpdate += UPDATE_STEP;
			//	}

			//	/* Draw particle system and text */
			//	_mainWindow.clear(sf::Color::Black);
			//	_mainWindow.draw(text);
			//	_mainWindow.draw(particleSystem);
			//	_mainWindow.display();
			//}
			break;
		}
		case Game::Playing:
		{
			_mainWindow.clear(sf::Color(0, 0, 0));

			ScoreCounter::DrawInGame(_mainWindow);

			sf::RectangleShape line(sf::Vector2f(1024, LineWidth));
			line.setFillColor(sf::Color::White);

			line.setPosition(0, LineTop);

			_mainWindow.draw(line);

			sf::Event currentEvent;

			if (_pacingClock.getElapsedTime().asSeconds() > 3) {
				_gameMaster.HandleMonsters(_gameObjectManager);				
			}			
				
			_gameObjectManager.UpdateAll(_mainWindow, timeDelta);			
			
			_gameObjectManager.DrawAll(_mainWindow);			

			while (_mainWindow.pollEvent(currentEvent)) {
				if (currentEvent.type == sf::Event::Closed)
				{
					_gameState = Game::Exiting;
				}
			}

			if (_gameObjectManager.Get("player")->IsFinallyDead()) {
				_gameState = Game::ShowingMenu;
			}

			_mainWindow.display();
			
			break;
		}
	}	
}

void Game::showMenu() {
	_mainWindow.clear(sf::Color(0, 0, 0));
	MainMenu menu;
	menu.Show(_mainWindow);
	while (true) {
		sf::Event event;
		while (_mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed) {
				//_gameState = Test;
				newGame();
				return;
			}
		}
	}
}

void Game::newGame() {
	Player* player = new Player();
	_gameState = Playing;
	_mainClock.restart();
	_pacingClock.restart();
	_gameObjectManager.Reset();
	ScoreCounter::Reset();
	_gameObjectManager.Add("player", player);		
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
float Game::LineTop;
float Game::LineBottom;
float Game::LineWidth = 26;
GameObjectManager Game::_gameObjectManager;
GameMaster Game::_gameMaster;
sf::Clock Game::_mainClock, Game::_pacingClock;

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Game.h"
#include "Menu.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "15puzzle"); //окно 600 на 600
	window.setFramerateLimit(60); // частота обновления 60 кадров в секунду

	Menu(window); //запуск окна меню

	sf::SoundBuffer Move;
	sf::Sound MoveSound;

	Move.loadFromFile("audio/sfx_wing.wav");
	MoveSound.setBuffer(Move);
	
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text("Space - New Game, Esc - Menu", font, 25);
	text.setFillColor(sf::Color::White);
	text.setPosition(5.f, 5.f);

	Game game;
	game.setPosition(50.f, 50.f);

	sf::Event event;
	int move_counter = 0; //счетчик случайных ходов для перемешивания головоломки


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)  
					Menu(window);  
				if (event.key.code == sf::Keyboard::Left) { 
					game.Move(Direction::Left); 
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Right) { 
					game.Move(Direction::Right); 
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Up) { 
					game.Move(Direction::Up); 
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Down) { 
					game.Move(Direction::Down); 
					MoveSound.play();
				}

				if (event.key.code == sf::Keyboard::Space) //новая игра
				{
					MoveSound.play();
					game.Init();
					move_counter = 100;
				}
			}
		}
		
		if (move_counter-- > 0) //перемешивание плашек
			game.Move((Direction)(rand() % 4));

		window.clear();
		window.draw(game);		
		window.draw(text);	
		window.display();
	}

	return 0;
}
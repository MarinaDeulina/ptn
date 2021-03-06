#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Game.h"
#include "Menu.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "15puzzle"); //���� 600 �� 600
	window.setFramerateLimit(60); // ������� ���������� 60 ������ � �������

	Menu(window); //������ ���� ����

	sf::SoundBuffer Move;
	sf::Sound MoveSound;

	Move.loadFromFile("audio/sfx_wing.wav");
	MoveSound.setBuffer(Move);
	
	bool sol = true;
	int score = 0;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text("Space - New Game, Esc - Menu", font, 25);
	text.setFillColor(sf::Color::White);
	text.setPosition(5.f, 5.f);

	sf::Text textc("Congratulations", font, 100);
	textc.setFillColor(sf::Color::Red);
	textc.setPosition(80.f, 250.f);

	Game game;
	game.setPosition(50.f, 50.f);

	sf::Event event;
	int move_counter = 0; //������� ��������� ����� ��� ������������� �����������


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
					sol = false;
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Right) { 
					game.Move(Direction::Right); 
					sol = false;
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Up) { 
					game.Move(Direction::Up); 
					sol = false;
					MoveSound.play();
				}
				if (event.key.code == sf::Keyboard::Down) { 
					game.Move(Direction::Down); 
					sol = false;
					MoveSound.play();
				}

				if (event.key.code == sf::Keyboard::Space) //����� ����
				{
					MoveSound.play();
					game.Init();
					move_counter = 100;
					sol = true;
				}
			}
		}
		

		if (move_counter-- > 0) //������������� ������
			game.Move((Direction)(rand() % 4));

		window.clear();
		window.draw(game);	

		if (game.Check() && !sol) {
			window.draw(textc);
			score += 100;
		}

		window.draw(text);	
		window.display();
	}

	return 0;
}
#include "Game.h"
#include <string>


Game::Game()
{
	font.loadFromFile("arial.ttf"); //шрифт
	Init();
}

void Game::Init()
{
	picture_number = rand() % 10; //рандомное значение для получение текстуры
	for (int i = 0; i < ARRAY_SIZE - 1; i++) { 
		elements[i] = i + 1; //заполнение массива плашек
	}
	empty_index = ARRAY_SIZE - 1; //пустая плашка стоит последней
	elements[empty_index] = 0;	//значение пустой плашки = 0
	solved = true;
}

bool Game::Check()
{
	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) {
			return false;
		}
	}
	return true;
}

void Game::Move(Direction direction)
{
	//строка и колонка пустой плашки
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;
	
	//проверка на возможность перемещения и вычисление индекса перемещаемой плашки
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1))
		move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0)
		move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1))
		move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0)
		move_index = empty_index - SIZE;

	//перемещение плашки на место пустой
	if (empty_index >= 0 && move_index >= 0)
	{
		int tmp = elements[empty_index];
		elements[empty_index] = elements[move_index];
		elements[move_index] = tmp;
		empty_index = move_index;
	}
	solved = Check();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Texture texture;
	sf::Sprite sprite[17];

	std::string images[10] = { "image2/1.jpg", "image2/2.jpg", "image2/3.jpg", "image2/4.jpg","image2/5.jpg" ,"image2/6.jpg", "image2/7.jpg" ,"image2/8.jpg","image2/9.jpg","image2/10.jpg" };
	texture.loadFromFile(images[picture_number]);

	int n = 0;
	//заполнение массива спрайтов
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++) {
			n++;
			sprite[n].setTexture(texture);
			sprite[n].setTextureRect(sf::IntRect(j * CELL_SIZE, i*CELL_SIZE, CELL_SIZE, CELL_SIZE));
		}

	}
	states.transform*= getTransform();
	sf::Color color = sf::Color(200, 100, 200);

	//рамка игрового поля
	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);

	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);

	sf::Text text("", font, 52);

	for (unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(std::to_string(elements[i]));
		if (solved) //если решена меняем цвет
		{
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			text.setFillColor(sf::Color::Green); //если плашка на своем месте меняем цвет
		}

		//рисуем все плашки от 1 до 15
		if (elements[i] > 0)
		{
			n = elements[i];

			sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f); //вычисление позиции для отрисовки
			
			shape.setPosition(position); //позиции рамок
			sprite[n].setPosition(position.x + 50.f, position.y + 50.f); //позиции каждой картинки
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f); //позиция текста

			target.draw(sprite[n]); //картинка
			target.draw(shape, states);	//рамка
			target.draw(text, states); //номер
		}
	}
}
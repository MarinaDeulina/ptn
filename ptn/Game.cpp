#include "Game.h"
#include <string>


Game::Game()
{
	font.loadFromFile("arial.ttf"); //�����
	Init();
}

void Game::Init()
{
	picture_number = rand() % 10; //��������� �������� ��� ��������� ��������
	for (int i = 0; i < ARRAY_SIZE - 1; i++) { 
		elements[i] = i + 1; //���������� ������� ������
	}
	empty_index = ARRAY_SIZE - 1; //������ ������ ����� ���������
	elements[empty_index] = 0;	//�������� ������ ������ = 0
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
	//������ � ������� ������ ������
	int col = empty_index % SIZE;
	int row = empty_index / SIZE;
	
	//�������� �� ����������� ����������� � ���������� ������� ������������ ������
	int move_index = -1;
	if (direction == Direction::Left && col < (SIZE - 1))
		move_index = empty_index + 1;
	if (direction == Direction::Right && col > 0)
		move_index = empty_index - 1;
	if (direction == Direction::Up && row < (SIZE - 1))
		move_index = empty_index + SIZE;
	if (direction == Direction::Down && row > 0)
		move_index = empty_index - SIZE;

	//����������� ������ �� ����� ������
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
	//���������� ������� ��������
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

	//����� �������� ����
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
		if (solved) //���� ������ ������ ����
		{
			shape.setOutlineColor(sf::Color::Cyan);
			text.setFillColor(sf::Color::Cyan);
		}
		else if (elements[i] == i + 1)
		{
			text.setFillColor(sf::Color::Green); //���� ������ �� ����� ����� ������ ����
		}

		//������ ��� ������ �� 1 �� 15
		if (elements[i] > 0)
		{
			n = elements[i];

			sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f); //���������� ������� ��� ���������
			
			shape.setPosition(position); //������� �����
			sprite[n].setPosition(position.x + 50.f, position.y + 50.f); //������� ������ ��������
			text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f); //������� ������

			target.draw(sprite[n]); //��������
			target.draw(shape, states);	//�����
			target.draw(text, states); //�����
		}
	}
}
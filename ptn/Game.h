#pragma once
#include <SFML/Graphics.hpp>

const int SIZE = 4;						// Размер игрового поля в плашках
const int ARRAY_SIZE = SIZE * SIZE;		// Размер массива
const int FIELD_SIZE = 500;				// Размер игрового поля в пикселях
const int CELL_SIZE = 120;				// Размер плашки в пикселях


enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int picture_number;
	int elements[ARRAY_SIZE];// массив плашек
	int empty_index; //индекс в массиве, соответствующий свободной ячейке
	bool solved; //признак того, что головоломка решена

	sf::Font font;
public:
	Game();
	void Init(); // Заполняем массив плашек
	bool Check(); // Проверка собранности головоломки
	void Move(Direction direction); //обработка передвижения плашек
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


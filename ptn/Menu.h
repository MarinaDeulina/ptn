#pragma once
#include <SFML/Graphics.hpp>
void Menu(sf:: RenderWindow & window) {
	sf::Texture mTexture1, mTexture2, mTexture3, menuBackground;

	mTexture1.loadFromFile("image2/play.png");
	mTexture2.loadFromFile("image2/exit.png");
	mTexture3.loadFromFile("image2/15.png");
	menuBackground.loadFromFile("image2/menu.jpg"); 

	sf:: Sprite menu1(mTexture1), menu2(mTexture2), name(mTexture3), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(200, 250);
	menu2.setPosition(200, 350);
	name.setPosition(75, 10);
	menuBg.setPosition(0, 0);


	while (isMenu)
	{
		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menuNum = 0;

		window.clear(sf::Color(129, 181, 221));

		if (sf::IntRect(200, 250, 150, 100).contains(sf::Mouse::getPosition(window))) { 
			menu1.setColor(sf::Color::Green); //изменение цвета кнопки по наведению курсора
			menuNum = 1; 
		}
		if (sf::IntRect(200, 350, 150, 100).contains(sf::Mouse::getPosition(window))) { 
			menu2.setColor(sf::Color::Red); //изменение цвета кнопки по наведению курсора
			menuNum = 2; 
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) {
				isMenu = false;
			}
				
			if (menuNum == 2) { 
				window.close(); 
				isMenu = false; 
			}
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(name);
		window.display();
	}

}
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
struct Ground {
	int x, y, w, h, lOrR;
	sf::RectangleShape rectangle;
	Ground(int xp, int yp, int width, int height);
	void update(sf::RenderWindow &window, double &gameSpeed, int &r, int&l);
};

Ground::Ground( int xp=0, int yp=560, int width=800, int height=20){
	x = xp;
	y = yp;
	w = width;
	h = height;
	rectangle.setSize(sf::Vector2f(w, h));
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setPosition(x, y);
}
void Ground::update(sf::RenderWindow &window, double &gameSpeed, int &l, int&r) {
	rectangle.move(sf::Vector2f(0, gameSpeed));
	x = rectangle.getPosition().x;
	y = rectangle.getPosition().y;
	window.draw(rectangle);
	if (y >= 600) {
		y = rand() % 100+100;
		w = rand() % 250 + 150;
		lOrR = rand() % 2;
		if (r == 2) {
			x = 0;
			r = 0;
		}
		else if (l == 2) {
			x = 800 - w;
			l = 0;
		}
		else if (lOrR) {
			x = 800 - w;
			l= 0;
			r++;
		}
		else {
			x = 0;
			r = 0;
			l++;
		}
		rectangle.setPosition(x, y);
		rectangle.setSize(sf::Vector2f(w, h));
		gameSpeed += 0.2/gameSpeed;
	}
}

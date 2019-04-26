#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "ground.h"
#include <vector>
class Player {
	sf::Texture heroTexture;
	
	bool onGround = true;
	int width=28, height=52, rotate=0, jump_speed=-8;
public:
	double speed = 0.1, xvel = 0, yvel = 0;
	sf::Sprite heroObj;
	int x, y;
	double gravitySpeed;
	Player(int xp, int yp, double gs);
	bool update(sf::RenderWindow &window, int &point,int &bonus, double gameSpeed);
	void gravity(std::vector<Ground> grounds);

};
void Player::gravity (std::vector<Ground> grounds) {
	int i = 0;
	onGround = false;
	for (std::vector<Ground>::iterator it = grounds.begin(); it != grounds.end(); it++) {
		if (grounds[i].x <= x+width && grounds[i].x + grounds[i].w >= x) {
			if (grounds[i].y <= y + height && grounds[i].y+grounds[i].h>=y+height){
				onGround = true;
				heroObj.setPosition(x, grounds[i].y - height);
			}
		}
		i++;
	}
	
	
	
}
Player::Player(int xp=0, int yp=500, double gs=0.1) {
	x = xp;
	y = yp;
	if (!heroTexture.loadFromFile("./data/hero.bmp")) std::cout << "Error while loading an texture";
	heroObj.setTexture(heroTexture);
	heroObj.setPosition(xp, yp);
	gravitySpeed = gs;
}

bool Player::update(sf::RenderWindow &window, int &point, int &bonus,double gameSpeed) {
	window.draw(heroObj);
	if (xvel <= 7||xvel>=-7) {
		xvel += sf::Keyboard::isKeyPressed(sf::Keyboard::D)*speed;
		xvel += -sf::Keyboard::isKeyPressed(sf::Keyboard::A)*speed;
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (xvel > 0)xvel -= speed;
				if (xvel < 0)xvel += speed;
			}
	}
	
	heroObj.move(
	sf::Vector2f(xvel, yvel));
	x = heroObj.getPosition().x;
	y = heroObj.getPosition().y;
	if(onGround){
		if (yvel >= 0) {
			rotate = 0;
			yvel = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
			yvel *= jump_speed;
			heroObj.move(sf::Vector2f(0, gameSpeed));
			bonus = 1;
		}
		speed = 0.1;
	}
	else {
		yvel += gravitySpeed;
		if (x < 0) {
			xvel *= -1;
			heroObj.setPosition(sf::Vector2f(0, y));
			bonus *= 2;
		}else if (x > 800 - width) {
			xvel *= -1;
			heroObj.setPosition(sf::Vector2f(800 - width, y));
			bonus *= 2;
		}
		rotate += 4 * sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		if (rotate >= 330) {
			rotate = 0;
			point += 1*bonus;
			
		}
		speed = 0.05;
	}
	
	if (y >= 600)return true;
	heroObj.setRotation(rotate);
	return false;
}

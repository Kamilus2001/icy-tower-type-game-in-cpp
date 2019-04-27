// FirstCPPGame.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "ground.h"
#include <vector>
#include <ctime>
#include <thread>
#include <fstream>
Ground ground, ground1( 0, 300, 300), ground2( 400, 450, 400);
std::vector<Ground>platforms;
int score=0, highScore
;
void newScore() {
	std::fstream file;
	std::string highS;

	file.open("score.txt", std::ios::in);
	std::getline(file, highS);
	file.close();
	highScore = std::stoi(highS);
	std::cout << highScore << std::endl;
	while (true) {
		if (score > highScore) {
			highScore = score;
			file.open("score.txt", std::ios::out);
			file << highScore;
			file.close();
		}
	}
}
void updatePlatforms() {
	while (true) {
		platforms[0] = ground;
		platforms[1] = ground1;
		platforms[2] = ground2;

	}
}
void updateScore(int score, sf::Text &txt, int bonus) {
	std::string t1;
	sf::String t2;
		t1 = "SCORE: ";
		t1 += std::to_string(score);
		if (bonus > 1) {
			t1 += " X.";
			t1 += std::to_string(bonus);
		}
		t2 = t1;
		txt.setString(t2);
}
int sort(std::vector<Ground> gd) {
	double y = gd[0].y, x=gd[0].x;
	for (int i = 1; i < gd.size(); i++) {
		if (y < gd[i].y) {
			y = gd[i].y;
			x = gd[i].x;
		}
	}	
	return x;
}
int main()
{
	srand(time(NULL));
	int width = 800, height = 600, size=30, bonus=1;
	int l = 0, r=0;
	double gameSpeed = 0.2;
	sf::RenderWindow window(sf::VideoMode(width, height), "Game");
	sf::Font f1;
	if(f1.loadFromFile("./data/fonts/comic.ttf"))std::cout<<"font loaded";
	sf::Text t1;
	std::string text = "SCORE: ";
	text += std::to_string(score);
	sf::String textSF = text;
	t1.setFont(f1);
	t1.setCharacterSize(size);
	t1.setString(textSF);
	t1.setFillColor(sf::Color::White);
	t1.setPosition(sf::Vector2f(width/2-100, 15));
	Player playerObj;
	platforms.push_back(ground);
	platforms.push_back(ground1);
	platforms.push_back(ground2);
	std::thread th1(updatePlatforms), th2(newScore);
	window.setFramerateLimit(100);
	while (window.isOpen()) {
		updateScore(score, t1, bonus);
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		playerObj.gravity(platforms);
		if (playerObj.update(window, score, bonus, gameSpeed)) {
			t1.setString("DEATH\n BEST SCORE: "+std::to_string(highScore)+"\nPRESS SPACE TO RESTART");
			t1.setFillColor(sf::Color::Red);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				playerObj.heroObj.setPosition(sort(platforms), 0);
				playerObj.xvel = 0;
				playerObj.yvel = 0;
				t1.setFillColor(sf::Color::White);
				score = 0;
				gameSpeed = 0.3;
			}
		}
		ground.update(window, gameSpeed, l, r);
		ground1.update(window, gameSpeed, l, r);
		ground2.update(window, gameSpeed, l, r);
		window.draw(t1);
		window.display();
		
	}
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln


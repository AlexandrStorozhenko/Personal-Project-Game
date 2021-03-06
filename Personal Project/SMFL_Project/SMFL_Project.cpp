#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>

float player_pos_x = 200.f;
float player_pos_y = 450.f;
float player_pos_y_jump;
float speed_x = -3.f;
float speed_y = 0.f;
float jump_h = 50.f;
int score = 0;
float i = 0;
bool jump_up = false;
bool jump_down = false;
bool Game_On = true;
float FrameRate = 100;

float pos_y(float iter) {
	float x = speed_x * iter;
	float x_pow2 = pow(x, 2.0);
	float pos_y = (-3.f*x_pow2 - 600.f*x) / 400.f;
	return pos_y;
}

int main() {

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Personal Project Game", sf::Style::Default);
	window.setFramerateLimit(FrameRate);
	window.setKeyRepeatEnabled(false);

	sf::RectangleShape line(sf::Vector2f(1000.f, 2.f));
	line.setFillColor(sf::Color::Black);
	line.setPosition(0.f, 499.f);

	sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
	player.setFillColor(sf::Color(0, 173, 181));
	player.setPosition(player_pos_x, player_pos_y);

	sf::CircleShape point1(8.f, 100);
	point1.setFillColor(sf::Color(255, 125, 0));
	point1.setPosition(500.f, 465.f);

	sf::CircleShape point2(8.f, 100);
	point2.setFillColor(sf::Color(255, 125, 0));
	point2.setPosition(800.f, 465.f);

	sf::CircleShape point3(8.f, 100);
	point3.setFillColor(sf::Color(255, 125, 0));
	point3.setPosition(1100.f, 465.f);

	sf::CircleShape point_aft(8.f, 100);
	point_aft.setFillColor(sf::Color(255, 125, 0));

	sf::CircleShape barrier1(30.f, 3);
	barrier1.setFillColor(sf::Color(57, 62, 70));
	barrier1.setPosition(625.f, 455.f);

	sf::CircleShape barrier2(30.f, 3);
	barrier2.setFillColor(sf::Color(57, 62, 70));
	barrier2.setPosition(925.f, 455.f);

	sf::CircleShape barrier3(30.f, 3);
	barrier3.setFillColor(sf::Color(57, 62, 70));
	barrier3.setPosition(1225.f, 455.f);

	sf::CircleShape barrier_aft(30.f, 3);
	barrier_aft.setFillColor(sf::Color(57, 62, 70));

	sf::RectangleShape rect_barrier1(sf::Vector2f(10.f, 100.f));
	rect_barrier1.setFillColor(sf::Color(57, 62, 70));

	sf::RectangleShape rect_barrier2(sf::Vector2f(10.f, 100.f));
	rect_barrier2.setFillColor(sf::Color(57, 62, 70));

	sf::RectangleShape rect_barrier3(sf::Vector2f(10.f, 100.f));
	rect_barrier3.setFillColor(sf::Color(57, 62, 70));

	sf::RectangleShape rect_barrier_aft(sf::Vector2f(10.f, 100.f));
	rect_barrier_aft.setFillColor(sf::Color(57, 62, 70));

	sf::RectangleShape button(sf::Vector2f(400, 100));
	button.setFillColor(sf::Color(0, 173, 181));
	button.setPosition(315.f, 700.f);
	sf::FloatRect button_bounds = button.getGlobalBounds();

	//text
	sf::Font font;
	if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {

		std::cout << "There was an error" << std::endl;

	}

	sf::Text score_text;
	score_text.setCharacterSize(50);
	score_text.setFillColor(sf::Color::Black);
	score_text.setFont(font);
	score_text.setPosition(400.f, 75.f);
	score_text.setStyle(sf::Text::Bold);
	score_text.setString("Score: " + std::to_string(score));

	sf::Text GO_text;
	GO_text.setCharacterSize(130);
	GO_text.setFillColor(sf::Color(57, 62, 70));
	GO_text.setFont(font);
	GO_text.setPosition(175.f, 250.f);
	GO_text.setStyle(sf::Text::Bold);
	GO_text.setString("Game Over");

	sf::Text restart;
	restart.setCharacterSize(75);
	restart.setFillColor(sf::Color(57, 62, 70));
	restart.setFont(font);
	restart.setPosition(387.5f, 702.5f);
	restart.setStyle(sf::Text::Bold);
	restart.setString("Restart");

	sf::Text final_score;
	final_score.setCharacterSize(75);
	final_score.setFillColor(sf::Color(57, 62, 70));
	final_score.setFont(font);
	final_score.setStyle(sf::Text::Bold);

	while (window.isOpen()) {

		FrameRate += 0.01f;
		window.setFramerateLimit(FrameRate);

		//user input - complete
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Up) {
					if (player_pos_y == 500.f) {
						if (jump_up == false && jump_down == false) {
							player_pos_y -= 50;
							player.setPosition(player_pos_x, player_pos_y);
						}
					}
					else if (player_pos_y == 450.f) {
						if (jump_up == false && jump_down == false) {
							i = 0;
							jump_up = true;
						}
					}
				}
				else if (event.key.code == sf::Keyboard::Down) {
					sf::Vector2f player_pos = player.getPosition();
					if (player_pos_y == 450.f) {
						if (jump_up == false && jump_down == false) {
							player_pos_y += 50;
							player.setPosition(player_pos_x, player_pos_y);
						}
					}
					else if (player_pos_y == 500.f) {
						if (jump_up == false && jump_down == false) {
							i = 0;
							jump_down = true;
						}
					}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (button_bounds.contains(float(event.mouseButton.x), float(event.mouseButton.y)) && !Game_On) {
					//Reinit
					score = 0;
					FrameRate = 100;
					speed_x = -3.f;
					player_pos_x = 200.f;
					player_pos_y = 450.f;
					point1.setPosition(500.f, 465.f);
					point2.setPosition(800.f, 465.f);
					point3.setPosition(1100.f, 465.f);
					barrier1.setPosition(625.f, 455.f);
					barrier2.setPosition(925.f, 455.f);
					barrier3.setPosition(1225.f, 455.f);
					rect_barrier1.setPosition(-100.f, -100.f);
					rect_barrier2.setPosition(-100.f, -100.f);
					rect_barrier3.setPosition(-100.f, -100.f);
					rect_barrier_aft.setPosition(-100.f, -100.f);
					point_aft.setPosition(-100.f, -100.f);
					barrier_aft.setPosition(-100.f, -100.f);
					barrier1.setRotation(0.f);
					barrier2.setRotation(0.f);
					barrier3.setRotation(0.f);
					score_text.setString("Score: " + std::to_string(score));
					srand(time(NULL));
					Game_On = true;
				}
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color(238, 238, 238));

		//movement
		point1.move(speed_x, speed_y);
		point2.move(speed_x, speed_y);
		point3.move(speed_x, speed_y);
		point_aft.move(speed_x, speed_y);
		barrier1.move(speed_x, speed_y);
		barrier2.move(speed_x, speed_y);
		barrier3.move(speed_x, speed_y);
		barrier_aft.move(speed_x, speed_y);
		rect_barrier1.move(speed_x, speed_y);
		rect_barrier2.move(speed_x, speed_y);
		rect_barrier3.move(speed_x, speed_y);
		rect_barrier_aft.move(speed_x, speed_y);

		//jump - complete ( the number of iterations is determined by the "distance of the jump"/speed_x )
		if (i <= 65.7f && jump_up == true) {
			i += 1.f;
			player_pos_y_jump = player_pos_y - pos_y(i);
			player.setPosition(player_pos_x, player_pos_y_jump);

		}
		else if (i <= 65.7f && jump_down == true) {
			i += 1.f;
			player_pos_y_jump = player_pos_y + pos_y(i);
			player.setPosition(player_pos_x, player_pos_y_jump);
		}
		else {
			player.setPosition(player_pos_x, player_pos_y);
			jump_up = false;
			jump_down = false;
		}

		//Scoring system - complete

		srand(time(NULL));
		int up_down = rand() % 2;
		sf::Vector2f point1_pos = point1.getPosition();
		sf::Vector2f point2_pos = point2.getPosition();
		sf::Vector2f point3_pos = point3.getPosition();
		sf::Vector2f player_pos = player.getPosition();
		sf::FloatRect point1_bounds = point1.getGlobalBounds();
		sf::FloatRect point2_bounds = point2.getGlobalBounds();
		sf::FloatRect point3_bounds = point3.getGlobalBounds();
		sf::FloatRect point_aft_bounds = point_aft.getGlobalBounds();
		sf::FloatRect player_bounds = player.getGlobalBounds();

		for (float i = 0.f; i < 51.f; i++) {
			if (point1_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && point1_pos.y == 465.f) {
					score += 1;
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y <= 450.f && point1_pos.y == 465.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y >= 500.f && point1_pos.y == 465.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 450.f && point1_pos.y != 465.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point1_pos.y == 520.f) {
					score += 1;
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y >= 500.f && point1_pos.y == 520.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y <= 450.f && point1_pos.y == 520.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point1_pos.y != 520.f) {
					point_aft.setPosition(point1_pos);
					if (up_down) {
						point1.setPosition(1100.f + i, 465.f);
					}
					else {
						point1.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
			}
			else if (point2_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && point2_pos.y == 465.f) {
					score += 1;
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y <= 450.f && point2_pos.y == 465.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y >= 500.f && point2_pos.y == 465.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 450.f && point2_pos.y != 465.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point2_pos.y == 520.f) {
					score += 1;
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y >= 500.f && point2_pos.y == 520.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y <= 450.f && point2_pos.y == 520.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point2_pos.y != 520.f) {
					point_aft.setPosition(point2_pos);
					if (up_down) {
						point2.setPosition(1100.f + i, 465.f);
					}
					else {
						point2.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
			}
			else if (point3_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && point3_pos.y == 465.f) {
					score += 1;
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y <= 450.f && point3_pos.y == 465.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y >= 500.f && point3_pos.y == 465.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 450.f && point3_pos.y != 465.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point3_pos.y == 520.f) {
					score += 1;
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
					break;
				}
				else if (player_pos.y >= 500.f && point3_pos.y == 520.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y <= 450.f && point3_pos.y == 520.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
				else if (player_pos.y == 500.f && point3_pos.y != 520.f) {
					point_aft.setPosition(point3_pos);
					if (up_down) {
						point3.setPosition(1100.f + i, 465.f);
					}
					else {
						point3.setPosition(1100.f + i, 520.f);
					}
					score_text.setString("Score: " + std::to_string(score));
				}
			}
			else if (point_aft_bounds.intersects(player_bounds)) {
				point_aft.setPosition(-100.f, 0.f);
				sf::FloatRect point_aft_bounds = point_aft.getGlobalBounds();
				score += 1;
				score_text.setString("Score: " + std::to_string(score));
				break;
			}
		}

		//Collision - add an aft_block collision check

		sf::Vector2f barrier1_pos = barrier1.getPosition();
		sf::Vector2f barrier2_pos = barrier2.getPosition();
		sf::Vector2f barrier3_pos = barrier3.getPosition();
		sf::Vector2f rect_barrier1_pos = rect_barrier1.getPosition();
		sf::Vector2f rect_barrier2_pos = rect_barrier2.getPosition();
		sf::Vector2f rect_barrier3_pos = rect_barrier3.getPosition();
		player_pos = player.getPosition();

		int block_up_down = rand() % 2;
		int block_type = rand() % 2;

		for (float i = 0.f; i < 51.f; i++) {
			sf::Vector2f barrier_aft_pos = barrier_aft.getPosition();
			if (barrier1_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && barrier1_pos.y == 455.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y == 500.f && barrier1_pos.y == 545.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y != 450.f && barrier1_pos.y == 455.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier1.getRotation());
						barrier_aft.setPosition(barrier1_pos);
						if (block_type) {
							barrier1.setRotation(0.f);
							barrier1.setPosition(1100.f + i, 455.f);
						}
						else {
							rect_barrier1.setPosition(1125.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier1.getRotation());
						barrier_aft.setPosition(barrier1_pos);
						if (block_type) {
							barrier1.setRotation(180.f);
							barrier1.setPosition(1160.f + i, 545.f);
						}
						else {
							rect_barrier1.setPosition(1125.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y != 500.f && barrier1_pos.y == 545.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier1.getRotation());
						barrier_aft.setPosition(barrier1_pos);
						if (block_type) {
							barrier1.setRotation(0.f);
							barrier1.setPosition(1040.f + i, 455.f);
						}
						else {
							rect_barrier1.setPosition(1075.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier1.getRotation());
						barrier_aft.setPosition(barrier1_pos);
						if (block_type) {
							barrier1.setRotation(180.f);
							barrier1.setPosition(1100.f + i, 545.f);
						}
						else {
							rect_barrier1.setPosition(1075.f + i, 500.f);
						}
					}
				}
			}
			else if (rect_barrier1_pos.x == player_pos_x + i) {
				if (player_pos.y <= 450.f && rect_barrier1_pos.y == 400.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier1_pos.y == 500.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier1_pos.y == 400.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier1_pos);
						if (block_type) {
							barrier1.setRotation(0.f);
							barrier1.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier1.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier1_pos);
						if (block_type) {
							barrier1.setRotation(180.f);
							barrier1.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier1.setPosition(1100.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y <= 450.f && rect_barrier1_pos.y == 500.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier1_pos);
						if (block_type) {
							barrier1.setRotation(0.f);
							barrier1.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier1.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier1_pos);
						if (block_type) {
							barrier1.setRotation(180.f);
							barrier1.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier1.setPosition(1100.f + i, 500.f);
						}
					}
				}
			}
			else if (barrier2_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && barrier2_pos.y == 455.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y == 500.f && barrier2_pos.y == 545.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y != 450.f && barrier2_pos.y == 455.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier2.getRotation());
						barrier_aft.setPosition(barrier2_pos);
						if (block_type) {
							barrier2.setRotation(0.f);
							barrier2.setPosition(1100.f + i, 455.f);
						}
						else {
							rect_barrier2.setPosition(1125.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier2.getRotation());
						barrier_aft.setPosition(barrier2_pos);
						if (block_type) {
							barrier2.setRotation(180.f);
							barrier2.setPosition(1160.f + i, 545.f);
						}
						else {
							rect_barrier2.setPosition(1125.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y != 500.f && barrier2_pos.y == 545.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier2.getRotation());
						barrier_aft.setPosition(barrier2_pos);
						if (block_type) {
							barrier2.setRotation(0.f);
							barrier2.setPosition(1040.f + i, 455.f);
						}
						else {
							rect_barrier2.setPosition(1075.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier2.getRotation());
						barrier_aft.setPosition(barrier2_pos);
						if (block_type) {
							barrier2.setRotation(180.f);
							barrier2.setPosition(1100.f + i, 545.f);
						}
						else {
							rect_barrier2.setPosition(1075.f + i, 500.f);
						}
					}
				}
			}
			else if (rect_barrier2_pos.x == player_pos_x + i) {
				if (player_pos.y <= 450.f && rect_barrier2_pos.y == 400.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier2_pos.y == 500.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier2_pos.y == 400.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier2_pos);
						if (block_type) {
							barrier2.setRotation(0.f);
							barrier2.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier2.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier2_pos);
						if (block_type) {
							barrier2.setRotation(180.f);
							barrier2.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier2.setPosition(1100.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y <= 450.f && rect_barrier2_pos.y == 500.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier2_pos);
						if (block_type) {
							barrier2.setRotation(0.f);
							barrier2.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier2.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier2_pos);
						if (block_type) {
							barrier2.setRotation(180.f);
							barrier2.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier2.setPosition(1100.f + i, 500.f);
						}
					}
				}
			}
			else if (barrier3_pos.x == player_pos_x + i) {
				if (player_pos.y == 450.f && barrier3_pos.y == 455.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y == 500.f && barrier3_pos.y == 545.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y != 450.f && barrier3_pos.y == 455.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier3.getRotation());
						barrier_aft.setPosition(barrier3_pos);
						if (block_type) {
							barrier3.setRotation(0.f);
							barrier3.setPosition(1100.f + i, 455.f);
						}
						else {
							rect_barrier3.setPosition(1125.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier3.getRotation());
						barrier_aft.setPosition(barrier3_pos);
						if (block_type) {
							barrier3.setRotation(180.f);
							barrier3.setPosition(1160.f + i, 545.f);
						}
						else {
							rect_barrier3.setPosition(1125.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y != 500.f && barrier3_pos.y == 545.f) {
					if (block_up_down) {
						barrier_aft.setRotation(barrier3.getRotation());
						barrier_aft.setPosition(barrier3_pos);
						if (block_type) {
							barrier3.setRotation(0.f);
							barrier3.setPosition(1040.f + i, 455.f);
						}
						else {
							rect_barrier3.setPosition(1075.f + i, 400.f);
						}
					}
					else {
						barrier_aft.setRotation(barrier3.getRotation());
						barrier_aft.setPosition(barrier3_pos);
						if (block_type) {
							barrier3.setRotation(180.f);
							barrier3.setPosition(1100.f + i, 545.f);
						}
						else {
							rect_barrier3.setPosition(1075.f + i, 500.f);
						}
					}
				}
			}
			else if (rect_barrier3_pos.x == player_pos_x + i) {
				if (player_pos.y <= 450.f && rect_barrier3_pos.y == 400.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier3_pos.y == 500.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
				else if (player_pos.y >= 500.f && rect_barrier3_pos.y == 400.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier3_pos);
						if (block_type) {
							barrier3.setRotation(0.f);
							barrier3.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier3.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier3_pos);
						if (block_type) {
							barrier3.setRotation(180.f);
							barrier3.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier3.setPosition(1100.f + i, 500.f);
						}
					}
				}
				else if (player_pos.y <= 450.f && rect_barrier3_pos.y == 500.f) {
					if (block_up_down) {
						rect_barrier_aft.setPosition(rect_barrier3_pos);
						if (block_type) {
							barrier3.setRotation(0.f);
							barrier3.setPosition(1075.f + i, 455.f);
						}
						else {
							rect_barrier3.setPosition(1100.f + i, 400.f);
						}
					}
					else {
						rect_barrier_aft.setPosition(rect_barrier3_pos);
						if (block_type) {
							barrier3.setRotation(180.f);
							barrier3.setPosition(1125.f + i, 545.f);
						}
						else {
							rect_barrier3.setPosition(1100.f + i, 500.f);
						}
					}
				}
			}
			else if (barrier_aft_pos.x == player_pos_x - i) {
				if (player_pos.y == 450.f && barrier_aft_pos.y == 455.f) {
					speed_x = 0.f;
					Game_On = false;
					break;
				}
			}
		}

		//Game State
		if (Game_On) {
			window.draw(line);
			window.draw(player);
			window.draw(point1);
			window.draw(barrier1);
			window.draw(rect_barrier1);
			window.draw(point2);
			window.draw(barrier2);
			window.draw(rect_barrier2);
			window.draw(point3);
			window.draw(barrier3);
			window.draw(rect_barrier3);
			window.draw(point_aft);
			window.draw(barrier_aft);
			window.draw(rect_barrier_aft);
			window.draw(score_text);
		}
		else {
			window.draw(GO_text);
			window.draw(button);
			window.draw(restart);
			final_score.setString("Final Score: " + std::to_string(score));
			if (score < 10) {
				final_score.setPosition(284.5f, 502.5f);
			}
			else if (score < 99) {
				final_score.setPosition(244.5f, 502.5f);
			}
			else if (score < 99) {
				final_score.setPosition(199.5f, 502.5f);
			}
			window.draw(final_score);
		}

		window.display();
	}
}
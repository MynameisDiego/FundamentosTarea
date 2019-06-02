#include "Player.h"
#include <SDL\SDL.h>
#include <iostream>

Player::Player()
{
	color.r = 255;
	color.g = 0;
	color.b = 255;
	color.a = 255;
}

Player::~Player()
{
}

void Player::init(float _speed, glm::vec2 _position,
	InputManager* _inputmanager) {
	position = _position;
	speed = _speed;
	inputmanager = _inputmanager;
}


void Player::update(const std::vector<std::string>& leveldata,
	std::vector<Human*> & humans,
	std::vector<Zombie*>& zombies) {

	
	if (inputmanager->isKeyPressed(SDLK_w)) {
		position.y += speed;
	}
	if (inputmanager->isKeyPressed(SDLK_s)) {
		position.y -= speed;
	}
	if (inputmanager->isKeyPressed(SDLK_a)) {
		position.x -= speed;
	}
	if (inputmanager->isKeyPressed(SDLK_d)) {
		position.x += speed;
	}
	collideWithLevel(leveldata);

}

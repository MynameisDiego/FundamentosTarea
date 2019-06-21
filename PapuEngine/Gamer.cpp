#include "Gamer.h"
#include <SDL\SDL.h>
#include <iostream>

using namespace std;

Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture):
	Agent(agent_width,agent_height,position,texture)
{

}

Gamer::Gamer(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* _inputmanager
) :Agent(agent_width, agent_height, position, texture) {
	inputManager = _inputmanager;
}

void Gamer::update() {
	if (inputManager->isKeyDown(SDLK_w)) {
		_position.y += 8.0f;
	}

	if (inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 8.0f;
	}
	if (inputManager->isKeyDown(SDLK_a))
	{
		_position.x -= 8.0f;
		tecla = 1;
	}
	if (inputManager->isKeyDown(SDLK_d))
	{
		_position.x += 8.0f;
		tecla = 2;
	}

	if (inputManager->isKeyDown(SDLK_b)) {
		cout << "X: " << _position.x << "Y: " << _position.y << endl;

	}
}

std::string Gamer::getTexture() {
	return _texturePath;
}


Gamer::~Gamer()
{
}

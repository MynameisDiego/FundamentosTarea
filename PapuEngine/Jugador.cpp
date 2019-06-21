#include "Jugador.h"
#include <SDL\SDL.h>
#include <iostream>


Jugador::Jugador(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture):
		Agent(agent_width,agent_height,position,texture)
{

}

Jugador::Jugador(float agent_width,
	float agent_height,
	glm::vec2 position,
	std::string texture,
	InputManager* inputManager
	) :
	Agent(agent_width, agent_height, position, texture)
{
	_inputManager = inputManager;
}

void Jugador::update(float deltaTime,bool reloj) {
	if (_inputManager->isKeyDown(SDLK_w)) {
		_position.y += 8.0f;
	}
	if (_inputManager->isKeyDown(SDLK_s)) {
		_position.y -= 8.0f;
	}
}


void Jugador::setPosition(glm::vec2 position) {
	_position = position;
}
void Jugador::changeTexture(std::string texturePath) {
	_texturePath = texturePath;
}
std::string Jugador::getTexture() {
	return _texturePath;
}

Jugador::~Jugador()
{
}

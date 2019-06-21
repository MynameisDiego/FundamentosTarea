#pragma once
#include "Agent.h"
#include "InputManager.h"

class Gamer : public Agent
{
private:
	InputManager* inputManager;
	int tecla = 0;
public:
	Gamer(float agent_width,
			float agent_height,
		glm::vec2 position,
		std::string texture);
	Gamer(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture,
		InputManager* _inputManager);
	void update();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}
	int gettecla() {
		return tecla;
	}
	std::string getTexture();
	~Gamer();
};


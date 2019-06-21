#pragma once
#include "Agent.h"
class Asteroid : public Agent
{
public:
	Asteroid(float agent_width,
		float agent_height,
		glm::vec2 position,
		std::string texture);
	void update();
	void setPosition(glm::vec2 position) {
		_position = position;
	}
	void changeTexture(std::string texturePath) {
		_texturePath = texturePath;
	}
	std::string getTexture();
	~Asteroid();
};


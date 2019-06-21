#include "Asteroid.h"




Asteroid::Asteroid(float agent_width, float agent_height, 
	glm::vec2 position, std::string texture) :Agent(agent_width, agent_height, position, texture)
{
}

void Asteroid::update()
{
	_position.y -= 1.0f;
}

std::string Asteroid::getTexture()
{
	return _texturePath;
}

Asteroid::~Asteroid()
{
}

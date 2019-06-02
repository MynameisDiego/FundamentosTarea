#include "Zombie.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Zombie::Zombie()
{
}

void Zombie::init(float _speed, glm::vec2 _position)
{
	speed = _speed;
	position = _position;
	color.r = 150;
	color.g = 125;
	color.b = 0;
	color.a = 255;

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	}
	direction = glm::vec2(direction);
}

void Zombie::update(const std::vector<std::string>& leveldata, 
	std::vector<Human*>& humans, 
	std::vector<Zombie*>& zombies){
	
}

Zombie::~Zombie()
{
}

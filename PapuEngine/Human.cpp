#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>


Human::Human()
{
}

void Human::init(float _speed,glm::vec2 _position) {
	speed = _speed;
	position = _position;
	color.r = 185;
	color.g = 0;
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

void Human::update(const std::vector<std::string>& leveldata,
	std::vector<Human*> & humans,
	std::vector<Zombie*>& zombies) {
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float>
								randRotate(-40.0f, 40.0f);
	position += direction* speed;
	if (collideWithLevel(leveldata)) {
		direction = 
			glm::rotate(direction, randRotate(randomEngine));
	}
}

Human::~Human()
{
}

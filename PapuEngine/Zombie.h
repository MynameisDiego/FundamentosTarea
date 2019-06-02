#pragma once
#include "Agent.h"
class Zombie : public Agent
{
private:
	glm::vec2 direction;
public:
	void init(float _speed, glm::vec2 _position);
	Zombie();
	~Zombie();

	void update(const std::vector<std::string>& leveldata,
		std::vector<Human*> & humans,
		std::vector<Zombie*>& zombies);
};


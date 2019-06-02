#pragma once
#include "Agent.h"
class Human : public Agent
{
private:
	glm::vec2 direction;
		
public:
	void init(float _speed, glm::vec2 _position);
	Human();
	~Human();

	void update(const std::vector<std::string>& leveldata,
		std::vector<Human*> & humans,
		std::vector<Zombie*>& zombies);
};


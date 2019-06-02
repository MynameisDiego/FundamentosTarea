#pragma once
#include "Human.h"
#include "InputManager.h"

class Player : public Human
{
private:
	InputManager* inputmanager;
public:
	Player();
	~Player();
	void init(float _speed, glm::vec2 _position, 
					InputManager* _inputmanager);
	void update(const std::vector<std::string>&levelData, 
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies
		);
};


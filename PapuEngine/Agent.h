#pragma once
#include <glm\glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"

class Zombie;
class Human;
class img;

const float AGENT_WIDTH = 60.0f;
const float AGENT_WIDTH2 = 300.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	glm::vec2 position;
	float speed;
	Color color;
	void checkTilePosition(const std::vector<std::string>& levelData,
		std::vector<glm::vec2>& collideTilePosition, float x,
		float y);
	void collideWithTile(glm::vec2 tilePos);
public:
	glm::vec2 getPosition() const {
		return position;
	}
	virtual void update(
		const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies) =0;//?
	void draw(SpriteBatch& spritebatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	Agent();
	virtual ~Agent();
};


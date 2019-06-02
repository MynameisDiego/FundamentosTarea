#include "Agent.h"
#include "ResourceManager.h"
#include "Level.h"
#include <algorithm>
#include <iostream>

Agent::Agent()
{
}

void Agent::draw(SpriteBatch& spritebatch) {
	static int textureID =
		ResourceManager::getTexture("Textures/circle.png").id;
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, AGENT_WIDTH, AGENT_WIDTH);
	spritebatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePosition;
	checkTilePosition(levelData, collideTilePosition, position.x, position.y);

	checkTilePosition(levelData, collideTilePosition, 
				position.x + AGENT_WIDTH, position.y);
	checkTilePosition(levelData, collideTilePosition, 
				position.x, position.y+AGENT_WIDTH);
	checkTilePosition(levelData, collideTilePosition, 
				position.x + AGENT_WIDTH, position.y + AGENT_WIDTH);
	if (collideTilePosition.size() == 0)return false;
	
	for (size_t i = 0; i < collideTilePosition.size(); i++)
	{
		collideWithTile(collideTilePosition[i]);
	}
	return true;
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collideTilePosition, float x,
	float y) {
	glm::vec2 cornesPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y/(float)TILE_WIDTH)
		);
	
	if (cornesPos.x < 0 || cornesPos.x >= levelData[0].size()
		|| cornesPos.y < 0 || cornesPos.y >= levelData.size()
		) {
		return;
	}
	
	if (levelData[cornesPos.y][cornesPos.x] != '.') {
		collideTilePosition.push_back(cornesPos*(float)TILE_WIDTH
			+ glm::vec2((float)TILE_WIDTH/2.0f));
	}
}

void Agent::collideWithTile(glm::vec2 tilePos) {
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerPosition = position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distvec = centerPosition - tilePos;
	float xdepth = MIN_DISTANCE - abs(distvec.x);
	float ydepth = MIN_DISTANCE - abs(distvec.y);

	if (xdepth > 0 || ydepth > 0) {
		if (std::max(xdepth,0.0f) < std::max(ydepth,0.0f)) {
			if (distvec.x < 0) {
				position.x -= xdepth;
			}
			else {
				position.x += xdepth;
			}
		}
		else {
			if (distvec.y < 0) {
				position.y -= ydepth;
			}
			else {
				position.y += ydepth;
			}
		}
	}
}

Agent::~Agent()
{
}

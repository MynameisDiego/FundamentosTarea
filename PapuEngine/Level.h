#pragma once
#include <string>
#include <vector>
#include "SpriteBatch.h"
using namespace std;

const int TILE_WIDTH = 64;

class Level
{
private:
	vector<string> levelData;
	int numHumans;
	int numZombies;
	void parseLevel();
public:
	glm::vec2 playerPosition;
	glm::vec2 zombiePosition;
	vector<glm::vec2> zombiesPosition;

	glm::vec2 getPlayerPosition()const {
		return playerPosition;
	}
	vector<glm::vec2> getZombiesPosition()const {
		return zombiesPosition;
	}
	vector<string> getLevelData()const {
		return levelData;
	}

	int getWidth() const {
		return TILE_WIDTH;
	}
	int getHeight() const {
		return TILE_WIDTH;
	}

	int getNumHumans()const {
		return numHumans;
	}
	int getNumZombies()const {
		return numZombies;
	}
	Level(const string& fileName);
	void draw();
	SpriteBatch spritebatch;
	~Level();
};


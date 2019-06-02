#include "Level.h"
#include <fstream>
#include "ResourceManager.h"
#include "Error.h"


Level::Level(const string &fileName)
{
	ifstream file;
	file.open(fileName);
	if (file.fail()) {
		fatalError("no abre el archivo " + fileName);
	}

	string tmp;
	file >> tmp >> numHumans;
	//numZombies = numHumans - 100;
	getline(file, tmp);
	while (getline(file, tmp)) {
		levelData.push_back(tmp);
	}
	parseLevel();
}

void Level::parseLevel() {
	spritebatch.init();
	spritebatch.begin();
	glm::uvec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	for (size_t i = 0; i < levelData.size(); i++)
	{
		for (size_t j = 0; j < levelData[i].size(); j++)
		{
			char tile = levelData[i][j];
			glm::vec4 destRect
				(j*TILE_WIDTH, i*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R':
			case 'B':
				spritebatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f, color
				);
				break;
			case 'G':
				spritebatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f, color
				);
				break;
			case 'L':
				spritebatch.draw(destRect, uvRect,
					ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.0f, color
				);
				break;
			case '@':
				levelData[i][j] = '.';
				playerPosition.x = j* TILE_WIDTH;
				playerPosition.y = i* TILE_WIDTH;
				break;
			case 'Z':
				levelData[i][j] = '.';
				zombiePosition.x = j* TILE_WIDTH;
				zombiePosition.y = i* TILE_WIDTH;
				zombiesPosition.push_back(zombiePosition);
				numZombies ++;
				break;
			case '.':
				break;
			default:
				break;
			}
		}
	}
	spritebatch.end();
}

void Level::draw() {
	spritebatch.renderBatch();
}


Level::~Level()
{
}

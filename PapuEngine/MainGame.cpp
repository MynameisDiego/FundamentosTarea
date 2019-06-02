#include "MainGame.h"
#include "Sprite.h"
#include "ImageLoader.h"
#include <iostream>
#include "PapuEngine.h"
#include <random>
#include <ctime>

using namespace std;

void MainGame::run() {
	init();

	update();
}

void MainGame::init() {
	Papu::init();
	_window.create("Engine", _witdh, _height, 0);
	initShaders();
	initLevel();
}

void MainGame::initLevel() {
	currentLevel = 0;
	levels.push_back(new Level("Level/level1.txt"));
	spritebatch.init();
	player = new Player();
	player->init(10.0f, 
			levels[currentLevel]->getPlayerPosition(),
		&inputManager);

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_int_distribution<int> randomX(
		1, levels[currentLevel]->getWidth() - 2
	);
	std::uniform_int_distribution<int> randomY(
		1, levels[currentLevel]->getHeight() - 2
	);

	for (int i = 0; i < 
			levels[currentLevel]->getNumHumans(); i++)
	{
		humans.push_back(new Human());
		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		humans.back()->init(10.0f, pos);

	}
	
}

void MainGame::initShaders() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}




void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();

	glActiveTexture(GL_TEXTURE0);

	/*GLuint timeLocation =
		_program.getUniformLocation("time");

	glUniform1f(timeLocation,_time);*/

	GLuint pLocation =
		_program.getUniformLocation("P");

	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);


	spritebatch.begin();
	levels[currentLevel]->draw();
	player->draw(spritebatch);

	/*
	string dir = "Textures/keen.png"; 
	if (inputManager.isKeyPressed(SDLK_o)) {
	player->drawimage(spritebatch, dir);
	}*/
	/*
	string dir = "Textures/keen.png";
	if (inputManager.isKeyPressed(SDLK_o)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randomX(
			1, levels[currentLevel]->getWidth() - 2
		);
		std::uniform_int_distribution<int> randomY(
			1, levels[currentLevel]->getHeight() - 2
		);

		glm::vec2 pos(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH);
		imgs->init(pos);
	}*/
	//imgs->drawimage(spritebatch, dir);
	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i]->draw(spritebatch);
	}
	/*
		for (size_t i = 0; i < imgs.size(); i++)
		{
			imgs[i]->drawimage(spritebatch, imgs[i]->getDir());
		}*/
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->draw();
	}
	spritebatch.end();
	spritebatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	
	_program.unuse();
	
	_window.swapBuffer();
}

void MainGame::procesInput() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				inputManager.setMouseCoords(event.motion.x,
					event.motion.y);
			break;
			case SDL_KEYUP:
				inputManager.releaseKey(event.key.keysym.sym);
				break;
			case  SDL_KEYDOWN:
				inputManager.pressKey(event.key.keysym.sym);
				break;
		}
	}
	handleInput();

}

void MainGame::handleInput()
{
	const float CAMERA_SPEED = 0.02;
	const float SCALE_SPEED = 0.01f;
	
	if (inputManager.isKeyPressed(SDLK_q)) {
		_camera.setScale(_camera.getScale() + SCALE_SPEED);
	}
	if (inputManager.isKeyPressed(SDLK_e)) {
		_camera.setScale(_camera.getScale() - SCALE_SPEED);
	}

	if (inputManager.isKeyPressed(SDLK_a)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randomX(
			1, levels[currentLevel]->getWidth() - 2
		);
		std::uniform_int_distribution<int> randomY(
			1, levels[currentLevel]->getHeight() - 2
		);
		_sprites.push_back(new Sprite());
		_sprites.back()->init(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH,
			_witdh / 2,
			_witdh / 2,
			"Textures/torterra.png");
	}
	if (inputManager.isKeyPressed(SDLK_b)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randomX(
			1, levels[currentLevel]->getWidth() - 2
		);
		std::uniform_int_distribution<int> randomY(
			1, levels[currentLevel]->getHeight() - 2
		);
		_sprites.push_back(new Sprite());
		_sprites.back()->init(randomX(randomEngine)*TILE_WIDTH,
			randomY(randomEngine)*TILE_WIDTH,
			_witdh / 2,
			_witdh / 2,
			"Textures/dd.png");
	}
	if (inputManager.isKeyPressed(SDLK_c)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randomX(
			1, levels[currentLevel]->getWidth() - 2
		);
		std::uniform_int_distribution<int> randomY(
			1, levels[currentLevel]->getHeight() - 2
		);
		_sprites.push_back(new Sprite());
		_sprites.back()->init(randomX(randomEngine)*TILE_WIDTH, 
			randomY(randomEngine)*TILE_WIDTH,
			_witdh / 2,
			_witdh / 2,
			"Textures/strange.png");
	}
	if (inputManager.isKeyPressed(SDLK_d)) {
		std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randomX(
			1, levels[currentLevel]->getWidth() - 2
		);
		std::uniform_int_distribution<int> randomY(
			1, levels[currentLevel]->getHeight() - 2
		);
		_sprites.push_back(new Sprite());
		_sprites.back()->init(randomX(randomEngine)*TILE_WIDTH, 
			randomY(randomEngine)*TILE_WIDTH,
			_witdh / 2, 
			_witdh / 2, "Textures/globox.png");
	}
}

void MainGame::update() {

	while (_gameState != GameState::EXIT) {
		procesInput();
		draw();
		_camera.update();
		_time += 0.002f;
		_camera.setPosition(player->getPosition());
		updateElements();
	}
}

void MainGame::updateElements() {
	player->update(levels[currentLevel]->getLevelData(),
		humans, zombies);

	for (size_t i = 0; i < humans.size(); i++)
	{
		humans[i]->update(levels[currentLevel]->getLevelData(),
			humans, zombies);
	}
}

MainGame::MainGame(): 
					  _witdh(800),
					  _height(600),
					  _gameState(GameState::PLAY),
					  _time(0)
{
	_camera.init(_witdh, _height);
}


MainGame::~MainGame()
{
}

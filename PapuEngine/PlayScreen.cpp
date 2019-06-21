#include "PlayScreen.h"
#include "Game.h"
#include "MyScreens.h"
#include <random>
#include <ctime>
#include <SDL\SDL.h>

#include <iostream>

using namespace std;

PlayScreen::PlayScreen(Window* window) :_window(window)
{
}


PlayScreen::~PlayScreen()
{
}

void PlayScreen::initGUI() {
	_hudBach.init();
	_hudCamera.init(_window->getScreenWidth(),
		_window->getScreenHeight());
	_hudCamera.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));
	background = new Background("Textures/game.png");
}

void PlayScreen::initSystem() {
	_program.compileShaders("Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt");
	_program.addAtribute("vertexPosition");
	_program.addAtribute("vertexColor");
	_program.addAtribute("vertexUV");
	_program.linkShader();
}

void PlayScreen::destroy() {
	delete background;
}

void PlayScreen::onExit() {}

void PlayScreen::onEntry() {
	initSystem();

	_camera2D.init(_window->getScreenWidth(),
		_window->getScreenHeight());

	_camera2D.setPosition(glm::vec2(
		_window->getScreenWidth() / 2.0f,
		_window->getScreenHeight() / 2.0f));

	_spriteBatch.init();

	player = new Gamer(106, 79,
		glm::vec2(200, 200), "Textures/Player.png",
		&_game->_inputManager);

	initGUI();

}



void PlayScreen::update() {
	_camera2D.update();
	player->update();

	_elapsed += 0.1f;

	if (player->gettecla() == 1 && player->getPosition().x < 0) {
		player->setPosition(glm::vec2(760 - (106 - (player->getPosition().x + 106)), (player->getPosition().y)));
	}
	if (player->gettecla() == 2 && player->getPosition().x + 106 > 760) {
		player->setPosition(glm::vec2(0, (player->getPosition().y)));
	}

	if (player->getPosition().y < 0) {
		player->setPosition(glm::vec2((player->getPosition().x), 0));
	}
	if (player->getPosition().y + 79 > 500) {
		player->setPosition(glm::vec2(player->getPosition().x, player->getPosition().y+79==500     )  );
	}

	if (_elapsed >= 20.0f) {
		std::mt19937 randomEngine;
		randomEngine.seed(time(nullptr));
		std::uniform_real_distribution<float>
			randX(0, _window->getScreenWidth());

		int x = int(randX(randomEngine));

		_asteroids.push_back(new Asteroid(50, 50, glm::vec2(x, _window->getScreenHeight()), "Textures/asteroid.png"));
		_elapsed = 0;
	}
	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		if (_asteroids[i]->getPosition().y + 50 < 0)
		{
			_asteroids.erase(_asteroids.begin() + i);
		}
	}
	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		_asteroids[i]->update();
	}
	checkInput();
}

void PlayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		_game->onSDLEvent(event);
	}
}

void PlayScreen::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint imageLocation = _program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	_spriteBatch.begin();
	background->draw(_spriteBatch);
	player->draw(_spriteBatch);
	for (size_t i = 0; i < _asteroids.size(); i++)
	{
		_asteroids[i]->draw(_spriteBatch);
	}
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	drawHUD();
	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();
}

void PlayScreen::drawHUD() {
	GLuint pLocation = _program.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera2D.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	char buffer[256];
	_hudBach.begin();

	_hudBach.end();
	_hudBach.renderBatch();
}

void PlayScreen::build() {}

int PlayScreen::getPreviousScreen() const {
	return SCREEN_INDEX_MENU;
}

int PlayScreen::getNextScreen() const {
	return SCREEN_INDEX_OVER;
}

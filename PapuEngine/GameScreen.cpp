#include "GameScreen.h"
#include "ScreenIndices.h"

GameScreen::~GameScreen()
{
}

GameScreen::GameScreen(Window * _window) :window(_window)
{
	screenIndex = SCREEN_INDEX_GAME;
}

void GameScreen::build()
{
}

void GameScreen::destroy()
{
}

void GameScreen::onExit()
{
}

void GameScreen::onEntry()
{
}

void GameScreen::draw()
{
}

void GameScreen::update()
{
}

void GameScreen::initSystem()
{
}

int GameScreen::getNextScreen() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameScreen::getPreviousScreen() const
{
	return SCREEN_INDEX_MENU;
}

void GameScreen::checkInput()
{
}

#pragma once
#include <algorithm>
#include "Game.h"
#include "MenuScreen.h"
#include "PlayScreen.h"
class App : public Game
{
public:
	App();
	~App();
	virtual void setScreen(int index) override;
	virtual void onInit() override;
	virtual void addScreens() override;
	virtual void onExit() override;
private:
	std::unique_ptr<MenuScreen> _menuScreen;
	std::unique_ptr<PlayScreen> _playScreen;
};


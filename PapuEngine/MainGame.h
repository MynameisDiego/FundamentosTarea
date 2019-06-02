#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GLS_Program.h"
#include "Sprite.h"
#include "Window.h"
#include "Camera2D.h"
#include <vector>
#include "InputManager.h"
#include "SpriteBatch.h"
#include "Level.h"
#include "Player.h"
#include "Zombie.h"
#include "Human.h"

enum class GameState
{
	PLAY, EXIT
};


class MainGame
{
private:
	int _witdh;
	int _height;
	float _time;
	Window _window;
	void init();
	Player* player;
	void procesInput();
	void handleInput();
	GLS_Program _program;
	vector<Sprite*> _sprites;
	Camera2D _camera;
	SpriteBatch spritebatch;
	InputManager inputManager;
	vector<Level*> levels;
	vector<Zombie*> zombies;
	vector<Human*> humans;
	void updateElements();
	int currentLevel;
	void initLevel();
	
public:
	MainGame();
	~MainGame();
	GameState _gameState;
	void initShaders();
	void run();
	void draw();
	void update();
};


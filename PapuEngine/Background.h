#pragma once
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>
using namespace std;

class Background
{
private:
	string texture;
	ColorRGBA color;
	int textureID;
public:
	Background(string _texture);
	void draw(SpriteBatch& spriteBatch);
	void setColor(ColorRGBA _color);
	ColorRGBA getColor() const {
		return color;
	}
	~Background();
};


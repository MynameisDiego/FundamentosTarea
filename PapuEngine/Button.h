#pragma once
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <glm\glm.hpp>
#include <string>


using namespace std;

class Button
{
private:
	string texture;
	ColorRGBA color;
	int textureID;
	bool clicked;
	glm::vec2 position;
public:
	void setClicked(bool _clicked) {
		clicked = _clicked;
	}
	bool getClicked()const {
		return clicked;
	}
	Button(string _texture);
	void draw(SpriteBatch& spriteBatch);
	void setColor(ColorRGBA _color);
	ColorRGBA getColor() const {
		return color;
	}
	bool click(glm::vec2 _position);
	~Button();
};


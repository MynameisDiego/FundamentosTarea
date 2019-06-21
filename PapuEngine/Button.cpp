#include "Button.h"
#include "ResourceManager.h";


Button::Button(std::string _texture)
	:texture(_texture), clicked(false)
{
	position = glm::vec2(200, 100);
	textureID
		= ResourceManager::getTexture(texture).id;
	color.set(255, 255, 255, 255);
}

void Button::draw(SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(position.x, position.y, 190, 50);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Button::setColor(ColorRGBA _color) {
	color = _color;
}

bool Button::click(glm::vec2 _position)
{
	bool result = (_position.x > position.x)
		&& (_position.x < position.x + 190)
		&& (500 - _position.y > position.y)
		&& (500 - _position.y < position.y + 50);
	return result;
}

Button::~Button()
{
}

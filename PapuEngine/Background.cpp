#include "Background.h"
#include "ResourceManager.h";


Background::Background(std::string _texture)
			:texture(_texture)
{
	textureID 
		= ResourceManager::getTexture(texture).id;
	color.set(255, 255, 255, 255);
}

void Background::draw(SpriteBatch& spriteBatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 desctRect(0, 0, 800, 600);
	spriteBatch.draw(desctRect, uvRect, textureID, 0.0f, color);
}

void Background::setColor(ColorRGBA _color) {
	color = _color;
}



Background::~Background()
{
}

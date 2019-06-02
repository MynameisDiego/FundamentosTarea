#pragma once
#include <GL\glew.h>
#include "Vertex.h"
#include <glm\glm.hpp>
#include <vector>

enum class GlypSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class Glyph {
public:
	Glyph() {}
	Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint _texture, float _depth, const Color& color) {
		texture = _texture;
		depth = _depth;

		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	}
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class Renderbatch {
public:
	Renderbatch(GLuint offset, GLuint numVertixex, GLuint texture);
	GLuint _offset;
	GLuint _numVertices;
	GLuint _texture;
};


class SpriteBatch
{
private:
	GLuint vbo;
	GLuint vao;
	std::vector<Glyph> glyphs;
	std::vector<Renderbatch> renderbatches;
	std::vector<Glyph*> glyphsPointers;
	void createVertexArray();
	void sortGlyph();
	void createRenderBatches();
public:
	void init();
	void begin(GlypSortType sortGlyph = GlypSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& ColorRGBA);
	void renderBatch();
	GlypSortType sortType;
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
	SpriteBatch();
	~SpriteBatch();
};


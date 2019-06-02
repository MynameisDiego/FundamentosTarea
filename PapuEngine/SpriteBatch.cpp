#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() :vbo(0), vao(0)
{
}

void SpriteBatch::init() {
	createVertexArray();
}

void SpriteBatch::begin(GlypSortType sortType) {
	sortType = sortType;
	renderbatches.clear();
	glyphs.clear();
}
void SpriteBatch::end() {
	glyphsPointers.resize(glyphs.size());
	for (size_t i = 0; i < glyphs.size(); i++)
	{
		glyphsPointers[i] = &glyphs[i];
	}
	sortGlyph();
	createRenderBatches();
}

void SpriteBatch::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.empty()) {
		return;
	}
	int cv = 0;
	int ofset = 0;
	renderbatches.emplace_back(ofset, 6, glyphsPointers[0]->texture);
	vertices[cv++] = glyphsPointers[0]->topLeft;
	vertices[cv++] = glyphsPointers[0]->bottomLeft;
	vertices[cv++] = glyphsPointers[0]->bottomRight;
	vertices[cv++] = glyphsPointers[0]->bottomRight;
	vertices[cv++] = glyphsPointers[0]->topRight;
	vertices[cv++] = glyphsPointers[0]->topLeft;
	ofset += 6;


	for (int cg = 1; cg < glyphsPointers.size(); cg++)
	{
		if (glyphsPointers[cg]->texture != glyphsPointers[cg - 1]->texture) {
			renderbatches.emplace_back(ofset, 6, glyphsPointers[cg]->texture);
		}
		else {
			renderbatches.back()._numVertices += 6;
		}

		vertices[cv++] = glyphsPointers[cg]->topLeft;
		vertices[cv++] = glyphsPointers[cg]->bottomLeft;
		vertices[cv++] = glyphsPointers[cg]->bottomRight;
		vertices[cv++] = glyphsPointers[cg]->bottomRight;
		vertices[cv++] = glyphsPointers[cg]->topRight;
		vertices[cv++] = glyphsPointers[cg]->topLeft;
		ofset += 6;

	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),vertices.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatch() {
	glBindVertexArray(vao);
	for (int i = 0; i < renderbatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderbatches[i]._texture);
		glDrawArrays(GL_TRIANGLES, renderbatches[i]._offset, renderbatches[i]._numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& ColorRGBA) {
	glyphs.emplace_back(destRect, uvRect, texture, depth, ColorRGBA);
}

void SpriteBatch::sortGlyph() {
	switch (sortType)
	{
	case GlypSortType::BACK_TO_FRONT:
		std::stable_sort(glyphsPointers.begin(), glyphsPointers.end(), compareBackToFront);
		break;
	case GlypSortType::FRONT_TO_BACK:
		std::stable_sort(glyphsPointers.begin(), glyphsPointers.end(), compareFrontToBack);
		break;
	case GlypSortType::TEXTURE:
		std::stable_sort(glyphsPointers.begin(), glyphsPointers.end(), compareTexture);
		break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}

void SpriteBatch::createVertexArray() {
	if (vao == 0) {
		glGenVertexArrays(1, &vao);
	}
	glBindVertexArray(vao);
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
		(void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
}


SpriteBatch::~SpriteBatch()
{
}
Renderbatch::Renderbatch(GLuint offset, GLuint numVertixex, GLuint texture) :_offset(offset), _numVertices(numVertixex), _texture(texture)
{
}
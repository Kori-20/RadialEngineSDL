#pragma once
#include "Core/Core.h"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "Aid/Transform.h"
#include <array>

class RE_API Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

	static void Init(Vector2D windowDimenssions);
	static void Unbind();

	static void RenderStart();
	static void RenderEnd();
	static void CleanBinds();

	static void RenderChar(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const glm::vec4& uv, Vector2D scale);

	static void ShutDown();

	static void LinkAtributes(GLuint ID, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset);
	static void CheckQuads(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const Vector2D& scale, const std::array<Vector2D, 4>& UVs);
	static void CheckQuads(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const Vector2D& scale);
	static void DrawQuad(float textureIndex, const glm::vec2& position, const glm::vec2& texCoord, const Vector2D& rendQuad);
};


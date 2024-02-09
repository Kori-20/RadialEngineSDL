#include "Renderer.h"
#include "TextureManager.h"
#include "Aid/Logger.h"

#pragma region Declarations
static const size_t maxQuads = 1000;
static const size_t maxVertices = maxQuads * 4;//Each quad has 4 vertices
static const size_t maxIndices = maxQuads * 6;//Each quad has 6 indices (2 triangles)
static const size_t maxTextures = 32;

struct VertexGL
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCoord;
	float TexID;
};

struct RenderData
{
	GLuint VAOID = 0;//Vertex Array Object 	
	GLuint VBOID = 0;//Vertex Buffer Object 
	GLuint EBOID = 0;//Element Buffer Object (Index Buffer Object)

	uint32_t IndexCount = 0;//Number of indices in the buffer

	VertexGL* QuadBuffer = nullptr;//Base pointer to the quad buffer
	VertexGL* QuadBufferPtr = nullptr;//Pointer to the current quad in the buffer

	std::array<uint32_t, maxTextures> TextureSlots;//Texture slots

	uint32_t textureSlotIndex = 1;//0 is reserved for white texture aka no texture/null texture
};

static RenderData rData;


float windowWidth, windowHeight;
#pragma endregion

void Renderer::Init(Vector2D windowDimenssions)
{
	rData.QuadBuffer = new VertexGL[maxVertices];

	windowWidth = windowDimenssions.x;
	windowHeight = windowDimenssions.y;

	//Buffers
	glCreateVertexArrays(1, &rData.VAOID);
	glBindVertexArray(rData.VAOID);

	glCreateBuffers(1, &rData.VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, rData.VBOID);
	glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(VertexGL), nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexArrayAttrib(rData.VAOID, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexGL), (const void*)offsetof(VertexGL, Position));

	glEnableVertexArrayAttrib(rData.VAOID, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexGL), (const void*)offsetof(VertexGL, Color));

	glEnableVertexArrayAttrib(rData.VAOID, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexGL), (const void*)offsetof(VertexGL, TexCoord));

	glEnableVertexArrayAttrib(rData.VAOID, 3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexGL), (const void*)offsetof(VertexGL, TexID));

	uint32_t indices[maxIndices];
	uint32_t offset = 0;

	for (GLsizeiptr i = 0; i < maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	glCreateBuffers(1, &rData.EBOID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rData.EBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	for (GLsizeiptr i = 0; i < maxTextures; i++)
	{
		rData.TextureSlots[i] = 0;
	}

	Unbind();
	//RenderStart();
}

void Renderer::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::RenderStart()
{
	rData.QuadBufferPtr = rData.QuadBuffer;
}

void Renderer::RenderEnd()
{
	GLsizeiptr size = (uint8_t*)rData.QuadBufferPtr - (uint8_t*)rData.QuadBuffer;

	glBindBuffer(GL_ARRAY_BUFFER, rData.VBOID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, rData.QuadBuffer);
}

void Renderer::CleanBinds()
{
	for (uint32_t i = 0; i < rData.textureSlotIndex; i++)
	{
		glBindTextureUnit(i, rData.TextureSlots[i]);
	}

	glBindVertexArray(rData.VAOID);
	glDrawElements(GL_TRIANGLES, rData.IndexCount, GL_UNSIGNED_INT, nullptr);

	rData.IndexCount = 0;
	rData.textureSlotIndex = 1;
}

void Renderer::RenderChar(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const glm::vec4& uv, Vector2D scale) {
	// Convert world coordinates to clip space coordinates
	glm::vec2 clipSpacePosition = 
	{
		2.0f * position.x / windowWidth - 1.0f,
		1.0f - 2.0f * position.y / windowHeight
	};

	// Calculate the vertex positions for the character quad
	glm::vec2 topLeft = clipSpacePosition;
	glm::vec2 bottomRight = clipSpacePosition + size;

	// Create the UV coordinates array for the character
	std::array<Vector2D, 4> UVs = {
		{ Vector2D(uv.x, uv.w), Vector2D(uv.z, uv.w), Vector2D(uv.z, uv.y), Vector2D(uv.x, uv.y) }
	};

	// Call the existing CheckQuads method to draw the character
	CheckQuads(position, size, textureID, scale, UVs);
}



void Renderer::ShutDown()
{
	glDeleteVertexArrays(1, &rData.VAOID);
	glDeleteBuffers(1, &rData.VBOID);
	glDeleteBuffers(1, &rData.EBOID);

	delete[] rData.QuadBuffer;
	Logger::Issue("Renderer shut down");
}

void Renderer::LinkAtributes(GLuint ID, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset)
{
	glEnableVertexArrayAttrib(ID, layout);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
}

//Used with sprite
void Renderer::CheckQuads(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const Vector2D& renderSize,const std::array<Vector2D, 4>& UVs)
{
	//Check if the buffer is full
	if (rData.IndexCount >= maxIndices || rData.textureSlotIndex > maxTextures - 1)
	{
		RenderEnd(); //Update the buffer with the new data
		CleanBinds();//Bind the textures and draw the quads
		RenderStart();//Reset the buffer
	}
	
	float textureIndex = 0.0f;

	// Checks if Texture is already bound and being used by another quad
	for (uint32_t i = 1; i < rData.textureSlotIndex; i++)
	{
		if (rData.TextureSlots[i] == textureID)
		{
			textureIndex = (float)i;
			break;
		}
	}

	// Else, bind the Texture to a new quad
	if (textureIndex == 0.0f)
	{
		textureIndex = (float)rData.textureSlotIndex;
		rData.TextureSlots[rData.textureSlotIndex] = textureID;
		rData.textureSlotIndex++;
	}

	float x = (2.0f * position.x) / windowWidth - 1.0f;
	float y = 1.0f - (2.0f * position.y) / windowHeight;

	if (rData.QuadBufferPtr == nullptr) 
	{
		Logger::Issue("Quad buffer pointer is null");
	}

	//Draw the quad
	for (size_t i = 0; i < 4; i++)
	{
		rData.QuadBufferPtr->Position = { x + (size.x * renderSize.x) * (i == 1 || i == 2), y + (size.y * renderSize.y) * (i == 2 || i == 3), 0.0f };
		rData.QuadBufferPtr->Color = { 1.0f, 1.0f, 1.0f };
		rData.QuadBufferPtr->TexCoord = { UVs[i].x, UVs[i].y };
		rData.QuadBufferPtr->TexID = textureIndex;
		rData.QuadBufferPtr++;
	}

	rData.IndexCount += 6;
}

void Renderer::CheckQuads(const glm::vec2& position, const glm::vec2& size, uint32_t textureID, const Vector2D& scale)
{
	if (rData.IndexCount >= maxIndices || rData.textureSlotIndex > maxTextures - 1)
	{
		RenderEnd();
		CleanBinds();
		RenderStart();
	}
	//	texture_size = rendQuad;
	float textureIndex = 0.0f;

	// Checks if Texture is already bound and being used by another quad
	for (uint32_t i = 1; i < rData.textureSlotIndex; i++)
	{
		if (rData.TextureSlots[i] == textureID)
		{
			textureIndex = static_cast<float>(i);
			break;
		}
	}

	// Else, bind the Texture to a new quad
	if (textureIndex == 0.0f)
	{
		textureIndex = static_cast<float>(rData.textureSlotIndex);
		rData.TextureSlots[rData.textureSlotIndex] = textureID;
		rData.textureSlotIndex++;
	}

	float x = (2.0f * position.x) / windowWidth - 1.0f;
	float y = 1.0f - (2.0f * position.y) / windowHeight;

	DrawQuad(textureIndex, { x, y }, { 0.0f, 0.0f }, scale); // Lower Left
	DrawQuad(textureIndex, { x + size.x, y }, { 1.0f, 0.0f }, scale); // Lower Right
	DrawQuad(textureIndex, { x + size.x, y + size.y }, { 1.0f, 1.0f }, scale); // UpPer Right
	DrawQuad(textureIndex, { x, y + size.y }, { 0.0f, 1.0f }, scale); // Upper Left

	rData.IndexCount += 6;
}

//Draw based on UV's
void Renderer::DrawQuad(float textureIndex, const glm::vec2& position, const glm::vec2& texCoord, const Vector2D& scale)
{
	rData.QuadBufferPtr->Position = { position.x, position.y, 0.0f };
	rData.QuadBufferPtr->Color = { 1.0f, 1.0f, 1.0f };
	rData.QuadBufferPtr->TexCoord = { texCoord.x * scale.x, texCoord.y * scale.y };
	rData.QuadBufferPtr->TexID = textureIndex;
	rData.QuadBufferPtr++;
}

#include "Font.h"
#include <iostream>
#include <stb/stb_image.h>
#include "Render/Renderer.h"
#include "Aid/Logger.h"

Font::Font(const std::string& fontPath) {
    SetFont(fontPath);
}

Font::Font()
{
}

Font::~Font() {
    // Cleanup if necessary
}

void Font::LoadFontMetrics() {
    // Calculate and store UV coordinates for each character
    for (char c : m_Format) {
        Vector2D indexPos = GetPositionIndexForChar(c);
        float u = (float)indexPos.x / m_Columns;
        float v = (float)indexPos.y / m_Rows;
        //og//m_CharacterMap[c] = glm::vec4(u, v, u + 1.0f / m_Columns, v + 1.0f / m_Rows);
        m_CharacterMap[c] = glm::vec4(u, v, u + 1.0f / m_Columns, v + 1.0f / m_Rows);
    }
}

glm::vec4 Font::GetCharacterUVs(char c) {
    auto it = m_CharacterMap.find(c);
    if (it != m_CharacterMap.end()) 
    {
        //std::cout << "Character found" << it->first << std::endl;
        return it->second;
    }
    return glm::vec4(0.0f); // Default to black rectangle
}

void Font::RenderText(const std::string& text, float x, float y, Vector2D scale, int spacing) {
    // Define a constant for character spacing
    const float characterSpacing = spacing * scale.x; // Adjust this value as needed

    // Render each character of the text
    for (auto c : text) {
        glm::vec4 uvs = GetCharacterUVs(c);
        // Check if UVs were successfully retrieved
        if (uvs != glm::vec4(0.0f)) {
            // Draw a quad with the texture coordinates from uvs
            // Adjust the size and position based on the scale factor
            Renderer::RenderChar({ x, y }, { m_CellWidth, m_CellHeight}, m_TextureID, uvs, scale);

            // Increment x by the width of the character plus spacing
            x += (m_CellWidth + characterSpacing); // Move to the next character position
            //Logger::Display("X: " + std::to_string(x) + " Y: " + std::to_string(y));
        }
        else {
            // Handle missing character UVs, e.g., log an error or skip the character
            std::cerr << "Warning: Missing UVs for character '" << c << "'." << std::endl;
        }
    }
}



void Font::SetFont(const std::string& fontPath)
{
    // Load the texture using TextureManager
    m_TextureID = TextureManager::LoadOpenGlTexture(fontPath.c_str(), true);
    Logger::Display("FontID: " + std::to_string(m_TextureID));

    // Load the image to get dimensions
    int width, height, channels;
    unsigned char* image = stbi_load(fontPath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (image) {
        m_TextureWidth = width;
        m_TextureHeight = height;
        stbi_image_free(image);
    }
    else {
        // Handle error
    }

    // Calculate cell dimensions
    m_CellWidth = m_TextureWidth / bitSize;
    m_CellHeight = m_TextureHeight / bitSize;

    // Load font metrics
    LoadFontMetrics();
}

Vector2D Font::GetPositionIndexForChar(char c)
{
    int y = 0;
    int x = 0;
    for (int i = 0; i < m_Format.size(); ++i) {
        if (c == m_Format[i]) {
            return Vector2D(x, y);
        }
        x++;
        if (x >= m_Columns) {
            x = 0;
            y++;
        }
    }
    return Vector2D::Zero(); // Return zero vector if character is not found
}

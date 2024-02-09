#pragma once
#include <map>
#include <string>
#include "Render/TextureManager.h"
#include "Aid/Transform.h"
#include <glad/glad.h>
#include <glm/ext/vector_float4.hpp>
#include <vector>

class RE_API Font {
public:
    Font(const std::string& fontPath);
    Font();
    ~Font();

    void RenderText(const std::string& text, float x, float y, Vector2D scale = Vector2D::One(), int spacing = 2000);
    void SetFont(const std::string& fontPath);
    Vector2D GetPositionIndexForChar(char c);
    void SetBitSize(int size) { bitSize = size; }
   
private:
    GLuint m_TextureID;
    int m_TextureWidth;
    int m_TextureHeight;
    int m_CellWidth;
    int m_CellHeight;
    std::map<char, glm::vec4> m_CharacterMap;

    int bitSize = 16;

    void LoadFontMetrics();

    glm::vec4 GetCharacterUVs(char c);
protected:
    std::vector<char> m_Format = { ' ','!','"','#','$','%','&',39,
                                '(',')','*','+',',','-','.','/',
                                '0','1','2','3','4','5','6','7',
                                '8','9',':',';','<','=','>','?',
                                '€','A','B','C','D','E','F','G',
                                'H','I','J','K','L','M','N','O',
                                'P','Q','R','S','T','U','V','W',
                                'X','Y','Z','[',92,']','^','_',
                                '`','a','b','c','d','e','f','g',
                                'h','i','j','k','l','m','n','o',
                                'p','q','r','s','t','u','v','w',
                                'x','y','z','{',':','}','»','«' };
    int m_Rows = 12;
    int m_Columns = 8;
};

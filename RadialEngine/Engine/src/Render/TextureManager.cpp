#include "TextureManager.h"

#include <iostream>
#include <ostream>
#include <stb/stb_image.h>

#include "Aid/Logger.h"
#include "OpenGL/OpenGLErrorHandler.h"
#include "glad/glad.h"

// Main function to load an OpenGL texture
int TextureManager::LoadOpenGlTexture(const char* path, bool flipHorizontal)
{
    int texWidth, texHeight, texChannels;

    if (flipHorizontal)
    stbi_set_flip_vertically_on_load(0);
    else 
    stbi_set_flip_vertically_on_load(1);

    // Load the image with an alpha channel to support transparency
    unsigned char* textureData = stbi_load(path, &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    if (!textureData)
    {
        std::cout << "Failed to load texture data" << std::endl;
        return   0;
    }

    //Generate and bind the texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    OpenGLErrorHandler::ErrorCheck();
    glBindTexture(GL_TEXTURE_2D, textureID);
    OpenGLErrorHandler::ErrorCheck();

   
    //ColorKey
    const GLubyte colorKey[3] = { 255,   0,   255 };

    //RemoveColor
    for (int y = 0; y < texHeight; ++y)
    {
        for (int x = 0; x < texWidth; ++x)
        {
            int index = (y * texWidth + x) * 4;
            // Check if the pixel matches the pink color key
            if (textureData[index] == colorKey[0] &&
                textureData[index + 1] == colorKey[1] &&
                textureData[index + 2] == colorKey[2])
            {
                // Set the alpha value to   0 for transparency
                textureData[index + 3] = 0;
            }
        }
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload the processed texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    OpenGLErrorHandler::ErrorCheck();

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    OpenGLErrorHandler::ErrorCheck();

    // Free the image data
    stbi_image_free(textureData);

    return textureID;
}





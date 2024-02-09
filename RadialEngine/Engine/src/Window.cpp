#include "Window.h"

#include <glad/glad.h>

#include "Aid\InitError.h"
#include "Aid\Logger.h"
#include <sdl2/SDL.h>
#include "Level/LevelManager.h"

SDL_Window* Window::m_Window = nullptr;
SDL_Renderer* Window::m_Renderer = nullptr;

Window::Window(const char* title, int windowWidth, int windowHeight, bool bUseVSYNC)
    : m_WindowDimmensions(windowWidth, windowHeight)
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);

    // Create SDL window
    m_Window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_OPENGL
    );

    if (!m_Window)
    { // Handle window creation failure
        throw InitError("Failed to create SDL window");
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {  // Initialize SDL2
        std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl; // Handle initialization failure with class
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Check that the render was m_Window created
    if (m_Renderer == nullptr)
    {
        std::cout << "Render Creation Error: " << SDL_GetError() << std::endl;
        return;
    }

    context = SDL_GL_CreateContext(m_Window);
    m_WindowDimmensions = Vector2D(windowWidth, windowHeight);

    Logger::Warning("Window created");
}

void Window::UpdateWindow(float deltaTime) 
{
    /*
    SDL_SetRenderDrawColor(m_Renderer, 103, 121, 171, 255); 
    SDL_RenderClear(m_Renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            Clean();
        }
    }

    LevelManager::getInstance().GetCurrentLevel()->Draw(deltaTime);

    SDL_RenderPresent(m_Renderer);
    */
}

void Window::Clean() {
    // Release SDL resources
    if (m_Renderer) 
    {
        //SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }
}

Window::~Window() {

    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    }
}



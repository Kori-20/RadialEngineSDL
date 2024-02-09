#pragma once
#include "Aid/Transform.h"
#include <sdl2/SDL.h>


class Window {
public:

    Window(const char* title, int windowWidth, int windowHeight, bool bUseVSYNC);
    ~Window();

    void UpdateWindow(float deltaTime);
    void Clean();

private:
    Vector2D m_WindowDimmensions;
    static inline Window* staticWindow = nullptr;

    static struct SDL_Window* m_Window;
    static struct SDL_Renderer* m_Renderer;

public:
    static SDL_Surface* GetSurface() { return SDL_GetWindowSurface(m_Window); }
    static SDL_Renderer* GetRenderer() { return m_Renderer; }
    static SDL_Window* GetWindow() { return m_Window; }
    SDL_GLContext context;
    
    Vector2D GetWindowSize() { return m_WindowDimmensions; }
};



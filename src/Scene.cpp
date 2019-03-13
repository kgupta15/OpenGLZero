/***************************************************************************
**                                                                        **
**  OpenGLZero - Simple Engine for prototyping                            **
**  Copyright (C) 2019 Kapil Gupta                                        **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Kapil Gupta                                          **
**           E-mail: kpgupta98@gmail.com                                  **
**           Date  : 13.03.2019                                           **
****************************************************************************/
#include <GL/glew.h>
#include "Platform.h"
#include "Renderer.h"
#include "Scene.h"

Scene::Scene(std::string title) :
    m_window(nullptr),
    m_context(NULL),
    m_window_title(title)
{
    this->m_renderers.push_back(new GameRenderer());
}

bool Scene::Init(int argc, char* argv[]) 
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialize SDL video\n");
        return 0;
    }

    m_window = SDL_CreateWindow(
        this->m_window_title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL);
    if (m_window == NULL) {
        fprintf(stderr, "Failed to create main window\n");
        SDL_Quit();
        return 0;
    }

    this->InitGL();    
    for(const auto& renderer : m_renderers) {
        renderer->Init(argc, argv);
    }

    return 1;
}

bool Scene::InitGL() 
{ 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        fprintf(stderr, "Failed to create GL context\n");
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return 1;
    }

    glewExperimental = GL_TRUE;
    glewInit();
    const GLubyte *gl_renderer = glGetString(GL_RENDERER);
    const GLubyte *gl_version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", gl_renderer);
    printf("OpenGL version supported %s\n", gl_version);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);

    return 1;     
}

void Scene::Run() 
{
    bool done = false;
    while(!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window))
                done = true;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                done = true;
        }
        
        for(const auto& renderer : m_renderers) {
            renderer->Draw();
        }

        SDL_GL_SwapWindow(m_window);
    }
}

void Scene::Shutdown() {}
Scene::~Scene() {}
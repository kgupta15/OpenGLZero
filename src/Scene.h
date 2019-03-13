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
#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <vector>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Renderer.h"

class Scene {
private:
    SDL_Window              *m_window;
    SDL_GLContext            m_context;
    std::string              m_window_title;
    std::vector<Renderer*>   m_renderers;

public:
    Scene(std::string title = "OpenGLZero");
    virtual ~Scene();

    bool Init(int argc, char* argv[]);
    bool InitGL();
    void Run();
    void Shutdown();

};

#endif  // __SCENE_H__
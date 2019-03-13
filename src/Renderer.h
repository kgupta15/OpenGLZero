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
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <GL/glew.h>

class Renderer {
public:
    virtual bool Init(int argc, char* argv[]) = 0;
    virtual void Draw() = 0;

};

class GameRenderer : public Renderer {
private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_vert_shader, m_frag_shader;
    GLuint m_shader_program;

public:
    GameRenderer();
    virtual ~GameRenderer() = default;

    bool Init(int argc, char* argv[]) override;
    void Draw() override;
};

#endif  // __RENDERER_H__
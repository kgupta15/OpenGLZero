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
#include "Renderer.h"

GameRenderer::GameRenderer() :
    m_vao(0),
    m_vbo(0),
    m_vert_shader(0), 
    m_frag_shader(0),
    m_shader_program(0) {}

bool GameRenderer::Init(int argc, char* argv[]) 
{
    GLfloat points[] = { 
        -0.5f,  0.5f, 0.0f, 
         0.5f,  0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    glGenBuffers( 1, &m_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( GLfloat ), points, GL_STATIC_DRAW );
    // vao
    glGenVertexArrays( 1, &m_vao );
    glBindVertexArray( m_vao );
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    
    
    const char *vertex_shader = "#version 410\n"
                                "in vec3 vp;"
                                "void main () {"
                                "  gl_Position = vec4(vp, 1.0);"
                                "}";

    const char *fragment_shader = "#version 410\n"
                                  "out vec4 frag_colour;"
                                  "void main () {"
                                  "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
                                  "}";

    m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vert_shader, 1, &vertex_shader, NULL);
    glCompileShader(m_vert_shader);
    m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_frag_shader, 1, &fragment_shader, NULL);
    glCompileShader(m_frag_shader);
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, m_frag_shader);
    glAttachShader(m_shader_program, m_vert_shader);
    glLinkProgram(m_shader_program);
    return 1;
}

void GameRenderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_shader_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glUseProgram(0);
}
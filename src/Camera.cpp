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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include "Platform.h"
#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) :
    m_fov(FOV),
    m_near_plane(NEAR_PLANE),
    m_far_plane(FAR_PLANE),
    m_viewport_aspect_ratio(WINDOW_WIDTH/WINDOW_HEIGHT),
    m_camera_speed(CAMERA_SPEED)
{
    this->m_position = position;
    this->m_direction = direction;
    this->m_up_vector = up;
}

Camera::Camera(float posX, float posY, float posZ, float directionX, float directionY, float directionZ, float upX, float upY, float upZ) :
    m_fov(FOV),
    m_near_plane(FAR_PLANE),
    m_far_plane(FAR_PLANE),
    m_viewport_aspect_ratio(WINDOW_WIDTH / WINDOW_HEIGHT),
    m_camera_speed(CAMERA_SPEED)
{
    this->m_position = glm::vec3(posX, posY, posZ);
    this->m_up_vector = glm::vec3(upX, upY, upZ);
}

glm::vec3 Camera::GetPosition() const { return this->m_position; }
void Camera::SetPosition(const glm::vec3& position) { this->m_position = position; }
void Camera::OffsetPosition(const glm::vec3& offset_value) { this->m_position += offset_value; }

glm::vec3 Camera::GetDirection() const { return this->m_direction; }
void Camera::SetDirection(const glm::vec3& direction) { this->m_direction = direction; }

float Camera::GetFieldOfView() const { return this->m_fov; }
void Camera::SetFieldOfView(float fov) { this->m_fov = fov; }

float Camera::GetNearPlane() const { return this->m_near_plane; }
void Camera::SetNearPlane(float near_plane) { this->m_near_plane = near_plane; }
float Camera::GetFarPlane() const { return this->m_far_plane; }
void Camera::SetFarPlane(float far_plane) { this->m_far_plane = far_plane; }
void Camera::SetNearFarPlanes(float near_plane, float far_plane) 
{
    this->m_near_plane = near_plane;
    this->m_far_plane = far_plane;
}

float Camera::GetViewportAspectRatio() const { return this->m_viewport_aspect_ratio; }
void Camera::SetViewportAspectRatio(float viewport_aspect_ratio) {}

float Camera::GetCameraSpeed() const { return this->m_camera_speed; }
void Camera::SetCameraSpeed(float speed) { this->m_camera_speed = speed; }

// TODO: Fix camera motion and add mouse control
void Camera::UpdateLookAt()
{
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        glm::vec3 camera_position = glm::vec3(0.0f, -300.0f, -500.0f);
        glm::vec3 direction = glm::normalize(camera_position - (camera_position + glm::vec3(0.0f, 0.0f, -1.0f)));
        this->m_position += this->m_camera_speed * direction;
        this->m_direction += this->m_camera_speed * direction;
    }

    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
        this->m_position += this->m_camera_speed * direction;
        this->m_direction += this->m_camera_speed * direction;
    }

    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        glm::vec3 direction = glm::vec3(-1.0f, 0.0f, 0.0f);
        this->m_position += this->m_camera_speed * direction;
        this->m_direction += this->m_camera_speed * direction;
    }

    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
        this->m_position += this->m_camera_speed * direction;
        this->m_direction += this->m_camera_speed * direction;
    }
}

glm::mat4 Camera::GetViewMatrix() const { return glm::lookAt(this->m_position, this->m_direction, this->m_up_vector); }
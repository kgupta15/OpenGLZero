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
#ifndef __CAMERA_H__
#define __CAMERA_H__

constexpr float NEAR_PLANE = 1.0f;
constexpr float FAR_PLANE = 100.0f;
constexpr float FOV = 67.0f;
constexpr float CAMERA_SPEED = 1.0f;

class Camera {
private:
    float       m_horizontal_angle;
    float       m_vertical_angle;
    float       m_near_plane;
    float       m_far_plane;
    float       m_fov;
    float       m_viewport_aspect_ratio;
    float       m_camera_speed;
    glm::vec3   m_position;
    glm::vec3   m_direction;
    glm::vec3   m_right;
    glm::vec3   m_up_vector;

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -10.0f), 
        glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    Camera(float posX, float posY, float posZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
    virtual ~Camera() = default;

    glm::vec3   GetPosition() const;
    void        SetPosition(const glm::vec3& position);
    void        OffsetPosition(const glm::vec3& offset_value);

    glm::vec3   GetDirection() const;
    void        SetDirection(const glm::vec3& direction);

    float       GetFieldOfView() const;
    void        SetFieldOfView(float fov);
        
    float       GetNearPlane() const;
    void        SetNearPlane(float near_plane);
    float       GetFarPlane() const;
    void        SetFarPlane(float far_plane);
    void        SetNearFarPlanes(float near_plane, float far_plane);

    float       GetViewportAspectRatio() const;
    void        SetViewportAspectRatio(float viewport_aspect_ratio);

    float       GetCameraSpeed() const;
    void        SetCameraSpeed(float speed);
    void        UpdateLookAt();

    glm::mat4   GetViewMatrix() const;
};

#endif  // __CAMERA_H__
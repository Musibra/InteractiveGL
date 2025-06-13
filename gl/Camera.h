//
// Created by ibrah on 6/13/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Camera {
public:
    Camera();
    [[nodiscard]] glm::mat4 getViewMatrix() const;

private:
    glm::vec3 mEye;
    glm::vec3 mViewDirection;
    glm::vec3 mUpVector;
};



#endif //CAMERA_H

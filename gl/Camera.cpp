//
// Created by ibrah on 6/13/2025.
//

#include "Camera.h"

Camera::Camera()
    : mEye(0.0f, 0.0f, 0.0f), // Initial position of the camera
      mViewDirection(0.0f, 0.0f, -1.0f), // Looking down the negative Z-axis
      mUpVector(0.0f, 1.0f, 0.0f) { // Up vector pointing in the positive Y direction
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(mEye, mEye + mViewDirection, mUpVector);
}

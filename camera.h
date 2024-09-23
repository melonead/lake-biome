#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CONTROL_WITH_MOUSE 1

struct Camera {
    bool rotate;
    float yaw;
    float pitch;
    glm::vec3 position;
    glm::vec3 up_axis;
    glm::vec3 right_axis;
    glm::vec3 direction;
    glm::vec3 front;
};

void set_up_camera(struct Camera *camera, glm::vec3 init_position, glm::vec3 init_target);
glm::mat4 update_camera(struct Camera *camera, glm::vec3 target);
#endif
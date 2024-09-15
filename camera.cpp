#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// set_up_camera: 
// probably unnecessary because glm already provides similar functionality
void set_up_camera(struct Camera *camera, glm::vec3 init_position, glm::vec3 init_target) {
    camera->position   = init_position;
    camera->direction  = glm::normalize(camera->position - init_target);
    glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f);
    camera->right_axis = glm::normalize(glm::cross(up, camera->direction));
    camera->up_axis    = glm::cross(camera->direction, camera->right_axis);
}

glm::mat4 update_camera(struct Camera *camera, glm::vec3 target) {
    
    return glm::lookAt(camera->position, target, glm::vec3(0.0, 1.0, 0.0));
}
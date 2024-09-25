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
    // SPEED: initialize model every frame is definitely not a good idea, but
    // just want to see if this works
    glm::mat4 model = glm::mat4(1.0f);
    if (camera->rotate) {
        model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
        camera->position = glm::vec3(model * glm::vec4(camera->position, 1.0f));
        camera->direction  = glm::normalize(camera->position - target);
        camera->rotate = false;
    }
    return glm::lookAt(camera->position, target, glm::vec3(0.0, 1.0, 0.0));
}
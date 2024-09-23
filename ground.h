#ifndef GROUND_H
#define GROUND_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define GROUND_VERTICES_COUNT 6

struct Ground {
    glm::vec3 top_left;
    float width;
    float length;
    float vertices[GROUND_VERTICES_COUNT * 3];
    unsigned int VBO;
    unsigned int VAO;
    int model_loc;
    glm::mat4 model; // do i need to store the model matrix in here?
};

void generate_ground_vertices(struct Ground *ground);
void init_ground(struct Ground *ground);


#endif
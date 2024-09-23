#ifndef GROUND_H
#define GROUND_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GROUND_LINES 15
#define GROUND_VERTICES_COUNT GROUND_LINES * 4

struct Ground {
    glm::vec3 top_left;
    float width;
    float length;
    float vertices[GROUND_VERTICES_COUNT * 3];
    unsigned int VBO;
    unsigned int VAO;
    int model_loc;
    glm::mat4 model;
};

void generate_ground_vertices(float *vertices);
void init_ground(struct Ground *ground);


#endif
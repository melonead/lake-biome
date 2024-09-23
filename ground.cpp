#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ground.h"
#include "shader.h"

void generate_ground_vertices(struct Ground *ground) {
    float width = 20.0f;
    glm::vec3 top_left = glm::vec3(-10.0f, 0.0f, -10.0f);

    /* first triangle */
    // top left
    ground->vertices[0] = top_left.x;
    ground->vertices[1] = top_left.y;
    ground->vertices[2] = top_left.z;
    // bottom left
    ground->vertices[3] = top_left.x;
    ground->vertices[4] = top_left.y;
    ground->vertices[5] = top_left.z + width;
    // bottom right
    ground->vertices[6] = top_left.x + width;
    ground->vertices[7] = top_left.y;
    ground->vertices[8] = top_left.z + width;

    /* second triangle */
    // top left
    ground->vertices[15] = top_left.x;
    ground->vertices[16] = top_left.y;
    ground->vertices[17] = top_left.z;
    // top right
    ground->vertices[12] = top_left.x + width;
    ground->vertices[13] = top_left.y;
    ground->vertices[14] = top_left.z;
    // bottom right
    ground->vertices[9] = top_left.x + width;
    ground->vertices[10] = top_left.y;
    ground->vertices[11] = top_left.z + width;


}

void init_ground(struct Ground *ground) {
    generate_ground_vertices(ground);
    glGenVertexArrays(1, &ground->VAO);
    glGenBuffers(1, &ground->VBO);
    glBindVertexArray(ground->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, ground->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ground->vertices), ground->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
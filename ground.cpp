#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ground.h"
#include "shader.h"

void generate_ground_vertices(struct Ground *ground) {

    /* first triangle */
    // top left
    ground->vertices[0] = ground->top_left.x;
    ground->vertices[1] = ground->top_left.y;
    ground->vertices[2] = ground->top_left.z;
    // bottom left
    ground->vertices[3] = ground->top_left.x;
    ground->vertices[4] = ground->top_left.y;
    ground->vertices[5] = ground->top_left.z + ground->width;
    // bottom right
    ground->vertices[6] = ground->top_left.x + ground->width;
    ground->vertices[7] = ground->top_left.y;
    ground->vertices[8] = ground->top_left.z + ground->width;

    /* second triangle */
    // top left
    ground->vertices[15] = ground->top_left.x;
    ground->vertices[16] = ground->top_left.y;
    ground->vertices[17] = ground->top_left.z;
    // top right
    ground->vertices[12] = ground->top_left.x + ground->width;
    ground->vertices[13] = ground->top_left.y;
    ground->vertices[14] = ground->top_left.z;
    // bottom right
    ground->vertices[9] = ground->top_left.x + ground->width;
    ground->vertices[10] = ground->top_left.y;
    ground->vertices[11] = ground->top_left.z + ground->width;


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
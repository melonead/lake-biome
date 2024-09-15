#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ground.h"
#include "shader.h"

void generate_ground_vertices(float *vertices) {
    float lines = 10.0f;
    float delta = 20.0f / lines;
    printf("delta = %f\n", delta);
    int index = 0;
    // vertical lines
    float p = 10;
    float n = -10;
    float x = -10;
    for(int i = 0; i < 10; i++) {
        vertices[index] = x;
        vertices[index + 1] = p;
        vertices[index + 2] = 0.0f;

        vertices[index + 3] = x;
        vertices[index + 4] = n;
        vertices[index + 5] = 0.0f;

        vertices[index + 6] = p;
        vertices[index + 7] = x;
        vertices[index + 8] = 0.0f;

        vertices[index + 9] = n;
        vertices[index + 10] = x;
        vertices[index + 11] = 0.0f;

        index += 12;
        x += delta;
    }
}

void init_ground(struct Ground *ground) {
    glGenVertexArrays(1, &ground->VAO);
    glGenBuffers(1, &ground->VBO);
    glBindVertexArray(ground->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, ground->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ground->vertices), ground->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
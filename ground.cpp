#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ground.h"
#include "shader.h"

void generate_ground_vertices(float *vertices) {
    
    float end = 30.0f;
    float beg = -30.0f;
    float x = -30.0f; 

    float delta =  (end - beg) / GROUND_LINES;
    printf("delta = %f\n", delta);
    int index = 0;
    while(x < end) {
        // vertical line
        vertices[index] = x;
        vertices[index + 1] = 0.0f;
        vertices[index + 2] = beg;

        vertices[index + 3] = x;
        vertices[index + 4] = 0.0f;
        vertices[index + 5] = end;
        // horizontal line
        vertices[index + 6] = beg;
        vertices[index + 7] = 0.0f;
        vertices[index + 8] = x;

        vertices[index + 9] = end;
        vertices[index + 10] = 0.0f;
        vertices[index + 11] = x;

        index += 12;
        x += delta;
        printf("x = %f \n", x);
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
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <malloc.h>


void read_shader_code(char* res, const char* path) {
    char* buffer = (char*) malloc(2000);
    FILE* fp = fopen(path, "r");
    while (fgets(buffer, 2000, fp)  != NULL) {
        strcat(res, buffer);
    }
    fclose(fp);
    free(buffer);
}

/* load and compile shader source */
unsigned int load_shaders(const char* vPath, const char* fPath) {
    unsigned int id = 0;
    unsigned int vertex, fragment;
    
    int success;
    char infoLog[512];
    // compile vertex shader
    char* vertexCode = (char*)malloc(2000);
    memset(vertexCode, 0, 2000);
    read_shader_code(vertexCode, vPath);

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("vertex shader compilation    failed: %s", infoLog);
    }
    // compile fragment shader
    char* fragmentCode = (char*)malloc(2000);
    memset(fragmentCode, 0, 2000);
    read_shader_code(fragmentCode, fPath);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("fragment shader compilation failed: %s", infoLog);
    } 
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);


    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        printf("linking shader program failed: %s ", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    free(vertexCode);
    free(fragmentCode);
    return id;
}


void setBool(const char* name, bool value, unsigned int ID)
{
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void setInt(const char* name, int value, unsigned int ID)
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void setFloat(const char* name, float value, unsigned int ID)
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}




// void setMatrix4fv(const char* name, glm::mat4 value, unsigned int ID)
// {
//     glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
// }

void setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void setMatrix4fv(const string name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
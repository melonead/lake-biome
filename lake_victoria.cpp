#include <time.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "settings.h"
#include "shader.h"
#include "camera.h"
#include "ground.h"

void processInput(GLFWwindow* window, struct Camera *camera);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

struct mouse_camera_data {
    float pitch = -90.0f;
    float yaw = -90.0f;
    float last_x = 300;
    float last_y = 300;
    float zoom;
    bool first_mouse = true;
    glm::vec3 direction;
    glm::vec3 front;
} mouse_cam_data;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    if (!glfwInit())
    {
        return -1;
    }

        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window; 
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tetris", NULL, NULL);
    
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowSizeLimits(window, SCR_WIDTH, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    /*-------------------------vertices--------------------------*/
    float vertices[] = { 
        // position          // normal          // texture coords
        -0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
         0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
         0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
         0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
        -0.5f, 0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
        -0.5f,-0.5f,-0.5f,   0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
 
        -0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
 
        -0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,-0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,-0.5f,-0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,-0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
 
         0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f, 0.5f,-0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f,-0.5f,-0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f,-0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
 
        -0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,-0.5f, 0.5f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
 
        -0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    }; 
 
    /* load shaders */

    unsigned int container_shader = load_shaders("../shaders/containerVert.glsl", "../shaders/containerFrag.glsl");
    /* transformation data */
    glm::mat4 model, view, projection;
    glm::vec3 view_pos = glm::vec3(0.0f, 0.0f, -30.0f);
    int view_pos_loc;
    model      = glm::mat4(1.0f);
    model      = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
    model      = glm::rotate(model, glm::radians(55.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model      = glm::scale(model, glm::vec3(0.5f));
    view       = glm::mat4(1.0f);
    view       = glm::translate(view, view_pos);
    projection = glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f);

    int model_loc, view_loc, projection_loc;


    /* container stuff */
    unsigned int VAO, CONTAINER_VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &CONTAINER_VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, CONTAINER_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* light source stuff */
    unsigned int light_source_shader = load_shaders("../shaders/lightSourceVert.glsl", "../shaders/lightSourceFrag.glsl");
    unsigned int LIGHT_SOURCE_VBO;
    glBindVertexArray(VAO);
    glGenBuffers(1, &LIGHT_SOURCE_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, LIGHT_SOURCE_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::mat4 ls_model;
    glm::vec3 light_source_pos = glm::vec3(-40.0f, 0.0f, 0.0f);
    int light_source_pos_loc;

    ls_model      = glm::mat4(1.0f);
    ls_model      = glm::rotate(ls_model, glm::radians(-5.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ls_model      = glm::scale(ls_model, glm::vec3(0.1f));
    ls_model      = glm::translate(ls_model, light_source_pos);

    int ls_model_loc;

    double mouse_xpos, mouse_ypos;

    /* set up camera data */   
    struct Camera camera;
    const float camera_rotation_radius = 10.0f;
    set_up_camera(&camera, view_pos, glm::vec3(0.0, 0.0, 0.0));

    /* ground */
    unsigned int ground_shader = load_shaders("../shaders/groundVert.glsl", "../shaders/groundFrag.glsl");
    struct Ground ground;
    generate_ground_vertices(ground.vertices);
    init_ground(&ground);

    ground.model      = glm::mat4(1.0f);
    ground.model      = glm::scale(ground.model, glm::vec3(10.0f));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwGetCursorPos(window, &mouse_xpos, &mouse_ypos);
        // light_source_pos.x = mouse_xpos;
        // light_source_pos.y = mouse_ypos;
        // ls_model      = glm::translate(ls_model, light_source_pos);
        
        /* camera stuff */
        // camera.position.x = sin(glfwGetTime()) * camera_rotation_radius;
        // camera.position.y = cos(glfwGetTime()) * camera_rotation_radius;
        //view = glm::lookAt(camera.position, camera.position + mouse_cam_data.front, glm::vec3(0.0, 1.0, 0.0));
        camera.direction.x = mouse_cam_data.direction.x;
        camera.direction.y = mouse_cam_data.direction.y;
        camera.direction.z = mouse_cam_data.direction.z;
        camera.direction   = glm::normalize(camera.direction);
        //printf("camera.direction.z  = %f\n", camera.direction.z);
        view = update_camera(&camera, camera.position + camera.direction);
        
        glUseProgram(container_shader);

        model_loc = glGetUniformLocation(container_shader, "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));        

        view_loc = glGetUniformLocation(container_shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        
        projection_loc = glGetUniformLocation(container_shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

        light_source_pos_loc = glGetUniformLocation(container_shader, "light_pos");
        glUniform3fv(light_source_pos_loc, 1, glm::value_ptr(light_source_pos));

        view_pos_loc = glGetUniformLocation(container_shader, "view_pos");
        glUniform3fv(view_pos_loc, 1, glm::value_ptr(camera.position));

        glBindVertexArray(VAO);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* light source shading */
        glUseProgram(light_source_shader);

        ls_model_loc = glGetUniformLocation(light_source_shader, "ls_model");
        glUniformMatrix4fv(ls_model_loc, 1, GL_FALSE, glm::value_ptr(ls_model));

        view_loc = glGetUniformLocation(light_source_shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        projection_loc = glGetUniformLocation(light_source_shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* ground shading */
        glBindVertexArray(ground.VAO);
        glUseProgram(ground_shader);

        ground.model_loc = glGetUniformLocation(ground_shader, "model");
        glUniformMatrix4fv(ground.model_loc, 1, GL_FALSE, glm::value_ptr(ground.model));

        view_loc = glGetUniformLocation(ground_shader, "view");
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));

        projection_loc = glGetUniformLocation(ground_shader, "projection");
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_LINES, 0, 40);

        

        glfwSwapBuffers(window);
        processInput(window, &camera);
        glfwPollEvents();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, struct Camera *camera)
{   
    const float camera_speed = 0.002f;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position += camera_speed * camera->direction;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position -= camera_speed * camera->direction;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position -= glm::normalize(glm::cross(camera->direction, camera->up_axis)) * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position += glm::normalize(glm::cross(camera->direction, camera->up_axis)) * camera_speed;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (mouse_cam_data.first_mouse) {
        mouse_cam_data.last_x = xpos;
        mouse_cam_data.last_y = ypos;
        mouse_cam_data.first_mouse = false;
    }

    float x_offset = xpos - mouse_cam_data.last_x;
    float y_offset = mouse_cam_data.last_y - ypos;
    mouse_cam_data.last_x = xpos;
    mouse_cam_data.last_y = ypos;

    float sensitivity = 0.1f;
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    mouse_cam_data.pitch += y_offset;
    mouse_cam_data.yaw   += x_offset;

    if (mouse_cam_data.pitch > 89.0f)
        mouse_cam_data.pitch = 89.0f;
    if (mouse_cam_data.pitch < -89.0f)
        mouse_cam_data.pitch = -89.0f;

    mouse_cam_data.direction.x = cos(glm::radians(mouse_cam_data.yaw)) * cos(glm::radians(mouse_cam_data.pitch));
    mouse_cam_data.direction.y = sin(glm::radians(mouse_cam_data.pitch));
    mouse_cam_data.direction.z = sin(glm::radians(mouse_cam_data.yaw)) * cos(glm::radians(mouse_cam_data.pitch));
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
 {
    mouse_cam_data.zoom-= (float)yoffset;
    if (mouse_cam_data.zoom < 1.0f)
        mouse_cam_data.zoom = 1.0f;
    if (mouse_cam_data.zoom > 45.0f)
        mouse_cam_data.zoom = 45.0f;
 }
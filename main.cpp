#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "GLUtils.h"
#include "Point.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
bool didGladInitialize();
bool isWindowNull(GLFWwindow* window);
void drawLine(float one, float two, float three, float four, float five, float six);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";

const int WINDOW_SIZE = 1000;
const int GAME_PIXEL_SIZE = 10; // One game pixel is equal to a 10x10 pixel on screen
const float GAME_PIXEL_FLOAT_SIZE = float(GAME_PIXEL_SIZE) / float(WINDOW_SIZE); // 0.01f

GLUtils utils;

int main() {
    glfwInit();

    // Create Window
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Project Brick", NULL, NULL);
    if (isWindowNull(window)) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!didGladInitialize()) return -1;

    glViewport(0, 0, WINDOW_SIZE, WINDOW_SIZE);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // create vertex arrays
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
   // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), NULL, GL_STATIC_DRAW);

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

    // compile vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // compile fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    drawLine(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        // INPUT
        processInput(window);

        // RENDERING

        // clear screen black
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Pixel
        glDrawArrays(GL_LINES, 0, 2);

        // CHECK/CALL EVENTS && SWAP BUFFERS
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void drawLine(float one, float two, float three, float four, float five, float six) {

    float vertices[] {
        one, two, three,
        four, five, six
    };
    // create buffer
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool didGladInitialize() {
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

bool isWindowNull(GLFWwindow* window) {
    if (window == NULL) {
        std::cout << "GLFW window is null" << std::endl;
        return true;
    }
    return false;
}
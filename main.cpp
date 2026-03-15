#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
bool didGladInitialize();
bool isWindowNull(GLFWwindow* window);

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

const float VERTICES[] = {
    -GAME_PIXEL_FLOAT_SIZE, -GAME_PIXEL_FLOAT_SIZE, 0.0f,  // bottom left
    GAME_PIXEL_FLOAT_SIZE, -GAME_PIXEL_FLOAT_SIZE, 0.0f,  // bottom right
    -GAME_PIXEL_FLOAT_SIZE,  GAME_PIXEL_FLOAT_SIZE, 0.0f,  // top left
    GAME_PIXEL_FLOAT_SIZE,  GAME_PIXEL_FLOAT_SIZE, 0.0f  // top right
};

const unsigned int INDICES[] = {  // note that we start from 0!
    0, 1, 2,  // first Triangle
    1, 2, 3   // second Triangle
};

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

    // create buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);

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

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        // INPUT
        processInput(window);

        // RENDERING

        // clear screen black
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Pixel
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // CHECK/CALL EVENTS && SWAP BUFFERS
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void createSquare(int width, int height) {
    // Create Vertices

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
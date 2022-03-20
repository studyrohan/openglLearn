#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
int createShaderProgram(GLuint& shaderProgram, const GLchar* vertexShaderSource = nullptr, const GLchar* fragmentShaderSource = nullptr);
int InitGlAndCreateWindow(GLFWwindow** window);
#include "errHandler.h"
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <conio.h>
#include <GLFW/glfw3.h>

errHandler::errHandler()
{
}
int errHandler::handleGlfwWindowError(GLFWwindow** window) {
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
}
void errHandler::handleShaderError(GLuint shader) {
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::nitVERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		_getch();
	}
}

errHandler::~errHandler()
{
}

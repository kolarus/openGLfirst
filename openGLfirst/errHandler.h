#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class errHandler
{
public:
	errHandler();
	int handleGlfwWindowError(GLFWwindow** window);
	void handleShaderError(GLuint shader);
	~errHandler();
};


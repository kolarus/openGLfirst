#include "glfw.h"
// GLFW
#include <GLFW/glfw3.h>


glfw::glfw(short majorGlVersion, short minorGlVersion, int profile, int resizable)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorGlVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorGlVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
	glfwWindowHint(GLFW_RESIZABLE, resizable);
}



glfw::~glfw()
{
}

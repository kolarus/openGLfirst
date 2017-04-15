// GLEW нужно подключать до GLFW.
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include "glfw.h"
#include "errHandler.h"
#include "Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//  огда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроетс€
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[])
{
	// GLFW INIT (major,minor,profile,resizable)
	glfw fw(3, 3, GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
	errHandler hndl;
	//—оздание окна GLFW(width,height,title,nullptr,nullptr)
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	//handling glfw window error
	hndl.handleGlfwWindowError(&window);

	glfwMakeContextCurrent(window);

	// transfering result of key_callback to glfw context
	glfwSetKeyCallback(window, key_callback);

	int width, height;
	// getting window size from GLFW
	glfwGetFramebufferSize(window, &width, &height);
	// Creating openGL viewport
	glViewport(0, 0, width, height);
	// GLEW INIT
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		_getch();
		return -1;
	}

	/*
	// Creating vertex buffer object to store vertex and allocate GPU memory
	GLuint VBO;
	// generating buffer from the object 
	glGenBuffers(1, &VBO);
	//VBO Ч GL_ARRAY_BUFFER , binding buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/*-------------------------------------------------------------
	Buffering data (bufferType, memoryToAlloc, vertices, DrawType)
	GL_STATIC_DRAW: данные либо никогда не будут измен€тьс€, либо будут измен€тьс€ очень редко;
	GL_DYNAMIC_DRAW: данные будут мен€тьс€ довольно часто;
	GL_STREAM_DRAW: данные будут мен€тьс€ при каждой отрисовке.
	-------------------------------------------------------------
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);*/
	/*-------------------------------------------------------------
	Shader should be written in a special language and included as a C string
	Setting version
	in vec3 position - атрибуты поданые на вход шейдеру
	gl_Position - request vec4 type and sets the positionn
	-------------------------------------------------------------*/

	Shader ourShader("Shaders/vertex.vs", "Shaders/fragmenr.frag");
	/*const GLchar* vertexShaderSource = "#version 330 core \n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"out vec3 ourColor;\n"
		"void main(){ \n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"ourColor = color;\n"
		"}\n";
	//creating shader object
	GLuint vertexShader;
	// writing shader into object,GL_VERTEX_SHADER - shader type
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// binding shader with its source code, 1 - number of lines
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// handling shader error
	hndl.handleShaderError(vertexShader);

	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(ourColor, 1.0f);\n"
		"};\n";
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// handling shader error
	hndl.handleShaderError(fragmentShader);

	//Creating  shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	//Shaders are no longer needed after creating shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);*/

	GLfloat vertices[] = {
		// ѕозиции         // ÷вета
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Ќижний правый угол
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Ќижний левый угол
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ¬ерхний угол
	};
	GLuint indices[] = {  // ѕомните, что мы начинаем с 0!
		0, 1, 2
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the triangle

		glUniform3f(glGetUniformLocation(ourShader.Program, "ourPosition"), 0.7f,0.7f,0.7f);

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	// cleaninng resources before quit
	glfwTerminate();
	return 0;
}
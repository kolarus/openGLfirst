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
#include <SOIL.h>
#include <GL\GL.h>




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


GLfloat mixValue = 0.2f;

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

	

	GLfloat vertices[] = {
		// ѕозиции          // ÷вета             // “екстурные координаты
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ¬ерхний правый
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Ќижний правый
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Ќижний левый
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ¬ерхний левый
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO




	int twidth[2], theight[2];
	unsigned char* image1 = SOIL_load_image("images/container.jpg", &twidth[0], &theight[0], 0, SOIL_LOAD_RGB);
	unsigned char* image2 = SOIL_load_image("images/awesomeface.png", &twidth[1], &theight[1], 0, SOIL_LOAD_RGB);
	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // NOTE the GL_NEAREST Here! 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // NOTE the GL_NEAREST Here!

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth[0], theight[0], 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // NOTE the GL_NEAREST Here! 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  // NOTE the GL_NEAREST Here!

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, twidth[1], theight[1], 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(ourShader.Program, "mixValue"), mixValue);
		// Activate shader
		ourShader.Use();

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//  огда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true, 
	// и приложение после этого закроетс€
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}

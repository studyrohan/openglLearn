// eddy 
#define GLEW_STATIC
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "head.h"
#include "tools.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "Tools/std_image.h"

void key_callback(GLFWwindow* windows, int key, int scanCode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(windows, GL_TRUE);
}
int func()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//我们在初始化GLEW之前设置glewExperimental变量的值为GL_TRUE，
	//这样做能让GLEW在管理OpenGL的函数指针时更多地使用现代化的技术，
	//如果把它设置为GL_FALSE的话可能会在使用OpenGL的核心模式时出现一些问题。
	glewExperimental = GLFW_TRUE;
	if (glewInit()!=GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);
	while (!glfwWindowShouldClose(window))
	{
		//check events ,like mouse move
		glfwPollEvents();
		//渲染一下
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 交换缓冲
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	

	return 0;
}

int drawTwoSameTriangleWithdifferentCollor()
{
	const GLuint WIDTH = 800, HEIGHT = 600;

	// Shaders
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	const GLchar* fragmentShader1Source = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	const GLchar* fragmentShader2Source = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 0.0f, 1.0f); // The color yellow \n"
		"}\n\0";
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Build and compile the shader programs (we ignored compile log checks for readability (if you do encounter issues, add the compile-checks!))
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // The first fragment shader that outputs the color orange
	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // The second fragment shader that outputs the color yellow
	GLuint shaderProgramOrange = glCreateProgram();
	GLuint shaderProgramYellow = glCreateProgram(); // The second shader program
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShaderYellow);
	// Link the first program object
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glLinkProgram(shaderProgramOrange);
	// Then link the second program object using a different fragment shader (but same vertex shader) this time.
	// This is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);


	GLfloat firstTriangle[] = {
	-0.9f, -0.5f, 0.0f,  // Left 
	-0.0f, -0.5f, 0.0f,  // Right
	-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
		 0.0f, -0.5f, 0.0f,  // Left
		 0.9f, -0.5f, 0.0f,  // Right
		 0.45f, 0.5f, 0.0f   // Top 
	};
	GLuint VAOs[2], VBOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//first triangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//second triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	 
	//GLfloat firstTriangle[] = {
	//   -0.9f, -0.5f, 0.0f,  // Left 
	//   -0.0f, -0.5f, 0.0f,  // Right
	//   -0.45f, 0.5f, 0.0f,  // Top 
	//};
	//GLfloat secondTriangle[] = {
	//	 0.0f, -0.5f, 0.0f,  // Left
	//	 0.9f, -0.5f, 0.0f,  // Right
	//	 0.45f, 0.5f, 0.0f   // Top 
	//};
	//GLuint VBOs[2], VAOs[2];
	//glGenVertexArrays(2, VAOs);
	//glGenBuffers(2, VBOs);
	//// ================================
	//// First Triangle setup
	//// ===============================
	//glBindVertexArray(VAOs[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	//// ================================
	//// Second Triangle setup
	//// ===============================
	//glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
	//glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
	//glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
	//glEnableVertexAttribArray(0);
	//game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//render 
		// clear color buffer
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//activate shader
		glUseProgram(shaderProgramOrange);
		//draw
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);


	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);

	glfwTerminate();
	return 0;

}
int drawTwoSameTriangle()
{
	GLFWwindow* window;
	InitGlAndCreateWindow(&window);
	GLuint shaderProgram1, shaderProgram2;
	createShaderProgram(shaderProgram1);
	const GLchar* fragmentShaderSourceDefault = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n\0";
	createShaderProgram(shaderProgram2,nullptr, fragmentShaderSourceDefault);
	glUseProgram(shaderProgram1);
	//渲染前指定OpenGL该如何解释顶点数据
	//位置数据被储存为32 - bit（4字节）浮点值。
	//	每个位置包含3个这样的值。
	//	在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列。
	//	数据中第一个值在缓冲开始的位置。

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (GLvoid*)0);
	//启用顶点属性 默认禁用
	glEnableVertexAttribArray(1);

	//GLfloat firstTriangle[] = {
	//-0.9f, -0.5f, 0.0f,  // Left 
	//-0.0f, -0.5f, 0.0f,  // Right
	//-0.45f, 0.5f, 0.0f,  // Top 
	//};
	//GLfloat secondTriangle[] = {
	//	 0.0f, -0.5f, 0.0f,  // Left
	//	 0.9f, -0.5f, 0.0f,  // Right
	//	 0.45f, 0.5f, 0.0f   // Top 
	//};
	//GLuint VAO[2], VBO[2];
	//glGenVertexArrays(2, VAO);
	//glGenBuffers(2, VBO);
	////first triangle
	//glBindVertexArray(VAO[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	////second triangle
	//glBindVertexArray(VAO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(VBO[1], sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	//game loop
	GLfloat firstTriangle[] = {
	   -0.9f, -0.5f, 0.0f,  // Left 
	   -0.0f, -0.5f, 0.0f,  // Right
	   -0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat secondTriangle[] = {
		 0.0f, -0.5f, 0.0f,  // Left
		 0.9f, -0.5f, 0.0f,  // Right
		 0.45f, 0.5f, 0.0f   // Top 
	};
	GLuint VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	// ================================
	// First Triangle setup
	// ===============================
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	// ================================
	// Second Triangle setup
	// ===============================
	glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
	glEnableVertexAttribArray(0);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//render 
		// clear color buffer
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//activate shader
		glUseProgram(shaderProgram1);
		//draw
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(shaderProgram2);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);
	}
		
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	
	glfwTerminate();
	return 0;
}
int drawTriangle()
{
	GLFWwindow* window;
	InitGlAndCreateWindow(&window);
	GLuint shaderProgram;
	createShaderProgram(shaderProgram);
	glUseProgram(shaderProgram);
	//渲染前指定OpenGL该如何解释顶点数据
	//位置数据被储存为32 - bit（4字节）浮点值。
	//	每个位置包含3个这样的值。
	//	在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列。
	//	数据中第一个值在缓冲开始的位置。

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (GLvoid*)0);
	//启用顶点属性 默认禁用
	glEnableVertexAttribArray(1);

	//

	GLfloat vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.0f,0.0f,
	0.0f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
	};

	//顶点缓冲对象 vertex buffer object vbo
	//GLuint vbo;
	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//把用户定义的数据复制到当前缓冲

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//bind the vertex array object first,the set vertex buffer(s) and attribute pointer
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (GLvoid*)0);
	//启用顶点属性 默认禁用
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//render
		//clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glfwTerminate();
	return 0;
}
int drawRectangle()
{
	GLFWwindow* window;
	InitGlAndCreateWindow(&window);
	GLuint shaderProgram;
	createShaderProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,  // Top Right
	 0.5f, -0.5f, 0.0f,  // Bottom Right
	-0.5f, -0.5f, 0.0f,  // Bottom Left
	-0.5f,  0.5f, 0.0f   // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		//render
		//clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;

	return 0;
}

int testPicture1()
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenBuffers(1, &texture);
	return 0;
}
//211224199512266914
//liuhan1226
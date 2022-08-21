#include <iostream>
#include "tools.h"

static void key_callback(GLFWwindow* windows, int key, int scanCode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(windows, GL_TRUE);
}
int InitGlAndCreateWindow(GLFWwindow** window)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	*window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (*window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(*window);
	//我们在初始化GLEW之前设置glewExperimental变量的值为GL_TRUE，
	//这样做能让GLEW在管理OpenGL的函数指针时更多地使用现代化的技术，
	//如果把它设置为GL_FALSE的话可能会在使用OpenGL的核心模式时出现一些问题。
	glewExperimental = GLFW_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int width, height;
	glfwGetFramebufferSize(*window, &width, &height);
	glViewport(0, 0, width, height);
	//glfwSetKeyCallback(*window, key_callback);
	return 0;

}
int createShaderProgram(GLuint& shaderProgram, const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource)
{
	const GLchar* vertexShaderSourceDefault = "#version 330 core\n"
		"layout  (location =0 ) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x,position.y,position.z,1.0);\n "
		"}\n";
	const GLchar* fragmentShaderSourceDefault = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	const GLchar* vertexSource = vertexShaderSource == nullptr ? vertexShaderSourceDefault : vertexShaderSource;
	const GLchar* framentSource = fragmentShaderSource == nullptr ? fragmentShaderSourceDefault : fragmentShaderSource;
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error:shader:vertex:complile" << infoLog << std::endl;
	}
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &framentSource, NULL);
	glCompileShader(fragmentShader);

	// create program link shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}
	//激活对象程序

	//链接进入程序对象之后，我们就不再需要着色器对象了
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return 0;
}

int drawRectangleChanged()
{
	GLFWwindow* window;
	InitGlAndCreateWindow(&window);
	GLuint shaderProgram;
	const GLchar* vertexShaderSource = "#version 330 core\n"
		"layout  (location =0 ) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x,position.y,position.z,1.0);\n "
		"}\n";
	const GLchar* fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	createShaderProgram(shaderProgram);
	glUseProgram(shaderProgram);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (GLvoid*)0);
	//启用顶点属性 默认禁用
	glEnableVertexAttribArray(1);
	GLfloat vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.0f,0.0f,
	};

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

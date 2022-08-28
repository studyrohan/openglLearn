
// eddy 
#define GLEW_STATIC
#include <GL/glew.h>
#include "SOIL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../resource.h"

#include "texture.h"
#include "tools.h"
#include "Tools/shader.h"


#include "translate.h"

int testTranslate()
{
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;
	//trans = glm::rotate(trans, 90.0f, glm::vec3(0.0, 0.0, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));


	GLFWwindow* window;
	InitGlAndCreateWindow(&window);

	Shader ourShader("resource/textures1.vs", "resource/textures2.frag");

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//为当前绑定的纹理对象设置环绕、过滤方式

	//  load generate wenli
	int width, height;
	unsigned char* image = SOIL_load_image("resource//container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		return -1;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image("resource//awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		return -1;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);



	GLfloat vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	GLuint indices[] = {
		0,1,3,// first triangle
		1,2,3// second triangle
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);//unbind VAO


	while (!glfwWindowShouldClose(window))
	{
		//check it any events have been activited ,
		glfwPollEvents();

		//render 
		// clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind Textures using texture units

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		ourShader.use();
		//create transformations
		//glm::mat4 transform;
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		//transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		//GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		//draw container

		glm::mat4 transform= glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glm::mat4 transform2 = glm::mat4(1.0f);
		transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.5f, 0.0f));
		transform2 = glm::rotate(transform2, (GLfloat)glfwGetTime()* 2.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		auto time = abs((GLfloat)glfwGetTime());
		transform2 = glm::scale(transform2, glm::vec3(sin(time), sin(time), 0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//swap the screen buffers
		glfwSwapBuffers(window);
	}
	//properly de-allocate all resources one they have outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}



// eddy 
#define GLEW_STATIC
#include <GL/glew.h>
#include "SOIL.h"
#include "../resource.h"
#include "texture.h"
#include "tools.h"
#include "Tools/shader.h"

int testPicture()
{
	GLFWwindow* window;
	InitGlAndCreateWindow(&window);

	Shader ourShader("resource/textures.vs", "resource/textures.frag");

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	
	//  load generate wenli
	int width, height;
	unsigned char* image = SOIL_load_image("resource//container.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLfloat vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	return 0;
}


//#include <iostream>

//int main()
//{
//	std::cout << "hello" << std::endl;
//	std::cin.get();
//	return 0;
//}
#include <GLFW/glfw3.h>
#include <iostream>

#include "head.h"
#include "texture.h"
#include "translate.h"
#include "CoordinateSystem.h"
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int test()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);



        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

const int WIDTH = 800;
const int HEIGHT = 600;

static float lastX = WIDTH / 2.0f;
static float lastY = HEIGHT / 2.0f;
static bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		firstMouse = true;
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	if (firstMouse) {
		xoffset = 0.0f;
		yoffset = 0.0f;
		firstMouse = false;
	}

	std::cout << "Mouse offset: (" << xoffset << ", " << yoffset << ")" << std::endl;

	// Rotate model with mouse movement
	float sensitivity = 0.1f; // Adjust this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(xoffset, 0.0f, 1.0f, 0.0f);
	glRotatef(yoffset, 1.0f, 0.0f, 0.0f);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	std::cout << "Scroll offset: (" << xoffset << ", " << yoffset << ")" << std::endl;

	// Scale model with mouse scroll
	float sensitivity = 0.1f; // Adjust this value to your liking
	yoffset *= sensitivity;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0f + yoffset, 1.0f + yoffset, 1.0f + yoffset);
}

int test5() {
	// 初始化 GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// 设置回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// 设置 OpenGL 上下文参数
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// 绘制三角形
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.5f, 0.0f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 清理资源
	glfwTerminate();
	return 0;
}
void drawTriangledd() {
	// 顶点坐标
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  // 左下角
		0.5f, -0.5f, 0.0f,   // 右下角
		0.0f, 0.5f, 0.0f     // 顶部
	};

	// 创建GLFW窗口
	GLFWwindow* window;
	if (!glfwInit()) {
		return;
	}

	window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// 绘制三角形
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);  // 设置颜色为红色
		glVertex3fv(vertices);
		glVertex3fv(vertices + 3);
		glVertex3fv(vertices + 6);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 清理资源
	glfwTerminate();
}
int main(void)
{
    //func();
    //drawTriangle();
    //drawRectangle();
    //drawTwoSameTriangle();
    //drawTwoSameTriangleWithdifferentCollor();
    //testPicture();
    testTexture();
    //testTranslate();
    //testPictureCoordianteTrans();
    //testPictureCoordiante36face();
    //testPictureCamera();
    //test5();
	//testRoateCube();
	//drawTriangledd();
    return 0;
}
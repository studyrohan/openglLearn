#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include "head.h"
 struct VsPoint
{
	float x;
	float y;
	float z;
};
static double gs_scale = 1.0;
static double gs_rotation = 0.0;
static double gs_translate[3] = { 0,0,0 };
static void Loc_Render(GLFWwindow* window, const std::vector<float>& points);
static void Loc_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
static void Loc_cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
static void Loc_keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mode);



int DISP_DrawLineData(const std::vector<std::pair<VsPoint, VsPoint>>& data);


void Loc_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	static const double scaleSpeed = 1.1;
	if (yoffset > 0)
	{
		gs_scale *= scaleSpeed;
	}
	else
	{
		gs_scale /= scaleSpeed;
	}
}


void Loc_cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	std::string str = "xpos = " + std::to_string(xpos) + ", ypos = " + std::to_string(ypos);
	std::cout << str << std::endl;
	glRasterPos2i(20, 20);
	int err = 0;
	for (unsigned char c : str)
	{
		glBitmap(10, 10, 0, 0, 0, 0, &c);
	}

	static double lastXpos = xpos;
	static double lastYpos = ypos;
	static const double rotationSpeed = 0.5;
	double dx = xpos - lastXpos;
	double dy = ypos - lastYpos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		gs_rotation -= dx * rotationSpeed;
	}
	lastXpos = xpos;
	lastYpos = ypos;
}

void Loc_keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mode)
{
	static const float translateSpeed = 0.1;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_LEFT)
	{
		gs_translate[0] -= translateSpeed;
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		gs_translate[0] += translateSpeed;
	}
	else if (key == GLFW_KEY_UP)
	{
		gs_translate[1] += translateSpeed;
	}
	else if (key == GLFW_KEY_DOWN)
	{
		gs_translate[1] -= translateSpeed;
	}
	else if (key == GLFW_KEY_W)
	{
		gs_rotation += 1;
	}
	else if (key == GLFW_KEY_S)
	{
		gs_rotation -= 1;
	}
	else if (key == GLFW_KEY_R)
	{
		gs_scale = 1.0;
		gs_rotation = 0.0;
		gs_translate[0] = 0;
		gs_translate[1] = 0;
		gs_translate[2] = 0;
	}

}
int testRoate()
{
	return DISP_DrawLineData({ std::pair<VsPoint, VsPoint>{ { 0, 0, 0 }, { 100,200,0 }} });
}
int DISP_DrawLineData(const std::vector<std::pair<VsPoint, VsPoint>>& data)
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		std::cout << "Problem to initialize GLFW" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(800, 600, "Test Geom ", NULL, NULL);

	if (!window)
	{
		std::cout << "fail to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetScrollCallback(window, Loc_ScrollCallback);
	glfwSetCursorPosCallback(window, Loc_cursorPosCallback);
	glfwSetKeyCallback(window, Loc_keyCallBack);
	glfwMakeContextCurrent(window);

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) == 0)
	{
		std::vector<float> points;
		points.reserve(data.size() * 6);
		for (auto& item : data)
		{
			points.push_back(float(item.first.x));
			points.push_back(float(item.first.y));
			points.push_back(float(item.first.z));
			points.push_back(float(item.second.x));
			points.push_back(float(item.second.y));
			points.push_back(float(item.second.z));
		}
		Loc_Render(window, points);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void Loc_Render(GLFWwindow* window, const std::vector<float>& points)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat matrixP[16];
	glGetFloatv(GL_PROJECTION, matrixP);

	glScalef(gs_scale, gs_scale, 1.0);
	glGetFloatv(GL_PROJECTION, matrixP);
	GLfloat matrix[16];
	glPushMatrix();
	GLdouble matrix2[16];
	glLoadMatrixd(matrix2);

	glRotated(gs_rotation, 0.0, 0.0, 1.0);
	glTranslated(gs_translate[0], gs_translate[1], gs_translate[2]);

	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i + 6 <= points.size(); i += 6)
	{
		glVertex3f(points[i], points[i + 1], points[i + 2]);
		glVertex3f(points[i + 3], points[i + 4], points[i + 5]);
	}
	glEnd();

	glfwSwapBuffers(window);
}


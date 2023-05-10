#include <GLFW/glfw3.h>
#include <iostream>
#include "head.h"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Left mouse button pressed at (" << xpos << ", " << ypos << ")" << std::endl;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static double last_xpos = xpos;
	static double last_ypos = ypos;

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		double dx = xpos - last_xpos;
		double dy = ypos - last_ypos;

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(dy, 1, 0, 0);
		glRotatef(dx, 0, 1, 0);
		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		glMultMatrixf(matrix);
	}

	last_xpos = xpos;
	last_ypos = ypos;
}

int testRoateCube(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Interactive Geometry", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Set the key callback */
	glfwSetKeyCallback(window, key_callback);

	/* Set the mouse button callback */
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Set the cursor position callback */
	glfwSetCursorPosCallback(window, cursor_position_callback);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Draw a cube */
		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);     // Red
		glVertex3f(-1.0f, 1.0f, -1.0f); // Top-left corner
		glVertex3f(1.0f, 1.0f, -1.0f);  // Top-right corner
		glVertex3f(1.0f, 1.0f, 1.0f);   // Bottom-right corner
		glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom-left corner

		glColor3f(0.0f, 1.0f, 0.0f);     // Green
		glVertex3f(-1.0f, -1.0f, 1.0f); // Top-left corner
		glVertex3f(1.0f, -1.0f, 1.0f);  // Top-right corner
		glVertex3f(1.0f, -1.0f, -1.0f); // Bottom-right corner
		glVertex3f(-1.0f, -1.0f, -1.0f);// Bottom-left corner

		glColor3f(0.0f, 0.0f, 1.0f);     // Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);  // Top-left corner
		glVertex3f(1.0f, 1.0f, 1.0f);   // Top-right corner
		glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-right corner
		glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom-left corner

		glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
		glVertex3f(-1.0f, -1.0f, -1.0f);// Top-left corner
		glVertex3f(1.0f, -1.0f, -1.0f); // Top-right corner
		glVertex3f(1.0f, 1.0f, -1.0f);  // Bottom-right corner
		glVertex3f(-1.0f, 1.0f, -1.0f); // Bottom-left corner
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <unistd.h>

double red_c = 0;
double green_c = 0;
double blue_c = 0;

void init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	(void)window;
	std::cout << "Resizing a window to width: " << width << " and height: " << height << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void loop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(red_c, green_c, blue_c, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	init();

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", 0, 0);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;	
	}

	glViewport(0, 0, 800, 600);

	loop(window);
	glfwTerminate();

	return 0;
}

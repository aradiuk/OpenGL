#include <glad.h>
#include <glfw3.h>

#include <iostream>
#include <unistd.h>

double red_c = 0.7;
double green_c = 0.5;
double blue_c = 0.3;

float vertices[] = {
	-0.5, -0.5, 0.0,
	0.5, -0.5, 0.0,
	0.0, 0.5, 0.0
};

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

void verifyShaderCompilation(unsigned int shader, const std::string& shaderName)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, 0, infoLog);
		std::cout << shaderName << " compilation failed - " << infoLog << std::endl;
	} else {
		std::cout << shaderName << " compiled successfully.\n";
	}
}

void verifyShaderLinking(unsigned int shaderProgram)
{
	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
		std::cout << "Shader program linking failed - " << infoLog << std::endl;
	} else {
		std::cout << "Shader program linked successfully.\n";
	}
}


void initVBO()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

unsigned int initVAO()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	initVBO();
	return VAO;
}

void initShaders()
{
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "void main()\n"
									 "{\n"
									 "	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
									 "}\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);
	verifyShaderCompilation(vertexShader, "vertexShader");

	const char *fragmentShaderSource = "#version 330 core\n"
						  			   "out vec4 FragColor;\n"
									   "void main()\n"
									   "{\n"
									   "	FragColor = vec4(0.1f, 0.4f, 0.5f, 1.0f);\n"
									   "}\0";
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);
	verifyShaderCompilation(fragmentShader, "fragmentShader");

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);	
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	verifyShaderLinking(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderProgram);
}

void init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void loop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(red_c, green_c, blue_c, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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

	unsigned int VAO = initVAO();
	initShaders();
	glBindVertexArray(VAO);
	loop(window);


	glfwTerminate();

	return 0;
}

#include "pch.hpp"

constexpr float width = 1920, height = 1080;

int main()
{
	if(!glfwInit())
	{
		std::cout << "GLFW could not be initialized";
		glfwTerminate();
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(width, height, "Life", glfwGetPrimaryMonitor(), NULL);
	//GLFWwindow* window = glfwCreateWindow(width, height, "Life", NULL, NULL);
	if(!window)
	{
		std::cout << "Window creation failed";
		glfwTerminate();
		return 3;
	}

	constexpr unsigned int rows = height/5;
	constexpr unsigned int cols = width/5;
	constexpr unsigned int hertz = 120;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return 3;
	}

	Shader shader("res/shaders/Basic.shader");
	shader.bind();

	glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height);
	shader.setUniformMat4("u_proj", proj);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Flock flock(200, width, height);
	CellGrid grid(rows, cols, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	//flock.drawFlock(renderer, shader);
	glfwSwapBuffers(window);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		double start = glfwGetTime();

		
		glClear(GL_COLOR_BUFFER_BIT);
		grid.updateGrid();
		grid.drawGrid(shader);
		//flock.update(hertz);
		//flock.drawFlock(renderer, shader);
		glfwSwapBuffers(window);

		double end = glfwGetTime();
		while(end-start < (1.0/hertz))
			end = glfwGetTime();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
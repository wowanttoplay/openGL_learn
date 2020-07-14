#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "cGLSL.h"
#include "Shader.h"
#include "Texture.h"
#include"camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



camera cameraObject;
float deltaTime = 0.0;
float lastTime = 0.0;

bool firstMouse = true;
float y_rotate = -90.0;
float x_rotate = 0;
float lastXRotate = 0;
float lastYPos = SCR_WIDTH / 2;
float lastXPos = SCR_HEIGHT / 2;

float fov = 45.0;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*************************** gl work ******************************/
	//create VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

//get vertex data buffer
unsigned int VBO;
glGenBuffers(1, &VBO);
//1. 复制顶点信息到缓冲中供opengl使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesQuard), verticesQuard, GL_STATIC_DRAW);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//get EBO
unsigned int EBO;
glGenBuffers(1, &EBO);
////1. 复制顶点的索引信息到EBO中
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//2. 设置顶点属性指针
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	shader shaderProgram(vertexShaderSrc, fragmentShaderSrc);
	vector<Texture>TexVec;
	TexVec.emplace_back(Texture("./icon/container.jpg"));
	TexVec.emplace_back(Texture("./icon/awesomeface.png"));

	//set texture uniform
	shaderProgram.use();
	shaderProgram.setInt("texture0", 0);
	shaderProgram.setInt("texture1", 1);
	
	//gl set
	glEnable(GL_DEPTH_TEST);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);


		// render
		// ------
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		//draw
		//-----------------
		for (int i = 0; i < TexVec.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			TexVec[i].bindTexture();
		}
		
		glBindVertexArray(VAO);
		shaderProgram.use();

		glm::mat4  view(1.0), projection(1.0);
		//view = glm::translate(view, glm::vec3(0.0, 0.0, -5.0));
		float radius = 50.0;
		view = cameraObject.getView();
		projection = glm::perspective((double)glm::radians(fov), (double)SCR_WIDTH/SCR_HEIGHT, 0.1, 200.0);


		//shaderProgram.setMate4("transform",model);
		shaderProgram.setMate4("view", view);
		shaderProgram.setMate4("projection", projection);
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model(1.0);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glm::radians(20.0 * i) * (float)glfwGetTime(), glm::vec3(1.0, 0.3, 0.5));
			shaderProgram.setMate4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		
		glBindVertexArray(0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
#ifdef USE_VBO
	glDeleteBuffers(1, &VBO);
#endif
#ifdef USE_EBO
	glDeleteBuffers(1, &EBO);
#endif
	glDeleteProgram(shaderProgram.getID());

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	float cameraSpeed = 0.1f * deltaTime;
	cameraObject.setSpeed(cameraSpeed);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraObject.moveFront();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraObject.moveBack();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraObject.moveLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraObject.moveRight();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastXPos = xpos;
		lastYPos = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastXPos;
	float yoffset = lastYPos - ypos; // reversed since y-coordinates go from bottom to top
	lastXPos = xpos;
	lastYPos = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	y_rotate += xoffset;
	x_rotate += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (x_rotate > 89.0f)
		x_rotate = 89.0f;
	if (x_rotate < -89.0f)
		x_rotate = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(y_rotate)) * cos(glm::radians(x_rotate));
	front.y = -sin(glm::radians(x_rotate));
	front.z = sin(glm::radians(y_rotate)) * cos(glm::radians(x_rotate));
	cameraObject.setCenter(glm::normalize(front));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
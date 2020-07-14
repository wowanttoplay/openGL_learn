#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <mutex>

using namespace std;

class camera
{
public:
	camera();
	void setPos(const glm::vec3& pos);
	void setCenter(const glm::vec3& center);
	void setUp(const glm::vec3& up);
	void setSpeed(const float& t);

	void movePos(const glm::vec3& displacement);
	void moveFront();
	void moveBack();
	void moveLeft();
	void moveRight();
	glm::mat4 getView();
private:
	glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);	//相机位置
	glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);	//相机瞄准方向
	glm::vec3 Up = glm::vec3(0.0, 1.0, 0.0);
	float cameraSpeed = 0.5f;	//相机移动速度

	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;



	glm::mat4 view;	//相机矩阵

	mutex cameraLock;	//相机的锁
};


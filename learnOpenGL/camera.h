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
	glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);	//���λ��
	glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);	//�����׼����
	glm::vec3 Up = glm::vec3(0.0, 1.0, 0.0);
	float cameraSpeed = 0.5f;	//����ƶ��ٶ�

	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;



	glm::mat4 view;	//�������

	mutex cameraLock;	//�������
};


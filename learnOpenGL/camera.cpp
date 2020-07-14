#include "camera.h"

camera::camera()
{
	cameraDirection = glm::normalize(cameraPos - cameraTarget);
	cameraRight = glm::normalize(glm::cross(Up, cameraDirection));
	cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

	view = glm::lookAt(cameraPos, cameraTarget, Up);
}

void camera::setPos(const glm::vec3& pos)
{
	lock_guard<mutex> lock(cameraLock);
	cameraPos = pos;
	
}

void camera::setCenter(const glm::vec3& center)
{
	lock_guard<mutex> lock(cameraLock);
	cameraTarget = center;
}

void camera::setUp(const glm::vec3& up)
{
	lock_guard<mutex> lock(cameraLock);
	this->Up = up;
}

void camera::setSpeed(const float& t)
{
	lock_guard<mutex> lock(cameraLock);
	cameraSpeed = t;
}

void camera::movePos(const glm::vec3& displacement)
{
	cameraPos = cameraPos + displacement;
}

void camera::moveFront()
{
	lock_guard<mutex> lock(cameraLock);
	glm::vec3 dis = glm::normalize(cameraDirection) * cameraSpeed;
	this->movePos(dis);
}

void camera::moveBack()
{
	lock_guard<mutex> lock(cameraLock);
	glm::vec3 dis = glm::normalize(cameraDirection) * -cameraSpeed;
	this->movePos(dis);
}

void camera::moveLeft()
{
	lock_guard<mutex> lock(cameraLock);
	
	cameraRight = glm::normalize(glm::cross(Up, cameraDirection
	));
	glm::vec3 dis = cameraRight * -cameraSpeed;
	this->movePos(dis);
	
}

void camera::moveRight()
{
	lock_guard<mutex> lock(cameraLock);
	cameraRight = glm::normalize(glm::cross(Up, cameraDirection
	));
	glm::vec3 dis = cameraRight * cameraSpeed;
	this->movePos(dis);
}

glm::mat4 camera::getView()
{
	lock_guard<mutex> lock(cameraLock);
	view = glm::lookAt(cameraPos, cameraTarget, Up);
	return view;
}

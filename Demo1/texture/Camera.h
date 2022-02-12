#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const float PITCH		= 0.0f;
const float YAW			= 0.0f;
const float SPEED		= 0.5f;
const float SENSITIVITY = 0.1f;

enum Movement
{
	W,
	A,
	S,
	D
};

class Camera
{
public:
	//���������
	glm::vec3 mCameraPos;
	glm::vec3 mCameraFront;
	glm::vec3 mCameraUp;
	glm::vec3 mCameraRight;
	glm::vec3 mWorldUp;

	//ŷ����
	float mPitch;
	float mYaw;

	//���������
	float mCameraSpeed;
	float mCameraSensitivity;

	//���캯��
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float pitch = PITCH, float yaw = YAW)
		:mCameraSpeed(SPEED), mCameraSensitivity(SENSITIVITY), mCameraFront(glm::vec3(0.0f, 0.0f, -1.0f))
	{
		mCameraPos = position;
		mWorldUp   = up;
		mPitch	   = pitch;
		mYaw       = yaw;
		updateCameraVectors();
	}

	//�õ�view����
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
	}

	//����������˶�
	void ProcessKeyboard(Movement direction, float deltaTime)
	{
		std::cout << deltaTime << std::endl;
		float velocity = mCameraSpeed * deltaTime;
		if (direction == W)
			mCameraPos += mCameraFront * velocity;
		if (direction == S)
			mCameraPos -= mCameraFront * velocity;
		if (direction == A)
			mCameraPos -= mCameraRight * velocity;
		if (direction == D)
			mCameraPos += mCameraRight * velocity;
	}

	//��������ת��
	void MoveMouse(float xoffset, float yoffset)
	{
		xoffset *= mCameraSensitivity;
		yoffset *= mCameraSensitivity;

		mYaw   += xoffset;
		mPitch += yoffset;

		if (mPitch > 89.0f)
			mPitch = 89.0f;
		if (mPitch < -89.0f)
			mPitch = -89.0f;
		updateCameraVectors();
	}

private:

	//�������������
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x		 = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
		front.y		 = sin(glm::radians(mPitch));
		front.z		 = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
		mCameraFront = glm::normalize(front);
		mCameraRight = glm::normalize(glm::cross(mCameraFront, mWorldUp));
		mCameraUp    = glm::normalize(glm::cross(mCameraRight, mCameraFront));
	}
};
#endif
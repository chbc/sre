#include "EventReceiver.h"
#include "application/SampleApplication.h"
#include <glm/glm.hpp>

#include <glm/gtx/rotate_vector.hpp>
#include <iostream>

EventReceiver::EventReceiver(SampleApplication *application, CameraComponent *camera)
{
	this->application = application;
	this->camera = camera;

	glm::vec3 position(0.0f, 2.5f, 10.0f);
	this->camera->setPosition(position);
	this->cameraDistance = glm::distance(position, glm::vec3(0, 0, 0));

	this->viewingActive = false;
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onKeyEvent(KeyboardButton key, bool pressed)
{
	if (pressed && key == KEY_ESC)
		this->application->quit();
}

void EventReceiver::onMouseButtonEvent(MouseButton mouseButton, const glm::vec2 &position, bool pressed)
{
	if (pressed)
	{
		static float yLookAt = 0.0f;

		this->viewingActive = true;
		if (mouseButton == MOUSEBUTTON_MIDDLE)
		{
			yLookAt += 1.0f;
			this->camera->setLookAt(glm::vec3(0.0f, yLookAt, 0.0f));
		}
	}
	else
		this->viewingActive = false;
}

void EventReceiver::onMouseMoveRelative(const glm::vec2 &relativePosition)
{
	if (this->viewingActive)
	{
		const float SPEED = 0.02f;
		glm::vec3 position = this->camera->getEntity()->getTransform()->getPosition();

		glm::vec3 direction = glm::normalize(position - glm::vec3(0, 0, 0));
		glm::vec3 right = glm::cross(direction, glm::vec3(0, 1, 0));
		glm::vec3 axis = glm::normalize((right * relativePosition.y) + (glm::vec3(0, 1, 0) * (-relativePosition.x)));
		float angle = relativePosition.length() * SPEED;
		
		direction = glm::rotate(direction, angle, axis);
		position = direction * this->cameraDistance;
		
		this->camera->setPosition(position);
	}
}

void EventReceiver::onMouseWheel(int direction)
{
	this->cameraDistance -= direction;
	
	glm::vec3 position = this->camera->getTransform()->getPosition();
	position = glm::normalize(position);
	position *= this->cameraDistance;

	this->camera->setPosition(position);
}

#include "EventReceiver.h"
#include <application/SampleApplication.h>
#include <glm/glm.hpp>

#include <glm/gtx/rotate_vector.hpp>

EventReceiver::EventReceiver(SampleApplication *application, CameraComponent *camera)
{
	this->application = application;
	this->camera = camera;

	glm::vec3 position(0, 0, 5);
	this->camera->setPosition(position);
	this->cameraDistance = glm::distance(position, glm::vec3(0, 0, 0));

	this->viewingActive = false;
}

void EventReceiver::onQuit()
{
	this->application->quit();
}

void EventReceiver::onKeyPressed(KeyboardButton key)
{
	if (key == KEY_ESC)
		this->application->quit();
}

void EventReceiver::onMouseButtonPressed(MouseButton mouseButton, const glm::vec2 &position)
{
	this->viewingActive = true;
}

void EventReceiver::onMouseButtonReleased(MouseButton mouseButton, const glm::vec2 &position)
{
	this->viewingActive = false;
}

void EventReceiver::onMouseMove(const glm::vec2 &relativePosition)
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

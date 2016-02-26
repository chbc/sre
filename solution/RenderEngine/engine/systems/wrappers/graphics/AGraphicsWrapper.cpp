#include "AGraphicsWrapper.h"
#include "OpenGLAPI.h"

namespace sre
{

std::unique_ptr<AGraphicsWrapper> AGraphicsWrapper::instance = std::unique_ptr<AGraphicsWrapper>{ nullptr };

AGraphicsWrapper *AGraphicsWrapper::getInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<AGraphicsWrapper>{ new OpenGLAPI{} };

	return instance.get();
}

void AGraphicsWrapper::TEST_drawTriangle()
{
	OpenGLAPI::TEST_drawTriangle();
}

} // namespace

#include "Texture.h"

namespace sre
{

Texture::Texture(uint32_t id, uint32_t width, uint32_t height, EMaterialMap::Type mapType, std::string fileName)
{
	this->id = id;
	this->width = width;
	this->height = height;
	this->mapType = mapType;
	this->fileName = fileName;
}

uint32_t Texture::getId()
{
	return this->id;
}

uint32_t Texture::getWidth()
{
	return this->width;
}

uint32_t Texture::getHeight()
{
	return this->height;
}

EMaterialMap::Type Texture::getMapType()
{
	return this->mapType;
}

const std::string &Texture::getFileName()
{
	return this->fileName;
}

} // namespace

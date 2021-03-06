#pragma once

#include "AEditorProperty.h"

namespace sre
{

class FloatEditorProperty : public AEditorProperty
{

private:
	float* value;

public:
	FloatEditorProperty(const char* title, float* arg_value);

	void draw() override;
};

} // namespace

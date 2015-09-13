#ifndef _LIGHT_NODE_H_
#define _LIGHT_NODE_H_

#include <engine/nodes/Node.h>
#include <string.h>

enum ELightType
{
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT = 1
};

namespace graphics
{
    class LightManager;
}

namespace nodes
{

/*!
	Base class to handle lighting.
*/
class LightNode : public Node
{
	private:
		Vector color;

	protected:
		Vector posDir;

		LightNode();

	public:
        void setColor(const Vector &color);
        virtual ELightType getType() =0;

    friend class graphics::LightManager;
};

} // namespace nodes

#endif

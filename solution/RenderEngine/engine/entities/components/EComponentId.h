#ifndef _E_COMPONENT_ID_H_
#define _E_COMPONENT_ID_H_

#include <cstddef>

namespace sre
{

namespace EComponentId
{

enum Type : std::size_t
{
    TRANSFORM = 0,
    CAMERA,
    DIRECTIONAL_LIGHT,
    POINT_LIGHT,
    MESH,

    COLOR_MATERIAL,
    DIFFUSE_MATERIAL,
    NORMAL_MATERIAL,
    SPECULAR_MATERIAL,
    AO_MATERIAL,

    GUI_IMAGE,
    GUI_TEXT,

    COLOR_RENDERER,
    DIFFUSE_RENDERER,
    NORMAL_RENDERER,
    SPECULAR_RENDERER,
    AO_RENDERER,

    SIZE
};

} // namespace

} // namespace
#endif
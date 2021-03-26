#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Angle.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include "app.hpp"

using namespace Magnum;
using namespace Math::Literals;

void TinyverseApp::mousePressEvent(MouseEvent& event)
{
    // Change color.
    color = Color3::fromHsv({color.hue() + 50.0_degf, 1.0f, 1.0f});
    event.setAccepted();
    redraw();
}

void TinyverseApp::mouseReleaseEvent(MouseEvent& event)
{
    event.setAccepted();
}

void TinyverseApp::mouseMoveEvent(MouseMoveEvent& event)
{
    if(!(event.buttons() & MouseMoveEvent::Button::Left))
        return;
    
    Vector2 delta = 3.0f*Vector2{event.relativePosition()}/Vector2{windowSize()};

    transformation = Matrix4::rotationX(Rad{delta.y()})*
    transformation* Matrix4::rotationY(Rad{delta.x()});

    event.setAccepted();
    redraw();
}

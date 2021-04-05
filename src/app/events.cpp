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

void TinyverseApp::viewportEvent(ViewportEvent& event)
{
    // Resize the main framebuffer.
    GL::defaultFramebuffer.setViewport({{}, event.framebufferSize()});

    // Recompute the camera's projection matrix. 
    camera->setViewport(event.framebufferSize());
}

void TinyverseApp::keyPressEvent(KeyEvent& event)
{
    if(event.key() == KeyEvent::Key::Space)
        simulation_running ^= true;
    
    event.setAccepted();
}

void TinyverseApp::keyReleaseEvent(KeyEvent& event)
{
    event.setAccepted();
}

void TinyverseApp::mousePressEvent(MouseEvent& event)
{
    previous_mouse_position = event.position();
    const Float current_depth = depth_at(event.position());
    const Float depth = current_depth == 1.0f ? last_depth : current_depth;
    translation_point = unproject(event.position(), depth);
    // Update the rotation point only if we're not zooming against infinite
    // depth or if the original rotation point is not yet initialized */
    if(current_depth != 1.0f || rotation_point.isZero())
    {
        rotation_point = translation_point;
        last_depth = depth;
    }

    mouse_pressed = true;

    event.setAccepted();
}

void TinyverseApp::mouseReleaseEvent(MouseEvent& event)
{
    event.setAccepted();
    mouse_pressed = false;
}

void TinyverseApp::mouseMoveEvent(MouseMoveEvent& event)
{
    const Vector2 delta = 3.0f*Vector2{event.position() - previous_mouse_position}/Vector2{framebufferSize()};
    previous_mouse_position = event.position();

    if(!event.buttons()) return;

    // Translate view
    if(event.modifiers() & MouseMoveEvent::Modifier::Shift)
    {
        const Vector3 p = unproject(event.position(), last_depth);
        camera_obj->translateLocal(translation_point - p);
        translation_point = p;
    }

    // Rotate around rotation point.
    else
    {
        camera_obj->transformLocal(
            Matrix4::translation(rotation_point)*
            Matrix4::rotationX(-0.51_radf*delta.y())*
            Matrix4::rotationY(-0.51_radf*delta.x())*
            Matrix4::translation(-rotation_point));
    }

    event.setAccepted();
}

void TinyverseApp::mouseScrollEvent(MouseScrollEvent& event)
{
    const Float delta = event.offset().y();
    if(Math::abs(delta) < 1.0e-2f)
        return;

    const Float current_depth = depth_at(event.position());
    const Float depth = current_depth == 1.0f ? last_depth : current_depth;
    const Vector3 p = unproject(event.position(), depth);

    // Update the rotation point only if we're not zooming against infinite
    // depth or if the original rotation point is not yet initialized.
    if(current_depth != 1.0f || rotation_point.isZero())
    {
        rotation_point = p;
        last_depth = depth;
    }

    // Move towards/backwards the rotation point in cam coords.
    camera_obj->translateLocal(rotation_point * delta * 0.1f);

    event.setAccepted();
}

void TinyverseApp::textInputEvent(TextInputEvent& event)
{
    event.setAccepted();
}

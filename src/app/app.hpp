#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <Corrade/Containers/Pointer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>

#include "renderer/particle_renderer.hpp"
#include "universe/universe.hpp"

using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
using Scene3D  = Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D>;

class TinyverseApp: public Magnum::Platform::Application 
{
public:
    explicit TinyverseApp(const Arguments& arguments);

private:
    void viewportEvent(ViewportEvent& event) override;
    void keyPressEvent(KeyEvent& event) override;
    void keyReleaseEvent(KeyEvent& event) override;
    void mousePressEvent(MouseEvent& event) override;
    void mouseReleaseEvent(MouseEvent& event) override;
    void mouseMoveEvent(MouseMoveEvent& event) override;
    void mouseScrollEvent(MouseScrollEvent& event) override;
    void textInputEvent(TextInputEvent& event) override;
    void drawEvent() override;
    
    // Helper functions for camera movement.
    Magnum::Float depth_at(const Magnum::Vector2i& window_position);
    Magnum::Vector3 unproject(const Magnum::Vector2i& window_position,
                              Magnum::Float depth) const;

    universe::Universe universe;

    Magnum::Containers::Pointer<ParticleRenderer> particle_renderer;

    // Note scene and all other drawable group must be constructed before
    // camera and drawable objects.
    Magnum::Containers::Pointer<Scene3D> scene;
    Magnum::Containers::Pointer<Magnum::SceneGraph::DrawableGroup3D> drawable_group;
    
    // All camera related magic.
    Magnum::Vector3 default_cam_position{0.0f, 1.5f, 8.0f};
    Magnum::Vector3 default_cam_target{0.0f, 1.0f, 0.0f};
    Magnum::Vector2i previous_mouse_position;
    Magnum::Vector3  rotation_point, translation_point;
    Magnum::Float last_depth;
    bool mouse_pressed = false;
    Magnum::Containers::Pointer<Object3D> camera_obj;
    Magnum::Containers::Pointer<Magnum::SceneGraph::Camera3D> camera;
};

#endif

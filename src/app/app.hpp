#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/Shaders/Phong.h>

class TinyverseApp : public Magnum::Platform::Application 
{
public:
    explicit TinyverseApp(const Arguments& arguments);

private:
    void drawEvent() override;
    void mousePressEvent(MouseEvent& event) override;
    void mouseReleaseEvent(MouseEvent& event) override;
    void mouseMoveEvent(MouseMoveEvent& event) override;

    Magnum::GL::Mesh mesh;
    Magnum::Matrix4 directionalLight, pointLight1, pointLight2;
    Magnum::Shaders::Phong shader; // 3 lights
    Magnum::Matrix4 transformation, projection;
    Magnum::Color3 color;
};

#endif

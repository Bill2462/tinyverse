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

void TinyverseApp::drawEvent()
{
    GL::defaultFramebuffer.clear(
        GL::FramebufferClear::Color | GL::FramebufferClear::Depth);
    
    Containers::ArrayView<const Vector3> directions;
    shader.setLightPosition({7.0f, 5.0f, 2.5f});
    shader.setLightColor(Color3{1.0f});
    shader.setDiffuseColor(color);
    shader.setTransformationMatrix(transformation);
    shader.setNormalMatrix(transformation.normalMatrix());
    shader.setProjectionMatrix(projection);
    shader.draw(mesh);

    swapBuffers();
}
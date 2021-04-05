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
    GL::defaultFramebuffer.clear(GL::FramebufferClear::Color | 
    GL::FramebufferClear::Depth);

    particle_renderer->update_displayed_particles();
    particle_renderer->draw_particles(camera, framebufferSize());
    camera->draw(*drawable_group);

    swapBuffers();
    redraw();
    
    if(simulation_running)
        universe.simulation_step();
}
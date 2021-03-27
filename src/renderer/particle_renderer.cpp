#include "particle_renderer.hpp"
#include <Corrade/Utility/Assert.h>
#include <Corrade/Containers/ArrayView.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Functions.h>
#include <Magnum/Shaders/Generic.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Trade/MeshData.h>

using namespace Magnum;
using namespace Math::Literals;

ParticleRenderer::ParticleRenderer(const Real* position_data, std::size_t n_points):
mesh_particles(GL::MeshPrimitive::Points)
{
    mesh_particles.addVertexBuffer(particle_position_buffer, 0,
    Shaders::Generic3D::Position{});

    particle_shader.reset(new ParticleShader);
    set_particles(position_data, n_points);
}

ParticleRenderer::ParticleRenderer(const Real* position_data, std::size_t n_points,
                                   const Settings& settings)
{
    ParticleRenderer(position_data,  n_points);
    set_settings(settings);
}

void ParticleRenderer::set_particles(const Real* position_data, std::size_t n_points)
{
    this->position_data = position_data;
    this->n_points = n_points;
}

void ParticleRenderer::set_settings(const ParticleRenderer::Settings& settings)
{
    this->settings = settings;
}

ParticleRenderer::Settings ParticleRenderer::get_settings() const
{
    return settings;
}

void ParticleRenderer::draw_particles(Containers::Pointer<SceneGraph::Camera3D>& camera,
                                      const Vector2i& viewport_size)
{
    if(should_update_particles)
    {
        Containers::ArrayView<const float> data(position_data, n_points*3);
        particle_position_buffer.setData(data);
        mesh_particles.setCount(n_points);
        should_update_particles = false;
    }

    (*particle_shader).set_particle_number(static_cast<int>(n_points));
    (*particle_shader).set_particle_radius(settings.particle_radius);
    
    // tan(half field-of-view angle (45_deg)
    (*particle_shader).set_point_size_scale(
    static_cast<float>(viewport_size.y()) / Math::tan(22.5_degf));

    (*particle_shader).set_color_mode(settings.color_mode);
    (*particle_shader).set_ambient_color(settings.ambient_color);
    (*particle_shader).set_diffuse_color(settings.diffuse_color);
    (*particle_shader).set_specular_color(settings.specular_color);
    (*particle_shader).set_shininess(settings.shininess);
    (*particle_shader).set_light_direction(settings.light_dir);

    (*particle_shader).set_view_matrix(camera->cameraMatrix());
    (*particle_shader).set_projection_matrix(camera->projectionMatrix());
    (*particle_shader).draw(mesh_particles);
}

void ParticleRenderer::update_displayed_particles()
{
    should_update_particles = true;
}

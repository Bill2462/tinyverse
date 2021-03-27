#ifndef PARTICLE_RENDERER_H_INCLUDED
#define PARTICLE_RENDERER_H_INCLUDED

#include "common_types.hpp"
#include "shaders/particle_shader.hpp"
#include <Corrade/Containers/Pointer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Math/Color.h>
#include <Magnum/SceneGraph/Camera.h>

// Class that is responsible for rendering a group of particles.
// You pass settings, pointer to memory where particle positions are stored
// as 3D vectors and size of that memory location and particles are rendered.
class ParticleRenderer
{
public:

    struct Settings
    {
        ParticleShader::ColorMode color_mode = ParticleShader::ColorMode::RAMP_COLOR_BY_ID;
        Magnum::Float particle_radius = 1.0f;
        Magnum::Color3 ambient_color{0.1f};
        Magnum::Color3 diffuse_color{0.0f, 0.5f, 0.9f};
        Magnum::Color3 specular_color{1.0f};
        Magnum::Float shininess = 150.0f;
        Magnum::Vector3 light_dir{1.0f, 1.0f, 2.0f};
    };

    ParticleRenderer(const Real* position_data, std::size_t n_points);
    ParticleRenderer(const Real* position_data, std::size_t n_points,
                     const Settings& settings);
    
    void draw_particles(Magnum::Containers::Pointer<Magnum::SceneGraph::Camera3D>& camera,
                        const Magnum::Vector2i& viewportSize);
    
    void set_particles(const Real* position_data, std::size_t n_points);
    
    void set_settings(const Settings& settings);
    Settings get_settings() const;

    // Renderer will update displayed particles on the next call of draw method.
    void update_displayed_particles();

private:
    Settings settings;
    const Real* position_data;
    std::size_t n_points;
    bool should_update_particles = true;
    
    Magnum::GL::Buffer particle_position_buffer;
    Magnum::GL::Mesh mesh_particles;
    Magnum::Containers::Pointer<ParticleShader> particle_shader;
};

#endif

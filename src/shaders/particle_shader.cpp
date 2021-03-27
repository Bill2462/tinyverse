#include "particle_shader.hpp"
#include <Corrade/Containers/Reference.h>
#include <Corrade/Utility/Resource.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix4.h>

using namespace Magnum;

ParticleShader::ParticleShader()
{
    Utility::Resource rs("shaders");
    GL::Shader vert_shader{GL::Version::GL330, GL::Shader::Type::Vertex};
    GL::Shader frag_shader{GL::Version::GL330, GL::Shader::Type::Fragment};
    vert_shader.addSource(rs.get("particle_shader.vert"));
    frag_shader.addSource(rs.get("particle_shader.frag"));

    CORRADE_INTERNAL_ASSERT(GL::Shader::compile({vert_shader, frag_shader}));
    attachShaders({vert_shader, frag_shader});
    CORRADE_INTERNAL_ASSERT(link());

    u_num_particles = uniformLocation("numParticles");
    u_particle_radius = uniformLocation("particleRadius");

    u_point_size_scale = uniformLocation("pointSizeScale");
    u_color_mode = uniformLocation("colorMode");
    u_ambient_color = uniformLocation("ambientColor");
    u_diffuse_color = uniformLocation("diffuseColor");
    u_specular_color = uniformLocation("specularColor");
    u_shininess = uniformLocation("shininess");

    u_view_matrix = uniformLocation("viewMatrix");
    u_projection_matrix = uniformLocation("projectionMatrix");
    u_light_dir = uniformLocation("lightDir");
}

void ParticleShader::set_particle_number(Magnum::Int num)
{
    setUniform(u_num_particles, num);
}

void ParticleShader::set_particle_radius(Magnum::Float radius)
{
    setUniform(u_particle_radius, radius);
}

void ParticleShader::set_point_size_scale(Magnum::Float scale)
{
    setUniform(u_point_size_scale, scale);
}

void ParticleShader::set_color_mode(ParticleShader::ColorMode color_mode)
{
    setUniform(u_color_mode, static_cast<Int>(color_mode));
}

void ParticleShader::set_ambient_color(const Magnum::Color3& color)
{
    setUniform(u_ambient_color, color);
}

void ParticleShader::set_diffuse_color(const Magnum::Color3& color)
{
    setUniform(u_diffuse_color, color);
}

void ParticleShader::set_specular_color(const Magnum:: Color3& color)
{
    setUniform(u_specular_color, color);
}

void ParticleShader::set_shininess(Magnum::Float shininess)
{
    setUniform(u_shininess, shininess);
}

void ParticleShader::set_view_matrix(const Magnum::Matrix4& matrix)
{
    setUniform(u_view_matrix, matrix);
}

void ParticleShader::set_projection_matrix(const Magnum::Matrix4& matrix)
{
    setUniform(u_projection_matrix, matrix);
}

void ParticleShader::set_light_direction(const Magnum::Vector3& light_dir)
{
    setUniform(u_light_dir, light_dir);
}

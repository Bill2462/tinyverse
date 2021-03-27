#ifndef PARTICLE_SHADER_HPP_INCLUDED
#define PARTICLE_SHADER_HPP_INCLUDED

#include <Magnum/GL/AbstractShaderProgram.h>

class ParticleShader: public Magnum::GL::AbstractShaderProgram
{
public:
    enum class ColorMode
    {
        UNIFORM_DIFFUSE_COLOR = 0,
        RAMP_COLOR_BY_ID,
        CONSISTENT_RADOM
    };

    explicit ParticleShader();
    void set_particle_number(Magnum::Int num);
    void set_particle_radius(Magnum::Float radius);

    void set_point_size_scale(Magnum::Float scale);
    void set_color_mode(ColorMode color_mode);
    void set_ambient_color(const Magnum::Color3& color);
    void set_diffuse_color(const Magnum::Color3& color);
    void set_specular_color(const Magnum:: Color3& color);
    void set_shininess(Magnum::Float shininess);

    void set_view_matrix(const Magnum::Matrix4& matrix);
    void set_projection_matrix(const Magnum::Matrix4& matrix);
    void set_light_direction(const Magnum::Vector3& light_dir);
    
private:
    Magnum::Int u_num_particles,
        u_particle_radius,
        u_point_size_scale,
        u_color_mode,
        u_ambient_color,
        u_diffuse_color,
        u_specular_color,
        u_shininess,
        u_view_matrix,
        u_projection_matrix,
        u_light_dir;
};

#endif

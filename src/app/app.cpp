#include <Corrade/Utility/StlMath.h>
#include <Magnum/Image.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/Version.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/FunctionsBatch.h>
#include <spdlog/spdlog.h>
#include "app.hpp"
#include "config.h"
#include "physics/universe_initializers/universe_initializers.hpp"

const char* BANNER = "\n"
"d888888P oo                                                                \n"
"   88                                                                      \n"
"   88    dP 88d888b. dP    dP dP   .dP .d8888b. 88d888b. .d8888b. .d8888b. \n"
"   88    88 88   `88 88    88 88   d8  88ooood8 88'  `88 Y8ooooo. 88ooood8 \n"
"   88    88 88    88 88.  .88 88 .88   88.  ... 88             88 88.  ... \n"
"   dP    dP dP    dP `8888P88 8888P    `88888P' dP       `88888P' `88888P' \n"
"                          .88                                              \n"
"                      d8888P                                               \n";

using namespace Magnum;
using namespace Math::Literals;

TinyverseApp::TinyverseApp(const Arguments& arguments):
Platform::Application{arguments, NoCreate}
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info(BANNER);
    spdlog::info(std::string("Welcome to Tinyverse version ") +
                 std::to_string(PROJECT_VERSION_MAJOR) + 
                 std::string(".") +
                 std::to_string(PROJECT_VERSION_MINOR) +
                 "!");

    // Setting up window.
    spdlog::debug("Setting up window...");

    const Vector2 dpi_scaling = this->dpiScaling({});
    Configuration window_conf;
    window_conf.setTitle("Tinyverse");
    window_conf.setSize(window_conf.size(), dpi_scaling);
    window_conf.setWindowFlags(Configuration::WindowFlag::Resizable);

    GLConfiguration gl_conf;
    gl_conf.setSampleCount(dpi_scaling.max() < 2.0f ? 8 : 2);
     if(!tryCreate(window_conf, gl_conf))
        create(window_conf, gl_conf.setSampleCount(0));

    spdlog::debug("Initializing camera and scene ...");
    scene.reset(new Scene3D{});
    drawable_group.reset(new SceneGraph::DrawableGroup3D{});

    // Configure camera
    camera_obj.reset(new Object3D{scene.get() });
    camera_obj->setTransformation(Matrix4::lookAt(Vector3(0, 1.5, 8), Vector3(0, 1, 0), Vector3(0, 1, 0)));

    const auto viewportSize = GL::defaultFramebuffer.viewport().size();
    camera.reset(new SceneGraph::Camera3D{*camera_obj});
    camera->setProjectionMatrix(Matrix4::perspectiveProjection(45.0_degf, Vector2{viewportSize}.aspectRatio(), 0.01f, 1000.0f));
    camera->setViewport(viewportSize);

    // Set default camera parameters.
    default_cam_position = Vector3(1.5f, 3.3f, 6.0f);
    default_cam_target   = Vector3(1.5f, 1.3f, 0.0f);
    camera_obj->setTransformation(Matrix4::lookAt(default_cam_position, default_cam_target, Vector3(0, 1, 0)));

    /* Initialize depth to the value at scene center */
    last_depth = ((camera->projectionMatrix() * camera->cameraMatrix()).transformPoint({}).z() + 1.0f) * 0.5f;

    const size_t n_body = 2;
    universe.set_size(n_body);
    auto initializer = std::make_shared<TwoBodyInitializer>();
    TwoBodyInitializer::Config universe_initializer_config;
    universe_initializer_config.body1_mass = 1000;
    universe_initializer_config.body2_mass = 10;
    universe_initializer_config.body2_position = {0, 0, 1};
    universe_initializer_config.body2_velocity = {0, 32, 0};
    initializer->set_config(universe_initializer_config);
    universe.apply_initializer(initializer);
    
    spdlog::debug("Initializing renderer...");
    particle_renderer.reset(new ParticleRenderer(universe.get_positions().data(), n_body));
    ParticleRenderer::Settings renderer_settings = particle_renderer->get_settings();
    renderer_settings.particle_radius = 0.1;
    renderer_settings.color_mode = ParticleShader::ColorMode::CONSISTENT_RADOM;
    particle_renderer->set_settings(renderer_settings);

    // Enable depth test, render particles as sprites.
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::ProgramPointSize);

    // Start the timer, loop at 60 Hz max.
    setMinimalLoopPeriod(16);
}

Float TinyverseApp::depth_at(const Vector2i& window_position)
{
    // First scale the position from being relative to window size to being
    // relative to framebuffer size as those two can be different on HiDPI
    // systems.
    const Vector2i position = window_position*Vector2{framebufferSize()}/Vector2{windowSize()};
    const Vector2i fb_position{position.x(), GL::defaultFramebuffer.viewport().sizeY() - position.y() - 1};

    GL::defaultFramebuffer.mapForRead(GL::DefaultFramebuffer::ReadAttachment::Front);
    
    Image2D data = GL::defaultFramebuffer.read(
        Range2Di::fromSize(fb_position, Vector2i{1}).padded(Vector2i{2}),
        {GL::PixelFormat::DepthComponent, GL::PixelType::Float});

    return Math::min<Float>(Containers::arrayCast<const Float>(data.data()));
}

Vector3 TinyverseApp::unproject(const Vector2i& window_position, Float depth) const
{
    // We have to take window size, not framebuffer size, since the position is
    // in window coordinates and the two can be different on HiDPI systems.
    const Vector2i viewSize = windowSize();
    const Vector2i view_position = Vector2i{window_position.x(), viewSize.y() - window_position.y() - 1};
    const Vector3 in{2.0f*Vector2{view_position}/Vector2{viewSize} - Vector2{1.0f}, depth*2.0f - 1.0f};

    return camera->projectionMatrix().inverted().transformPoint(in);
}

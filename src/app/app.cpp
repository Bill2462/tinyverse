#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Angle.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include "app.hpp"
#include "config.h"
#include <spdlog/spdlog.h>

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
Platform::Application{arguments, Configuration{}.setTitle("Rotating cube!")}
{
    spdlog::info(BANNER);
    spdlog::info(std::string("Welcome to Tinyverse version ") +
                 std::to_string(PROJECT_VERSION_MAJOR) + 
                 std::string(".") +
                 std::to_string(PROJECT_VERSION_MINOR) +
                 "!");
    
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);

    Trade::MeshData cube = Primitives::cubeSolid();

    GL::Buffer vertices;
    vertices.setData(MeshTools::interleave(cube.positions3DAsArray(),
                                           cube.normalsAsArray()));

    std::pair<Containers::Array<char>, MeshIndexType> compressed =
        MeshTools::compressIndices(cube.indicesAsArray());
    
    GL::Buffer indices;
    indices.setData(compressed.first);

    mesh.setPrimitive(cube.primitive());
    mesh.setCount(cube.indexCount());
    mesh.addVertexBuffer(std::move(vertices), 0, Shaders::Phong::Position{}, Shaders::Phong::Normal{});
    mesh.setIndexBuffer(std::move(indices), 0, compressed.second);

    // Initialize projecttion and transformation relatex matrixes.
    transformation = Matrix4::rotationX(30.0_degf)*Matrix4::rotationY(40.0_degf);
    projection = Matrix4::perspectiveProjection(35.0_degf, Vector2{windowSize()}.aspectRatio(), 0.01f, 100.0f)*
    Matrix4::translation(Vector3::zAxis(-10.0f));

    // Initialize color.
    color = Color3::fromHsv({35.0_degf, 1.0f, 1.0f});
}

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <spdlog/spdlog.h>
#include "log/log.hpp"

int main(int argc, char* argv[])
{
    sf::Window window(sf::VideoMode(800, 600), "tinyverse");
    log_configuration(window.getSettings());
    window.setActive(true);
    
    bool running = true;
    while(running)
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                running = false;
                break;

                // Resize OpenGL viewport when window is resized.
                case sf::Event::Resized:
                glViewport(0, 0, event.size.width, event.size.height);
                break;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // End the current frame (internally swaps the front and back buffers).
        window.display();
    }

    return 0;
}

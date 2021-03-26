#include <SFML/Window.hpp>
#include <spdlog/spdlog.h>
#include "log/log.hpp"

int main(int argc, char* argv[])
{
    sf::Window window(sf::VideoMode(800, 600), "tinyverse");
    log_configuration(window.getSettings());

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            switch(e.type)
            {
            case sf::Event::EventType::Closed:
                window.close();
                break;
            }
        }
    }

    return 0;
}

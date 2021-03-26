#include <SFML/Window.hpp>

int main(int argc, char* argv[])
{
    sf::Window window(sf::VideoMode(800, 600), "tinyverse");
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

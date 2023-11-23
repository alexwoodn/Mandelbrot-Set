#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"

int main() {
    // Get desktop resolution
    unsigned int screenWidth = sf::VideoMode::getDesktopMode().width / 2;
    unsigned int screenHeight = sf::VideoMode::getDesktopMode().height / 2;

    // Construct the RenderWindow
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Complex Plane Visualization");

    // Construct the ComplexPlane
    ComplexPlane complexPlane(screenWidth, screenHeight);

    // Construct the Font and Text objects
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    // Main loop
    while (window.isOpen()) {
        // Handle Input segment
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        // Right click to zoom out
                        complexPlane.zoomOut(event.mouseButton.x, event.mouseButton.y);
                        complexPlane.setCalculationState(ComplexPlane::CalculationState::CALCULATING);
                    } else if (event.mouseButton.button == sf::Mouse::Left) {
                        // Left click to zoom in
                        complexPlane.zoomIn(event.mouseButton.x, event.mouseButton.y);
                        complexPlane.setCalculationState(ComplexPlane::CalculationState::CALCULATING);
                    }
                    break;

                case sf::Event::MouseMoved:
                    // Store mouse location for later use
                    complexPlane.setMouseLocation(event.mouseMove.x, event.mouseMove.y);
                    break;

                default:
                    break;
            }
        }

        // Check if Escape key is pressed to close the window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        // Update Scene segment
        complexPlane.updateRender();
        complexPlane.loadText();
        
        // Draw Scene segment
        window.clear();
        window.draw(complexPlane);
        text.setString("Mouse Coordinates: (" + std::to_string(complexPlane.getMouseX()) + ", " +
                        std::to_string(complexPlane.getMouseY()) + ")");
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}

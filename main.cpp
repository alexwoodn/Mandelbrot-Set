#include <SFML/Graphics.hpp>
#include "ComplexPlane.cpp"

using namespace sf;

int main() {
    // Get desktop resolution
    unsigned int screenWidth = VideoMode::getDesktopMode().width / 2;
    unsigned int screenHeight = VideoMode::getDesktopMode().height / 2;

    // Construct the RenderWindow
    RenderWindow window(VideoMode(screenWidth, screenHeight), "Complex Plane Visualization");

    // Construct the ComplexPlane
    ComplexPlane complexPlane(screenWidth, screenHeight);

    // Construct the Font and Text objects
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font loading error
        return EXIT_FAILURE;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);

    // Main loop
    while (window.isOpen()) {
        // Handle Input segment
        Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Right) {
                        // Right click to zoom out
                        complexPlane.zoomOut(event.mouseButton.x, event.mouseButton.y);
                        complexPlane.setCalculationState(ComplexPlane::CalculationState::CALCULATING);
                    } else if (event.mouseButton.button == Mouse::Left) {
                        // Left click to zoom in
                        complexPlane.zoomIn(event.mouseButton.x, event.mouseButton.y);
                        complexPlane.setCalculationState(ComplexPlane::CalculationState::CALCULATING);
                    }
                    break;

                case Event::MouseMoved:
                    // Store mouse location for later use
                    complexPlane.setMouseLocation(event.mouseMove.x, event.mouseMove.y);
                    break;

                default:
                    break;
            }
        }

        // Check if Escape key is pressed to close the window
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // Update Scene segment
        complexPlane.updateRender();

        // Load the text into the sf::Text object
        complexPlane.loadText(text);

        // Draw Scene segment
        window.clear();
        window.draw(complexPlane);
        window.draw(text);  // Draw the text
        window.display();
    }

    return EXIT_SUCCESS;
}

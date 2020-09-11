#include <SFML/Window.hpp>
#include "Program.h"
using namespace std;
using namespace sf;

int main() {
    //========Setup========
    RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    Program program;
    program.Initialize(window);
//========Execution========
    while (window.isOpen()) { //loop for game events until closed
        Event event;
        while (window.pollEvent(event)) {
            Vector2i position = Mouse::getPosition(window);
            if (event.type == Event::Closed) { //Event for closing window
                window.close();
            }
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    program.LeftMouseClick(position);
                }
                if (event.mouseButton.button == Mouse::Right) {
                    program.RightMouseClick(position);
                }
            }
        }
        program.Draw();
    }
    //========Shut Down========
    program.Shutdown();
    return 0;
}

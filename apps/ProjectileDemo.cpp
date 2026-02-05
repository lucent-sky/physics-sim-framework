#include <SFML/Graphics.hpp>
#include "physics/Simulation.h"
#include "viz/SfmlRenderer.h"
#include <optional>
#include <variant>
#include <vector>
#include <iostream> // <-- needed for std::cout

sf::Vector2f toScreen(
    const Body& body,
    float ppm,
    const sf::Vector2f& origin)
{
    return sf::Vector2f{
        origin.x + static_cast<float>(body.position.x) * ppm,
        origin.y - static_cast<float>(body.position.y) * ppm
    };
}

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u{800, 600}), "Projectile Motion");
    window.setFramerateLimit(60);

    std::vector<sf::Vertex> trajectory;
    trajectory.reserve(2000);

    Simulation sim(9.81, 0.05, 1.0/60.0);
    Body projectile{{0.0, 0.0}, {20.0, 30.0}, 1.0};
    sim.addBody(projectile);

    SfmlRenderer renderer(10.0f, sf::Vector2f(100.0f, 500.0f));

    while (window.isOpen())
    {
        while (auto eOpt = window.pollEvent())
        {
            eOpt->visit(overloaded{
                [&](const sf::Event::Closed&) { window.close(); },
                [&](const sf::Event::KeyPressed& key) {
                    if (key.code == sf::Keyboard::Key::Escape)
                        std::cout << "Escape pressed!\n";
                },
                [&](const sf::Event::MouseButtonPressed& mouse) {
                    std::cout << "Mouse button " << static_cast<int>(mouse.button)
                            << " pressed at (" << mouse.position.x << ", " << mouse.position.y << ")\n";
                },
                [&](auto&) {} // catch-all for any other events
            });
        }

        // Simulation step
        sim.step();

        sf::Vector2f screenPos = toScreen(sim.bodies()[0], 10.0f, sf::Vector2f(100.0f, 500.0f));
        trajectory.emplace_back(sf::Vertex{screenPos, sf::Color::Yellow});

        window.clear(sf::Color::Black);
        if (trajectory.size() > 1)
            window.draw(trajectory.data(), trajectory.size(), sf::PrimitiveType::LineStrip);

        renderer.drawBody(window, sim.bodies()[0]);
        window.display();
    }
}

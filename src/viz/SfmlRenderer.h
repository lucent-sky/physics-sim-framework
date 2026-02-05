#pragma once
#include <SFML/Graphics.hpp>
#include "physics/Simulation.h"

class SfmlRenderer
{
public:
    SfmlRenderer(float ppm, sf::Vector2f origin);

    void drawBody(sf::RenderWindow& window, const Body& body);

private:
    float ppm_;
    sf::Vector2f origin_;
};

#include "SfmlRenderer.h"

SfmlRenderer::SfmlRenderer(float ppm, sf::Vector2f origin)
    : ppm_(ppm), origin_(origin) {}

void SfmlRenderer::drawBody(sf::RenderWindow& window, const Body& body)
{
    sf::CircleShape circle(5.0f);
    circle.setFillColor(sf::Color::Red);

    float x = origin_.x + static_cast<float>(body.position.x) * ppm_;
    float y = origin_.y - static_cast<float>(body.position.y) * ppm_;

    circle.setPosition(sf::Vector2f(x, y));
    window.draw(circle);
}

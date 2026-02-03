#pragma once

struct Vector2 {
    double x;
    double y;

    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }
};

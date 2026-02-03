#pragma once
#include "../math/Vector2.h"
#include "Body.h"

namespace Forces {


inline Vector2 gravity(const Body& body, double g) {
    return Vector2{0.0, -body.mass * g};
}

inline Vector2 linearDrag(const Body& body, double k) {
    return body.velocity * (-k);
}

inline Vector2 netForce(
    const Body& body,
    double g,
    double dragCoeff
) {
    return gravity(body, g) + linearDrag(body, dragCoeff);
}

}

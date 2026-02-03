#pragma once
#include "Body.h"
#include "../math/Vector2.h"

namespace Integrator {

inline void euler(
    Body& body,
    const Vector2& force,
    double dt
) {
    Vector2 acceleration = force * (1.0 / body.mass);

    body.velocity = body.velocity + acceleration * dt;
    body.position = body.position + body.velocity * dt;
}

}

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "physics/Body.h"
#include "physics/Forces.h"
#include "physics/Integrator.h"

TEST_CASE("Gravity accelerates downward") {
    Body b{{0.0, 0.0}, {0.0, 0.0}, 1.0};

    REQUIRE(b.mass == Catch::Approx(1.0));
}

TEST_CASE("Gravity force points downward") {
    Body b{{0,0}, {0,0}, 2.0};
    double g = 9.81;

    auto F = Forces::gravity(b, g);

    REQUIRE(F.x == Catch::Approx(0.0));
    REQUIRE(F.y == Catch::Approx(-19.62));
}

TEST_CASE("Euler integration updates velocity under gravity") {
    Body b{{0,0}, {0,0}, 1.0};
    double g = 9.81;
    double dt = 0.1;

    auto F = Forces::gravity(b, g);
    Integrator::euler(b, F, dt);

    REQUIRE(b.velocity.y == Catch::Approx(-0.981));
}

TEST_CASE("Drag opposes velocity") {
    Body b{{0,0}, {10,0}, 1.0};
    double k = 0.5;

    auto F = Forces::linearDrag(b, k);

    REQUIRE(F.x == Catch::Approx(-5.0));
    REQUIRE(F.y == Catch::Approx(0.0));
}
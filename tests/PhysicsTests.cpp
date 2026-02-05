#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <filesystem>

#include "physics/Body.h"
#include "physics/Forces.h"
#include "physics/Integrator.h"
#include "physics/Simulation.h"
#include "io/CsvLogger.h"

double totalEnergy(const Body& body, double gravity)
{
    double kinetic =
        0.5 * body.mass * body.velocity.lengthSquared();

    double potential =
        body.mass * gravity * body.position.y;

    return kinetic + potential;
}

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

TEST_CASE("Simulation time advances by fixed timestep") {
    Simulation sim(9.81, 0.0, 0.1);
    Body b{{0,0}, {0,0}, 1.0};

    sim.step();
    sim.step();

    REQUIRE(sim.time() == Catch::Approx(0.2));
}

TEST_CASE("Projectile falls under gravity in simulation") {
    Simulation sim(9.81, 0.0, 0.1);
    Body b{{0,10}, {0,0}, 1.0};

    sim.addBody(b);
    sim.step();

    REQUIRE(sim.bodies()[0].position.y < 10.0);
}

TEST_CASE("Drag reduces horizontal velocity") {
    Simulation sim(9.81, 0.5, 0.1);
    Body b{{0,0}, {10,0}, 1.0};

    sim.addBody(b);
    sim.step();

    REQUIRE(sim.bodies()[0].velocity.x < 10.0);
}

// NOTE: does not test correctness of logs!! only tests existence
TEST_CASE("CSV log file is created") {
    {
        CsvLogger logger("test_log.csv");
        Body b{{0,0}, {1,1}, 1.0};
        logger.log(0.0, b);
    }

    REQUIRE(std::filesystem::exists("test_log.csv"));
}

//NOTE: this test assers that it will fail, using a large timestep to showcase instability
TEST_CASE("Explicit Euler becomes unstable with large timestep", "[instability]")
{
    const double gravity = 9.81;
    const double dt = 0.5;

    Body projectile{{0,0}, {10,10}, 1.0};

    Simulation sim(gravity, 0.0, dt);
    sim.addBody(projectile);

    for (int i = 0; i < 200; ++i)
        sim.step();

    const auto& b = sim.bodies()[0];

    REQUIRE(std::abs(b.position.y) > 1000.0);
}
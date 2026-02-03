#pragma once

#include "Body.h"
#include "Forces.h"
#include "Integrator.h"

class Simulation {
public:
    Simulation(double gravity, double dragCoeff, double dt)
        : g_(gravity), drag_(dragCoeff), dt_(dt), time_(0.0) {}

    void step(Body& body) {
        auto force = Forces::netForce(body, g_, drag_);
        Integrator::euler(body, force, dt_);
        time_ += dt_;
    }

    double time() const { return time_; }

private:
    double g_;
    double drag_;
    double dt_;
    double time_;
};

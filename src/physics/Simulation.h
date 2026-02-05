#pragma once

#include <vector>
#include "Body.h"
#include "Forces.h"
#include "Integrator.h"

class Simulation {
public:
    Simulation(double gravity, double dragCoeff, double dt)
        : g_(gravity), drag_(dragCoeff), dt_(dt), time_(0.0) {}

    void addBody(const Body& body) {
        bodies_.push_back(body);
    }

    void step() {
        for (auto& body : bodies_) {
            auto force = Forces::netForce(body, g_, drag_);
            Integrator::euler(body, force, dt_);
        }
        time_ += dt_;
    }

    const std::vector<Body>& bodies() const {
        return bodies_;
    }

    double time() const {
        return time_;
    }

private:
    double g_;
    double drag_;
    double dt_;
    double time_;
    std::vector<Body> bodies_;
};

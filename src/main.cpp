#include "physics/Simulation.h"
#include "io/CsvLogger.h"

int main() {
    Body projectile{
        {0.0, 0.0},
        {10.0, 10.0},
        1.0
    };

    Simulation sim(9.81, 0.1, 0.01);
    CsvLogger logger("trajectory.csv");

    for (int i = 0; i < 1000; ++i) {
        logger.log(sim.time(), projectile);
        sim.step(projectile);
    }

    return 0;
}

#pragma once
#include <fstream>
#include "../physics/Body.h"

class CsvLogger {
public:
    CsvLogger(const std::string& filename) : file_(filename) {
        file_ << "time,x,y,vx,vy\n";
    }

    void log(double time, const Body& body) {
        file_
            << time << ","
            << body.position.x << ","
            << body.position.y << ","
            << body.velocity.x << ","
            << body.velocity.y << "\n";
    }

private:
    std::ofstream file_;
};

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/Vector2.h"

TEST_CASE("Vector addition") {
    Vector2 a{1.0, 2.0};
    Vector2 b{3.0, 4.0};
    auto c = a + b;

    REQUIRE(c.x == Catch::Approx(4.0));
    REQUIRE(c.y == Catch::Approx(6.0));
}

TEST_CASE("Vector scaling") {
    Vector2 v{2.0, -3.0};
    auto s = v * 2.0;

    REQUIRE(s.x == Catch::Approx(4.0));
    REQUIRE(s.y == Catch::Approx(-6.0));
}

#pragma once
#include <exception>

#include "Scene.hpp"

class StdRayTracer {
public:
    void render(Scene scene);
};

class FixedAntiAliasingRayTracer {
protected:
    int sqrtAAPower;

public:
    int getAAPower() { return this->sqrtAAPower; }
    void setAAPower(int pow) { this->sqrtAAPower = pow; }

    void render(Scene scene);

    explicit FixedAntiAliasingRayTracer() : sqrtAAPower(4) {}
    explicit FixedAntiAliasingRayTracer(int pow) { this->sqrtAAPower = pow; }
};

/*class StochasticAntiAliasingRayTracer {
protected:
    int minSteps;

public:

    void render(Scene scene);
};*/

class SuperSampler {};
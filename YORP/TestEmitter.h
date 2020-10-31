#pragma once
#include <list>
#include "Ray.h"
template<size_t numberOfRays>
class TestEmitter{
public :
    TestEmitter(double radius);
    ~TestEmitter() = default;

    std::list<Ray> rays;
};



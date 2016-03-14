#pragma once

#include <vector>

#include "testcollection.h"

namespace unit {
class TestRunner;
}

class unit::TestRunner : public TestCollection {
public:
    void run();
};

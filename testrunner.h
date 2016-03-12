#pragma once

#include <vector>

#include "testcollection.h"

namespace unit {
class TestRunner : public TestCollection {
public:
    void run();
};
}

#pragma once

#include "testcollection.h"
#include "itest.h"

namespace unit {
class TestSet;
}

class unit::TestSet : public TestCollection, public ITest {
    std::string name;
    int maxNameLength;

public:
    TestSet(const std::string &name);

    void addTest(ITest *$);

    std::string getName();
    void run();
    void report();
};

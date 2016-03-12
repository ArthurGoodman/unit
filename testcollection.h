#pragma once

#include <vector>

namespace unit {
class ITest;

class TestCollection {
    std::vector<ITest *> tests;

public:
    ~TestCollection();

    virtual void addTest(ITest *test);

    std::vector<ITest *>::iterator begin();
    std::vector<ITest *>::iterator end();
};
}

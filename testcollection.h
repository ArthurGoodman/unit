#pragma once

#include <vector>
#include <string>
#include <functional>

namespace unit {
class ITest;
class TestCollection;
}

class unit::TestCollection {
    std::vector<ITest *> tests;

public:
    ~TestCollection();

    virtual void addTest(ITest *test);

    virtual void $(const std::string &name, const std::string &result, const std::function<void()> &f);

    std::vector<ITest *>::iterator begin();
    std::vector<ITest *>::iterator end();
};

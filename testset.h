#pragma once

#include <string>
#include <functional>

#include "testcollection.h"
#include "itest.h"

namespace unit {
class TestSet : public TestCollection, public ITest {
    std::string name;
    int maxNameLength;

public:
    TestSet(const std::string &name);

    void addTest(ITest *test);

    std::string getName();

    void run();

    void report();

    void test(const std::string &name, const std::string &result, const std::function<void()> &f);
};
}

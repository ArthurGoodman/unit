#pragma once

#include <vector>

namespace unit {
class Test;

class __declspec(dllexport) TestManager {
    std::vector<Test *> tests;

public:
    static TestManager &instance();

    void addTest(Test *test);

    void run();
};
}

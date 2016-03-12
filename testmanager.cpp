#include "testmanager.h"

#include "test.h"

namespace unit {

TestManager &TestManager::instance() {
    static TestManager instance;
    return instance;
}

void TestManager::addTest(Test *test) {
    tests.push_back(test);
}

void TestManager::run() {
    for (Test *test : tests)
        test->run();
}
}

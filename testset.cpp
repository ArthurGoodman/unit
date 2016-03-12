#include "testset.h"

#include <iostream>

#include "literalmatchtest.h"

unit::TestSet::TestSet(const std::string &name)
    : name(name) {
}

std::string unit::TestSet::getName() {
    return name;
}

void unit::TestSet::run() {
    std::cout << "Testing " << name << "\n";

    for (ITest *test : *this) {
        test->run();
        test->report();
    }

    std::cout << "\n";
}

void unit::TestSet::report() {
}

void unit::TestSet::test(const std::string &name, const std::string &result, const std::function<void()> &f) {
    addTest(new LiteralMatchTest(name, result, f));
}

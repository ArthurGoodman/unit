#include "testset.h"

#include <iostream>

#include "basictest.h"

unit::TestSet::TestSet(const std::string &name)
    : name(name), maxNameLength(0) {
}

void unit::TestSet::addTest(unit::ITest *test) {
    maxNameLength = std::max(maxNameLength, (int)test->getName().length());
    TestCollection::addTest(test);
}

std::string unit::TestSet::getName() {
    return name;
}

void unit::TestSet::run() {
    std::cout << "Testing " << name << "\n";

    for (ITest *test : *this) {
        test->run();

        if (dynamic_cast<BasicTest *>(test))
            ((BasicTest *)test)->align(maxNameLength);

        test->report();
    }

    std::cout << "\n";
}

void unit::TestSet::report() {
}

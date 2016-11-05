#include "testset.h"

#include <iostream>

#include "testbase.h"

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
        preTest();
        test->run();
        postTest();

        if (dynamic_cast<TestBase *>(test))
            ((TestBase *)test)->align(maxNameLength);

        test->report();
    }

    std::cout << "\n";
}

void unit::TestSet::report() {
}

void unit::TestSet::preTest() {
}

void unit::TestSet::postTest() {
}

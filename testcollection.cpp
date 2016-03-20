#include "testcollection.h"

#include "itest.h"

unit::TestCollection::~TestCollection() {
    for (ITest *test : *this)
        delete test;
}

void unit::TestCollection::addTest(ITest *test) {
    tests.push_back(test);
}

std::vector<unit::ITest *>::iterator unit::TestCollection::begin() {
    return tests.begin();
}

std::vector<unit::ITest *>::iterator unit::TestCollection::end() {
    return tests.end();
}

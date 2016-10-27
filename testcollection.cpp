#include "testcollection.h"

#include "itest.h"

unit::TestCollection::~TestCollection() {
}

void unit::TestCollection::addTest(ITest *test) {
    tests.push_back(test);
}

void unit::TestCollection::cleanup() {
    for (ITest *test : *this)
        delete test;
}

std::vector<unit::ITest *>::iterator unit::TestCollection::begin() {
    return tests.begin();
}

std::vector<unit::ITest *>::iterator unit::TestCollection::end() {
    return tests.end();
}

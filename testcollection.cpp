#include "testcollection.h"

#include "itest.h"
#include "literalmatchtest.h"

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

void unit::TestCollection::$(const std::string &name, const std::string &result, const std::function<void()> &f) {
    addTest(new LiteralMatchTest(name, result, f));
}

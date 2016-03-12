#include "basictest.h"

#include <iostream>

unit::BasicTest::BasicTest(const std::string &name)
    : name(name), passed(false) {
}

std::string unit::BasicTest::getName() {
    return name;
}

void unit::BasicTest::report() {
    std::cout << (passed ? "ok\n" : "fail\n");
}

void unit::BasicTest::pass() {
    passed = true;
}

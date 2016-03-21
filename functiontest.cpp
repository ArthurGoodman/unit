#include "functiontest.h"

#include <iostream>
#include <sstream>

unit::FunctionTest::FunctionTest(const std::string &name, const std::function<void()> &f)
    : unit::TestBase(name), f(f) {
}

std::string unit::FunctionTest::invoke() {
    std::streambuf *buf = std::cout.rdbuf();
    std::ostringstream stream;
    std::cout.rdbuf(stream.rdbuf());

    f();

    std::cout.rdbuf(buf);

    return stream.str();
}

#include "literalmatchtest.h"

unit::LiteralMatchTest::LiteralMatchTest(const std::string &name, const std::string &result, const std::function<void()> &f)
    : unit::FunctionTest(name, f), result(result) {
}

void unit::LiteralMatchTest::run() {
    if (invoke() == result)
        pass();
}

#include "testrunner.h"

#include "itest.h"

void unit::TestRunner::run() {
    for (ITest *test : *this)
        test->run();

    for (ITest *test : *this)
        test->report();
}

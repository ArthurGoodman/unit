#include "test.h"

#include "testmanager.h"

namespace unit {
Test::Test() {
    TestManager::instance().addTest(this);
}
}

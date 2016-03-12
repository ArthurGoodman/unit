#pragma once

#include <string>

namespace unit {
class ITest {
public:
    virtual ~ITest();

    virtual std::string getName() = 0;
    virtual void run() = 0;
    virtual void report() = 0;
};
}

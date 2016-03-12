#pragma once

namespace unit {
class __declspec(dllexport) Test {
public:
    Test();

    virtual void run() = 0;
};
}

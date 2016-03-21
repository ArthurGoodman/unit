#pragma once

#include <vector>
#include <string>
#include <functional>

#include "test.h"

namespace unit {
class ITest;
class TestCollection;
}

class unit::TestCollection {
    std::vector<ITest *> tests;

public:
    ~TestCollection();

    virtual void addTest(ITest *test);

    template <class F>
    auto $(const std::string &name, F f) -> typename std::enable_if<not std::is_void<typename function_traits<F>::return_type>::value, Test<F, typename CheckerWrapper<F>::ValueChecker> &>::type;

    template <class F>
    auto $(const std::string &name, F f) -> typename std::enable_if<std::is_void<typename function_traits<F>::return_type>::value, Test<F, typename CheckerWrapper<F>::ActionChecker> &>::type;

    std::vector<ITest *>::iterator begin();
    std::vector<ITest *>::iterator end();
};

template <class F>
auto unit::TestCollection::$(const std::string &name, F f) -> typename std::enable_if<not std::is_void<typename function_traits<F>::return_type>::value, Test<F, typename CheckerWrapper<F>::ValueChecker> &>::type {
    Test<F, typename CheckerWrapper<F>::ValueChecker> *wrapper = new Test<F, typename CheckerWrapper<F>::ValueChecker>(name, f);
    addTest(wrapper);
    return *wrapper;
}

template <class F>
auto unit::TestCollection::$(const std::string &name, F f) -> typename std::enable_if<std::is_void<typename function_traits<F>::return_type>::value, Test<F, typename CheckerWrapper<F>::ActionChecker> &>::type {
    Test<F, typename CheckerWrapper<F>::ActionChecker> *wrapper = new Test<F, typename CheckerWrapper<F>::ActionChecker>(name, f);
    addTest(wrapper);
    return *wrapper;
}

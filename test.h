#pragma once

#include <functional>
#include <iostream>
#include <sstream>

#include "basictest.h"

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())> {
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const> {
    enum { arity = sizeof...(Args) };

    typedef ReturnType return_type;

    template <size_t i>
    struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

namespace unit {
template <class F>
class Test;

template <class F, class C>
class Wrapper;
}

template <class F>
class unit::Test : public BasicTest {
    class Checker {
    protected:
        Test<F> &test;
        std::function<bool(bool)> predicate;

    public:
        Checker(Test<F> &test, const std::function<bool(bool)> &predicate);
    };

    F f;
    std::function<bool()> checker;

public:
    class ValueChecker : public Checker {
        typedef typename function_traits<F>::return_type T;

    public:
        class Be : public Checker {
        public:
            Be(Test<F> &test, const std::function<bool(bool)> &predicate);

            void equal(T value);
            void operator==(T value);

            void lessThan(T value);
            void operator<(T value);

            void ok();
        } be;

        ValueChecker(Test<F> &test, const std::function<bool(bool)> &predicate);
    };

    class ActionChecker : public Checker {
    public:
        class Be : public Checker {
        public:
            Be(Test<F> &test, const std::function<bool(bool)> &predicate);

            void ok();
        } be;

        ActionChecker(Test<F> &test, const std::function<bool(bool)> &predicate);

        void print(const std::string &text);
    };

    Test(const std::string &name, F f);

    void run();
};

template <class F, class C>
class unit::Wrapper {
    Test<F> &test;

public:
    C should;
    C should_not;

    Wrapper(Test<F> &test);
};

template <class F>
unit::Test<F>::Checker::Checker(Test<F> &test, const std::function<bool(bool)> &predicate)
    : test(test), predicate(predicate) {
}

template <class F>
unit::Test<F>::ValueChecker::Be::Be(Test<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate) {
}

template <class F>
void unit::Test<F>::ValueChecker::Be::equal(T value) {
    Be::test.checker = [=]() {
        return Be::predicate(Be::test.f() == value);
    };
}

template <class F>
void unit::Test<F>::ValueChecker::Be::operator==(T value) {
    equal(value);
}

template <class F>
void unit::Test<F>::ValueChecker::Be::lessThan(T value) {
    Be::test.checker = [=]() {
        return Be::predicate(Be::test.f() < value);
    };
}

template <class F>
void unit::Test<F>::ValueChecker::Be::operator<(T value) {
    lessThan(value);
}

template <class F>
void unit::Test<F>::ValueChecker::Be::ok() {
    Be::test.checker = [=]() {
        try {
            Be::test.f();
            return Be::predicate(true);
        } catch (...) {
            return Be::predicate(false);
        }
    };
}

template <class F>
unit::Test<F>::ValueChecker::ValueChecker(Test<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate), be(test, predicate) {
}

template <class F>
unit::Test<F>::ActionChecker::Be::Be(Test<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate) {
}

template <class F>
void unit::Test<F>::ActionChecker::Be::ok() {
    Be::test.checker = [=]() {
        try {
            Be::test.f();
            return Be::predicate(true);
        } catch (...) {
            return Be::predicate(false);
        }
    };
}

template <class F>
unit::Test<F>::ActionChecker::ActionChecker(Test<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate), be(test, predicate) {
}

template <class F>
void unit::Test<F>::ActionChecker::print(const std::string &text) {
    ActionChecker::test.checker = [=]() {
        std::streambuf *buf = std::cout.rdbuf();
        std::ostringstream stream;
        std::cout.rdbuf(stream.rdbuf());

        ActionChecker::test.f();

        std::cout.rdbuf(buf);

        return ActionChecker::predicate(stream.str() == text);
    };
}

template <class F>
unit::Test<F>::Test(const std::string &name, F f)
    : BasicTest(name), f(f), checker([]() { return false; }) {
}

template <class F>
void unit::Test<F>::run() {
    if (checker())
        pass();
}

template <class F, class C>
unit::Wrapper<F, C>::Wrapper(Test<F> &test)
    : test(test), should(test, [](bool b) { return b; }), should_not(test, [](bool b) { return not b; }) {
}

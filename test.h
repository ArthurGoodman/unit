#pragma once

#include <functional>
#include <iostream>
#include <sstream>

#include "testbase.h"
#include "function_traits.h"

namespace unit {
template <class F>
class CheckerWrapper;

template <class F, class C>
class Test;
}

template <class F>
class unit::CheckerWrapper {
    class Checker {
    protected:
        CheckerWrapper<F> &checker;
        std::function<bool(bool)> predicate;

    public:
        Checker(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate);
    };

    F f;
    std::function<bool()> checker;

public:
    class ValueChecker : public Checker {
        typedef typename function_traits<F>::return_type T;

    public:
        class Be : public Checker {
        public:
            Be(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate);

            void equal(T value);
            void operator==(T value);

            void lessThan(T value);
            void operator<(T value);

            void ok();
        } be;

        ValueChecker(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate);
    };

    class ActionChecker : public Checker {
    public:
        class Be : public Checker {
        public:
            Be(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate);

            void ok();
        } be;

        ActionChecker(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate);

        void print(const std::string &text);
    };

    CheckerWrapper(F f);

    bool check();
};

template <class F, class C>
class unit::Test : public TestBase {
    CheckerWrapper<F> checker;

public:
    C should;
    C should_not;

    Test(const std::string &name, F f);

    void run();
};

template <class F>
unit::CheckerWrapper<F>::Checker::Checker(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate)
    : checker(checker), predicate(predicate) {
}

template <class F>
unit::CheckerWrapper<F>::ValueChecker::Be::Be(CheckerWrapper<F> &checker, const std::function<bool(bool)> &predicate)
    : Checker(checker, predicate) {
}

template <class F>
void unit::CheckerWrapper<F>::ValueChecker::Be::equal(T value) {
    Be::test.checker = [=]() {
        return Be::predicate(Be::test.f() == value);
    };
}

template <class F>
void unit::CheckerWrapper<F>::ValueChecker::Be::operator==(T value) {
    equal(value);
}

template <class F>
void unit::CheckerWrapper<F>::ValueChecker::Be::lessThan(T value) {
    Be::test.checker = [=]() {
        return Be::predicate(Be::test.f() < value);
    };
}

template <class F>
void unit::CheckerWrapper<F>::ValueChecker::Be::operator<(T value) {
    lessThan(value);
}

template <class F>
void unit::CheckerWrapper<F>::ValueChecker::Be::ok() {
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
unit::CheckerWrapper<F>::ValueChecker::ValueChecker(CheckerWrapper<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate), be(test, predicate) {
}

template <class F>
unit::CheckerWrapper<F>::ActionChecker::Be::Be(CheckerWrapper<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate) {
}

template <class F>
void unit::CheckerWrapper<F>::ActionChecker::Be::ok() {
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
unit::CheckerWrapper<F>::ActionChecker::ActionChecker(CheckerWrapper<F> &test, const std::function<bool(bool)> &predicate)
    : Checker(test, predicate), be(test, predicate) {
}

template <class F>
void unit::CheckerWrapper<F>::ActionChecker::print(const std::string &text) {
    ActionChecker::checker.checker = [=]() {
        std::streambuf *buf = std::cout.rdbuf();
        std::ostringstream stream;
        std::cout.rdbuf(stream.rdbuf());

        ActionChecker::checker.f();

        std::cout.rdbuf(buf);

        return ActionChecker::predicate(stream.str() == text);
    };
}

template <class F>
unit::CheckerWrapper<F>::CheckerWrapper(F f)
    : f(f), checker([]() { return false; }) {
}

template <class F>
bool unit::CheckerWrapper<F>::check() {
    return checker();
}

template <class F, class C>
unit::Test<F, C>::Test(const std::string &name, F f)
    : TestBase(name), checker(f), should(checker, [](bool b) { return b; }), should_not(checker, [](bool b) { return not b; }) {
}

template <class F, class C>
void unit::Test<F, C>::run() {
    if (checker.check())
        pass();
}

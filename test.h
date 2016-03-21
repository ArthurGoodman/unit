#pragma once

#include <functional>
#include <iostream>
#include <sstream>

#include "testbase.h"
#include "function_traits.h"

namespace unit {
template <class F>
class Checker;

template <class F, class C>
class Test;
}

template <class F>
class unit::Checker {
    class CheckerBase {
    protected:
        Checker<F> &checker;
        std::function<bool(bool)> predicate;

    public:
        CheckerBase(Checker<F> &checker, const std::function<bool(bool)> &predicate);
    };

    F f;

public:
    std::function<bool()> check;

    class ValueChecker : public CheckerBase {
        typedef typename function_traits<F>::return_type T;

    public:
        class Be : public CheckerBase {
        public:
            Be(Checker<F> &checker, const std::function<bool(bool)> &predicate);

            void equal(T value);
            void operator==(T value);

            void lessThan(T value);
            void operator<(T value);

            void ok();
        } be;

        ValueChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate);
    };

    class ActionChecker : public CheckerBase {
    public:
        class Be : public CheckerBase {
        public:
            Be(Checker<F> &checker, const std::function<bool(bool)> &predicate);

            void ok();
        } be;

        ActionChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate);

        void print(const std::string &text);
    };

    Checker(F f);
};

template <class F, class C>
class unit::Test : public TestBase {
    Checker<F> checker;

public:
    C should;
    C should_not;

    Test(const std::string &name, F f);

    void run();
};

template <class F>
unit::Checker<F>::CheckerBase::CheckerBase(Checker<F> &checker, const std::function<bool(bool)> &predicate)
    : checker(checker), predicate(predicate) {
}

template <class F>
unit::Checker<F>::ValueChecker::Be::Be(Checker<F> &checker, const std::function<bool(bool)> &predicate)
    : CheckerBase(checker, predicate) {
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::equal(T value) {
    this->test.checker = [=]() {
        return this->predicate(this->test.f() == value);
    };
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator==(T value) {
    equal(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::lessThan(T value) {
    this->test.checker = [=]() {
        return this->predicate(this->test.f() < value);
    };
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator<(T value) {
    lessThan(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::ok() {
    this->test.checker = [=]() {
        try {
            this->test.f();
            return this->predicate(true);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
unit::Checker<F>::ValueChecker::ValueChecker(Checker<F> &test, const std::function<bool(bool)> &predicate)
    : CheckerBase(test, predicate), be(test, predicate) {
}

template <class F>
unit::Checker<F>::ActionChecker::Be::Be(Checker<F> &test, const std::function<bool(bool)> &predicate)
    : CheckerBase(test, predicate) {
}

template <class F>
void unit::Checker<F>::ActionChecker::Be::ok() {
    this->test.checker = [=]() {
        try {
            this->test.f();
            return this->predicate(true);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
unit::Checker<F>::ActionChecker::ActionChecker(Checker<F> &test, const std::function<bool(bool)> &predicate)
    : CheckerBase(test, predicate), be(test, predicate) {
}

template <class F>
void unit::Checker<F>::ActionChecker::print(const std::string &text) {
    this->checker.check = [=]() {
        std::streambuf *buf = std::cout.rdbuf();
        std::ostringstream stream;
        std::cout.rdbuf(stream.rdbuf());

        this->checker.f();

        std::cout.rdbuf(buf);

        return this->predicate(stream.str() == text);
    };
}

template <class F>
unit::Checker<F>::Checker(F f)
    : f(f), check([]() { return false; }) {
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

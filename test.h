#pragma once

#include <functional>
#include <iostream>
#include <sstream>

#include "testbase.h"
#include "function_traits.h"

namespace unit {
template <class>
class Checker;

template <class, class>
class Test;
}

template <class F>
class unit::Checker {
    class CheckerBase;

    F f;

public:
    std::function<bool()> check;

    class ValueChecker;
    class ActionChecker;

    Checker(F f);
};

template <class F>
class unit::Checker<F>::CheckerBase {
protected:
    Checker<F> &checker;
    std::function<bool(bool)> predicate;

public:
    CheckerBase(Checker<F> &checker, const std::function<bool(bool)> &predicate);
};

template <class F>
class unit::Checker<F>::ValueChecker : public CheckerBase {
    typedef typename function_traits<F>::return_type T;

    class Be;

public:
    Be be;

    ValueChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate);
};

template <class F>
class unit::Checker<F>::ValueChecker::Be : public CheckerBase {
public:
    Be(Checker<F> &checker, const std::function<bool(bool)> &predicate);

    void equal(T value);
    void operator==(T value);
    void operator=(T value);

    void lessThan(T value);
    void operator<(T value);

    void greaterThan(T value);
    void operator>(T value);

    void ok();
};

template <class F>
class unit::Checker<F>::ActionChecker : public CheckerBase {
    class Be;

public:
    Be be;

    ActionChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate);

    void print(const std::string &text);
};

template <class F>
class unit::Checker<F>::ActionChecker::Be : public CheckerBase {
public:
    Be(Checker<F> &checker, const std::function<bool(bool)> &predicate);

    void ok();
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
    this->checker.check = [=]() {
        try {
            return this->predicate(this->checker.f() == value);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator==(T value) {
    equal(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator=(T value) {
    equal(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::lessThan(T value) {
    this->checker.check = [=]() {
        try {
            return this->predicate(this->checker.f() < value);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator<(T value) {
    lessThan(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::greaterThan(T value) {
    this->checker.check = [=]() {
        try {
            return this->predicate(this->checker.f() > value);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::operator>(T value) {
    greaterThan(value);
}

template <class F>
void unit::Checker<F>::ValueChecker::Be::ok() {
    this->checker.check = [=]() {
        try {
            this->checker.f();
            return this->predicate(true);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
unit::Checker<F>::ValueChecker::ValueChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate)
    : CheckerBase(checker, predicate), be(checker, predicate) {
}

template <class F>
unit::Checker<F>::ActionChecker::Be::Be(Checker<F> &checker, const std::function<bool(bool)> &predicate)
    : CheckerBase(checker, predicate) {
}

template <class F>
void unit::Checker<F>::ActionChecker::Be::ok() {
    this->checker.check = [=]() {
        try {
            this->checker.f();
            return this->predicate(true);
        } catch (...) {
            return this->predicate(false);
        }
    };
}

template <class F>
unit::Checker<F>::ActionChecker::ActionChecker(Checker<F> &checker, const std::function<bool(bool)> &predicate)
    : CheckerBase(checker, predicate), be(checker, predicate) {
}

template <class F>
void unit::Checker<F>::ActionChecker::print(const std::string &text) {
    this->checker.check = [=]() {
        try {
            std::streambuf *buf = std::cout.rdbuf();
            std::ostringstream stream;
            std::cout.rdbuf(stream.rdbuf());

            this->checker.f();

            std::cout.rdbuf(buf);

            return this->predicate(stream.str() == text);
        } catch (...) {
            return this->predicate(false);
        }
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

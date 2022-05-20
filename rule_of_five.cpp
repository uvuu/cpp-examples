#include "rule_of_five.h"

#include <iostream>
#include <utility>

/*
 * Forward declarations
 */
void zeroRuleClass();
void nonDefaultConstructor();
void defaultConstructor();

/*
 *  The example runner
 */
void runRuleOfFiveExample()
{
    std::cout << std::endl << "Rule of Five(Three/Zero)" << std::endl;

    zeroRuleClass();
    nonDefaultConstructor();
    defaultConstructor();
}

class A
{
};

void zeroRuleClass()
{
    A a;
    A a1(a);
    A a2(A());
    A a3 = a;
    A a4 = A{};
}

class B
{
public:
    B(int) {};
};

void nonDefaultConstructor()
{
    //B b; // no matching constructor
    B b(1);
    B b1(b);
    //B b2(B{}); // no matching constructor
    B b3 = b;
    //B b4 = B{}; // no matching constructor
}

class C
{
public:
    C() = default; // We need it otherwise it will be uavailable if any other constructor is defined

    /*
     * Uncomment in parts depending on the gaps in the lines
     * P.S. Maybe we have there some influence of RVO
     */

    //C(const C& c) = default; // Here defaultConstructor() is OK

    //C(const C& c) = delete; // All c1-4 are broken here because of trying to call deleted constructor

    //C(C&& c) = default; // Here we have problems with c1 and c2 because copy functions are implicitly deleted

    //C(C&& c) = delete; // All c1-4 are broken and reasons are combined from two previous points

    // Here we have a problem with c2 and c4 because of call of delete constructor
    //C(const C& c) = default;
    //C(C&& c) = delete;

    // Here we have a problem with c1 and c3 because of call of delete constructor
    //C(const C& c) = delete;
    //C(C&& c) = default;

    //C& operator=(const C& c) = default; // Here we are OK

    //C& operator=(const C& c) = delete; // Strange... but it is OK

    //C& operator=(C&& c) = default; // c1-4 are broken because copy functions are implicitly deleted

    //C& operator=(C&& c) = delete; // c1-4 are broken because copy functions are implicitly deleted
};

void defaultConstructor()
{
    C c;
    C c1(c);
    C c2(C{});
    C c3 = c;
    C c4 = C{};
}

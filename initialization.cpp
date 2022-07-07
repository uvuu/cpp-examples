#include "initialization.h"

#include <iostream>

/*
 * Forward declarations
 */
void defaultInitialization();
void valueInitialization();
void directInitialization();
void copyInitialization();
void listInitialization();
void aggregateInitialization();
void referenceInitialization();
void autoInitialization();
void narrowing();

/*
 *  The example runner
 */
void runInitializationExample()
{
    std::cout << std::endl << "Initialization" << std::endl;

    defaultInitialization();
    valueInitialization();
    directInitialization();
    copyInitialization();
    listInitialization();
    aggregateInitialization();
    referenceInitialization();
    autoInitialization();
    narrowing();
}

struct A
{
    A() {};
    A(int oia) : ia(oia) {};
    A(int oia, float ofa) : ia(oia), fa(ofa) {};
    int ia;
    float fa;
};

void defaultInitialization()
{
    A a;
    auto pa = new A;
    auto pint = new int; // TODO: Is it really default init?

    struct B
    {
        A a;

        B()// This is the case, because we don't mention 'a' here
        {}
    } b;
}

void valueInitialization()
{
    A();
    //A a(); //  This is wrong because it is function declaration
    new A();

    struct B
    {
        A a;

        B()
            : a()/*{}*/ // This is the case
        {}
    } b;

    A a{};
    A{};
    new A{};
}

void directInitialization()
{
    A a(5);
    A a1(5, 1.0);
    A a2{5};
    A(5, 1.0);
    static_cast<A>(a);
    new A(5, 1.0);

    struct B
    {
        A a;

        B()
            : a(5, 1.0) // This is the case
        {}
    } b;

    [a](){};
}

A func(A a)
{
    return a; // This is copy initialization too
}

void copyInitialization()
{
    A a; // This isn't copy initialization. Just necessary for the example

    A a1 = a;
    A a2 = {a};

    func(a); // The case

    try
    {
        throw a; // The case
    }
    catch (A a) // The case
    {
    }

    A aar[2] = {a , a1};
}

A func1(A a)
{
    return {5, 1.0}; // This is list copy initialization too
}

void listInitialization()
{
    // Direct-list-initialization
    A a{ 5, 1.0 };
    A{ 5, 1.0 };
    new A{ 5, 1.0 };

    class B
    {
        A a{ 5, 1.0 };
    } b;

    struct C
    {
        A a;

        C()
            : a{5, 1.0} // This is the case
        {}
    } c;

    // Copy-list-initialization
    A a1 = {5, 1.0};
    func({5, 1.0});

    //object[ { arg1, arg2, ... } ]
    //object = { arg1, arg2, ... }
    //U( { arg1, arg2, ... } )
    //Class { T member = { arg1, arg2, ... }; };
}

void aggregateInitialization()
{
    //T object = {arg1, arg2, ...};	(1)
    //T object {arg1, arg2, ... };	(2)	(since C++11)
    //T object = { .designator = arg1 , .designator { arg2 } ... };	(3)	(since C++20)
    //T object { .designator = arg1 , .designator { arg2 } ... };	(4)	(since C++20)
    //T object (arg1, arg2, ...);

    struct A { int x; int y; int z; };

    //A a{.y = 2, .x = 1}; // Error; designator order does not match declaration order
    A b{.x = 1, .z = 2}; // Ok, b.y initialized to 0

    union u { int a; const char* b; };

    u f = {.b = "asdf"};         // OK, active member of the union is b
    //u g = {.a = 1, .b = "asdf"}; // Error, only one initializer may be provided
}

void referenceInitialization()
{
    //T & ref = target ;
    //T & ref = { arg1, arg2, ... };
    //T & ref ( target );
    //T & ref { arg1, arg2, ... };
    //T && ref = target;
    //T && ref = { arg1, arg2, ... };
    //T && ref ( target );
    //T && ref { arg1, arg2, ... };

    //given R fn ( T & arg ); or R fn ( T && arg ); (since C++11)
    //fn ( target )
    //fn ({ arg1, arg2, ... });

    //inside T & fn () or T && fn () (since C++11)
    //return target;

    //given T & ref ; or T && ref ; (since C++11) inside the definition of Class
    //Class::Class(...) : ref ( target ) { ... }
}


// TODO: Add an example about initialize_list


void autoInitialization()
{
    auto z1 {99};   // z1 is an int
    auto z2 = {99}; // z2 is std::initializer_list<int>
    auto z3 = 99;   // z3 is an int
}

void narrowing()
{
    struct A
    {
        int a;
        float b;
    };


    A a{1,3};
    A a1{1ll, 2.0}; // Why does this works? What about narrowing?
    long long v = 10000000000ll; // This is OK
    //A a2{10000000000ll, 2.0}; // The problem with narrowing - error

    long long l = 5;
    double d = 1.0;
    //A a2{l, d}; // The problem with narrowing - error

    struct B
    {
        //B(bool oa, char* oc){}
        bool a;
        const char* c;
    };

    B b{1, "c"}; // This is OK
    //B b1{2, "c"}; // The problem with narrowing - error
    //B b2{true, (int*)5}; // Wrong pointer type
    //B b3{true, true}; // Wrong pointer type
    //B b4 {true};

    struct C
    {
        C(bool oa, const char* oc){}
        C(int oi){};
        bool a;
        const char* c;
    };

    //C{true}; // No matching constructor
    //C c{.a = false, .c = 'a'}; // Seems doesn't work here
    C c1 = 1;
    C c2{true};
    //C c3{l};// Narrowing
    C c4(l); // There is narrowing too, but it is OK
    C c5(&a, "");
}

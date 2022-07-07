#include "attributes.h"

/*
 * Forward declarations
 */
void noDiscard();
void noReturn();
void fallThrough();
void mayBeUnused();

/*
 *  The example runner
 */
void runAttributesExample()
{
    noDiscard();
    noReturn();
    fallThrough();
    mayBeUnused();
}

//[[nodiscard]] class A{}; // Misplaced attribute
//class A [[nodiscard]]{}; // Attibute list cannot appear here
class [[nodiscard]] A{};
A func()
{
    return {};
}

[[nodiscard/*("Please don't leave me alone")*/]] int func2() // After an attempt to compile this you will have an error message about
                                                         // the attribute arguments number
{
    return 1;
}

void noDiscard()
{
    func(); // We have a warning about nodiscard
    func2(); // The same warning, but with an miserable message
    auto a = func(); // OK
    auto&& a2 = func(); // OK
}

[[noreturn]] void func3()
{
} // We have a warning here but I don't understand why

//int func4(); // After that we can't define the function with the attribute.
               // Note: there is no problem in MSVC and we may uncomment it.
[[noreturn]] int func4()
{
    return 1; // The 'no return' warning
}

[[noreturn]] int func5(); // This is OK with the definition without the attribute in the signature
int func5()
{
    return 1; // The 'no return' warning
}

void noReturn()
{
    // For some reasons using these two functions leads to segmentation fault in C++20
    // but they were fine in C++11
    //func3();
    //func4();
}

void fallThrough()
{
    int a = 1;
    switch (a)
    {
    case 1:
        [[fallthrough]]; // A semicolon is necessary here
    case 2:
        // Hm, here is no error or warning in the output
    case 3:
    default:
        break;
    }
}

void mayBeUnused()
{
    [[maybe_unused]]int a; // It works
}



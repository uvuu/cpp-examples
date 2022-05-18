#include "move_semantics.h"

#include <iostream>
#include <utility>

void creatingRvalueReference();
void referencesCollapsing();

/*
 *  The example runner
 */
void runMoveSemanticsExample()
{
    creatingRvalueReference();
    referencesCollapsing();
}


void creatingRvalueReference()
{
    int a = 1;
    // int&& r = a; // rvalue reference to type 'int' cannot bind to lvalue of type 'int'
    int&& r1 = static_cast<int&&>(a); // but we may force it
    int&& r2 = std::move(a);          // or use the more gentle and general way from 'utility'
}

template <typename T>
constexpr bool funcLVR()
{
    return std::is_same<T&, T>::value;
}

template <typename T>
constexpr bool funcRVR()
{
    return std::is_same<T&&, T>::value;
}

void referencesCollapsing()
{
    int a = 1;
    // int& & ra = a; // it is prohibited and if you want to do this you need to code:
    typedef int& intlvr;
    intlvr& r1 = a;       // &
    intlvr&& r2 = a;      // &

    // the same thing about rvalue
    typedef int&& intrvl;
    intrvl& r3 = a;       // &
    intrvl&& r4 = 1;      // && only

    // intrvl&& r4 = a; // it is prohibited too because we can't attach lvalue to rvalue reference

    std::cout << "& " << funcLVR<int&>() << std::endl;   // 1 means &
    std::cout << "& " << funcRVR<int&>() << std::endl;   // 1 means &
    std::cout << "&& " << funcLVR<int&&>() << std::endl; // 0 means &
    std::cout << "&& " << funcRVR<int&&>() << std::endl; // 1 means &&
}

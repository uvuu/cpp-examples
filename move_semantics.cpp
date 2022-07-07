#include "move_semantics.h"

#include <iostream>
#include <string>
#include <utility>

/*
 * Forward declarations
 */
void creatingRvalueReference();
void referencesCollapsing();
void hadlingRvalueReference();

/*
 *  The example runner
 */
void runMoveSemanticsExample()
{
    std::cout << std::endl << "Move semantics" << std::endl;

    creatingRvalueReference();
    hadlingRvalueReference();
    referencesCollapsing();
}


void creatingRvalueReference()
{
    int a = 1;
    // int&& r = a; // rvalue reference to type 'int' cannot bind to lvalue of type 'int'
    int&& r1 = static_cast<int&&>(a); // but we may force it
    int&& r2 = std::move(a);          // or use the more gentle and general way from 'utility'
}

void hadlingRvalueReference()
{
    std::string s = "str";
    std::string s1 = s; // Do you think we will have the movement here? Nope.
                        // In this case s is an lvalue that has a rvalue reference type.

    // If you really want to move s when you need to perform one of the two next operations.
    std::string s2 = std::move(s);
    // or
    //std::string s3 = static_cast<std::string&&>(s); 
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

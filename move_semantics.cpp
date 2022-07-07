#include "move_semantics.h"

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <utility>

/*
 * Forward declarations
 */
void creatingRvalueReference();
void referencesCollapsing();
void hadlingRvalueReference();
void universalReverence(); // I highly recommend reading Scott Mayers' article on this:
                           // https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

/*
 *  The example runner
 */
void runMoveSemanticsExample()
{
    std::cout << std::endl << "Move semantics" << std::endl;

    creatingRvalueReference();
    hadlingRvalueReference();
    referencesCollapsing();
    universalReverence();
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

    // intrvl&& r4 = a; // it is prohibited too because we can't attach lvalue to rvalue reference.
    // Notice that instead of using "typedef" we are able to use "using".
    // Moreover, the same principle works for decltype expressions.
    int&& rvi = 1;

    decltype(rvi) di = 1;      // &&
    decltype(rvi)& rdi1 = rvi; // &
    decltype(rvi)&& rdi2 = 1;  // &&


    std::cout << "& " << funcLVR<int&>() << std::endl;   // 1 means &
    std::cout << "& " << funcRVR<int&>() << std::endl;   // 1 means &
    std::cout << "&& " << funcLVR<int&&>() << std::endl; // 0 means &
    std::cout << "&& " << funcRVR<int&&>() << std::endl; // 1 means &&
}

void f(int&& i) {}; // The argument in rvalue reference

template<typename T>
void f1(T&& t)   // We don't really know the type of the argument because
                 // it is an universal reference and the exact value type
                 // will be know after type deduction and reference collapsing.
{
    std::cout << std::boolalpha << std::endl << std::is_rvalue_reference_v<decltype(t)>;
};

template<typename T>
void cf1(const T&& t)
{
    std::cout << std::boolalpha << std::endl << std::is_rvalue_reference_v<decltype(t)>;
};

template<typename T>
void f2(std::vector<T>&& param) {}; // There is no exact T&& expression so there is rvalue reference

void universalReverence()
{
    int&& i = 5; // rvalue reference
    auto&& ari = 5; // rvalue reference
    auto&& ali = i; // lvalue reference 

    f1(5); // rvalue reference
    f1(i); // lvalue reference

    cf1(5); // rvalue reference
    //cf1(i); // We cannot write the code like this because const converts an
              // universal reference into regular rvalue reference!
              // This means that only T&& can be an universal reference but
              // not const T&&!
}
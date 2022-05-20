#include "sfinae.h"

#include <iostream>
#include <vector>
#include <set>
#include <type_traits>

/*
 * Forward declarations
 */
void findDetection();
void enableIfUsage();

/*
 *  The example runner
 */
void runSfinaeExample()
{
    std::cout << std::endl << "SFINAE" << std::endl;

    findDetection();
    enableIfUsage();
}

template<typename T>
class DetectFind
{
    struct Fallback { int find; }; // add member name "find"
    struct Derived : T, Fallback { };

    template<typename U, U> struct Check;

    typedef char Yes[1];  // typedef for an array of size one.
    typedef char No[2];  // typedef for an array of size two.

    template<typename U>
    static No& func(Check<int Fallback::*, &U::find> *);

    template<typename U>
    static Yes& func(...);

  public:
    typedef DetectFind type;
    enum { value = sizeof(func<Derived>(0)) == sizeof(Yes) };
};

void findDetection() // Wiki example
{
    std::cout << DetectFind<std::vector<int> >::value << ' '
              << DetectFind<std::set<int> >::value << std::endl;
}

template <typename T, typename U>
typename std::enable_if<std::is_same<T, U>::value, int>::type func()
{
    return 0;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, float>::type func()
{
    return 0;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_const<T>::value, long>::type func()
{
    return 0;
}

void enableIfUsage()
{
    // is_same case
    int a = func<int, int>();
    //int b = func<int, double>();

    // is_floating_point case
    float c = func<float>();
    float d = func<const float>();
    bool e = func<double>();

    // is_integral && is_const
    //int f = func<int>(); // The compiler cannot instantiate the function because of the absence of const
    int g = func<const long>();
    const float i = func<const long long>();
}


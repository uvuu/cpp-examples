#include "initializer_list_problems.h"

#include <initializer_list>
#include <iostream>
#include <memory>

/*
 * Forward declarations
 */
void ilInitialization();
void typeDeduction();
void objectsMoving();

/*
 *  The example runner
 */
void runInitializerListProblemsExample()
{
    std::cout << std::endl << "Initializer list" << std::endl;

    ilInitialization();
    typeDeduction();
    objectsMoving();
}

class TestVector
{
public:
    // TestVector([[maybe_unused]] int size, [[maybe_unused]] int filler) {}; // We can't put the attribute after '(' here it leads to the error
    TestVector(int size [[maybe_unused]], int filler [[maybe_unused]])
    {
        std::cout << std::endl << "Non-il-consturctor!" << std::endl;
    }

    TestVector(std::initializer_list<int> list [[maybe_unused]])
    {
        std::cout << std::endl << "Il-constructor!" << std::endl;
    }
};

void ilInitialization()
{
    TestVector v1(std::initializer_list<int>{1, 2});
    // The problem with initializer list is that the use of il-constuructor isn't obvious in
    // the following expressions and if we comment out it the compiler would use non-il-constructor
    TestVector v2({1, 2});
    TestVector v3{1, 2};
    TestVector v4 = {1, 2};

    // Also we face the following inconsistency
    TestVector v5(1, 2); // There is used the non-il-constructor
    TestVector v6{1, 2}; // But there is used the il-constructor
                         // So the uniform initialization isn't uniform enough...
}

template <typename T>
void testFunction(T t[[maybe_unused]]) {}

void typeDeduction()
{
    [[maybe_unused]] auto il = {1, 2, 3}; // It won't work if there is no initializer list header(<initializer_list>)!
                         // The situation is occurred due to a lack of type of {1, 2, 3} expression.

    //testFunction({1, 2, 3}); // It resolves into the error because there is no type of {1, 2, 3} expression again

    //auto ptr = std::make_shared<TestVector>({1, 2}); // Candidate template ignored: substitution failure [with _Tp = TestVector]:
                                                       // deduced incomplete pack <(no value)> for template parameter '_Args'
}

class MovableObject
{
public:
    MovableObject() {}
    MovableObject(const MovableObject&)
    {
        std::cout << std::endl << "Copying is here!" << std::endl;
    }
    MovableObject(MovableObject&&)
    {
        std::cout << std::endl << "Moving is here!" << std::endl;
    }
    MovableObject& operator=(const MovableObject&)
    {
        std::cout << std::endl << "Copying is here!" << std::endl;
        return *this;
    }
    MovableObject& operator=(MovableObject&&)
    {
        std::cout << std::endl << "Moving is here!" << std::endl;
        return *this;
    }
};

void objectsMoving()
{
    auto il = {MovableObject{}, MovableObject{}};
    auto ilCopied = std::move(*il.begin()); // Copying
    auto ilMoved = std::move(MovableObject{}); // Moving
    auto ilMoved2 = std::move(*const_cast<MovableObject*>(il.begin())); // Moving, and it works due to casting away constness
}



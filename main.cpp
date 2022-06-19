#include "attributes.h"
#include "initialization.h"
#include "initializer_list_problems.h"
#include "move_semantics.h"
#include "rule_of_five.h"
#include "sfinae.h"

int main()
{
    runAttributesExample();
    runInitializationExample();
    runInitializerListProblemsExample();
    runMoveSemanticsExample();
    runRuleOfFiveExample();
    runSfinaeExample();

    return 0;
}

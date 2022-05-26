#include "attributes.h"
#include "initialization.h"
#include "move_semantics.h"
#include "rule_of_five.h"
#include "sfinae.h"

int main()
{
    runAttributesExample();
    runInitializationExample();
    runMoveSemanticsExample();
    runRuleOfFiveExample();
    runSfinaeExample();

    return 0;
}

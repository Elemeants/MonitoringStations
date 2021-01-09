#include "cmd.h"
#include "tests/include.h"

CliTestId_t CliTests[] = {
    {"led", AgricosCli_CMD_Test_Led},
    {"microsd", AgricosCli_CMD_Test_MicroSD}};

static void AgricosCli_CMD_Test(cmd *_)
{
    Command cmd(_);

    String testCode = cmd.getArgument("d").getValue();
    for_in_range(uint8_t, i, 0, array_size(CliTests))
    {
        if (testCode == CliTests[i].id)
        {
            CliTests[i].callback();
        }
    }
}

void AgricosCli_Add_Test()
{
    Command cmd = AgricosCli.addCommand("test", AgricosCli_CMD_Test);
    cmd.addArgument("d");
    cmd.setCaseSensetive(true);
    cmd.setDescription(" Test a device for errors (-d set target)");
}
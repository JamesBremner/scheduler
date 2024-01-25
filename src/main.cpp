
#include <wex.h>
#include "cStarterGUI.h"

#include "scheduler.h"



main()
{
    cScheduler theScheduler;
    theScheduler.daily(
        cJob(
            "awake",
            "070000",
            59,
            {"person"}));
    theScheduler.daily(
        cJob(
            "commute",
            "080000",
            60,
            {"person"}));

    theScheduler.run();

    return 0;
}

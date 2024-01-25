
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
            60));
    theScheduler.run();
    return 0;
}

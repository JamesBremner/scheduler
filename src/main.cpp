#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"

#include "scheduler.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};

void cJob::start(const std::string &start)
{
    myStart =
        atoi(start.substr(0, 2).c_str()) * 60 + atoi(start.substr(2, 2).c_str());
}
    std::string cJob::start() const
    {
        std::stringstream ss;
        int h =  myStart / 60;
        ss << myStart / 60 <<":"<< myStart - h * 60;
        return ss.str();
    }

void cJob::makeStop()
{
    myName += "_stop";
    myStart += myDurationMins;
    
}

void cScheduler::run()
{
    std::cout << "Day 0\n"
    myDay = 0;
    while ( myDay <= 7)
    {
        if (myQueue.empty())
        {
            myDay++;
            std::cout << "Day " << myDay << "\n";
            for (auto &j : myJobv)
                myQueue.push(j);
            continue;
        }

        cJob j = myQueue.top();
        myQueue.pop();
        std::cout << j.name() << " " << j.start() << "\n";

        if (!j.isStop())
        {
            j.makeStop();
            myQueue.push(j);
        }
    }
}

main()
{
    // cGUI theGUI;

    cScheduler theScheduler;
    theScheduler.daily(
        cJob(
            "awake",
            "070000",
            60));
    theScheduler.run();
    return 0;
}

#include "scheduler.h"

cJob::cJob(
    const std::string &name,
    const std::string &hhmmss,
    int durationMins)
    : myName(name),
      myDurationMins(durationMins),
      myfstop(false)
{
    start(hhmmss);
}

void cJob::start(const std::string &start)
{
    myStart =
        atoi(start.substr(0, 2).c_str()) * 60 + atoi(start.substr(2, 2).c_str());
}
std::string cJob::start() const
{
    std::stringstream ss;
    int h = myStart / 60;
    ss << myStart / 60 << ":" << myStart - h * 60;
    return ss.str();
}

void cJob::makeStop()
{
    myfstop = true;
    myStart += myDurationMins;
}

std::string cJob::textOnStart() const
{
    std::stringstream ss;
    if (!myfstop)
        ss << myName << " ";
    else
        ss << myName << " ends ";
    ss << start() << "\n";
    return ss.str();
}

bool cJob::operator<(const cJob &other) const
{
    // ensure that the job with the earliest start time
    // is on the top of the priority queue
    
    return myStart > other.myStart;
}

void cScheduler::run()
{
    std::cout << "Day 0\n";
    myDay = 0;
    while (myDay <= 7)
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
        std::cout << j.textOnStart();

        if (!j.isStop())
        {
            j.makeStop();
            myQueue.push(j);
        }
    }
}
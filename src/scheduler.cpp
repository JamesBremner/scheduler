#include "scheduler.h"

cJob::cJob(
    const std::string &name,
    const std::string &hhmmss,
    int durationMins,
    const std::vector<std::string> &resourcev)
    : myName(name),
      myDurationMins(durationMins),
      myfstop(false),
      myResourcev(resourcev)
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

void cScheduler::daily(
    const cJob &job)
{
    myJobv.push_back(job);
    myQueue.push(job);
    addNovelResources(job);
}

void cScheduler::addNovelResources(const cJob &job)
{
    std::vector<std::string> novel;
    for (auto &rname : job.resources())
    {
        bool exists = false;
        for (auto &r : myResourcev)
        {
            if (rname == r.name())
            {
                exists = true;
                break;
            }
        }
        if( ! exists )
            novel.push_back(rname);
    }
    for (auto &rname : novel)
        myResourcev.emplace_back(rname);
}
bool cScheduler::isResourceFree(
    const cJob &job) const
{
    if( job.isStop() )
        return true;

    for (auto &r : myResourcev)
    {
        for (auto &req : job.resources())
        {
            if (r.name() == req)
            {
                if (!r.isFree())
                {
                    std::cout << "missing resource to start " << job.name() << "\n";
                    return false;
                }
            }
        }
    }
    return true;
}

void cScheduler::allocate(const cJob &job)
{
    for (auto &r : myResourcev)
    {
        for (auto &req : job.resources())
        {
            if (r.name() == req)
                r.allocate();
        }
    }
}

void cScheduler::free(const cJob &job)
{
    for (auto &req : job.resources())
    {
        for (auto &r : myResourcev)
        {
            if (r.name() == req)
            {
                r.free();
                break;
            }
        }
    }
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
        if (!isResourceFree(j))
            exit(1);
        allocate(j);

        myQueue.pop();
        std::cout << j.textOnStart();

        if (!j.isStop())
        {
            j.makeStop();
            myQueue.push(j);
        } else {
            free( j );
        }
    }
}
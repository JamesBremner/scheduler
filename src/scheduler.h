#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class cJob
{
public:
    cJob(
        const std::string &name,
        const std::string &hhmmss,
        int durationMins);

    void name(const std::string &name)
    {
        myName = name;
    }
    void start(const std::string &start);

    void makeStop();

    bool isStop() const
    {
        return myfstop;
    }

    bool operator<(const cJob &other) const;

    std::string name() const
    {
        return myName;
    }
    std::string start() const;

    std::string textOnStart() const;

private:
    std::string myName;
    int myStart;
    int myDurationMins;
    bool myfstop;
};

class cScheduler
{
public:
    cScheduler()
        : myDay(0)
    {
    }
    void daily(
        const cJob &job)
    {
        myJobv.push_back(job);
        myQueue.push(job);
    }
    void run();

private:
    std::vector<cJob> myJobv;
    std::priority_queue<cJob> myQueue;
    int myDay;
};
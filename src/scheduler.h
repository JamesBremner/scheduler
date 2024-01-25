#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class cResource
{
public:
    cResource(const std::string &name)
        : myName(name),
          myFree(true)
    {
    }
    std::string name() const
    {
        return myName;
    }
    bool isFree() const
    {
        return myFree;
    }

    void allocate()
    {
        myFree = false;
    }

    void free()
    {
        myFree = true;
    }

private:
    std::string myName;
    bool myFree;
};

class cJob
{
public:
    cJob(
        const std::string &name,
        const std::string &hhmmss,
        int durationMins,
        const std::vector<std::string> &resourcev = {});

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

    std::vector<std::string> resources() const
    {
        return myResourcev;
    }

    std::string textOnStart() const;

private:
    std::string myName;
    int myStart;
    int myDurationMins;
    bool myfstop;
    std::vector<std::string> myResourcev;
};

class cScheduler
{
public:
    cScheduler()
        : myDay(0)
    {
    }
    void daily(
        const cJob &job);

    void run();

private:
    std::vector<cJob> myJobv;
    std::priority_queue<cJob> myQueue;
    std::vector<cResource> myResourcev;
    int myDay;

    void addNovelResources( const cJob& job );
    bool isResourceFree(  const cJob& job ) const;
    void allocate(const cJob& job );
    void free(const cJob& job);
};
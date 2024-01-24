#include <queue>

class cJob
{
public:
    cJob(
        const std::string &name,
        const std::string &hhmmss,
        int durationMins)
        : myName(name),
          myDurationMins(durationMins)
    {
        start( hhmmss);
    }

    void name(const std::string &name)
    {
        myName = name;
    }
    void start(const std::string &start);

    void makeStop();

    bool isStop() const
    {
        return ( myName.find("_stop") != -1 );
    }

    bool operator<(const cJob &other) const
    {
        return myStart < other.myStart;
    }

    std::string name() const
    {
        return myName;
    }
    std::string start() const;

private:
    std::string myName;
    int myStart;
    int myDurationMins;
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
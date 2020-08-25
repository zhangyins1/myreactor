#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <vector>
#include <functional>
#include <memory>

class Channel;
class EPoller;
class EventLoop
{

public:
    using pendingFunctor = std::function<void()>;

public:
    EventLoop();
    ~EventLoop();
    void addPendingFunctor(const pendingFunctor &functor);
    void loop();
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    void doPendingFunctors();
    bool hasChannel(Channel *channel);

private:
    bool isLooping;
    std::unique_ptr<EPoller> poller;
    std::vector<Channel *> activeChannels;
    Channel *currentActiveChannel;
    std::vector<pendingFunctor> pendingFunctors;
};

#endif
#include <vector>
#include <map>
#include "EventLoop.h"

struct epoll_event;
class Channel;
class EpollPoller
{
public:
    using ChannelList=std::vector<Channel*>; 
    EpollPoller(EventLoop* loop);
    ~EpollPoller();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    void poll(int timeoutMs,ChannelList* activeChannels);
private:
    typedef std::vector<struct epoll_event> EventList;
    using ChannelMap = std::map<int, Channel *>;
    void update(int op,Channel* channel);
    EventLoop *ownerLoop;
    EventList events;
    ChannelMap channels;
    static const int kInitEventListSize = 16;
    int epollFd;
};
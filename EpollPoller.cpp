#include <sys/epoll.h>
#include <sys/errno.h>
#include <unistd.h>
#include "EpollPoller.h"
#include "../utility/log.h"

namespace
{
    const int kNew = -1;
    const int kAdded = 1;
    const int kDeleted = 2;
} // namespace

EpollPoller::EpollPoller(EventLoop *loop) : events(16), epollFd(::epoll_create1(EPOLL_CLOEXEC)), ownerLoop(loop)
{
    if (epollFd < 0)
    {
        LOG_ERROR("error on epoll_create().", errno);
    }
}

EpollPoller::~EpollPoller()
{
    ::close(epollFd);
}

void EpollPoller::updateChannel(Channel *channel)
{
    int state = channel->state();
    if (state == kNew || channel->state == kDeleted)
    {
        int fd = channel->fd();
        if (state == kNew)
        {
            channels[fd] = channel;
        }
        else
        {
        }
        channel->setState(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        if (channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->setState(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EpollPoller::update(int op, Channel *channel)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = channel->events();
    event.data = channel;
    int fd = channel->fd();
    if (::epoll_ctl(epollFd, op, fd, &event) < 0)
    {
        LOG_ERROR("epoll update error", 0);
    }
}

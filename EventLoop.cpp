#include "EventLoop.h"
#include "EpollPoller.h"
#include "Channel.h"

void EventLoop::loop(){
    isLooping=true;
    while(isLooping){
        activeChannels.clear();
        
    }
}
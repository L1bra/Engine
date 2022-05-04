#pragma once

#include "event.h"



class WindowResizedEvent : public IEvent
{
private:
    int width;
    int height;
public:
    DECLARE_EVENT(WindowResizedEvent);
    
    WindowResizedEvent(int width, int height)
        :
        width(width),
        height(height)
    {
    }

    ~WindowResizedEvent()
    {
    }
};


class WindowClosedEvent: public IEvent
{
public:
    DECLARE_EVENT(WindowClosedEvent);

    WindowClosedEvent()
    {

    };
    ~WindowClosedEvent()
    {
    };
};
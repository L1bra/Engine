#pragma once

#include "event.h"



class WindowResizeEvent : public IEvent
{
private:
    int m_Width;
    int m_Height;
public:
    DECLARE_EVENT(WindowResizeEvent);
    
    WindowResizeEvent(int width, int height)
        :
        m_Width(width),
        m_Height(height)
    {
        printf("Resize event -> width: %d height: %d\n", width, height);
    }

    ~WindowResizeEvent()
    {
    }

    int GetWidth()
    {
        return m_Width;
    }

    int GetHeight()
    {
        return m_Height;
    }
};


class WindowCloseEvent: public IEvent
{
public:
    DECLARE_EVENT(WindowCloseEvent);

    WindowCloseEvent()
    {

    };
    ~WindowCloseEvent()
    {
    };
};
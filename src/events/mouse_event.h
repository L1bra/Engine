#pragma once

#include "event.h"

class MouseMovedEvent : public IEvent
{
private:
    double x;
    double y;
public:
    DECLARE_EVENT(MouseMovedEvent);

    MouseMovedEvent(double x, double y)
        :
        x(x),
        y(y)
    {
    }

    ~MouseMovedEvent()
    {
    };
};


class MouseScrolledEvent : public IEvent
{
private:
    double x;
    double y;
public:
    DECLARE_EVENT(MouseScrolledEvent);

    MouseScrolledEvent(double x, double y)
        :
        x(x),
        y(y)
    {
    }

    ~MouseScrolledEvent()
    {
    };
};


class MouseButtonPressedEvent : public IEvent
{
private:
    int button;
public:
    DECLARE_EVENT(MouseScrolledEvent);

    MouseButtonPressedEvent(int button)
        :
        button(button)
    {
    }

    ~MouseButtonPressedEvent()
    {
    };
};


class MouseButtonReleasedEvent : public IEvent
{
private:
    int button;
public:
    DECLARE_EVENT(MouseScrolledEvent);

    MouseButtonReleasedEvent(int button)
        :
        button(button)
    {
    }

    ~MouseButtonReleasedEvent()
    {
    };
};
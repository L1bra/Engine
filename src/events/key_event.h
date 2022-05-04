#pragma once

#include "event.h"

#include <string>

class KeyPressedEvent : public IEvent
{
private:
    int key;
public:
    DECLARE_EVENT(KeyPressedEvent);
    KeyPressedEvent(int key)
        :
        key(key)
    {
    }

    ~KeyPressedEvent()
    {
    }
    
    std::string format() const
    {
        std::string formatted = "KeyPressedEvent: " + (char)key;
        return formatted;
    }

    int get_key() const
    {
        return key;
    }
};

class KeyReleasedEvent : public IEvent
{
private:
    int key;
public:
    DECLARE_EVENT(KeyReleasedEvent);
    KeyReleasedEvent(int key)
        :
        key(key)
    {
    }
};
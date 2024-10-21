#pragma once

#include "event.h"

#include <string>

class KeyPressedEvent : public IEvent
{
private:
    int key;
    int scancode;
    int action;
    int mods;
public:
    DECLARE_EVENT(KeyPressedEvent);

    KeyPressedEvent(int key, int scancode, int action, int mods)
        :
        key(key),
        scancode(scancode),
        action(action),
        mods(mods)
    {
    }

    ~KeyPressedEvent()
    {
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
    int scancode;
    int action;
    int mods;
public:
    DECLARE_EVENT(KeyReleasedEvent);

    KeyReleasedEvent(int key, int scancode, int action, int mods)
        :
        key(key),
        scancode(scancode),
        action(action),
        mods(mods)
    {
    }

    ~KeyReleasedEvent()
    {
    }

    int get_key() const
    {
        return key;
    }
};
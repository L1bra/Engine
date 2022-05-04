#pragma once

#include "bitmask.h"
#include "events/event_manager.h"
#include "events/key_event.h"

class InputHandler : public EventListener
{
private:
    Bitmask prev_frame_keys;
    Bitmask curr_frame_keys;

    std::shared_ptr<IEventManager> m_em;
public:
    enum class Key
    {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN,

        W,
        A,
        S,
        D,

        ENTER,
        ESC
    };
public:
    InputHandler(std::shared_ptr<IEventManager> em);
    ~InputHandler();

    void OnExampleEvent(IEventPtr& data);

    // void update();

    // bool is_key_pressed(Key key_code) const;
    // bool is_key_down(Key key_code) const;
    // bool is_key_up(Key key_code) const;
};
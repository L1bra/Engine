#pragma once

#include <memory>
#include <functional>

class IEvent
{
public:
    typedef size_t id_t;
    virtual id_t get_id() = 0;
    //virtual std::string format() const = 0;
};

typedef std::shared_ptr<IEvent> IEventPtr;
typedef std::function<void(std::shared_ptr<IEvent>&)> EventDelegate;

class IEventManager
{
public:
    virtual bool add_listener(IEvent::id_t id, EventDelegate proc) = 0;
    virtual bool remove_listener(IEvent::id_t id, EventDelegate proc) = 0;
    virtual void queue_event(std::shared_ptr<IEvent> event) = 0;
    virtual void process_events() = 0;
};


#define DECLARE_EVENT(type) \
    static IEvent::id_t ID() \
    { \
        return reinterpret_cast<IEvent::id_t>(&ID); \
    } \
    IEvent::id_t get_id() override \
    { \
        return ID(); \
    } \
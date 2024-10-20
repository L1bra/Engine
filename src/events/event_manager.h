#pragma once

#include <list>
#include <map>
#include <vector>

#include "event.h"


class EventManager : public IEventManager 
{
private:
    typedef std::list<EventDelegate> event_delegate_list;

    std::list<std::shared_ptr<IEvent>> m_event_queue;
    std::map<IEvent::id_t, event_delegate_list> m_event_listeners;
public:

    ~EventManager() {};
    // Adds a listener to the event. The listener should invalidate itself when it needs to be removed. 
    virtual bool add_listener(IEvent::id_t id, EventDelegate proc) override;

    // Removes the specified delegate from the list
    virtual bool remove_listener(IEvent::id_t id, EventDelegate proc) override;

    // Queues an event to be processed during the next update
    virtual void queue_event(IEventPtr ev) override;

    // Processes all events
    virtual void process_events() override;
};


/*  Helper class that automatically handles removal of individual event listeners 
    registered using OnEvent() member function upon destruction of an object derived from this class. */ 
class EventListener
{
private:
    typedef std::pair<IEvent::id_t, EventDelegate> m_EventPair;
    std::vector<m_EventPair> m_LocalEvents;
    //std::vector<_DynEvPair> mDynamicLocalEvents; 
protected:
    std::weak_ptr<IEventManager> m_EventManager;
protected:
    EventListener(std::weak_ptr<IEventManager> mgr) 
        :
        m_EventManager(mgr)
    {
    }
    
    virtual ~EventListener()
    {
        if (m_EventManager.expired()) return;
        auto em = m_EventManager.lock();
        for (auto i : m_LocalEvents)
        {
            em->remove_listener(i.first, i.second);
        }
    }

    bool on_event(IEvent::id_t id, EventDelegate proc)
    {
        if (m_EventManager.expired()) return false;
        auto em = m_EventManager.lock();
        if (em->add_listener(id, proc))
        {
            m_LocalEvents.push_back(m_EventPair(id, proc));
        }

        return true;
    }
public:
    // Template function that also converts the event into the right data type before calling the event listener. 
    template<class T>
    bool on_event(std::function<void(std::shared_ptr<T>)> proc)
    {
        return on_event(T::ID(), [&, proc](std::shared_ptr<IEvent> data)
        {
            auto ev = std::dynamic_pointer_cast<T>(data);
            if (ev) proc(ev);
        });
    }
};
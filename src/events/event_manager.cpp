#include "event_manager.h"

// TODO: return 
bool EventManager::add_listener(IEvent::id_t id, EventDelegate proc) {
    auto i = m_event_listeners.find(id);

    if (i == m_event_listeners.end())
    {
        m_event_listeners[id] = std::list<EventDelegate>();
    }

    auto& list = m_event_listeners[id];
    for (auto i = list.begin(); i != list.end(); i++)
    {
        EventDelegate& func = *i;
        if (func.target<EventDelegate>() == proc.target<EventDelegate>())
            return false;
    }

    list.push_back(proc);
    // ?
    return true;
}

bool EventManager::remove_listener(IEvent::id_t id, EventDelegate proc) {
    auto j = m_event_listeners.find(id);
    if (j == m_event_listeners.end()) return false;
    auto& list = j->second;

    for (auto i = list.begin(); i != list.end(); ++i)
    {
        EventDelegate& func = *i;
        if (func.target<EventDelegate>() == proc.target<EventDelegate>()) 
        {
            list.erase(i);
            return true;
        }
    }
    return false;
}

void EventManager::queue_event(IEventPtr ev)
{
    m_event_queue.push_back(ev);
}

void EventManager::process_events()
{
    auto it = m_event_queue.begin();
    while(it != m_event_queue.end())
    {
        // printf("Processing event..\n");

        auto listeners = m_event_listeners.find((*it)->get_id());
        if (listeners != m_event_listeners.end())
        {
            // Call listeners
            for (auto l : listeners->second)
            {
                l(*it);
            }
        }
        
        // remove event
        it = m_event_queue.erase(it);
    }
}
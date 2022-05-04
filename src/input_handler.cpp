#include "input_handler.h"

InputHandler::InputHandler(std::shared_ptr<IEventManager> em)
    :
    EventListener(em)
{
    m_em = em;

    on_event<KeyPressedEvent>([&](std::shared_ptr<KeyPressedEvent> data)
    {
        printf("keypressedvent!\n");
    });
}

InputHandler::~InputHandler()
{
    m_em->remove_listener(KeyPressedEvent::ID(), std::bind(&InputHandler::OnExampleEvent, this, std::placeholders::_1));
}

void InputHandler::OnExampleEvent(IEventPtr& data)
{
    auto ev = std::dynamic_pointer_cast<KeyPressedEvent>(data);
    if (!ev) return;
}
#include "input_handler.h"

InputHandler::InputHandler(std::shared_ptr<IEventManager> em)
    :
    EventListener(em)
{
    m_em = em;

    on_event<KeyPressedEvent>([&](std::shared_ptr<KeyPressedEvent> data)
    {
        return on_key_event(data->get_key(), true);
    });

    on_event<KeyReleasedEvent>([&](std::shared_ptr<KeyReleasedEvent> data)
    {
        return on_key_event(data->get_key(), false);
    });
}

InputHandler::~InputHandler()
{
    m_em->remove_listener(KeyPressedEvent::ID(), std::bind(&InputHandler::OnExampleEvent, this, std::placeholders::_1));
}

void InputHandler::on_key_event(int key, bool is_pressed)
{
    switch(key)
    {
        case GLFW_KEY_ENTER:  curr_frame_keys.set_bit((int)Key::ENTER, is_pressed); break;
        case GLFW_KEY_ESCAPE: curr_frame_keys.set_bit((int)Key::ESC, is_pressed); break;
        case GLFW_KEY_LEFT:   curr_frame_keys.set_bit((int)Key::LEFT, is_pressed); break;
        case GLFW_KEY_RIGHT:  curr_frame_keys.set_bit((int)Key::RIGHT, is_pressed); break;
        case GLFW_KEY_UP:     curr_frame_keys.set_bit((int)Key::UP, is_pressed); break;
        case GLFW_KEY_DOWN:   curr_frame_keys.set_bit((int)Key::DOWN, is_pressed); break;
        case GLFW_KEY_W:      curr_frame_keys.set_bit((int)Key::W, is_pressed); break;
        case GLFW_KEY_A:      curr_frame_keys.set_bit((int)Key::A, is_pressed); break;
        case GLFW_KEY_S:      curr_frame_keys.set_bit((int)Key::S, is_pressed); break;     
        case GLFW_KEY_D:      curr_frame_keys.set_bit((int)Key::D, is_pressed); break;
        case GLFW_KEY_M:      curr_frame_keys.set_bit((int)Key::C, is_pressed); break;
    }
}

void InputHandler::OnExampleEvent(IEventPtr& data)
{
    auto ev = std::dynamic_pointer_cast<KeyPressedEvent>(data);
    if (!ev) return;
}

void InputHandler::update()
{
    prev_frame_keys.set_mask(curr_frame_keys);
}

bool InputHandler::is_key_pressed(Key key_code)
{
    return curr_frame_keys.get_bit((int)key_code);
}


bool InputHandler::is_key_down(Key key_code)
{
    bool prev_frame = prev_frame_keys.get_bit((int)key_code);
    bool curr_frame = curr_frame_keys.get_bit((int)key_code);

    return curr_frame && !prev_frame;
}


bool InputHandler::is_key_up(Key key_code)
{
    bool prev_frame = prev_frame_keys.get_bit((int)key_code);
    bool curr_frame = curr_frame_keys.get_bit((int)key_code);

    return !curr_frame && prev_frame;
}
#include "Core/Application.h"

int main()
{
    std::unique_ptr<ApplicationContext> pApp_ctx = std::make_unique<ApplicationContext>(); // TODO
    Application app(pApp_ctx->m_EventManager);
    return 0;
}
cmake_minimum_required(VERSION 3.1)

project(Engine VERSION 0.1 LANGUAGES CXX C)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/src/*.cpp 
)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/*.h
)

set(GLAD_SOURCE ${PROJECT_SOURCE_DIR}/dependencies/include/glad/glad.c)
set(GLFW_LIB ${PROJECT_SOURCE_DIR}/dependencies/lib/glfw3.lib)

include_directories(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/dependencies/include
)

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${GLAD_SOURCE}
)

target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIB}
)
project(andy-widgets)

add_library(andy-widgets OBJECT
    ${CMAKE_CURRENT_LIST_DIR}/src/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/text.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/input.cpp
)

target_link_libraries(andy-widgets andy-drawing andy-xml andy-binary)

if (TARGET andy-test)
    andy_tests_configure(andy-widgets)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
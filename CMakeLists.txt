project(uva-widgets)

add_library(uva-widgets
    ${CMAKE_CURRENT_LIST_DIR}/src/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/text.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/input.cpp
)

target_link_libraries(uva-widgets uva-drawing uva-xml uva-binary)

if (TARGET uva-test)
    uva_tests_configure(uva-widgets)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
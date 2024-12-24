project(uva-widgets)

add_library(uva-widgets
    ${CMAKE_CURRENT_LIST_DIR}/src/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/text.cpp
)

target_link_libraries(uva-widgets -lSDL2 uva-xml uva-binary -lSDL2_ttf -lSDL2_gfx)

if (TARGET uva-test)
    uva_tests_configure(uva-widgets)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
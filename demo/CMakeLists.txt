file(GLOB
    SRC
    *.c
)

add_executable(demo ${SRC})

target_include_directories(demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(demo PUBLIC canmaster ulfius pthread jansson)

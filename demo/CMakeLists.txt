file(GLOB
    SRC
    *.c
)

add_executable(demo ${SRC})

target_link_libraries(demo PUBLIC canmaster)

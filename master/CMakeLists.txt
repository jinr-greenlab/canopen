file(GLOB
    SRC
    *.c
    application/*.c
    CANopen/*.c
    confile/*.c
    logger/*.c
)

add_library(canmaster SHARED ${SRC})

target_include_directories(canmaster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(-DCAN_OS_LINUX)
target_link_libraries(canmaster PUBLIC chai yaml)

set(_srcs Thread.cpp Timer.cpp SerialPort.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Threads)

add_library(${PROJECT_NAME} SHARED ${_srcs})
add_library(${PROJECT_NAME}Static STATIC  ${_srcs})

install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)


cmake_minimum_required(VERSION 3.27)

project(MongoCXXExample VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable(App main.cpp)

include_directories(
    "/usr/local/include/mongocxx/v_noabi"
    "/usr/local/include/bsoncxx/v_noabi"
    "/usr/local/include/bsoncxx/v_noabi/bsoncxx/third_party/mnmlstc"
)

target_link_libraries(
    App
    PRIVATE
    "/usr/local/lib/libmongocxx._noabi.dylib"
    "/usr/local/lib/libbsoncxx._noabi.dylib"
)

install(TARGETS App DESTINATION bin)

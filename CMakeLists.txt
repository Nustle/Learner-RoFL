cmake_minimum_required(VERSION 3.14)
project(Learner-RoFL)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 1.10.4
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

add_executable(Learner-RoFL main.cpp
        utils.cpp
        api.cpp
        table_aux.cpp
        include/api.h
        include/utils.h
        include/table_aux.h
)

target_link_libraries(Learner-RoFL PRIVATE cpr::cpr nlohmann_json::nlohmann_json)
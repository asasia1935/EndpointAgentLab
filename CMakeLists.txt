cmake_minimum_required(VERSION 3.20)

project(EndpointAgentLab LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(eal_core INTERFACE)
target_include_directories(eal_core INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(eal_core INTERFACE cxx_std_20)

if(MSVC)
    target_compile_options(eal_core INTERFACE /W4)
endif()

add_library(eal_runtime STATIC src/core/agent_runtime.cpp)
target_link_libraries(eal_runtime PUBLIC eal_core)

add_executable(EndpointAgentLab src/main.cpp)
target_link_libraries(EndpointAgentLab PRIVATE eal_runtime)

include(CTest)

if(BUILD_TESTING)
    add_executable(eal_event_smoke tests/event_model_smoke.cpp)
    target_link_libraries(eal_event_smoke PRIVATE eal_core)
    add_test(NAME eal_event_smoke COMMAND eal_event_smoke)

    add_executable(eal_runtime_smoke tests/agent_runtime_smoke.cpp)
    target_link_libraries(eal_runtime_smoke PRIVATE eal_runtime)
    add_test(NAME eal_runtime_smoke COMMAND eal_runtime_smoke)
endif()

#include "eal/core/agent_runtime.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <thread>

namespace {

std::atomic<bool> stop_requested{false};

BOOL WINAPI console_control_handler(DWORD control_type) {
    if (control_type == CTRL_C_EVENT) {
        stop_requested.store(true, std::memory_order_relaxed);
        return TRUE;
    }

    return FALSE;
}

} // namespace

int main(int argc, char* argv[]) {
    if (argc != 2 || std::string_view{argv[1]} != "console") {
        std::cerr << "Usage: EndpointAgentLab.exe console\n";
        return EXIT_FAILURE;
    }

    eal::core::AgentRuntime runtime;

    if (!SetConsoleCtrlHandler(console_control_handler, TRUE)) {
        std::cerr << "[ConsoleHost] Failed to register Ctrl+C handler (Windows error "
                  << GetLastError() << ")\n";
        return EXIT_FAILURE;
    }

    std::cout << "[ConsoleHost] Starting agent...\n";
    if (!runtime.start()) {
        std::cerr << "[ConsoleHost] Failed to start agent\n";
        if (!SetConsoleCtrlHandler(console_control_handler, FALSE)) {
            std::cerr << "[ConsoleHost] Failed to unregister Ctrl+C handler (Windows error "
                      << GetLastError() << ")\n";
        }
        return EXIT_FAILURE;
    }

    std::cout << "[ConsoleHost] AgentRuntime started\n"
              << "[ConsoleHost] Press Ctrl+C to stop\n";

    while (!stop_requested.load(std::memory_order_relaxed)) {
        std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }

    std::cout << "[ConsoleHost] Stop requested\n";
    runtime.stop();
    std::cout << "[ConsoleHost] AgentRuntime stopped\n";

    if (!SetConsoleCtrlHandler(console_control_handler, FALSE)) {
        std::cerr << "[ConsoleHost] Failed to unregister Ctrl+C handler (Windows error "
                  << GetLastError() << ")\n";
        return EXIT_FAILURE;
    }

    std::cout << "[ConsoleHost] Exiting\n";
    return EXIT_SUCCESS;
}

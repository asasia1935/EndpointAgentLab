#include "eal/core/agent_runtime.hpp"

int main() {
    eal::core::AgentRuntime runtime;

    if (runtime.is_running()) {
        return 1;
    }
    if (!runtime.start()) {
        return 2;
    }
    if (!runtime.is_running()) {
        return 3;
    }
    if (!runtime.start() || !runtime.is_running()) {
        return 4;
    }

    runtime.stop();
    if (runtime.is_running()) {
        return 5;
    }
    runtime.stop();
    if (runtime.is_running()) {
        return 6;
    }

    if (!runtime.start() || !runtime.is_running()) {
        return 7;
    }
    runtime.stop();
    if (runtime.is_running()) {
        return 8;
    }

    return 0;
}

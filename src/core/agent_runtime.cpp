#include "eal/core/agent_runtime.hpp"

namespace eal::core {

bool AgentRuntime::start() {
    if (running_) {
        return true;
    }

    running_ = true;
    return true;
}

void AgentRuntime::stop() {
    if (!running_) {
        return;
    }

    running_ = false;
}

bool AgentRuntime::is_running() const {
    return running_;
}

} // namespace eal::core

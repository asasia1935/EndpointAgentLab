#pragma once

namespace eal::core {

class AgentRuntime {
public:
    bool start();
    void stop();
    bool is_running() const;

private:
    bool running_ = false;
};

} // namespace eal::core

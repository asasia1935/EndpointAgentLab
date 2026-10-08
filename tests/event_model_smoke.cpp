#include "eal/core/event.hpp"

#include <chrono>
#include <string>

int main() {
    const auto observed_at = std::chrono::system_clock::now();
    const eal::core::EndpointEvent event{
        .type = eal::core::EventType::FileCreated,
        .observed_at = observed_at,
        .target = "C:/temp/example.txt",
    };

    if (event.type != eal::core::EventType::FileCreated ||
        event.observed_at != observed_at ||
        event.target != "C:/temp/example.txt") {
        return 1;
    }

    return 0;
}

#pragma once

#include <chrono>
#include <string>

namespace eal::core {

enum class EventType {
    FileCreated,
    FileModified,
    FileDeleted,
    FileRenamed,
    ProcessStarted,
    ProcessExited,
};

struct EndpointEvent {
    EventType type;
    // Wall-clock time when the agent observed the event.
    std::chrono::system_clock::time_point observed_at;
    // UTF-8 event target; platform layers convert Windows UTF-16 input as needed.
    std::string target;
};

} // namespace eal::core

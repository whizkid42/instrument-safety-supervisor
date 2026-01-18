#include "SafetySupervisor.h"
#include "Logger.h"

SafetySupervisor::SafetySupervisor(const SafetyLimits& limits)
    : limits(limits) {}

SafetyDecision SafetySupervisor::evaluate(const MotionCommand& command, const InstrumentState& state, MotionCommand& safeCommandOut) 
    const {
        if (state.status != SensorStatus::OK) {
            Logger::log(LogLevel::ERROR, "SafetySupervisor", "Sensor health not OK. Rejecting command.");
            return SafetyDecision::REJECT;
        }
        if (command.targetPosition < limits.minPosition || command.targetPosition > limits.maxPosition) {
            Logger::log(LogLevel::ERROR, "SafetySupervisor", "Target position out of bounds. Rejecting command.");
            return SafetyDecision::REJECT;
        }

        safeCommandOut = command;

        if (command.maxVelocity > limits.maxVelocity) {
            Logger::log(LogLevel::WARN, "SafetySupervisor", "Velocity exceeds limit. Clamping command.");
            safeCommandOut.maxVelocity = limits.maxVelocity;
            return SafetyDecision::CLAMP;
        }
        Logger::log(LogLevel::INFO, "SafetySupervisor", "Command is safe. Allowing execution.");
        return SafetyDecision::ALLOW;
}

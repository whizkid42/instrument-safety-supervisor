#include "SafetySupervisor.h"

SafetySupervisor::SafetySupervisor(const SafetyLimits& limits)
    : limits(limits) {}

SafetyDecision SafetySupervisor::evaluate(const MotionCommand& command, const InstrumentState& state, MotionCommand& safeCommandOut) 
    const {
        if (state.status == SensorStatus::OK && command.targetPosition >= limits.minPosition && command.targetPosition <= limits.maxPosition && 
            command.maxVelocity <= limits.maxVelocity) {
            safeCommandOut = command;
            return SafetyDecision::ALLOW;
        }
        return SafetyDecision::REJECT;
}

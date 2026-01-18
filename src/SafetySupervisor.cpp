#include "SafetySupervisor.h"

SafetySupervisor::SafetySupervisor(const SafetyLimits& limits)
    : limits(limits) {}

SafetyDecision SafetySupervisor::evaluate(const MotionCommand& command, const InstrumentState& state, MotionCommand& safeCommandOut) 
    const {
        if (state.status != SensorStatus::OK) {
            return SafetyDecision::REJECT;
        }
        if (command.targetPosition < limits.minPosition || command.targetPosition > limits.maxPosition) {
            return SafetyDecision::REJECT;
        }

        safeCommandOut = command;

        if (command.maxVelocity > limits.maxVelocity) {
            safeCommandOut.maxVelocity = limits.maxVelocity;
            return SafetyDecision::CLAMP;
        }
        return SafetyDecision::ALLOW;
}

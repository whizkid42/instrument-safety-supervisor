#include "SafetySupervisor.h"

SafetySupervisor::SafetySupervisor(const SafetyLimits& limits)
    : limits_(limits) {}

SafetyDecision SafetySupervisor::evaluate(const MotionCommand& command, const InstrumentState& state, MotionCommand& safeCommandOut) 
    const {
        return SafetyDecision::REJECT;
}

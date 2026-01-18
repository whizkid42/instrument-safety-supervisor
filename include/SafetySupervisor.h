#ifndef SAFETY_SUPERVISOR_H
#define SAFETY_SUPERVISOR_H

#include "MotionCommand.h"
#include "InstrumentState.h"
#include "SafetyLimits.h"
#include "SafetyDecision.h"

class SafetySupervisor {
public:
    explicit SafetySupervisor(const SafetyLimits& limits);

    SafetyDecision evaluate(const MotionCommand& command, const InstrumentState& state, MotionCommand& safeCommandOut) const;

private:
    SafetyLimits limits;
};  
#endif 
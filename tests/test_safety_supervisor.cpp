#include "SafetySupervisor.h"
#include <cassert>

int main() {
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{60.0, 8.0};
    InstrumentState state{SensorStatus::OK, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::ALLOW);
    assert(safeCommand.targetPosition == command.targetPosition);
    assert(safeCommand.maxVelocity == command.maxVelocity);
    
    return 0;
}
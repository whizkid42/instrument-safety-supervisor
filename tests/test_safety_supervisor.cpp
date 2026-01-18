#include "SafetySupervisor.h"
#include <cassert>

int main() {
    {
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{60.0, 8.0};
    InstrumentState state{SensorStatus::OK, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::ALLOW);
    assert(safeCommand.targetPosition == command.targetPosition);
    assert(safeCommand.maxVelocity == command.maxVelocity);
}
{   
    //test 2: velocity exceeds limit
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{60.0, 20.0};
    InstrumentState state{SensorStatus::OK, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::CLAMP);
    assert(safeCommand.targetPosition == command.targetPosition);
    assert(safeCommand.maxVelocity == limits.maxVelocity);
}
{
    //test 3: target position out of bounds
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{150.0, 5.0};
    InstrumentState state{SensorStatus::OK, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::REJECT);
}
{
    //test 4: sensor status not OK
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{60.0, 5.0};
    InstrumentState state{SensorStatus::FAILED, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::REJECT);
}
{
    // test 5: Sensor status STATLE
    SafetyLimits limits{0.0, 100.0, 10.0};
    SafetySupervisor supervisor(limits);
    MotionCommand command{60.0, 5.0};
    InstrumentState state{SensorStatus::STATLE, 50.0, 5.0};
    MotionCommand safeCommand;
    SafetyDecision decision = supervisor.evaluate(command, state, safeCommand);
    assert(decision == SafetyDecision::REJECT);
}
    return 0;
}


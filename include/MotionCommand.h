#ifndef MOTION_COMMAND_H
#define MOTION_COMMAND_H

struct MotionCommand {
    double targetPosition; // in mm
    double maxVelocity; // in mm/s

};

#endif // MOTION_COMMAND_H
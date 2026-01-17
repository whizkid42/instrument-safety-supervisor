#ifndef SAFETY_DECISION_H
#define SAFETY_DECISION_H

enum class SafetyDecision {
    ALLOW, //command is safe as-is
    CLAMP, // command needs to be modified to be safe
    REJECT // command is unsafe and should not be executed
};

#endif 
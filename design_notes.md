# 🛡️ Surgical Instrument Safety Supervisor — Design Notes

## 📌 Purpose of This Document
This document explains the **design rationale, safety criteria, and decision logic**
behind the *Surgical Instrument Safety Supervisor*.

The intent is to clearly answer:
- **What safety problems are being solved**
- **How safety is enforced**
- **Why specific design decisions were made**
- **How unsafe motion is prevented under all conditions**

This mirrors the level of reasoning expected in **medical and surgical robotics software**.

---

## 🧠 System Intent (High-Level)

In a surgical robotic system, **motion commands must never directly reach actuators**.
Every command must first pass through a **safety supervisor** that evaluates:

- system health
- physical limits
- command validity

The Safety Supervisor acts as a **hard safety gate** between *intent* and *motion*.

Motion Command
    |
    v
+............+
|Safety Supervisor|
+............+
    |
    v
Actuator Interface


Unsafe motion is **blocked deterministically**.

---

## 🧱 Core Design Principles

### 1️⃣ Safety Before Functionality 🛑
The system prioritizes **preventing unsafe motion** over executing commands.

If any doubt exists:
> **Motion is inhibited.**

This is implemented through:
- conservative checks
- early rejection
- explicit health gating

---

### 2️⃣ Explicit Modeling (No Implicit Assumptions) 🔍
Safety-critical information is **modeled explicitly**, not inferred.

Examples:
- Sensor health is a first-class field (`SensorStatus`)
- Safety limits are defined centrally (`SafetyLimits`)
- Decisions are explicit (`SafetyDecision` enum)

This avoids:
- hidden assumptions
- magic values
- silent failures

---

### 3️⃣ Graduated Safety Responses ⚖️
Not all violations are treated equally.

Some unsafe commands can be **made safe**.  
Others must be **rejected outright**.

This distinction is critical in surgical robotics.

---

## 🧩 Key Data Models

### 📍 InstrumentState
Represents the **current state of the instrument** as perceived by the system.

```cpp
struct InstrumentState {
    double position;    // mm
    double velocity;    // mm/s
    SensorStatus status;
};
---
 ### 🎯 MotionCommand

Represents intent, not execution.

struct MotionCommand {
    double targetPosition; // mm
    double maxVelocity;    // mm/s
};


This allows the supervisor to:

modify commands (clamp)

reject commands

pass through unchanged

---
### 🚧 SafetyLimits

Defines hard physical constraints of the system.

struct SafetyLimits {
    double minPosition;  // mm
    double maxPosition;  // mm
    double maxVelocity;  // mm/s
};

Design rationale:

Centralized limits prevent inconsistent enforcement

Limits are owned by the supervisor

Limits are immutable during evaluation

## Safety Decisions:
Decision meanings
Decision	Meaning
Allow	Command is safe and unmodified
Clamp	Command modified to safe limits
Reject	Command is unsafe and blocked

## Supervisor logic:
1. Sensor Health Check
2. Workspace Bound Check
3. Velocity Limit Check
4. Allow Safe Command
            ┌──────────────┐
            │ Sensor OK ?  │
            └──────┬───────┘
                   │ NO
                   ▼
                REJECT ❌
                   │
                  STOP
                   │
                   ▼
            ┌──────────────┐
            │ Position OK? │
            └──────┬───────┘
                   │ NO
                   ▼
                REJECT ❌
                   │
                  STOP
                   │
                   ▼
            ┌──────────────┐
            │ Velocity OK? │
            └──────┬───────┘
                   │ NO
                   ▼
               CLAMP ⚠️
                   │
                   ▼
                ALLOW ✅


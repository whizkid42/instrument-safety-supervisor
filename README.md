# 🛡️ Surgical Instrument Safety Supervisor (Simulation)

## Overview
This project implements a **fail-safe safety supervisor** for a simulated
surgical robotic instrument.  
The supervisor evaluates motion commands against **system health** and
**hard safety limits** before allowing any motion to proceed.

The design mirrors how **real surgical robotic systems** ensure that
unsafe commands never reach actuators — even under failure conditions.

This project emphasizes:
- safety-first design
- explicit failure modeling
- explainable decisions
- verification through tests

---

## Why a Safety Supervisor?
In surgical robotics, motion commands must **never be trusted blindly**.

Before any actuator moves, the system must answer:
- Is the sensor data valid?
- Is the command physically safe?
- Can the command be modified safely?
- Should motion be inhibited entirely?

The **Safety Supervisor** is the component responsible for making
these decisions.

```cpp
Motion Command
    |
    v
+............+
|Safety Supervisor|
+............+
    |
    v
Actuator Interface
```


Unsafe motion is **deterministically blocked**.

---

## Key Concepts

### 1️⃣ Explicit Safety Limits
All motion is evaluated against immutable limits:
- workspace boundaries
- maximum velocity

These limits represent **physical constraints**, not tunable parameters.

---

### 2️⃣ Sensor Health Awareness
Sensor values are never evaluated in isolation.

Each instrument state includes an explicit health indicator:
- `OK` – data valid
- `FAILED` – sensor failure detected
- `STALE` – data unreliable or outdated

If sensor health is not `OK`, **all motion is rejected immediately**.

---

### 3️⃣ Graduated Safety Decisions
Not all unsafe commands are treated equally.

The supervisor returns one of three explicit decisions:

| Decision | Meaning |
|--------|--------|
Allow | Command is safe and unchanged |
Clamp | Command modified to remain safe |
Reject | Command unsafe and blocked |

This prevents silent correction of dangerous conditions and ensures
explainable behavior.

---

## Safety Rules Enforced

1. **Health Gate (Highest Priority)**  
   - If sensor status is not `OK` → motion is rejected

2. **Workspace Enforcement**  
   - Target positions outside bounds → rejected

3. **Velocity Enforcement**  
   - Excessive velocity → clamped to safe limit

4. **Normal Operation**  
   - Healthy system + valid command → allowed unchanged

The supervisor always favors **fail-safe behavior** over execution.

---

## Failure Handling & Verification
Failure scenarios are **explicitly modeled and verified** using automated tests,
including:
- sensor failure
- stale sensor data
- out-of-bounds commands
- excessive velocity requests

Rather than relying on a runtime demo, **tests serve as the primary system-level
evidence** that unsafe motion cannot occur.

This approach reflects real medical robotics development, where safety behavior
is validated through **deterministic verification**, not manual observation.

---

## Project Structure

```text
surgical-safety-supervisor/
├── include/
│   ├── InstrumentState.h
│   ├── MotionCommand.h
│   ├── SafetyLimits.h
│   ├── SafetyDecision.h
│   ├── SensorStatus.h
│   ├── SafetySupervisor.h
│   └── Logger.h
├── src/
│   ├── SafetySupervisor.cpp
│   └── Logger.cpp
├── tests/
│   └── test_safety_supervisor.cpp
├── design_notes.md
└── README.md
```
---

## Design Notes

For detailed reasoning behind safety limits, decision ordering, health modeling,
and fail-safe philosophy, see:

📄 design_notes.md

This document explains:

why certain violations are clamped vs rejected

how sensor health gates all motion

how failure injection is used for verification

how unsafe motion is made provably impossible

---

## Build & Run Tests
```cpp
g++ -Iinclude src/SafetySupervisor.cpp src/Logger.cpp tests/test_safety_supervisor.cpp -o test_supervisor
```
```cpp
./test_supervisor
```
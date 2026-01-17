#ifndef INSTRUMENT_STATE_H
#define INSTRUMENT_STATE_H

#include "SensorStatus.h"

struct InstrumentState {
    SensorStatus status;
    double position; // in mm
    double velocity; // in mm/s

};

#endif // INSTRUMENT_STATE_H
#ifndef COIN_SENSOR_H
#define COIN_SENSOR_H

#include "Arduino.h"
#include <CapacitiveSensor.h>

class CoinSensor
{
  public:

    CoinSensor(int threshold, int debounce_ms, int tx_pin, int rx_pin, int output);
    CoinSensor(int threshold, int debounce_ms, int tx_pin, int rx_pin, int output, const char *name);
    ~CoinSensor();

    void initialize(unsigned long timeout_ms, unsigned long calibration_period_ms);
    int read_sensor(int samples);
    const char *get_name() { return sensor_name; }


  private:

    const int sensor_threshold;     // The threshold value for detecting a touch
    const int sensor_debounce_ms;   // The debounce lock time
    const char *sensor_name;        // (Debugging) name for the sensor
    const int output_pin;           // The output pin to switch high or low based on sensed input

    CapacitiveSensor sensor;        // The actual sensor

    // Tracking variables
    int prev_state;
    long bounce_time;
    int output;
};

#endif

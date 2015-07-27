#include "coin_sensor.h"

#define NUM_SAMPLES (50)

CoinSensor::CoinSensor(int threshold, int debounce_ms, int tx_pin, int rx_pin, int output) :
  CoinSensor(threshold, debounce_ms, tx_pin, rx_pin, output, "SENSOR")
{}

CoinSensor::CoinSensor(int threshold, int debounce_ms, int tx_pin, int rx_pin, int output, const char *name) :
  sensor_threshold(threshold),
  sensor_debounce_ms(debounce_ms),
  sensor(tx_pin, rx_pin),
  output_pin(output),
  sensor_name(name)
{}

CoinSensor::~CoinSensor()
{}

void CoinSensor::initialize(unsigned long timeout_ms, unsigned long calibration_period_ms)
{
  prev_state = LOW;
  bounce_time = 0;
  output = LOW;

  // Configure sensor
  sensor.set_CS_Timeout_Millis(timeout_ms);
  sensor.set_CS_AutocaL_Millis(calibration_period_ms);

  // Configure output pin
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, LOW);
}

int CoinSensor::read_sensor(int samples)
{
  long currentTime = millis();
  long sensor_value = sensor.capacitiveSensor(samples);
  int new_state = ((sensor_value > sensor_threshold) || (sensor_value < 0)) ? HIGH : LOW;

  // Debugging - uncomment this and monitor to get threshold values
  //Serial.print(sensor_name);
  //Serial.print(": ");
  //Serial.println(sensor_value);
  ////////////////

  // Reset debounce clock if the state has changed
  if(new_state != prev_state)
  {
    bounce_time = currentTime;
  }

  // If debounceclock expires
  if((currentTime - bounce_time) > sensor_debounce_ms)
  {
    if(new_state != output)
    {
      output = new_state;
      digitalWrite(output_pin, output);
    }
  }

  prev_state = new_state;
  return output;
}

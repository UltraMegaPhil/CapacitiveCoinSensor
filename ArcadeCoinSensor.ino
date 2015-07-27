#include <CapacitiveSensor.h>
#include "coin_sensor.h"

// Sensor constants
const int NUM_SENSORS = 2;

const int SENSOR_1_THRESHOLD = 3000;
const int SENSOR_2_THRESHOLD = 3000;

const int SENSOR_1_DEBOUNCE_MS  = 25;
const int SENSOR_1_TX_PIN       = 5;
const int SENSOR_1_RX_PIN       = 2;
const int SENSOR_1_CTRL_PIN     = 11;

const int SENSOR_2_DEBOUNCE_MS  = 25;
const int SENSOR_2_TX_PIN       = 6;
const int SENSOR_2_RX_PIN       = 3;
const int SENSOR_2_CTRL_PIN     = 12;

// Sensor objects
CoinSensor sensors[] = 
{
  CoinSensor(SENSOR_1_THRESHOLD, SENSOR_1_DEBOUNCE_MS, SENSOR_1_TX_PIN, SENSOR_1_RX_PIN, SENSOR_1_CTRL_PIN, "Player 1"),
  CoinSensor(SENSOR_2_THRESHOLD, SENSOR_2_DEBOUNCE_MS, SENSOR_2_TX_PIN, SENSOR_2_RX_PIN, SENSOR_2_CTRL_PIN, "Player 2")
};

// Tracks sensorr values for debugging to serial port
int sensor_values[] = 
{
  LOW,
  LOW  
};

void setup()                    
{
  Serial.begin(9600);

  for(int i = 0; i < NUM_SENSORS; ++i)
  {
    sensors[i].initialize(500, 5000);
  }
}

void loop()                    
{
  for(int i = 0; i < NUM_SENSORS; ++i)
  {
    int value = sensors[i].read_sensor(50);  
    if(value != sensor_values[i])
    {
      // DEBUGGING
      if(value == HIGH)
      {
        Serial.print("[");
        Serial.print(sensors[i].get_name());
        Serial.println("] ON!");
      }
      else 
      {
        Serial.print("[");
        Serial.print(sensors[i].get_name());
        Serial.println("] OFF!");
      }
      ////////////////////////////////////////////////////

      sensor_values[i] = value;
    }
  }
}

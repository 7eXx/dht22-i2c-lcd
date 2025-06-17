#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

void dhtBegin();
void updateReadValues();
float getTemperature();
float getHumidity();
float getMinTemperature();
float getMaxTemperature();
float getMinHumidity();
float getMaxHumidity();

#endif
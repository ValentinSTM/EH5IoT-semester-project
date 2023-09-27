/*
 * Project PT500
 * Description: Temperature measurement with PT500 and Particle Argon
 * (https://docs.particle.io/datasheets/wi-fi/argon-datasheet/)
 * Author: Valentin-Stefan Tudora-Mayer
 * Date: August 03, 2023
 */
#include <Particle.h>
#include <deque>
#include <algorithm>

struct RtdValue
{
  float temperature;
  float resistance;
};
// Tabel RTD table for PT500 (temperature , resistance) (Kamstrup A/S)
const RtdValue rtdTable[] = {
    {0, 500.000},
    {1, 501.954},
    {2, 503.907},
    {3, 505.860},
    {4, 507.812},
    {5, 509.764},
    {6, 511.715},
    {7, 513.665},
    {8, 515.615},
    {9, 517.564},
    {10, 519.513},
    {11, 521.461},
    {12, 523.408},
    {13, 525.355},
    {14, 527.302},
    {15, 529.247},
    {16, 531.192},
    {17, 533.137},
    {18, 535.081},
    {19, 537.025},
    {20, 538.968},
    {21, 540.910},
    {22, 542.852},
    {23, 544.793},
    {24, 546.733},
    {25, 548.673},
    {26, 550.613},
    {27, 552.552},
    {28, 554.490},
    {29, 556.428},
    {30, 558.365},
    {31, 560.301},
    {32, 562.237},
    {33, 564.173},
    {34, 566.107},
    {35, 568.042},
    {36, 569.975},
    {37, 571.908},
    {38, 573.841},
    {39, 575.773},
    {40, 577.704},
    {41, 579.635},
    {42, 581.565},
    {43, 583.495},
    {44, 585.424},
    {45, 587.352},
    {46, 589.280},
    {47, 591.207},
    {48, 593.134},
    {49, 595.060},
    {50, 596.986},
    {51, 598.911},
    {52, 600.835},
    {53, 602.759},
    {54, 604.682},
    {55, 606.605},
    {56, 608.527},
    {57, 610.448},
    {58, 612.369},
    {59, 614.290},
    {60, 616.210},
    {61, 618.129},
    {62, 620.047},
    {63, 621.965},
    {64, 623.883},
    {65, 625.800},
    {66, 627.716},
    {67, 629.632},
    {68, 631.547},
    {69, 633.462},
    {70, 635.376},
    {71, 637.289},
    {72, 639.202},
    {73, 641.114},
    {74, 643.026},
    {75, 644.937},
    {76, 646.848},
    {77, 648.758},
    {78, 650.667},
    {79, 652.576},
    {80, 654.484},
    {81, 656.392},
    {82, 658.299},
    {83, 660.205},
    {84, 662.111},
    {85, 664.017},
    {86, 665.921},
    {87, 667.826},
    {88, 669.729},
    {89, 671.632},
    {90, 673.535},
    {91, 675.437},
    {92, 677.338},
    {93, 679.239},
    {94, 681.139},
    {95, 683.038},
    {96, 684.937},
    {97, 686.836},
    {98, 688.734},
    {99, 690.631},
    {100, 692.528}
    // ... all values from PT500 table (Kamstrup A/S)
};

// Number of elements in the table
const int rtdTableSize = sizeof(rtdTable) / sizeof(rtdTable[0]);

// PT500 circuit parameters
const int analogPin = A0;            // PT500 connected to A0
const float referenceVoltage = 3.3;  // Argon reference voltage  3.3V
const float adcMaxValue = 4095.0;    // 12-bit ADC resolution  4095  (2^12 - 1)
const float seriesResistor = 596;    // 596 Ohm series resistor
const size_t sampleSize = 5;         // Number of samples to average
std::deque<float> resistanceSamples; // Queue of resistance samples
float sumOfSamples = 0;              // Sum of resistance samples

// Interpolate the temperature from the table
float interpolateTemperature(float measured_resistance) // measured_resistance is the resistance of the PT500
{
  // Find the first element in the table that is greater than the measured resistance
  auto it = std::upper_bound(rtdTable, rtdTable + rtdTableSize, measured_resistance,
                             [](float a, const RtdValue &b)
                             { return a < b.resistance; }); // a is measured_resistance, b is the RtdValue

  if (it == rtdTable + rtdTableSize) // If the measured resistance is greater than the last element in the table
  {
    return rtdTable[rtdTableSize - 1].temperature; // return the temperature of the last element in the table
  }

  if (it == rtdTable) // If the measured resistance is smaller than the first element in the table
  {
    return rtdTable[0].temperature; // return the temperature of the first element in the table
  }

  RtdValue upper = *it;     // upper is the first element in the table that is greater than the measured resistance
  RtdValue lower = *(--it); // lower is the element before upper

  return lower.temperature + (upper.temperature - lower.temperature) *
                                 (measured_resistance - lower.resistance) / (upper.resistance - lower.resistance); // Linear interpolation between lower and upper element in the table
}

// Setup function
void setup()
{
  pinMode(analogPin, INPUT); // Set analog pin as input
  Serial.begin(9600);        // Start serial communication
}

// Loop function
void loop()
{
  int adcValue = analogRead(analogPin);                                     // Read analog value from analog pin
  float voltage = (adcValue / adcMaxValue) * referenceVoltage;              // Calculate voltage from analog value  (adcValue / adcMaxValue) is the ratio between the measured value and the maximum value,  referenceVoltage is the maximum value
  float resistance = seriesResistor / ((referenceVoltage / voltage) - 1.0); // Calculate resistance from voltage  (referenceVoltage / voltage) is the ratio between the maximum value and the measured value,  seriesResistor is the maximum value

  sumOfSamples += resistance;              // Add resistance to the sum of resistance samples  (sumOfSamples is the sum of the last sampleSize resistance samples)
  resistanceSamples.push_back(resistance); // Add resistance to the queue of resistance samples  (resistanceSamples is the queue of the last sampleSize resistance samples)

  if (resistanceSamples.size() > sampleSize) // If the queue of resistance samples has more than sampleSize elements
  {
    sumOfSamples -= resistanceSamples.front(); // Remove the first element from the queue of resistance samples from the sum of resistance samples
    resistanceSamples.pop_front();             // Remove the first element from the queue of resistance samples
  }

  float movingAverage = 0;        // Moving average of the last sampleSize resistance samples
  if (!resistanceSamples.empty()) // If the queue of resistance samples is not empty
  {
    movingAverage = sumOfSamples / (float)resistanceSamples.size(); // Calculate the moving average of the last sampleSize resistance samples
  }

  float temperature = interpolateTemperature(movingAverage);                                     // Calculate the temperature from the moving average resistance
  Serial.printlnf("Moving Average Resistance: %f, Temperature: %f", movingAverage, temperature); // Print the moving average resistance and the temperature

  // Publish the temperature value
  Particle.publish("temperature", String(temperature), PRIVATE);

  // Wait for a time interval before the next read/publish
  // delay(3600000); // 1 hour = 3600000 ms
  delay(20000); // 20 seconds = 20000 ms
}

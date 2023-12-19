// CollectData.cpp
#include "CollectData.h"
#include "Common.h"

std::deque<LogData> logData;

void collectData(LogData *data) // Function to collect data for logging
{
    if (data != NULL)
    {
        logData.push_back(*data);
        Log.info("Added data to log: timestamp: %ld, temperature: %.2f, valveOutput: %.2f",
                 data->timestamp, data->temperature, data->valveOutput);

        while (logData.size() > LOGGED_DATA_SIZE)
        {
            logData.pop_front();
        }
    }
    else
    {
        Log.warn("No data added to log");
    }
}

// Function to encode the data to JSON and send it to Particle cloud
// Format is the following:
// {"node":"iot10","deviceId":"{{{PARTICLE_DEVICE_ID}}}",
// "data":[{"timestamp":{{timestamp1}},"temperature":{{temperature1}},"valveOutput":{{valveOutput1}}},
// {"timestamp":{{timestamp2}},"temperature":{{temperature2}},"valveOutput":{{valveOutput2}}},
// {"timestamp":{{timestamp3}},"temperature":{{temperature3}},"valveOutput":{{valveOutput3}}}]}
void sendCollectData()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    JSONBufferWriter writer(buffer, sizeof(buffer));

    writer.beginObject(); // Start of the JSON object

    writer.name("node").value("iot10"); // Name of the node. Hardcoded, as there is no function to get it from the device
    writer.name("deviceId").value(System.deviceID().c_str());

    writer.name("data").beginArray(); // Start of the array containing the data samples, as JSON objects

    for (size_t i = 0; i < logData.size(); i++)
    {
        writer.beginObject();
        writer.name("timestamp").value(logData[i].timestamp);
        char tempStr[32];
        snprintf(tempStr, sizeof(tempStr), "%.2f", logData[i].temperature);
        writer.name("temperature").value(tempStr);
        snprintf(tempStr, sizeof(tempStr), "%.2f", logData[i].valveOutput);
        writer.name("valveOutput").value(tempStr);
        writer.endObject();
    }

    writer.endArray(); // End of the array

    writer.endObject(); // End of the JSON object

    publishCollectedData(buffer);
}

// Function to publish data to Particle cloud (https://docs.particle.io/reference/device-os/firmware/photon/#particle-publish-)
void publishCollectedData(const char *eventData)
{
    if (Particle.connected())
    {
        Log.trace("Event (%s) data sent: %s", COLLECTED_DATA_EVENT_NAME, eventData);
        Particle.publish(COLLECTED_DATA_EVENT_NAME, eventData, PRIVATE);
    }
}

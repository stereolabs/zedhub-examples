#include <stdio.h>
#include <string.h>
#include <chrono>

#include <sl_iot/IoTCloud.hpp>
#include <csignal>
#include <ctime>

using namespace std;
using namespace sl;
using namespace sl_iot;
using json = sl_iot::json;


void onDataReceived(std::string topic, std::string message, TARGET target, void* arg)
{
    std::cout << "Message received !" << std::endl;
    json my_raw_data = json::parse(message);
    std::cout << "My received message : " << my_raw_data << std::endl;
    IoTCloud::log("MQTT message received on topic " + topic,LOG_LEVEL::INFO); 
}


int main(int argc, char **argv) {

    STATUS_CODE status_iot;
    status_iot = IoTCloud::init("basic_app");
    if (status_iot != STATUS_CODE::SUCCESS) {
        std::cout << "Initiliazation error " << status_iot << std::endl;
        exit(EXIT_FAILURE);
    }

    // Topic to be listen
    TARGET topic_prefix = TARGET::LOCAL_NETWORK;
    std::string topic_name = "/my_custom_data";

    //
    IoTCloud::subscribeToMqttTopic(topic_name, onDataReceived, topic_prefix);

    // Main loop
    while (true) {

        sleep_ms(1000);
    }

    return 0;
}
  
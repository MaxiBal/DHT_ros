#include <ros/ros.h>


#include "sensor_msgs/Temperature.h"
#include "sensor_msgs/RelativeHumidity.h"

#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

using namespace DHT;

DHT dht(DHTPIN, DHTTYPE);
dht.begin();


/**
 * Defines the output of the DHT sensor
 * 
 * @paramref temp temperature with +/- 2deg C error
 * @paramref humidity percent humidity
 */
struct DHT_Output
{
    float temp;
    float humidity;
};

DHT_Output get_reading()
{
    return {
        dht.readTemperature(),
        dht.readHumidity()
    };
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "temperature_node");

    ros::NodeHandle nh;

    ros::Publisher  temp_publisher = nh.advertise<sensor_msgs::Temperature>("temperature", 100),
                    humidity_publisher = nh.advertise<sensor_msgs::RelativeHumidity>("humidity", 100);


    ros::Rate loop_rate(10);

    float temp, humidity;

    while (ros::ok())
    {
        const auto [temp, humidity] = get_reading();

        sensor_msgs::Temperature temp_msg;

        temp_msg.temperature = temp;
        temp_msg.variance = 0;


        sensor_msgs::RelativeHumidity humidity_msg;

        humidity_msg.relative_humidity = humidity;
        humidity_msg.variance = 0;

        // send both messages

        temp_publisher.publish(temp_msg);
        humidity_publisher.publish(humidity_msg);

        loop_rate.sleep();
    }

    ros::spin();

    return 0;

}

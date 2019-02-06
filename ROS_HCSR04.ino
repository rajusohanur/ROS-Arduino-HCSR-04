/*
 * rosserial Publisher Example
 * edited by Md. Sohanur E Hijrat Raju
 * Prints Sonar Sensor data (HCSR-04)
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <NewPing.h>

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


ros::NodeHandle  nh;

char distance[10];

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);


void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{ 
  String dist_data_One =  String(sonar.ping_cm(), DEC); //convert sonar integer data to string
  String dist_data_Two = String(dist_data_One + "cm");  //adding cm unit to show
  dist_data_Two.toCharArray(distance, 10);        //converting string to character
  str_msg.data = distance;
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}


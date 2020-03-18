#include <ros/ros.h>
/**
#include <sensor_msgs/LaserScan.h>
#include <string>
**/
#include "husky_highlevel_controller/HuskyHighLevelController.h"

class Scanner {
public:
    void callback(const sensor_msgs::LaserScan::ConstPtr& msg){
/*
    ROS_INFO_STREAM("I heard: seq = [%i], time = [%i, %i], frame_id = [%s]",
        msg->seq, msg->stamp.sec, msg->stamp.nsec, msg->frame_id.c_str());
*/
    ROS_INFO_STREAM("Smallest distance measurement:" << msg->range_min);
    }

};

int main(int argc, char** argv){
    ros::init(argc, argv, "husky_highlevel_controller");
    ros::NodeHandle nh("~");
/**    ROS_INFO_STREAM("node handle namespace:" << nh.getNamespace());

    std::string topic_name;
    int queue_size;
    nh.getParam("topic_name", topic_name);
    nh.getParam("queue_size", queue_size);
//    ROS_INFO_STREAM("topic_name:" << topic_name);


    Scanner scanner;
    ros::Subscriber subscriber =
        nh.subscribe(topic_name, queue_size, &Scanner::callback, &scanner);
**/

    husky_highlevel_controller::HuskyHighlevelController huskyControl(nh);

    ros::spin();
    return 0;
}


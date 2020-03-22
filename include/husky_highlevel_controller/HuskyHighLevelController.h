#ifndef HUSKY_HIGHLEVEL_CONTROLLER_
#define HUSKY_HIGHLEVEL_CONTROLLER_

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <string>
#include "husky_highlevel_controller/HuskyHighLevelController.h"

namespace husky_highlevel_controller {

// Class containing the Husky Highlevel Controller
class HuskyHighlevelController{
public:
    HuskyHighlevelController(ros::NodeHandle& nodeHandle);
    virtual ~HuskyHighlevelController();

private:
    void readParameters_();
    void callback_(const sensor_msgs::LaserScan::ConstPtr& msg);
    void stop_();
    void forward_();

    ros::NodeHandle nh_;
    ros::Subscriber subscriber_;
    ros::Publisher publisher_;
    geometry_msgs::Twist twist_;
    std::string topic_name_;
    int queue_size_;
};

}

#endif

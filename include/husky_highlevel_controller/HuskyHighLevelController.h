#ifndef HUSKY_HIGHLEVEL_CONTROLLER_H_
#define HUSKY_HIGHLEVEL_CONTROLLER_H_

#include <string>
#include <cmath>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <husky_highlevel_controller/HuskyObject.h>

#include "husky_highlevel_controller/HuskyHighLevelController.h"
#include "husky_highlevel_controller/MarkerPublisher.h"

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
    std::string topic_name_;
    int queue_size_;

    ros::Publisher twist_publisher_;
    geometry_msgs::Twist twist_;
    MarkerPublisher marker_publisher_;
    float speed_;
    float yaw_;
    float yaw_p_;

    husky_highlevel_controller::HuskyObject husky_object_;
};

}

#endif  // #define HUSKY_HIGHLEVEL_CONTROLLER_H_

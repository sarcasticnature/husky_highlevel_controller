#include "husky_highlevel_controller/HuskyHighLevelController.h"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle)
    : nh_(nodeHandle){
    readParameters_();
    subscriber_ = nh_.subscribe("/scan", 1,
        &HuskyHighlevelController::callback_, this);
    if(subscriber_) ROS_INFO_STREAM("subscriber created, topic is: " << 
        subscriber_.getTopic());
    publisher_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    speed_ = 1;
    yaw_ = 0;
    stop_();
}

HuskyHighlevelController::~HuskyHighlevelController() {}

void HuskyHighlevelController::readParameters_(){
//    ROS_INFO_STREAM("node handle namespace:" << nh_.getNamespace());
    nh_.getParam("topic_name", topic_name_);
    nh_.getParam("queue_size", queue_size_);
    nh_.getParam("speed", speed_);
    nh_.getParam("yaw_p", yaw_p_);
}

void HuskyHighlevelController::callback_(const sensor_msgs::LaserScan::ConstPtr& msg){
    int index = 0;
    float min = msg->range_max;
    float pi = 3.1415926535897;
    for(int n=0; n < msg->ranges.size(); n++){
        if(msg->ranges[n] < min){
            index = n;
            min = msg->ranges[n];
        }
    }
    yaw_ = msg->angle_min + index * msg->angle_increment;
    ROS_INFO_STREAM("Error: " << yaw_ * 180 / pi << " deg");
    ROS_INFO_STREAM("Distance to object: " << min);
    yaw_ *= -yaw_p_;
    forward_();
}

void HuskyHighlevelController::stop_(){
    twist_.linear.x = 0;
    twist_.linear.y = 0;
    twist_.linear.z = 0;
    twist_.angular.x = 0;
    twist_.angular.y = 0;
    twist_.angular.z = 0;
    publisher_.publish(twist_);
}

void HuskyHighlevelController::forward_(){
    twist_.linear.x = speed_;
    twist_.linear.y = 0;
    twist_.linear.z = 0;
    twist_.angular.x = 0;
    twist_.angular.y = 0;
    twist_.angular.z = yaw_;
    publisher_.publish(twist_);
}

}


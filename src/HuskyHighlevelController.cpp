#include "husky_highlevel_controller/HuskyHighLevelController.h"

namespace husky_highlevel_controller {
using husky_highlevel_controller::HuskyObject;

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle)
    : nh_(nodeHandle), marker_publisher_(nodeHandle){
    readParameters_();
    subscriber_ = nh_.subscribe("/scan", 1,
                                &HuskyHighlevelController::callback_, this);
    if(subscriber_) ROS_INFO_STREAM("subscriber created, topic is: " << 
                                    subscriber_.getTopic());
    twist_publisher_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    speed_ = 1;
    yaw_ = 0;
    stop_();
    husky_object_.distance = 0;
    husky_object_.angle = 0;
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
    for (int n=0; n < msg->ranges.size(); n++){
        if (msg->ranges[n] < min){
            index = n;
            min = msg->ranges[n];
        }
    }
    husky_object_.distance = min;
    husky_object_.angle = msg->angle_min + index * msg->angle_increment;
    if (husky_object_.distance < msg->range_max) {
        marker_publisher_.publish(husky_object_);
    }
    else marker_publisher_.clearObject();
    
    ROS_INFO_STREAM("Error: " << husky_object_.angle * 180 / pi << " deg");
    ROS_INFO_STREAM("Distance to object: " << husky_object_.distance);
    yaw_ = -yaw_p_ * husky_object_.angle;
    forward_();
}

void HuskyHighlevelController::stop_(){
    twist_.linear.x = 0;
    twist_.linear.y = 0;
    twist_.linear.z = 0;
    twist_.angular.x = 0;
    twist_.angular.y = 0;
    twist_.angular.z = 0;
    twist_publisher_.publish(twist_);
}

void HuskyHighlevelController::forward_(){
    twist_.linear.x = speed_;
    twist_.linear.y = 0;
    twist_.linear.z = 0;
    twist_.angular.x = 0;
    twist_.angular.y = 0;
    twist_.angular.z = yaw_;
    twist_publisher_.publish(twist_);
}

}


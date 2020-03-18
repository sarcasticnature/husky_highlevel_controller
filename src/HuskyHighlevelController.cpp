#include "husky_highlevel_controller/HuskyHighLevelController.h"

namespace husky_highlevel_controller {

HuskyHighlevelController::HuskyHighlevelController(ros::NodeHandle& nodeHandle)
    : nh_(nodeHandle){
    readParameters_();
//    ros::Subscriber subscriber = nh_.subscribe(topic_name_, queue_size_,
//        &HuskyHighlevelController::callback_, this);
    subscriber_ = nh_.subscribe("/scan", 1,
        &HuskyHighlevelController::callback_, this);
    if(subscriber_) ROS_INFO_STREAM("subscriber created, topic is: " << 
        subscriber_.getTopic());
}

HuskyHighlevelController::~HuskyHighlevelController() {}

void HuskyHighlevelController::readParameters_(){
    ROS_INFO_STREAM("node handle namespace:" << nh_.getNamespace());
    nh_.getParam("topic_name", topic_name_);
    ROS_INFO_STREAM("topic_name: " << topic_name_);
    nh_.getParam("queue_size", queue_size_);
    ROS_INFO_STREAM("queue_size: " << queue_size_);
}

void HuskyHighlevelController::callback_(const sensor_msgs::LaserScan::ConstPtr& msg){
    ROS_DEBUG_STREAM("hit tutorial callback function");
    ROS_INFO_STREAM("Smallest distance measurement:" << msg->range_min);
}

}


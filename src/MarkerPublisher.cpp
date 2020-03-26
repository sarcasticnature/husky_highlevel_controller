#include "husky_highlevel_controller/MarkerPublisher.h"

namespace husky_highlevel_controller {

using husky_highlevel_controller::HuskyObject;

MarkerPublisher::MarkerPublisher(ros::NodeHandle& nodehandle) : nh_(nodehandle){
    publisher_ = nh_.advertise<visualization_msgs::Marker>("object_marker", 1);
    initObject();
}


void MarkerPublisher::initObject(){
    marker_.header.frame_id = "/base_laser";
    marker_.header.stamp = ros::Time::now();
    marker_.ns = "husky_object";
    marker_.id = 0;
    marker_.type = visualization_msgs::Marker::CYLINDER;
    marker_.action = visualization_msgs::Marker::DELETE;
    marker_.pose.position.x = 0;
    marker_.pose.position.y = 0;
    marker_.pose.position.z = 0;
    marker_.pose.orientation.x = 0;
    marker_.pose.orientation.y = 0;
    marker_.pose.orientation.z = 0;
    marker_.pose.orientation.w = 1;
    marker_.scale.x = 1.0;
    marker_.scale.y = 1.0;
    marker_.scale.z = 1.0;
    marker_.color.r = 1.0;
    marker_.color.g = 0.0;
    marker_.color.b = 0.0;
    marker_.color.a = 1.0;
    marker_.lifetime = ros::Duration();
}


void MarkerPublisher::publish(HuskyObject object){
    setLocation(object);
    marker_.action = visualization_msgs::Marker::ADD;
    publisher_.publish(marker_);
}


void MarkerPublisher::clearObject(){
    marker_.action = visualization_msgs::Marker::DELETE;
    publisher_.publish(marker_);
}


void MarkerPublisher::setLocation(HuskyObject object){
    marker_.pose.position.x = cos(object.angle) * object.distance;
    marker_.pose.position.y = sin(object.angle) * object.distance;
}


}


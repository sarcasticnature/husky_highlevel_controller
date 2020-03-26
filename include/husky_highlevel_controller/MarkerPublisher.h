#ifndef MARKER_PUBLISHER_H_
#define MARKER_PUBLISHER_H_

#include <cmath>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <husky_highlevel_controller/HuskyObject.h>
namespace husky_highlevel_controller{

class MarkerPublisher {
public:
//    MarkerPublisher() {}
    MarkerPublisher(ros::NodeHandle& nodehandle);
    void initObject();
    void publish(HuskyObject object);
    void clearObject();

private:
    void setLocation(husky_highlevel_controller::HuskyObject);

    ros::NodeHandle nh_;
    ros::Publisher publisher_;
    visualization_msgs::Marker marker_;
};

}

#endif  // #define MARKER_TRANSFORMER_H_


#include <ros/ros.h>
#include <ros_autorunner/ros_autorunner.h>

// Include subscribe message type
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int32.h>

#define TOTAL_STEP_NUM 2 // Need to change when total step number is changed

class LaneKeepingAutorunner : public AutorunnerBase{
private:    
    ros::NodeHandle     nh_;
    ROSAutorunner        ros_autorunner_;
private:
    virtual void register_subscribers();
private:
    // CALLBACKS FOR CHECK
public:
    Sub_v               sub_v_;
public:
    LaneKeepingAutorunner() {}
    LaneKeepingAutorunner(ros::NodeHandle nh) : nh_(nh){}
    virtual void Run();
};
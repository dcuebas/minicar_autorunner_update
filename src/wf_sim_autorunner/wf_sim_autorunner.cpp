#include <wf_sim_autorunner/wf_sim_autorunner.h>

void WfSimAutorunner::Run(){
    register_subscribers();             // Register subscribers that shoud check can go next or not
    ros_autorunner_.init(nh_, sub_v_);   // Initialize the ROS-Autorunner
    ros::Rate rate(1);                  // Rate can be changed
    while(ros::ok()){               
        ros_autorunner_.Run();           // Run Autorunner
        ros::spinOnce();
        rate.sleep();
    }    
}

void WfSimAutorunner::register_subscribers(){
    sub_v_.resize(TOTAL_STEP_NUM);          // Resizing the subscriber vectors. Its size must be same with number of steps

    // Set the check function(subscriber)
    //sub_v_[STEP(1)] 
    sub_v_[STEP(2)] = nh_.subscribe("/lane_waypoints_array", 1, &WfSimAutorunner::lane_waypoints_array_cb, this);
    sub_v_[STEP(3)] = nh_.subscribe("/local_trajectories", 1, &WfSimAutorunner::local_trajectories_cb, this);
    //sub_v_[STEP(4)]
    sub_v_[STEP(5)] = nh_.subscribe("/behavior_state", 1, &WfSimAutorunner::behavior_state_cb, this);
    //sub_v_[STEP(6)] 
}

void WfSimAutorunner::lane_waypoints_array_cb(const autoware_msgs::LaneArray& msg){
    if(!msg.lanes.empty()){
        ROS_WARN("STEP2 DONE");
        ros_autorunner_.step_info_list_[STEP(3)].is_prepared = true;
    }
}

void WfSimAutorunner::local_trajectories_cb(const autoware_msgs::LaneArray& msg){
    if(!msg.lanes.empty()){
        ROS_WARN("STEP3 DONE");
        ros_autorunner_.step_info_list_[STEP(4)].is_prepared = true;
    }
}

void WfSimAutorunner::behavior_state_cb(const visualization_msgs::MarkerArray& msg){
    ROS_WARN("text %s", msg.markers.front().text.c_str());
    if(!msg.markers.empty() && msg.markers.front().text == std::string("(0)Forward")){
        ROS_WARN("STEP5 DONE");
        ros_autorunner_.step_info_list_[STEP(6)].is_prepared = true;
    }
}


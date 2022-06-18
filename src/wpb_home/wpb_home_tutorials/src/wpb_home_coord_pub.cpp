#include <algorithm>
#include <vector>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <wpb_home_behaviors/Coord.h>
#include <tf/transform_listener.h>
#include <std_msgs/Bool.h>
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h" 
//#include <wpb_home_tutorials/Face_ctrl.h>
using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static ros::Publisher face1_pub;
static ros::Publisher face2_pub;


int main(int argc, char** argv){
  ros::init(argc, argv, "wpb_home_coord_pub");

  ros::NodeHandle nh;
  // ros::Subscriber msg_sub = nh.subscribe(point_topic, 1, callbackJUDGE);
  face1_pub = nh.advertise<move_base_msgs::MoveBaseGoal>("/person/waypoint1",10 );
  face2_pub = nh.advertise<move_base_msgs::MoveBaseGoal>("/person/waypoint2",10);
//   // msg_pub = nh.advertise<string>("face_pointcloud",1);
  move_base_msgs::MoveBaseGoal goal1;
    ROS_WARN("finish build");
    move_base_msgs::MoveBaseGoal goal2;

    goal1.target_pose.header.frame_id = "map";
    goal1.target_pose.header.stamp = ros::Time::now();
    ROS_WARN("666");
    goal1.target_pose.pose.position.x = 0;
    goal1.target_pose.pose.position.y = 0;
    goal1.target_pose.pose.orientation.w = 1.0;
    goal2.target_pose.header.frame_id = "map";
    goal2.target_pose.header.stamp = ros::Time::now();
    ROS_WARN("666");
    goal2.target_pose.pose.position.x = 1;
    goal2.target_pose.pose.position.y = 0;
    goal2.target_pose.pose.orientation.w = 1.0;
  ros::Rate loop_rate(10);
    while( ros::ok())
    {
    //     ROS_INFO("Waiting !!!!");
    face1_pub.publish(goal1);
    face2_pub.publish(goal2);
        loop_rate.sleep();
    }

  return 0;
}
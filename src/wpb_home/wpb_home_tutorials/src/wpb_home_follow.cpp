/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/*!******************************************************************
 @author     ZhangWanjie
 ********************************************************************/
#define CV_IMWRITE_PNG_COMPRESSION cv::IMWRITE_PNG_COMPRESSION
#define CV_IMWRITE_JPEG_QUALITY cv::IMWRITE_JPEG_QUALITY
#define CV_IMWRITE_PNG_STRATEGY cv::IMWRITE_PNG_STRATEGY
#define CV_IMWRITE_PNG_STRATEGY_RLE cv::IMWRITE_PNG_STRATEGY_RLE
#define CV_BGRA2BGR cv::COLOR_BGRA2BGR
#define CV_RGBA2BGR cv::COLOR_RGBA2BGR
#define CV_AA LINE_AA

#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/LaserScan.h>
#include <pcl_conversions/pcl_conversions.h>
#include <geometry_msgs/PointStamped.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include "kl_outlier.h"
#include "wpb_home_tutorials/Follow.h"
#include <wpb_home_behaviors/Coord.h>

static ros::Publisher vel_pub;
static tf::TransformListener *tf_listener;
static bool bActive = false;
static float keep_dist = 0.5; //跟随距离
static float flw_x = keep_dist;
static float flw_y = 0;
static float human_x = 0;
static float human_y = 0;
static float human_z = 0;
static float max_linear_vel = 0.5;
static float max_angular_vel = 1.5;
static float linear_rate = 0.4;
static float angular_rate = 0.5;


void ProcHuman_pose(const wpb_home_behaviors::Coord::ConstPtr &msg)
{
    if(bActive == false) return;

    //ROS_WARN("ProcHuman_pose");
    human_x = (msg->x)[0];
    human_y = (msg->y)[0];
    human_z = (msg->z)[0];
    float angle = -tanh(human_x/human_z);

    geometry_msgs::Twist vel_cmd;

    float flw_dist = sqrt(human_x*human_x+human_z*human_z);

    float diff_dist = flw_dist - keep_dist;
    float flw_linear = diff_dist * linear_rate;
    if (fabs(diff_dist) > 0.05)
    {
        vel_cmd.linear.x = flw_linear;
        if (vel_cmd.linear.x > max_linear_vel)
            vel_cmd.linear.x = max_linear_vel;
        if (vel_cmd.linear.x < -max_linear_vel)
            vel_cmd.linear.x = -max_linear_vel;
        if (vel_cmd.linear.x < 0)
            vel_cmd.linear.x *= 0.5;
    }
    else
    {
        vel_cmd.linear.x = 0;
    }
    ROS_INFO("human_x:%f, human_y:%f, human_z:%f, angle:%f, diff_dist:%f", human_x, human_y, human_z, angle, diff_dist);
    float flw_turn = angle * angular_rate;
    if (fabs(angle) > 0.05)
    {
        vel_cmd.angular.z = flw_turn;
        if (vel_cmd.angular.z > max_angular_vel)
            vel_cmd.angular.z = max_angular_vel;
        if (vel_cmd.angular.z < -max_angular_vel)
            vel_cmd.angular.z = -max_angular_vel;
    }
    else
    {
        vel_cmd.angular.z = 0;
    }
    vel_pub.publish(vel_cmd);
}

bool follow_start(wpb_home_tutorials::Follow::Request &req, wpb_home_tutorials::Follow::Response &res)
{
    float fThredhold = (float)req.thredhold;
    flw_x = fThredhold;
    flw_y = 0;
    keep_dist = flw_x;
    thredhold(flw_x);
    bActive = true;
    ROS_WARN("[follow_start] thredhold = %.2f", fThredhold);
    return true;
}

bool follow_stop(wpb_home_tutorials::Follow::Request &req, wpb_home_tutorials::Follow::Response &res)
{
    float fThredhold = (float)req.thredhold;
    ROS_WARN("[follow_stop] thredhold = %.2f", fThredhold);
    bActive = false;
    geometry_msgs::Twist vel_cmd;
    vel_cmd.linear.x = 0;
    vel_cmd.linear.y = 0;
    vel_cmd.linear.z = 0;
    vel_cmd.angular.x = 0;
    vel_cmd.angular.y = 0;
    vel_cmd.angular.z = 0;
    vel_pub.publish(vel_cmd);
    return true;
}

bool follow_resume(wpb_home_tutorials::Follow::Request &req, wpb_home_tutorials::Follow::Response &res)
{
    float fThredhold = (float)req.thredhold;
    ROS_WARN("[follow_resume] thredhold = %.2f", fThredhold);
    bActive = true;
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "wpb_home_follow");
    ROS_WARN("[wpb_home_follow]");
    flw_x = keep_dist;
    flw_y = 0;
    thredhold(flw_x);
    tf_listener = new tf::TransformListener();

    ros::NodeHandle nh_param("~");
    nh_param.param<bool>("start", bActive, false);

    ros::NodeHandle nh;
    ros::Subscriber pose_sub = nh.subscribe<wpb_home_behaviors::Coord>("/Human_pose", 1, ProcHuman_pose);

    ros::ServiceServer start_svr = nh.advertiseService("wpb_home_follow/start", follow_start);
    ros::ServiceServer stop_svr = nh.advertiseService("wpb_home_follow/stop", follow_stop);
    ros::ServiceServer resume_svr = nh.advertiseService("wpb_home_follow/resume", follow_resume);

    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin();

    delete tf_listener;

    return 0;
}
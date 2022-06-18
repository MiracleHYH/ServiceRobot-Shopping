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
/* @author Zhang Wanjie                                             */
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include "wpb_home_tutorials/Follow.h"
#include <geometry_msgs/Twist.h>
#include "xfyun_waterplus/IATSwitch.h"
#include <sound_play/SoundRequest.h>
#include "wpb_home_tutorials/Follow.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <waterplus_map_tools/Waypoint.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <sentence_voice/Sentence.h>
#include <geometry_msgs/PointStamped.h>
#include <std_srvs/SetBool.h>

#include <map>
#include <vector>
#include <string>

using namespace std;

#define STATE_READY     0
#define STATE_FOLLOW    1
#define STATE_ASK       2
#define STATE_GOTO      3
#define STATE_GRAB      4
#define STATE_COMEBACK  5
#define STATE_PASS      6
#define STATE_FIND_1    7//找第一个志愿者
#define STATE_FIND_2	8//找第二个志愿者
#define STATE_LEAVE     9//离开
int finishedTask = 0;//增加已完成任务数
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static string strGoto;
static sentence_voice::Sentence spk_msg;
static ros::Publisher status_pub;//给人脸检测节点，发送运行信息
static ros::Publisher spk_pub;
static ros::Publisher vel_pub;
static string strToSpeak = "";
static string strKeyWord = "";
static ros::ServiceClient clientIAT;
static xfyun_waterplus::IATSwitch srvIAT;
static ros::ServiceClient cliGetWPName;
static waterplus_map_tools::GetWaypointByName srvName;
static ros::Publisher add_waypoint_pub;
static ros::ServiceClient follow_start;
static ros::ServiceClient follow_stop;
static ros::ServiceClient follow_resume;
static wpb_home_tutorials::Follow srvFlw;
static ros::Publisher behaviors_pub;
static std_msgs::String behavior_msg;

static ros::Subscriber grab_result_sub;
static ros::Subscriber pass_result_sub;
static bool bGrabDone;
static bool bPassDone;

static int nState = STATE_READY;
static int nDelay = 0;

static vector<string> arKeyword; //航点关键词
static vector<string> arObjectWant;//需要的物品

bool Getperson1 = false, Getperson2 = false;
static int nIndexWant = 0;
static map<string, bool> is_record; //记录航点是否已经被记录
static map<string, bool> is_goto; //记录航点是否已经被记录
static map<string, vector<string>> keywordReflaction;

static ros::ServiceClient find_client;

// 添加航点关键词
void InitKeyword()
{
    arKeyword.push_back("start");   //机器人开始启动的地点,最后要回去
    //共有四个地点
    arKeyword.push_back("Oreo");
    arKeyword.push_back("Potatowish");
    arKeyword.push_back("Lays");
    arKeyword.push_back("Cookie");
    arKeyword.push_back("Sprite");
    arKeyword.push_back("Cola");
    arKeyword.push_back("Orange juice");
    arKeyword.push_back("Water");
    arKeyword.push_back("Milk");
    arKeyword.push_back("Handwash");
    arKeyword.push_back("Dishsoap");
    arKeyword.push_back("Shampoo");

    is_record["Oreo"] = false;
    is_record["Potatowish"] = false;
    is_record["Lays"] = false;
    is_record["Cookie"] = false;
    is_record["Sprite"] = false;
    is_record["Cola"] = false;
    is_record["Orange juice"] = false;
    is_record["Water"] = false;
    is_record["Milk"] = false;
    is_record["Handwash"] = false;
    is_record["Dishsoap"] = false;
    is_record["Shampoo"] = false;


    is_goto["Oreo"] = false;
    is_goto["Potatowish"] = false;
    is_goto["Lays"] = false;
    is_goto["Cookie"] = false;
    is_goto["Sprite"] = false;
    is_goto["Cola"] = false;
    is_goto["Orange juice"] = false;
    is_goto["Water"] = false;
    is_goto["Milk"] = false;
    is_goto["Handwash"] = false;
    is_goto["Dishsoap"] = false;
    is_goto["Shampoo"] = false;

    keywordReflaction["Oreo"] = vector<string>({"oreo", "all real", "real"});
    keywordReflaction["Potatowish"] = vector<string>({"potatowish", "potato wish", "potato", "wish"});
    keywordReflaction["Lays"] = vector<string>({"lays", "layz", "lazy", "nice", "less", "legs"});
    keywordReflaction["Cookie"] = vector<string>({"cookie", "cook"});
    keywordReflaction["Sprite"] = vector<string>({"sprite", "spirit"});
    keywordReflaction["Cola"] = vector<string>({"cola", "color", "cole", "kola"});
    keywordReflaction["Orange juice"] = vector<string>({"orangejuice", "orange juice", "orange", "juice"});
    keywordReflaction["Water"] = vector<string>({"water"});
    keywordReflaction["Milk"] = vector<string>({"milk"});
    keywordReflaction["Handwash"] = vector<string>({"handwash", "hand wash", "hand", "wash"});
    keywordReflaction["Dishsoap"] = vector<string>({"dishsoap", "dish soap", "dish", "soap"});
    keywordReflaction["Shampoo"] = vector<string>({"shampoo", "shamp"});
}

// 从句子里找arKeyword里存在的关键词
static string FindKeyword(string inSentence)
{
    if(inSentence.length() == 0) return string("");
    int nSize = arKeyword.size(), mSize;
    transform(inSentence.begin(), inSentence.end(), inSentence.begin(), ::tolower);
    for(int i = 0; i < nSize; ++ i){
        mSize = keywordReflaction[arKeyword[i]].size();
        for(int j = 0; j < mSize; ++ j){
            int nFindIndex = inSentence.find(keywordReflaction[arKeyword[i]][j]);
            if(nFindIndex >= 0){
                // ROS_WARN("Find Keyword:%s", arKeyword[i].c_str());
                return arKeyword[i];
            }
        }
    }
    return string("");
}

// 从句子里找多个arKeyword关键词
static string FindMultiKeyword(string inSentence)
{
    arObjectWant.clear();
    string res = "";
    int nSize = arKeyword.size();
    for(int i=0;i<nSize;i++)
    {
        int nFindIndex = inSentence.find(arKeyword[i]);
        if(nFindIndex >= 0)
        {
            arObjectWant.push_back(arKeyword[i]);
        }
    }
    int nNumObject = arObjectWant.size();
    for(int i=0;i<nNumObject;i++)
    {
        res += arObjectWant[i];
        res += " , ";
    }
    return res;
}

// 将机器人当前位置保存为新航点
void AddNewWaypoint(string inStr)
{
    tf::TransformListener listener;
    tf::StampedTransform transform;
    try
    {
        listener.waitForTransform("/map","/base_footprint",  ros::Time(0), ros::Duration(10.0) );
        listener.lookupTransform("/map","/base_footprint", ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) 
    {
        ROS_ERROR("[lookupTransform] %s",ex.what());
        return;
    }

    float tx = transform.getOrigin().x();
    float ty = transform.getOrigin().y();
    tf::Stamped<tf::Pose> p = tf::Stamped<tf::Pose>(tf::Pose(transform.getRotation() , tf::Point(tx, ty, 0.0)), ros::Time::now(), "map");
    geometry_msgs::PoseStamped new_pos;
    tf::poseStampedTFToMsg(p, new_pos);

    waterplus_map_tools::Waypoint new_waypoint;
    new_waypoint.name = inStr;
    new_waypoint.pose = new_pos.pose;
    add_waypoint_pub.publish(new_waypoint);

    ROS_WARN("[New Waypoint] %s ( %.2f , %.2f )" , new_waypoint.name.c_str(), tx, ty);
}

// 语音说话
void Speak(string inStr)
{
    //spk_msg.arg = inStr;
    //spk_msg.volume = 1.0f;  //indigo(Ubuntu 14.04)需要注释掉这一句才能编译
    spk_msg.sentence = inStr;
    spk_msg.header.stamp.sec = 10;
    spk_pub.publish(spk_msg);
    ros::spinOnce();
}

// 跟随模式开关
static void FollowSwitch(bool inActive, float inDist)
{
    if(inActive == true)
    {
        srvFlw.request.thredhold = inDist;
        if (!follow_start.call(srvFlw))
        {
            ROS_WARN("[CActionManager] - follow start failed...");
        }
    }
    else
    {
        if (!follow_stop.call(srvFlw))
        {
            ROS_WARN("[CActionManager] - failed to stop following...");
        }
    }
}

// 物品抓取模式开关
static void GrabSwitch(bool inActive)
{
    if(inActive == true)
    {
        behavior_msg.data = "grab start";
        behaviors_pub.publish(behavior_msg);
    }
    else
    {
        behavior_msg.data = "grab stop";
        behaviors_pub.publish(behavior_msg);
    }
}

// 物品递给开关
static void PassSwitch(bool inActive)
{
    if(inActive == true)
    {
        behavior_msg.data = "pass start";
        behaviors_pub.publish(behavior_msg);
    }
    else
    {
        behavior_msg.data = "pass stop";
        behaviors_pub.publish(behavior_msg);
    }
}

// 语音识别结果处理函数
void KeywordCB(const std_msgs::String::ConstPtr & msg)
{
    if(msg->data.length() == 0) return;
    if(nState == STATE_FOLLOW)
    {
        // 从识别结果句子中查找物品（航点）关键词
        string strKeyword = FindKeyword(msg->data);
        if(strKeyword.length() > 0 && is_record[strKeyword] == false)
        {
            is_record[strKeyword] = true;
            // 发现物品（航点）关键词
            AddNewWaypoint(strKeyword);
            // ROS_WARN("------ Keyword = %s ------",msg->data.c_str());
            ROS_INFO("[Project Place] Find Keyword:%s", strKeyword.c_str());
            string strSpeak = strKeyword + " . OK. I have memoried. Next one , please"; 
            Speak(strSpeak);
            // ros::Duration(3).sleep();
        }

        // 停止跟随的指令
        int nFindIndex = msg->data.find("Stop follow");
        if(nFindIndex >= 0)
        {
            FollowSwitch(false, 0);
            AddNewWaypoint("master");
            Speak("OK!I have stoped.");
            nState = STATE_FIND_1;
            std_srvs::SetBool srv;
            srv.request.data=true;
            if(find_client.call(srv))
            {
                ;
            }
            else
            {
                ;
            }
            ROS_INFO("Ready to receive person1's waypoint!");
            nDelay = 0;
	        std_msgs::Bool status_msg;
	        status_msg.data = true;
            //ros::Duration(3).sleep();// 人脸检测的等待时间
	        status_pub.publish(status_msg);
            ROS_INFO("Follow stop!");
            //Speak("OK. What do you want me to fetch?");
        }
    }

    if(nState == STATE_ASK)
    {
        // 从识别结果句子中查找物品（航点）关键词
        string strKeyword = FindKeyword(msg->data); // change from FindMultiKeyword
        if(strKeyword.length() > 0 && is_goto[strKeyword] == false)
        {
            is_goto[strKeyword] = true;
            // change
            arObjectWant.clear();
            arObjectWant.push_back(strKeyword);
            //end change

            // 发现物品（航点）关键词
            ROS_INFO("[Consummer Want] Find Keyword:%s", strKeyword.c_str());
            string strSpeak = "OK. I will go to get " + strKeyword + " for you."; 
            Speak(strSpeak);
            sleep(5);   //暂停一会，等机器人把话说完再行动
            nIndexWant = 0;
            nState = STATE_GOTO;
        }
    }
}

// 物品抓取状态
void GrabResultCallback(const std_msgs::String::ConstPtr& res)
{
    int nFindIndex = 0;
    nFindIndex = res->data.find("done");
    if( nFindIndex >= 0 )
    {
        bGrabDone = true;
    }
}

// 物品递给状态
void PassResultCallback(const std_msgs::String::ConstPtr& res)
{
    int nFindIndex = 0;
    nFindIndex = res->data.find("done");
    if( nFindIndex >= 0 )
    {
        bPassDone = true;
    }
}

void FindIt_1(const  move_base_msgs::MoveBaseGoal& goal)
{
    if(nState == STATE_FIND_1)
    {
        // test
        // geometry_msgs::PoseStamped new_pos;
        // waterplus_map_tools::Waypoint new_waypoint;
        // new_waypoint.name = "person1-preview";
        // new_waypoint.frame_id = "map";
        // new_waypoint.pose = goal.target_pose.pose;
        // add_waypoint_pub.publish(new_waypoint);
        // test

        //ROS_WARN("nState OK!");
        MoveBaseClient ac("move_base", true);
        ac.waitForServer();
        //ROS_WARN("serve start");
        ac.sendGoal(goal);
        //ROS_WARN("sent goal");
        ac.waitForResult();
        //ROS_WARN("get result");
        while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ac.waitForServer();
            ac.sendGoal(goal);
            ac.waitForResult();
        }
        ROS_INFO("Arrived at person1");
        nState = STATE_ASK; 
        Speak("OK. What do you want me to fetch?");
        AddNewWaypoint("person1");
        nDelay = 0;
    }
}

void FindIt_2(const  move_base_msgs::MoveBaseGoal& goal)
{
    if(nState == STATE_FIND_2)
    {

        // test
        // geometry_msgs::PoseStamped new_pos;
        // waterplus_map_tools::Waypoint new_waypoint;
        // new_waypoint.name = "person2-preview";
        // new_waypoint.frame_id = "map";
        // new_waypoint.pose = goal.target_pose.pose;
        // add_waypoint_pub.publish(new_waypoint);
        // test

        MoveBaseClient ac("move_base", true);
        ac.waitForServer();
        ac.sendGoal(goal);
        ac.waitForResult();
        while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ac.waitForServer();
            ac.sendGoal(goal);
            ac.waitForResult();
        }
        AddNewWaypoint("person2");
        nState = STATE_ASK;
        ROS_INFO("Arrived at person2!"); 
        Speak("OK. What do you want me to fetch?");
        nDelay = 0;
     }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "wpb_home_shopping");
    ros::NodeHandle n;
    //ros::Subscriber sub_sr = n.subscribe("/xfyun/iat", 10, KeywordCB); //订阅 语音话题，回调函数进行语音识别
    ros::Subscriber sub_sr = n.subscribe("/listen_result", 10, KeywordCB); //订阅 语音话题，回调函数进行语音识别
    ros::Subscriber person_sr_1 = n.subscribe("/person/waypoint1", 10,  FindIt_1);//定阅 志愿者1所在航点
    ros::Subscriber person_sr_2 = n.subscribe("/person/waypoint2", 10,  FindIt_2);//定阅 志愿者2所在航点
    follow_start = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/start");
    follow_stop = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/stop");
    follow_resume = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/resume");
    cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
    add_waypoint_pub = n.advertise<waterplus_map_tools::Waypoint>( "/waterplus/add_waypoint", 1);
    //spk_pub = n.advertise<sound_play::SoundRequest>("/robotsound", 20);
    spk_pub = n.advertise<sentence_voice::Sentence>("/sentence_to_speak", 20);
    status_pub = n.advertise<std_msgs::Bool>("/person/status", 10);//给人脸检测节点，发送运行信息
    //spk_msg.sound = sound_play::SoundRequest::SAY;
    //spk_msg.command = sound_play::SoundRequest::PLAY_ONCE;
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    //clientIAT = n.serviceClient<xfyun_waterplus::IATSwitch>("xfyun_waterplus/IATSwitch");
    behaviors_pub = n.advertise<std_msgs::String>("/wpb_home/behaviors", 30);
    grab_result_sub = n.subscribe<std_msgs::String>("/wpb_home/grab_result",30,&GrabResultCallback);//订阅
    pass_result_sub = n.subscribe<std_msgs::String>("/wpb_home/pass_result",30,&PassResultCallback);//订阅


    find_client = n.serviceClient<std_srvs::SetBool>("human_detection/face_detection_switch");

    InitKeyword();

    ROS_WARN("[main] wpb_home_shopping");
    ros::Rate r(30);
    while(ros::ok())
    {
        // 1、刚启动，准备
        if(nState == STATE_READY)
        {
            // 启动后延迟一段时间然后开始跟随
            nDelay ++;
            // ROS_WARN("[STATE_READY] - nDelay = %d", nDelay);
            if(nDelay > 100)
            {
                AddNewWaypoint("start");
                nDelay = 0;
                nState = STATE_FOLLOW;
            }
        }

        // 2、跟随阶段
        if(nState == STATE_FOLLOW)
        {
            if(nDelay == 0)
            {
               FollowSwitch(true, 0.7);
            }
            nDelay ++;
        }
        //识别志愿者
        if(nState == STATE_FIND_1 || nState == STATE_FIND_2)
        {
            
        }
        // 3、询问要去哪个航点
        if(nState == STATE_ASK)
        {
            
        }

        // 4、导航去指定航点
        if(nState == STATE_GOTO)
        {
            int nNumWant = arObjectWant.size();
            if(nIndexWant < nNumWant)
            {
                strGoto = arObjectWant[nIndexWant];
            }
            srvName.request.name = strGoto;
            if (cliGetWPName.call(srvName))
            {
                std::string name = srvName.response.name;
                float x = srvName.response.pose.position.x;
                float y = srvName.response.pose.position.y;
                ROS_INFO("[STATE_GOTO] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(),x,y);

                MoveBaseClient ac("move_base", true);
                if(!ac.waitForServer(ros::Duration(5.0)))
                {
                    ROS_INFO("The move_base action server is no running. action abort...");
                }
                else
                {
                    move_base_msgs::MoveBaseGoal goal;
                    goal.target_pose.header.frame_id = "map";
                    goal.target_pose.header.stamp = ros::Time::now();
                    goal.target_pose.pose = srvName.response.pose;
                    ac.sendGoal(goal);
                    ac.waitForResult();
                    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                    {
                        ROS_INFO("Arrived at %s!",strGoto.c_str());
                        Speak("OK. I am taking it.");
                        nState = STATE_GRAB;
                        nDelay = 0;
                    }
                    else
                    {
                        ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
                        Speak("Failed to go to the waypoint.");
                        nState = STATE_ASK;
                    }
                }
                
            }
            else
            {
                ROS_ERROR("Failed to call service GetWaypointByName");
                Speak("There is no this waypoint.");
                nState = STATE_ASK;
            }
        }

        // 5、抓取物品
        if(nState == STATE_GRAB)
        {
            if(nDelay == 0)
            {
                sleep(5);
                bGrabDone = false;
                GrabSwitch(true);
            }
            nDelay ++;
            if(bGrabDone == true)
            {
                GrabSwitch(false);
                Speak("I got it. I am coming back.");
                nState = STATE_COMEBACK;
            }
        }

        // 6、抓完物品回来
        if(nState == STATE_COMEBACK)
        {
            if(finishedTask == 0)//获取回来的目标航点
                srvName.request.name = "person1";
            else
                srvName.request.name = "person2";
            if (cliGetWPName.call(srvName))
            {
                std::string name = srvName.response.name;
                float x = srvName.response.pose.position.x;
                float y = srvName.response.pose.position.y;
                ROS_INFO("[STATE_COMEBACK] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(),x,y);

                MoveBaseClient ac("move_base", true);
                if(!ac.waitForServer(ros::Duration(5.0)))
                {
                    ROS_INFO("The move_base action server is no running. action abort...");
                }
                else
                {
                    move_base_msgs::MoveBaseGoal goal;
                    goal.target_pose.header.frame_id = "map";
                    goal.target_pose.header.stamp = ros::Time::now();
                    goal.target_pose.pose = srvName.response.pose;
                    ac.sendGoal(goal);
                    ac.waitForResult();
                    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
                    {
                        ROS_INFO("Arrived at %s!",strGoto.c_str());
                        Speak("Hi,master. This is what you wanted.");
                        nState = STATE_PASS;
                        nDelay = 0;
                    }
                    else
                    {
                        ROS_INFO("Failed to get to %s ...",strGoto.c_str() );
                        Speak("Failed to go to the master.");
                        nState = STATE_ASK;
                    }
                }
                
            }
            else
            {
                ROS_ERROR("Failed to call service GetWaypointByName");
                Speak("There is no waypoint named personx.");
                nState = STATE_ASK;
            }
        }

        // 7、将物品给主人
        if(nState == STATE_PASS)
        {
            if(nDelay == 0)
            {
                bPassDone = false;
                PassSwitch(true);
            }
            nDelay ++;
            if(bPassDone == true)
            {
                ROS_INFO("Passing has been done!");
                sleep(10);
                PassSwitch(false);
                /* nIndexWant ++;
                int nNumWant = arObjectWant.size();
               if(nIndexWant < nNumWant)
                {
                    string strSpeak = "OK. I am going to get the next , "+arObjectWant[nIndexWant];
                    Speak(strSpeak);
                    sleep(3);   //暂停一会，让机器人把话说完
                    nState = STATE_GOTO;
                }
                else
                {
                    Speak("All is done! Do you want something else?");
                    nState = STATE_ASK;
                }*/
                finishedTask++;
                if(finishedTask == 2)
                {
                    nState = STATE_LEAVE;
                }
                else
                {
                    nState = STATE_FIND_2;
                    ROS_INFO("Ready to receive person2's waypoint!");
                }
            }
        }

        //回到收银台
        if(nState == STATE_LEAVE)
        {
            ROS_INFO("leaving");
            MoveBaseClient ac("move_base", true);
            if(!ac.waitForServer(ros::Duration(5.0)))
            {
                ROS_INFO("The move_base action server is no running. action abort...");
            }
            else
            {

                srvName.request.name = "master";
                if (cliGetWPName.call(srvName))
                {
                    move_base_msgs::MoveBaseGoal goal;
                    goal.target_pose.header.frame_id = "map";
                    goal.target_pose.header.stamp = ros::Time::now();
                    goal.target_pose.pose = srvName.response.pose;
                    ac.waitForServer();
                    ac.sendGoal(goal);
                    ac.waitForResult();
                    while(ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
                    {
                        ac.waitForServer();
                        ac.sendGoal(goal);
                        ac.waitForResult();
                    }
                }
            }
        }
        ros::spinOnce();//ros消息回调处理函数，即就是，每次运行到这里都要进行对订阅的话题中的消息进行回调
        r.sleep();
    }

    return 0;
}

#! /usr/bin/python
# -*- coding: UTF-8 -*-


import rospy
import tf2_ros
from wpb_home_behaviors.msg import Coord
from std_srvs.srv import SetBool
from tf2_geometry_msgs import PointStamped
from move_base_msgs.msg import MoveBaseGoal
from math import sqrt, cos, sin, atan2, pi


flg = [False, False]
consummer = [None, None]
delta_dist = 0.5
camera_robot = [0, 0]
tag = False

def trans(pose):
    x, y = pose.z[0]+camera_robot[0], -pose.x[0]+camera_robot[1]
    theta = atan2(y, x)
    tho = sqrt(x**2+y**2)
    tho1 = tho-delta_dist
    x1, y1 = get_map_pose(tho1*cos(theta), tho1*sin(theta))
    x0, y0 = get_map_pose(0, 0)
    theta1 = atan2(y1-y0, x1-x0)
    goal = MoveBaseGoal()
    goal.target_pose.header.frame_id = "map"
    goal.target_pose.pose.position.x = x1
    goal.target_pose.pose.position.y = y1
    goal.target_pose.pose.orientation.w = cos(theta1/2)
    goal.target_pose.pose.orientation.z = sin(theta1/2)
    return goal


def get_map_pose(x, y):
    ps = PointStamped()
    ps.header.frame_id = "base_footprint"
    ps.point.x = x
    ps.point.y = y
    ps.header.stamp = rospy.Time.now()
    ps_new = tfBuffer.transform(ps, "map", rospy.Duration(1))
    return ps_new.point.x, ps_new.point.y


def dis(p1, p2):
    return sqrt((p1[0]-p2[0])**2+(p1[1]-p2[1])**2)


def trans1(pose):
    global flg, consummer
    if flg[0] is False:
        flg[0] = True
        consummer[0] = trans(pose)
        rospy.logdebug("person1:"+str(consummer[0]))
    if flg[1] is True:
        face_detection_client(False)


def trans2(pose):
    global flg, consummer
    if flg[1] is False:
        flg[1] = True
        consummer[1] = trans(pose)
        rospy.logdebug("person2:"+str(consummer[1]))
    if flg[0] is True:
        face_detection_client(False)


def pub(info):
    if flg[0] is True and flg[1] is True:
        consummer[0].target_pose.header.stamp = consummer[1].target_pose.header.stamp = rospy.Time.now()
        pub1.publish(consummer[0])
        pub2.publish(consummer[1])


if __name__ == '__main__':
    rospy.init_node("trans_pub", anonymous=True)
    face_detection_client = rospy.ServiceProxy('human_detection/face_detection_switch', SetBool)
    rospy.wait_for_service('human_detection/face_detection_switch')
    rospy.Subscriber("/Consummer1", Coord, trans1, queue_size=1)
    rospy.Subscriber("/Consummer2", Coord, trans2, queue_size=1)
    pub1 = rospy.Publisher("/person/waypoint1", MoveBaseGoal, queue_size=1)
    pub2 = rospy.Publisher("/person/waypoint2", MoveBaseGoal, queue_size=1)
    tfBuffer = tf2_ros.Buffer()
    tfSub = tf2_ros.TransformListener(tfBuffer)
    rospy.Subscriber("/send_pose", Coord, pub, queue_size=1)
    rospy.spin()
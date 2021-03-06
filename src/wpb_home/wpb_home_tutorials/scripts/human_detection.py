#! /home/zzy/anaconda3/envs/ros/bin/python
# -*- coding: UTF-8 -*-



import rospy
import message_filters
import cv2
import cv_bridge
import time
import mediapipe as mp
from sensor_msgs.msg import Image, CameraInfo
from wpb_home_behaviors.msg import Coord
from math import tan, pi, sqrt, atan
from std_srvs.srv import SetBool, SetBoolRequest, SetBoolResponse
from libyolo import YoloV5s
from geometry_msgs.msg import Twist
import numpy as np

'''
镜头相关参数
图像：
*----------> x(u_img)
|
|
|     *(p_x,p_y)
|
|
y(v_img)
真实：
Y(v_img)
^               Z 
|             *
|          *
|       *
|    *
| *
*--------------> X(-u_img)
'''
INIT_FLAG = False
W_img = 960 # 图像宽度
H_img = 540 # 图像高度
P_x = W_img//2-1 # 图像中心点x坐标
P_y = H_img//2-1 # 图像中心点y坐标
f_x = 540.68603515625
f_y = 540.68603515625
eps = 1e-5 # 极小正数
'''
MediaPipe模型
'''
Pose = mp.solutions.pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.7)
FaceDetection = mp.solutions.face_detection.FaceDetection(min_detection_confidence=0.5)
'''
检测相关参数
'''
DETECT_POSE = True
DETECT_FACE = False
LOST_FLAG = True # 跟随目标丢失标志
LOST_TIME = -1 # 跟随丢失计时器
LOST_TIME_DELTA = 0.5 # 丢失判定延时，单位：秒（s）
HISTORY_DIRECTION = 1 # -1:左 1:右 
'''
OpenCV相关参数
'''
_cv_bridge = cv_bridge.CvBridge()

'''
跟随相关参数
'''
FOLLOW_DIST = 0.5 # 跟随距离，单位：米（m）
MAX_LINEAR = 0.5
MAX_ANGULAR = 1.5
LINEAR_RATE = 0.4
ANGLE_RATE = 0.7 # 真实旋转速度比例
ANGLE_SPEED = 30/ANGLE_RATE # 原地旋转速度，单位：度每秒（角度/s）
BLACK_LOWER = np.array([0, 0, 0])
BLACK_UPPER = np.array([50, 50, 50])
JUDGE_CONFIDENCE = 0.8
JUDGE_D = 25
TARGET_FLAG = False
'''
yolo相关参数
'''
yolo = YoloV5s(weight_path=None)
FIND_TIME = -1
FIND_TIME_DELTA = 1


def InitCamera(camera_info):
    global INIT_FLAG, P_x, P_y, f_x, f_y
    if INIT_FLAG is True:
        return
    f_x = camera_info.K[0]
    P_x = camera_info.K[2]
    f_y = camera_info.K[4]
    P_y = camera_info.K[5]



'''
由镜头内参加距离信息计算出人在真实空间中相对镜头的坐标
'''
def real_pose(u_img, v_img, d):
    Z = d/sqrt(1+(u_img-P_x)**2/f_x**2+(v_img-P_y)**2/f_y**2)
    X = (u_img-P_x)*Z/f_x
    Y = (v_img-P_y)*Z/f_y
    return X/1000, Y/1000, Z/1000


def adjust(x, lim):
    if x < 0:
        return 0
    if x >= lim:
        return lim-1
    return x


def get_rect(u_img, v_img, d):
    u1 = adjust(u_img-d, W_img)
    u2 = adjust(u_img+d, W_img)
    v1 = adjust(v_img-d, H_img)
    v2 = adjust(v_img+d, H_img)
    return u1, u2, v1, v2


'''
从MediaPipe获取到的关键点中提取出人物的中心点的像素坐标
Input: landmarks
Output: u_img, v_img

MediaPipe关键点对应信息
0-10 -> head
12 11 --> body-up
24 23 --> body-down
'''
def pixel_pose(landmarks):
    u_img = W_img*(landmarks[11].x+landmarks[12].x+landmarks[23].x+landmarks[24].x)//4
    v_img = H_img*(landmarks[11].y+landmarks[12].y+landmarks[23].y+landmarks[24].y)//4
    if u_img < 0:
        u_img = 0
    elif u_img >= W_img:
        u_img = W_img-1
    if v_img < 0:
        v_img = 0
    elif v_img >= H_img:
        v_img = H_img-1
    return int(u_img), int(v_img)


def human_pixel_pose(person_box):
    u_img = W_img*person_box[0]
    v_img = H_img*person_box[1]
    if u_img < 0:
        u_img = 0
    elif u_img >= W_img:
        u_img = W_img-1
    if v_img < 0:
        v = 0
    elif v_img >= H_img:
        v_img = H_img-1
    return int(u_img), int(v_img)


def follow_pub(pose):
    if pose.z[0] > 0:
        human_x = pose.z[0]
        human_y = -pose.x[0]
        angle = atan(human_y/human_x)
        vel_cmd = Twist()
        flw_dist = sqrt(human_x**2 + human_y**2)
        diff_dist = flw_dist-FOLLOW_DIST
        vel_cmd.linear.x = diff_dist*LINEAR_RATE
        vel_cmd.angular.z = angle*ANGLE_RATE
        if vel_cmd.linear.x < 0:
            vel_cmd.linear.x *= 0.5
        if vel_cmd.linear.x < -MAX_LINEAR:
            vel_cmd.linear.x = -MAX_LINEAR
        if vel_cmd.linear.x > MAX_LINEAR:
            vel_cmd.linear.x = MAX_LINEAR
        if vel_cmd.angular.z < -MAX_ANGULAR:
            vel_cmd.angular.z = -MAX_ANGULAR
        if vel_cmd.angular.z > MAX_ANGULAR:
            vel_cmd.angular.z = MAX_ANGULAR
        vel_pub.publish(vel_cmd)


def rotate(angle):
    vel_cmd = Twist()
    vel_cmd.angular.z = -angle*pi/180
    vel_pub.publish(vel_cmd)


def stop():
    vel_cmd = Twist()
    vel_cmd.linear.x = 0
    vel_cmd.linear.y = 0
    vel_cmd.linear.z = 0
    vel_cmd.angular.x = 0
    vel_cmd.angular.y = 0
    vel_cmd.angular.z = 0
    vel_pub.publish(vel_cmd)


'''
图像回调函数

[wpb_home_behaviors/Coord]:
string[] name
float64[] x
float64[] y
float64[] z
float64[] probability
'''
def image_cb(image_rgb, image_depth):
    global LOST_FLAG, LOST_TIME, HISTORY_DIRECTION, FIND_TIME, TARGET_FLAG

    # ros image 转为 cv image
    image = _cv_bridge.imgmsg_to_cv2(image_rgb, desired_encoding='passthrough')
    depth = _cv_bridge.imgmsg_to_cv2(image_depth, desired_encoding='passthrough')

    u_img, v_img = 0, 0
    if DETECT_POSE:
        X, Y, Z = 0, 0, 0
        # MediaPipe Pose 识别图像中任人物关键点
        image.flags.writeable = False
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        results = Pose.process(image)
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        # 最终发布的follw目标信息
        pose_msg = Coord()
        pose_msg.name = 'follow_target'
        # 
        status_info = ""
        # 从landmark中提取关键点
        if results.pose_landmarks is not None: # 在画面中找到人物
            # 当前帧没有丢失，则重置丢失标记为False
            if LOST_FLAG is True:
                LOST_FLAG = False
            u_img, v_img = pixel_pose(results.pose_landmarks.landmark)
            # 检测出人物信息，但由于深度信息在图像边缘丢失，使得无法计算准确位置
            # 这种情况下，不认为目标丢失。
            # 机器人原地朝目标方向以ANGLE_SPPED速度转动，直至获取到深度信息
            if depth[v_img][u_img]/1000 > eps:
                u1, u2, v1, v2 = get_rect(u_img, v_img, JUDGE_D)
                cnt = 0
                for i in range(u1, u2+1):
                    for j in range(v1, v2+1):
                        dcnt = 1
                        for k in range(3):
                            if image[j][i][k] < BLACK_LOWER[k] or image[j][i][k] > BLACK_UPPER[k]:
                                dcnt = 0
                                break
                        cnt += dcnt
                if cnt/((u2-u1)*(v2-v1)) > JUDGE_CONFIDENCE:
                    TARGET_FLAG = False
                    X, Y, Z = real_pose(u_img, v_img, depth[v_img][u_img])
                    HISTORY_DIRECTION = -1 if u_img < P_x else 1
                    status_info = "[FOUND]: Follow"
                    pose_msg.x, pose_msg.y, pose_msg.z = [X], [Y], [Z]
                    follow_pub(pose_msg)
                else:
                    TARGET_FLAG = True
                    rotate(30)
                    status_info = "[LOST]: Search"
            else:
                if 100 < u_img < W_img-100:
                    # X, Y, Z = 0, 0, FOLLOW_DIST
                    stop()
                    status_info = "[LOST]: Too close, waiting"
                else:
                    rotate(HISTORY_DIRECTION*30)
                    # X, Y, Z = HISTORY_DIRECTION*FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                    status_info = "[FOUND]: Lost depth, searching"
                HISTORY_DIRECTION = -1 if u_img < P_x else 1
            cv2.circle(image, (u_img, v_img), 10, (0, 0, 255), -1)
        else: # 当前帧人物丢失
            # 跟随距离为FOLLOW_DIST，若人物太近导致部分部分肢体在图像外而无法被MediaPipe识别出关键点
            # 认为人物在水平方向（X方向）上居中，并取图像中心点离镜头的距离当作间距
            # 有如下情况：
            # >= FOLLOW_DIST 认为丢失
            # < FOLLOW_DIST 不认为丢失，机器人保持不动
            # min_d = depth[P_y][P_x]
            # for i in range(-100, 100):
            #     min_d = min(min_d, depth[P_y][P_x+i])
            # if min_d/1000 > FOLLOW_DIST: # 认为丢失
            #     # 避免因个别帧为能准确识别导致的丢失
            #     # 采用丢失计时器
            #     # 在0.5s内的所有帧都丢失才认为丢失
            #     if LOST_FLAG is False:HISTORY_DIRECTION
            #         LOST_FLAG = True
            #         LOST_TIME = time.time()
            #         X, Y, Z = 0, 0, FOLLOW_DIST
            #         status_info = "[LOST]: Judge"
            #     else:
            #         if time.time()-LOST_TIME < LOST_TIME_DELTA: # 在判定延时内保持机器人位置不变
            #             X, Y, Z = 0, 0, FOLLOW_DIST
            #             status_info = "[LOST]: Judge"
            #         else: # 超过判定延时，认为人物丢失，开始向人物最后一次被检测到的方向按ANGLE_SPPED速度原地转动搜寻
            #             X, Y, Z = HISTORY_DIRECTION*FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
            #             status_info = "[LOST]: Search"
            # else: # < FOLLOW_DIST 不认为丢失，机器人保持不动
            #     X, Y, Z = 0, 0, FOLLOW_DIST
            #     status_info = "[LOST]: Too close, waiting"
            if TARGET_FLAG is True:
                rotate(30)
                status_info = "[LOST]: Search"
            elif LOST_FLAG is False:
                    LOST_FLAG = True
                    LOST_TIME = time.time()
                    # X, Y, Z = 0, 0, FOLLOW_DIST
                    stop()
                    status_info = "[LOST]: Judge"
            else:
                if time.time()-LOST_TIME < LOST_TIME_DELTA: # 在判定result.detections[0].relative_bounding_box延时内保持机器人位置不变
                    # X, Y, Z = 0, 0, FOLLOW_DIST
                    stop()
                    status_info = "[LOST]: Judge"
                else: # 超过判定延时，认为人物丢失，开始向人物最后一次被检测到的方向按ANGLE_SPPED速度原地转动搜寻
                    # X, Y, Z = HISTORY_DIRECTION*FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                    rotate(HISTORY_DIRECTION*30)
                    status_info = "[LOST]: Search"    
        # pose_pub.publish(pose_msg) # 发布人物空间位置信息
        cv2.putText(image, status_info, (0, H_img-1), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5) # 识别状态信息
        cv2.putText(image, ("X=%.2f Y=%.2f Z=%.2f" % (X, Y, Z)), (0, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5) # 人物空间位置信息
        image_pub.publish(_cv_bridge.cv2_to_imgmsg(image)) # 发布实时跟随图像信息
    if DETECT_FACE:
        # YoloV5 识别图像中人键点
        results = yolo.inference(img=image, if_show=False, if_absolute=True)
        # 当前图像中没找到符合条件的志愿者时，调用follow来发布cmd_vel信息，原地转圈寻找志愿者
        pose_msg = Coord()
        pose_msg.name = 'find_consumers'
        status_info = ""
        if 'person' in results:
            persons = []
            for person in results['person']:
                if person[4] > 0.6:
                    persons.append(person)
            # rospy.logerr(str(results['person']))
            if len(persons) == 2:
                status_info = "FOUND 2"
                u_img_1, v_img_1 = human_pixel_pose(persons[0])
                u_img_2, v_img_2 = human_pixel_pose(persons[1])
                mid_u = (u_img_1+u_img_2)//2
                if depth[v_img_1][u_img_1] > eps and depth[v_img_2][u_img_2] > eps:
                    X1, Y1, Z1 = real_pose(u_img_1, v_img_1, depth[v_img_1][u_img_1])
                    X2, Y2, Z2 = real_pose(u_img_2, v_img_2, depth[v_img_2][u_img_2])
                    if FIND_TIME < 0:
                        FIND_TIME = time.time()
                        if mid_u < P_x-100:
                            rotate(-30)
                        elif mid_u > P_x+100:
                            rotate(30)
                        else:
                            stop()
                    elif time.time()-FIND_TIME > FIND_TIME_DELTA:
                        stop()
                        cv2.putText(image, ("p1"), (u_img_1, v_img_1), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5)
                        cv2.putText(image, ("p2"), (u_img_2, v_img_2), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5)
                        image_pub.publish(_cv_bridge.cv2_to_imgmsg(image)) # 发布实时跟随图像信息
                        # rospy.sleep(3)
                        consumemr_pub1.publish(Coord('consummer1', [X1], [Y1], [Z1], [persons[0][4]]))
                        consumemr_pub2.publish(Coord('consummer2', [X2], [Y2], [Z2], [persons[1][4]]))
                    else:
                        if mid_u < P_x-100:
                            rotate(-30)
                        elif mid_u > P_x+100:
                            rotate(30)
                        else:
                            stop()
                    status_info = "FOUND 2"
                else:
                    status_info = "FOUND 2, LOST DEPTH"
                    if mid_u < P_x:
                        # X, Y, Z = -FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                        rotate(-30)
                    else:
                        rotate(30)
                        # X, Y, Z = FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                    # pose_msg.x, pose_msg.y, pose_msg.z = [X], [Y], [Z]
                    # pose_pub.publish(pose_msg) # 发布人物空间位置信息
                    FIND_TIME = -1
                cv2.circle(image, (u_img_1, v_img_1), 10, (0, 0, 255), -1)
                cv2.circle(image, (u_img_2, v_img_2), 10, (0, 0, 255), -1)
            elif len(persons) > 2:
                for pose in persons:
                    u_img, v_img = human_pixel_pose(pose)
                    cv2.circle(image, (u_img, v_img), 10, (0, 0, 255), -1)
                # pose_msg.x, pose_msg.y, pose_msg.z = [FOLLOW_DIST/tan(ANGLE_SPEED*pi/180)], [0], [FOLLOW_DIST]
                # pose_pub.publish(pose_msg) # 发布人物空间位置信息
                rotate(30)
                status_info = "OVER 2"
                FIND_TIME = -1
            elif len(persons) == 1:
                # 找到一个人，向这个人所在边方向寻找另一个
                u_img, v_img = human_pixel_pose(persons[0])
                # if u_img < P_x:
                #     # X, Y, Z = -FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                #     rotate(-30)
                # else:
                #     rotate(30)
                rotate(30)
                    # X, Y, Z = FOLLOW_DIST/tan(ANGLE_SPEED*pi/180), 0, FOLLOW_DIST
                # pose_msg.x, pose_msg.y, pose_msg.z = [X], [Y], [Z]
                # pose_pub.publish(pose_msg) # 发布人物空间位置信息
                cv2.circle(image, (u_img, v_img), 10, (0, 0, 255), -1)
                tx, ty, tz = real_pose(u_img,v_img, depth[v_img][u_img])
                cv2.putText(image, ("X=%.2f Y=%.2f Z=%.2f" % (tx, ty, tz)), (0, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5) # 人物空间位置信息
                status_info = "FOUND 1"
                FIND_TIME = -1
                # consumemr_pub1.publish(Coord('consummer1', [tx], [ty], [tz], [results['person'][0][4]]))
            else:
                status_info = "SEARCH"
                rotate(30)
                FIND_TIME = -1
        else:
            # 一个人也没有，则旋转寻找
            status_info = "SEARCH"
            # pose_msg.x, pose_msg.y, pose_msg.z = [FOLLOW_DIST/tan(ANGLE_SPEED*pi/180)], [0], [FOLLOW_DIST]
            # pose_pub.publish(pose_msg) # 发布人物空间位置信息
            rotate(30)
            FIND_TIME = -1
        cv2.putText(image, status_info, (0, H_img-1), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 0, 255), 5) # 识别状态信息
        image_pub.publish(_cv_bridge.cv2_to_imgmsg(image)) # 发布实时跟随图像信息
    if DETECT_POSE is False and DETECT_POSE is False:
        image_pub.publish(_cv_bridge.cv2_to_imgmsg(image)) # 发布实时跟随图像信息
        activate_pub.publish(Coord())

'''
std_srvs/SetBool
------------------
bool data
---
bool success
string message
'''
def switch_face_detection(request):
    global DETECT_FACE, DETECT_POSE
    res = SetBoolResponse()
    try:
        if request.data:
            DETECT_POSE = False
            stop()
            rospy.sleep(3)
            DETECT_FACE = True
        else:
            DETECT_FACE = False
            stop()
            rospy.logdebug("send stop")
        res.success = True
    except Exception as e:
        res.success = False
        res.message = e
    return res


if __name__ == '__main__':
    rospy.init_node('human_detection', anonymous=True)
    # 相机参数
    camera_sub = rospy.Subscriber("/kinect2/qhd/camera_info", CameraInfo, InitCamera)
    # rgb图和深度图对应
    rgb_sub = message_filters.Subscriber("/kinect2/qhd/image_color", Image)
    depth_sub = message_filters.Subscriber("/kinect2/qhd/image_depth_rect", Image)
    ts = message_filters.TimeSynchronizer([rgb_sub, depth_sub], 10)
    ts.registerCallback(image_cb)
    # 最终follow信息的发布
    pose_pub = rospy.Publisher('/Human_pose', Coord, queue_size=1)
    # 带关键点的follow图像的发布
    image_pub = rospy.Publisher('/Follow_image', Image, queue_size=1)
    # 人脸识别开关
    face_detection_srv = rospy.Service('human_detection/face_detection_switch', SetBool, switch_face_detection)
    # 人脸测试
    # rospy.wait_for_service('human_detection/face_detection_switch')
    # face_detection_client = rospy.ServiceProxy('human_detection/face_detection_switch', SetBool)
    # res = face_detection_client(True)
    consumemr_pub1 = rospy.Publisher("/Consummer1", Coord, queue_size=1)
    consumemr_pub2 = rospy.Publisher("/Consummer2", Coord, queue_size=1)
    activate_pub = rospy.Publisher("/send_pose", Coord, queue_size=1)
    vel_pub = rospy.Publisher("/cmd_vel", Twist, queue_size=10)
    rospy.spin()